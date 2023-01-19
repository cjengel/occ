/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/occ_405/mem/dimm.c $                                      */
/*                                                                        */
/* OpenPOWER OnChipController Project                                     */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2011,2023                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

//#define DIMM_DEBUG

#include <ssx.h>
#include <occhw_async.h>
#include <dimm_structs.h>

#include <trac_interface.h>
#include <trac.h>
#include <occ_common.h>
#include <comp_ids.h>
#include <occ_service_codes.h>
#include <memory.h>
#include <dimm_service_codes.h>
#include <state.h>
#include <occ_sys_config.h>
#include "sensor.h"
#include "amec_sys.h"
#include "lock.h"
#include "common.h"
#include "amec_health.h"
#include "i2c.h"

extern bool G_mem_monitoring_allowed;
extern memory_control_task_t G_memory_control_task;

extern data_cnfg_t * G_data_cnfg;

uint64_t G_inject_dimm = 0;
uint32_t G_inject_dimm_trace[MAX_NUM_OCMBS][MAX_NUM_I2C_DIMMS_PER_OCMB] = {{0}};

uint8_t G_dimm_state = DIMM_STATE_INIT;     // Curret state of DIMM state machine
// G_maxDimmPort is the maximum I2C port number
uint8_t G_maxDimmPort = 0;

bool     G_dimm_i2c_reset_required = false;
uint32_t G_dimm_i2c_reset_cause = 0;

// # consecutive errors for this DIMM
uint8_t G_dimm_errorCount[MAX_NUM_OCMBS][MAX_NUM_I2C_DIMMS_PER_OCMB] = {{0}};

// If still no i2c interrupt after MAX_TICK_COUNT_WAIT, then try next operation anyway
#define MAX_TICK_COUNT_WAIT 2

// used for tracing
#define OCMB_AND_DIMM ((G_dimm_sm_args.ocmb<<8) | G_dimm_sm_args.dimm)
#define DIMM_INDEX(ocmb,dimm) ((ocmb*MAX_NUM_I2C_DIMMS_PER_OCMB)+dimm)

// GPE Requests
GpeRequest G_dimm_sm_request;

// GPE arguments
GPE_BUFFER(dimm_sm_args_t  G_dimm_sm_args);


// Read OCC_MISC register to see if an I2C interrupt was generated for
// the specified engine.
bool check_for_i2c_interrupt(const uint8_t i_engine)
{
    bool l_interruptTriggered = false;
    ocb_occmisc_t occmisc;
    occmisc.value = in32(OCB_OCCMISC);

    // I2CM_INTR_STATUS has a one bit status for each engine: C, D, and E
    if (PIB_I2C_ENGINE_E == i_engine)
    {
        // Engine E
        l_interruptTriggered = occmisc.fields.i2cm_intr_status & 0x01;
    }
    else if (PIB_I2C_ENGINE_D == i_engine)
    {
        // Engine D
        l_interruptTriggered = occmisc.fields.i2cm_intr_status & 0x02;
    }
    else if (PIB_I2C_ENGINE_C == i_engine)
    {
        // Engine C
        l_interruptTriggered = occmisc.fields.i2cm_intr_status & 0x04;
    }
    else
    {
        // Invalid engine
        DIMM_DBG("check_for_i2c_interrupt: invalid engine 0x%02X", i_engine);
    }

    if (!l_interruptTriggered)
    {
        DIMM_DBG("check_for_i2c_interrupt: no interrupt for engine 0x%02X (tick=%d)", i_engine, DIMM_TICK);
    }
    else
    {
        DIMM_DBG("check_for_i2c_interrupt: got interrupt for engine 0x%02X (tick=%d)", i_engine, DIMM_TICK);
    }

    return l_interruptTriggered;

} // end check_for_i2c_interrupt()


// Create DIMM state machine IPC request
void memory_i2c_init()
{
    errlHndl_t l_err = NULL;    // Error handler
    int rc_dimm_sm = 0; // rcs from gpe ipc request creation commands

    do
    {
        // Initializes GPE request for DIMM I2C temperature reading IPC Task,
        DIMM_DBG("memory_i2c_init: Creating request GPE1 DIMM data IPC task");
        rc_dimm_sm = gpe_request_create(
                                        &G_dimm_sm_request,              // gpe_req for the task
                                        &G_async_gpe_queue1,             // queue
                                        IPC_ST_DIMM_SM_FUNCID,           // Function ID
                                        &G_dimm_sm_args,                 // parm for the task
                                        SSX_WAIT_FOREVER,                // no timeout
                                        NULL,                            // callback
                                        NULL,                            // callback arg
                                        ASYNC_CALLBACK_IMMEDIATE);       // options
        if(rc_dimm_sm)
        {
            TRAC_ERR("memory_i2c_init: Failed to initialize dimm state"
                     " machine IPC task [rc_dimm_sm=0x%x]",
                     rc_dimm_sm);
            break;
        }
    }
    while(0);


    if(rc_dimm_sm)
    {
        /* @
         * @errortype
         * @moduleid    DIMM_MID_NIMBUS_INIT
         * @reasoncode  SSX_GENERIC_FAILURE
         * @userdata1   l_rc_gpe  - Return code of failing function
         * @userdata2   0
         * @userdata4   OCC_NO_EXTENDED_RC
         * @devdesc     Failed to initialize GPE1 DIMM IPC job
         */
        l_err = createErrl(
                           DIMM_MID_NIMBUS_INIT,                       //modId
                           SSX_GENERIC_FAILURE,                        //reasoncode
                           OCC_NO_EXTENDED_RC,                         //Extended reason code
                           ERRL_SEV_PREDICTIVE,                        //Severity
                           NULL,                                       //Trace Buf
                           DEFAULT_TRACE_SIZE,                         //Trace Size
                           rc_dimm_sm,                                 //userdata1
                           0                                           //userdata2
                          );

        REQUEST_RESET(l_err);
    }

}


// Scan all of the DIMM temps and keep track of the hottest
void update_hottest_dimm()
{
    // Find/save the hottest DIMM temperature for the last set of readings
    uint8_t hottest = 0;
    int ocmbIndex, dIndex;
    for (ocmbIndex = 0; ocmbIndex < MAX_NUM_OCMBS; ++ocmbIndex)
    {
        for (dIndex = 0; dIndex < MAX_NUM_I2C_DIMMS_PER_OCMB; ++dIndex)
        {
            if(g_amec->proc[0].memctl[ocmbIndex].membuf.dimm_temps[dIndex].cur_temp > hottest)
            {
                hottest = g_amec->proc[0].memctl[ocmbIndex].membuf.dimm_temps[dIndex].cur_temp;
            }
        }
    }

    // Store the hottest DIMM temp sensor
    if(hottest)
        sensor_update(AMECSENSOR_PTR(TEMPDIMMTHRM), (uint16_t)hottest);
}


// Update current I2C ocmb/DIMM index to next potential DIMM
void use_next_dimm(uint8_t * i_ocmb, uint8_t * i_dimm)
{
    if (++*i_dimm == MAX_NUM_I2C_DIMMS_PER_OCMB)
    {
        // Finished all DIMMs for current OCMB, move to next OCMB
        *i_dimm = 0;
        if (++*i_ocmb == MAX_NUM_OCMBS)
            *i_ocmb = 0;
    }

    // Check if we are starting a new set of readings and if so, update hottest DIMM
    if ((*i_ocmb == 0) && (*i_dimm == 0))
    {
        update_hottest_dimm();
    }
}


// Called after a failure to read a DIMM temperature.  The error will
// be counted and if threshold is reached, and error will be created with
// the DIMM as a callout and then set flag to trigger I2C reset
void mark_dimm_failed()
{
    const uint8_t port = G_dimm_sm_args.i2cPort;
    const uint8_t dimm = G_dimm_sm_args.dimm;
    const uint8_t ocmb = G_dimm_sm_args.ocmb;

    // Trace the first 3 consecutive failures for this DIMM
    if (G_dimm_errorCount[ocmb][dimm] < 3)
    {
        INTR_TRAC_ERR("mark_dimm_failed: DIMM%04X failed in state/rc/count=0x%06X "
                      "(ffdc 0x%08X%08X, completion_state 0x%02X)",
                      OCMB_AND_DIMM, (G_dimm_sm_args.state << 16) | (G_dimm_sm_args.error.rc << 8) | G_dimm_errorCount[ocmb][dimm],
                      WORD_HIGH(G_dimm_sm_args.error.ffdc),
                      WORD_LOW(G_dimm_sm_args.error.ffdc),
                      G_dimm_sm_request.request.completion_state);
    }

    g_amec->proc[0].memctl[ocmb].membuf.dimm_temps[dimm].flags |= FRU_SENSOR_STATUS_ERROR;

    if (G_dimm_errorCount[ocmb][dimm] < 255)
    {
        ++G_dimm_errorCount[ocmb][dimm];
    }

    // Reset DIMM I2C engine
    G_dimm_i2c_reset_required = true;
    G_dimm_i2c_reset_cause = port<<24 | dimm<<16 | (G_dimm_sm_args.error.rc & 0xFFFF);
    G_dimm_state = DIMM_STATE_RESET_MASTER;

} // end mark_dimm_failed()


// Schedule a GPE request for the specified DIMM state
bool schedule_dimm_req(uint8_t i_state, dimm_sm_args_t i_new_args)
{
    bool l_scheduled = false;
    bool scheduleRequest = true;

    DIMM_DBG("schedule_dimm_req called with state 0x%02X (tick=%d)", i_state, DIMM_TICK);

    if (!async_request_is_idle(&G_dimm_sm_request.request))
    {
        INTR_TRAC_INFO("E>schedule_dimm_req: request not idle when scheduling 0x%02X (tick=%d) (prior state 0x%02X / DIMM%04X)",
                       i_state, DIMM_TICK, G_dimm_sm_args.state, OCMB_AND_DIMM);
    }
    else
    {
        DIMM_DBG("schedule_dimm_req: scheduling 0x%02X (tick=%d) (prior state 0x%02X / DIMM%04X)",
                 i_state, DIMM_TICK, G_dimm_sm_args.state, OCMB_AND_DIMM);
        G_dimm_sm_args = i_new_args;
        switch(i_state)
        {
            // Init
            case DIMM_STATE_INIT:
                break;

                // Read DIMM temp
            case DIMM_STATE_WRITE_MODE:
            case DIMM_STATE_WRITE_ADDR:
            case DIMM_STATE_INITIATE_READ:
            case DIMM_STATE_READ_TEMP:
                break;

                // I2C reset
            case DIMM_STATE_RESET_MASTER:
            case DIMM_STATE_RESET_SLAVE_PORT:
            case DIMM_STATE_RESET_SLAVE_PORT_COMPLETE:
                break;

            default:
                INTR_TRAC_ERR("schedule_dimm_req: Invalid state (0x%02X)", i_state);
                errlHndl_t err = NULL;
                /*
                 * @errortype
                 * @moduleid    DIMM_MID_DIMM_SM
                 * @reasoncode  DIMM_INVALID_STATE
                 * @userdata1   DIMM state
                 * @userdata2   0
                 * @devdesc     Invalid DIMM I2C state requested
                 */
                err = createErrl(DIMM_MID_DIMM_SM,
                                 DIMM_INVALID_STATE,
                                 OCC_NO_EXTENDED_RC,
                                 ERRL_SEV_PREDICTIVE,
                                 NULL,
                                 DEFAULT_TRACE_SIZE,
                                 i_state,
                                 0);
                // Request reset since this should never happen.
                REQUEST_RESET(err);
                scheduleRequest = false;
                break;
        }

        if (scheduleRequest)
        {
            // Clear errors and init common arguments for GPE
            G_dimm_sm_args.error.error = 0;
            G_dimm_sm_args.state = i_state;

            DIMM_DBG("schedule_dimm_req: Scheduling GPE1 DIMM I2C state 0x%02X (tick %d)", i_state, DIMM_TICK);
            int l_rc = gpe_request_schedule(&G_dimm_sm_request);
            if (0 == l_rc)
            {
                l_scheduled = true;
            }
            else
            {
                errlHndl_t l_err = NULL;
                INTR_TRAC_ERR("schedule_dimm_req: schedule failed w/rc=0x%08X (%d us)",
                              l_rc, (int) ((ssx_timebase_get())/(SSX_TIMEBASE_FREQUENCY_HZ/1000000)));
                /*
                 * @errortype
                 * @moduleid    DIMM_MID_DIMM_SM
                 * @reasoncode  SSX_GENERIC_FAILURE
                 * @userdata1   GPE shedule returned rc code
                 * @userdata2   state
                 * @devdesc     dimm_req schedule failed
                 */
                l_err = createErrl(DIMM_MID_DIMM_SM,
                                   SSX_GENERIC_FAILURE,
                                   ERC_DIMM_SCHEDULE_FAILURE,
                                   ERRL_SEV_PREDICTIVE,
                                   NULL,
                                   DEFAULT_TRACE_SIZE,
                                   l_rc,
                                   i_state);
                // Request reset since this should never happen.
                REQUEST_RESET(l_err);
            }
        }
    }

    return l_scheduled;

} // end schedule_dimm_req()


// Check if the last I2C operation completed, and force failure if not
bool check_for_i2c_failure()
{
    bool failed = false;

    // Check if I2C operation is complete
    if (ASYNC_REQUEST_STATE_COMPLETE == G_dimm_sm_request.request.completion_state)
    {
        // Check if I2C operation failed
        if ((GPE_RC_SUCCESS != G_dimm_sm_args.error.rc) &&
            (GPE_RC_NOT_COMPLETE != G_dimm_sm_args.error.rc))
        {
            failed = true;
            // Only mark DIMM as failed if not during an I2C reset
            if (false == G_dimm_i2c_reset_required)
            {
                mark_dimm_failed();
            }
        }
    }
    return failed;
}


// Handle the DIMM reset states
uint8_t dimm_reset_sm()
{
    uint8_t nextState = G_dimm_state;
    int ocmbIndex = 0;
    static uint8_t L_next_ocmb = 0;
    static dimm_sm_args_t L_new_dimm_args = {{{{0}}}};

    switch (G_dimm_state)
    {
        case DIMM_STATE_RESET_MASTER:
            if (DIMM_TICK == 0)
            {
                TRAC_INFO("dimm_reset_sm: Initiating I2C reset of engine %d", G_sysConfigData.dimm_i2c_engine);
                L_new_dimm_args.i2cEngine = G_sysConfigData.dimm_i2c_engine;
                if (schedule_dimm_req(DIMM_STATE_RESET_MASTER, L_new_dimm_args))
                {
                    nextState = DIMM_STATE_RESET_SLAVE_PORT;
                }
            }
            // else wait for tick 0
            break;

        case DIMM_STATE_RESET_SLAVE_PORT:
            for (ocmbIndex = L_next_ocmb; ocmbIndex < MAX_NUM_OCMBS; ++ocmbIndex)
            {
                if(G_dimm_enabled_sensors.bytes[ocmbIndex])
                    break;
            }
            if(ocmbIndex != MAX_NUM_OCMBS)
            {
                L_new_dimm_args.i2cPort = g_amec->proc[0].memctl[ocmbIndex].membuf.dimm_temps[0].i2c_port;
                if (schedule_dimm_req(DIMM_STATE_RESET_SLAVE_PORT, L_new_dimm_args))
                {
                    nextState = DIMM_STATE_RESET_SLAVE_PORT_WAIT;

                    // setup to reset next port when this port reset is complete
                    L_next_ocmb = ocmbIndex++;
                }
            }
            else // done resetting ports
            {
                L_next_ocmb = 0;
                nextState = DIMM_STATE_INIT;
                DIMM_DBG("dimm_reset_sm: I2C reset completed");
            }
            break;

        case DIMM_STATE_RESET_SLAVE_PORT_WAIT:
            // Delay to allow reset to complete
            DIMM_DBG("dimm_reset_sm: waiting during slave port %d reset", L_new_dimm_args.i2cPort);
            nextState = DIMM_STATE_RESET_SLAVE_PORT_COMPLETE;
            break;

        case DIMM_STATE_RESET_SLAVE_PORT_COMPLETE:
            if (schedule_dimm_req(DIMM_STATE_RESET_SLAVE_PORT_COMPLETE, L_new_dimm_args))
            {
                nextState = DIMM_STATE_RESET_SLAVE_PORT;
            }
            break;

        default:
            INTR_TRAC_ERR("dimm_reset_sm: INVALID STATE: 0x%02X when reset is required", G_dimm_state);
            nextState = DIMM_STATE_RESET_MASTER;
            break;
    }

    return nextState;

} // end dimm_reset_sm()



#ifdef DEBUG_LOCK_TESTING
// Simulate I2C locking behavior from the host
void host_i2c_lock_request();
void host_i2c_lock_release();
#define DURATION_EXTINT     2 // number of ticks before clearing external interrupt
#define DURATION_LOCK       6 // 80 // minimum ticks to keep lock
#define DURATION_LOCK_DELTA 5 // additional ticks to hold lock (for timing variation)
#define DURATION_UNLOCK    20 // 15 // number of ticks before host releases lock
void SIMULATE_HOST()
{
    static int lockDuration = DURATION_LOCK;     // Unlock when this gets to 0
    static int unlockDuration = DURATION_UNLOCK; // Request lock after this gets to 0
    static int extIntDuration = DURATION_EXTINT; // Release external interrupt when this gets to 0
    static int durationDelta = DURATION_LOCK_DELTA; // additional variability on how long lock is kept

#if 1
    // Force notifications (to ensure they are queued correctly
    static int newNotification = 45; // new notification every ticks
    if (--newNotification == 0)
    {
        ocb_occmisc_t current_occmisc0;
        current_occmisc0.value = in32(OCB_OCCMISC);
        TRAC_INFO("SIMULATE_HOST: forcing additional notifications (tmgt+tmgt+tmgt+shmem) currentInt=%d",
                  current_occmisc0.fields.core_ext_intr);
        notify_host(INTR_REASON_HTMGT_SERVICE_REQUIRED);
        //notify_host(INTR_REASON_I2C_OWNERSHIP_CHANGE);
        notify_host(INTR_REASON_HTMGT_SERVICE_REQUIRED);
        notify_host(INTR_REASON_HTMGT_SERVICE_REQUIRED);
        notify_host(INTR_REASON_OPAL_SHARED_MEM_CHANGE);
        newNotification = 20;
    }
#endif

    ocb_occflg_t occ_flags = {0};
    occ_flags.value = in32(OCB_OCCFLG);
    if (occ_flags.fields.i2c_engine3_lock_host == 1)
    {
        if (occ_flags.fields.i2c_engine3_lock_occ == 0)
        {
            // Host owns lock
            if (--lockDuration == 0)
            {
                host_i2c_lock_release();
                unlockDuration = DURATION_UNLOCK;
            }
        }
        else
        {
            // Host requested lock, but does not own it yet
        }
    }
    else
    {
        // Host has NOT requested lock yet
        if (--unlockDuration == 0)
        {
            // Request the lock
            host_i2c_lock_request();
            lockDuration = DURATION_LOCK + durationDelta;
            if (--durationDelta < 0)
            {
                durationDelta = DURATION_LOCK_DELTA;
            }
        }
    }

    // Handle clearing the external interrupt periodically
    ocb_occmisc_t current_occmisc;
    current_occmisc.value = in32(OCB_OCCMISC);
    if (current_occmisc.fields.core_ext_intr)
    {
        if (--extIntDuration == 0)
        {
            TRAC_INFO("SIMULATE_HOST: clearing ext_intr");
            current_occmisc.fields.core_ext_intr = 0;
            out32(OCB_OCCMISC,current_occmisc.value);
            extIntDuration = 2;
        }
    }
}
#endif // DEBUG_LOCK_TESTING



// Function Specification
//
// Name:  process_dimm_temp
//
// Description: Validate and store DIMM temperature
//
// End Function Specification
void process_dimm_temp()
{
    const uint8_t ocmb = G_dimm_sm_args.ocmb;
    const uint8_t dimm = G_dimm_sm_args.dimm;
    uint8_t l_dimm_temp = G_dimm_sm_args.temp;
    static bool L_ot_traced[MAX_NUM_OCMBS][MAX_NUM_I2C_DIMMS_PER_OCMB] = {{false}};

#define MIN_VALID_DIMM_TEMP 1
#define MAX_VALID_DIMM_TEMP 125 //according to Mike Pardiek
#define MAX_MEM_TEMP_CHANGE 16

    // Last DIMM read completed, update sensor and clear error count
    DIMM_DBG("process_dimm_temp: Successfully read DIMM%04X temperature: %dC, tick %d",
             OCMB_AND_DIMM, l_dimm_temp, DIMM_TICK);

    fru_temp_t* l_fru = &g_amec->proc[0].memctl[ocmb].membuf.dimm_temps[dimm];

    uint8_t l_prev_temp = l_fru->cur_temp;
    if (l_prev_temp == 0)
    {
        l_prev_temp = l_dimm_temp;
    }

    //make sure temperature is within a 'reasonable' range.
    if (l_dimm_temp < MIN_VALID_DIMM_TEMP ||
        l_dimm_temp > MAX_VALID_DIMM_TEMP)
    {
        //set a flag so that if we end up logging an error we have something to debug why
        l_fru->flags |= FRU_TEMP_OUT_OF_RANGE;
        l_dimm_temp = l_prev_temp;
    }
    else
    {
        //don't allow temp to change more than is reasonable
        if (l_dimm_temp > (l_prev_temp + MAX_MEM_TEMP_CHANGE))
        {
            if (!l_fru->flags)
            {
                TRAC_INFO("dimm temp rose faster than reasonable: DIMM%04X prev[%d] cur[%d]",
                          OCMB_AND_DIMM, l_prev_temp, l_dimm_temp);
                l_fru->flags |= FRU_TEMP_FAST_CHANGE;
            }
            l_dimm_temp = l_prev_temp + MAX_MEM_TEMP_CHANGE;
        }
        else if (l_dimm_temp < (l_prev_temp - MAX_MEM_TEMP_CHANGE))
        {
            if (!l_fru->flags)
            {
                TRAC_INFO("dimm temp fell faster than reasonable: DIMM%04X prev[%d] cur[%d]",
                          OCMB_AND_DIMM, l_prev_temp, l_dimm_temp);
                l_fru->flags |= FRU_TEMP_FAST_CHANGE;
            }
            l_dimm_temp = l_prev_temp - MAX_MEM_TEMP_CHANGE;
        }
        else //reasonable amount of change occurred
        {
            l_fru->flags &= ~FRU_TEMP_FAST_CHANGE;
        }

        //Notify thermal thread that temperature has been updated
        G_dimm_temp_updated_bitmap.bytes[ocmb] |= DIMM_SENSOR0 >> dimm;

        //clear other error flags
        l_fru->flags &= FRU_TEMP_FAST_CHANGE;
    }

    //Check if at or above the error temperature
    if (l_dimm_temp >= G_data_cnfg->thrm_thresh.data[DATA_FRU_DIMM].error)
    {
        //Set a bit so that this dimm can be called out by the thermal thread
        G_dimm_overtemp_bitmap.bytes[ocmb] |= (DIMM_SENSOR0 >> dimm);

        // trace first time OT per DIMM
        if( !L_ot_traced[ocmb][dimm] )
        {
           TRAC_ERR("process_dimm_temp: ocmb[%d] DIMM[%d] reached error temp[%d]. current[%d]",
                     ocmb,
                     dimm,
                     G_data_cnfg->thrm_thresh.data[DATA_FRU_DIMM].error,
                     l_dimm_temp);
           L_ot_traced[ocmb][dimm] = true;
        }
    }

    l_fru->cur_temp = l_dimm_temp;

    // Successful temp collected, reset error count
    if (G_dimm_errorCount[ocmb][dimm] > 2)
    {
        INTR_TRAC_INFO("process_dimm_temp: successfully read temp for DIMM%04X (after %d consecutive errors)",
                       OCMB_AND_DIMM, G_dimm_errorCount[ocmb][dimm]);
    }
    G_dimm_errorCount[ocmb][dimm] = 0;

} // end process_dimm_temp()


void disable_all_dimms()
{
    if (G_mem_monitoring_allowed)
    {
        TRAC_INFO("disable_all_dimms: DIMM temp collection is being stopped");
        G_mem_monitoring_allowed = false;
    }

    if (MEM_TYPE_OCM_DDR4_I2C == G_sysConfigData.mem_type)
    {
        occ_i2c_lock_release(G_dimm_sm_args.i2cEngine);
    }
}

// Function Specification
//
// Name:  task_dimm_sm
//
// Description: DIMM State Machine - Called every other tick to collect all of
//              the DIMM temperatures.
//
// Task Flags: RTL_FLAG_ACTIVE
//
// End Function Specification
void task_dimm_sm(struct task *i_self)
{
    int ocmbIndex = 0;
    errlHndl_t l_err = NULL;
    static uint8_t L_dimmIndex = 0x00;
    static uint8_t L_ocmb  = 0x00;
    static uint8_t L_notReadyCount = 0;
#define MAX_READ_ATTEMPT 3
    static uint8_t L_readAttempt = 0;
    static bool L_readIssued = false;
    const uint8_t engine = G_sysConfigData.dimm_i2c_engine;
    static bool L_occ_owns_lock = false;

    static unsigned int L_dimms_enabled = false;
    if (!L_dimms_enabled)
    {
        L_dimms_enabled = true;
        TRAC_INFO("task_dimm_sm: DIMM temp collection is being started (0x%08X)", (uint32_t)(G_dimm_configured_sensors.dw[0] >> 32));
        G_dimm_enabled_sensors = G_dimm_configured_sensors;
    }

    if (G_mem_monitoring_allowed)
    {
#ifdef DEBUG_LOCK_TESTING
        SIMULATE_HOST();
#endif
        // First handle any outstanding I2C reset
        if (G_dimm_i2c_reset_required)
        {
            if ((G_dimm_state != DIMM_STATE_RESET_MASTER) && (check_for_i2c_failure()))
            {
                // I2C failure occurred during a reset...
                INTR_TRAC_ERR("task_dimm_sm: Failure during I2C reset - memory monitoring disabled");
                // release I2C lock to the host for this engine and stop monitoring
                L_occ_owns_lock = false;
                disable_all_dimms();
            }
            else
            {
                if (G_dimm_state == DIMM_STATE_INIT)
                {
                    // Reset has completed successfully
                    TRAC_INFO("task_dimm_sm: I2C reset completed");
                    G_dimm_i2c_reset_required = false;
                    // Check if host needs I2C lock
                    L_occ_owns_lock = check_and_update_i2c_lock(engine);
                }
                else
                {
                    // Reset still in progress
                    G_dimm_state = dimm_reset_sm();
                }
            }
        }

        if (G_dimm_i2c_reset_required == false)
        {
            if ((L_occ_owns_lock == false) && ((DIMM_TICK == 0) || (DIMM_TICK == 8)))
            {
                // Check if host gave up the I2C lock
                L_occ_owns_lock = check_and_update_i2c_lock(engine);
                if (L_occ_owns_lock)
                {
                    // Start over at the INIT state after receiving the lock
                    G_dimm_state = DIMM_STATE_INIT;
                }
            }
            if (L_occ_owns_lock)
            {
                // Check for failure on prior operation
                if (check_for_i2c_failure())
                {
                    // If there was a failure, continue to the next DIMM (after I2c reset)
                    use_next_dimm(&L_ocmb, &L_dimmIndex);
                }
                uint8_t nextState = G_dimm_state;
                static dimm_sm_args_t L_new_dimm_args = {{{{0}}}};

                if (G_dimm_state == DIMM_STATE_INIT)
                {
                    // Setup I2C Interrupt Mask Register
                    DIMM_DBG("DIMM_STATE_INIT: (I2C Engine 0x%02X, Memory Type 0x%02X)",
                             engine, G_sysConfigData.mem_type);
                    L_new_dimm_args.i2cEngine = engine;
                    if (schedule_dimm_req(DIMM_STATE_INIT, L_new_dimm_args))
                    {
                        nextState = DIMM_STATE_WRITE_MODE;
                    }
                }
                else
                {
                    bool intTriggered = check_for_i2c_interrupt(engine);
                    if (intTriggered == false)
                    {
                        // Interrupt not generated, I2C operation may not have completed.
                        // After MAX_TICK_COUNT_WAIT, attempt operation anyway.
                        ++L_notReadyCount;
                    }

                    // Check if prior command completed (or timed out waiting for it)
                    if (intTriggered || (L_notReadyCount > MAX_TICK_COUNT_WAIT))
                    {
                        if (ASYNC_REQUEST_STATE_COMPLETE == G_dimm_sm_request.request.completion_state)
                        {
                            // IPC request completed, now check return code
                            if (GPE_RC_SUCCESS == G_dimm_sm_args.error.rc)
                            {
                                // last request completed without error
                                switch (G_dimm_sm_args.state)
                                {
                                    case DIMM_STATE_INIT:
                                        // Save max I2C ports
                                        if (G_maxDimmPort != G_dimm_sm_args.maxPorts)
                                        {
                                            G_maxDimmPort = G_dimm_sm_args.maxPorts;
                                            DIMM_DBG("task_dimm_sm: updating DIMM Max I2C Port to %d", G_maxDimmPort);
                                            // verify that we don't have a port higher than max
                                            for (ocmbIndex = 0; ocmbIndex < MAX_NUM_OCMBS; ++ocmbIndex)
                                            {
                                                if(G_dimm_enabled_sensors.bytes[ocmbIndex] &&
                                                  (g_amec->proc[0].memctl[ocmbIndex].membuf.dimm_temps[0].i2c_port > G_maxDimmPort))
                                                {
                                                    TRAC_ERR("task_dimm_sm: found DIMM%04X with port %d > max %d",
                                                              DIMM_INDEX(ocmbIndex, 0),
                                                              g_amec->proc[0].memctl[ocmbIndex].membuf.dimm_temps[0].i2c_port,
                                                              G_maxDimmPort);
                                                    /*
                                                     * @errortype
                                                     * @moduleid    DIMM_MID_DIMM_SM
                                                     * @reasoncode  INVALID_CONFIG_DATA
                                                     * @userdata1   OCMB
                                                     * @userdata2   dimm port
                                                     * @devdesc     Invalid DIMM I2C port
                                                     */
                                                    l_err = createErrl(DIMM_MID_DIMM_SM,
                                                                       INVALID_CONFIG_DATA,
                                                                       OCC_NO_EXTENDED_RC,
                                                                       ERRL_SEV_PREDICTIVE,
                                                                       NULL,
                                                                       DEFAULT_TRACE_SIZE,
                                                                       ocmbIndex,
                                                                       g_amec->proc[0].memctl[ocmbIndex].membuf.dimm_temps[0].i2c_port);
                                                    commitErrl(&l_err);

                                                    // disable this DIMM
                                                    G_dimm_enabled_sensors.bytes[ocmbIndex] = 0;
                                                }
                                            }
                                        }
                                        break;

                                    case DIMM_STATE_READ_TEMP:
                                        if (L_readIssued)
                                        {
                                            if ((G_inject_dimm & ((uint64_t)1 << ((L_ocmb * 8) + L_dimmIndex))) == 0)
                                            {
                                                if (G_inject_dimm_trace[L_ocmb][L_dimmIndex] != 0)
                                                {
                                                    TRAC_INFO("task_dimm_sm: stopping injection of errors for DIMM%04X", DIMM_INDEX(L_ocmb, L_dimmIndex));
                                                    G_inject_dimm_trace[L_ocmb][L_dimmIndex] = 0;
                                                }
                                                // Validate  and store temperature
                                                process_dimm_temp();
                                            }
                                            else
                                            {
                                                if (G_inject_dimm_trace[L_ocmb][L_dimmIndex] == 0)
                                                {
                                                    TRAC_INFO("task_dimm_sm: injecting errors for DIMM%04X", DIMM_INDEX(L_ocmb, L_dimmIndex));
                                                    G_inject_dimm_trace[L_ocmb][L_dimmIndex] = 1;
                                                }
                                            }

                                            // Move on to next DIMM
                                            use_next_dimm(&L_ocmb, &L_dimmIndex);
                                            L_readIssued = false;

                                            // Check if host needs the I2C lock
                                            L_occ_owns_lock = check_and_update_i2c_lock(engine);
                                        }
                                        break;

                                    default:
                                        // Nothing to do
                                            break;
                                }
                            }
                            else
                            {
                                // last request did not return success
                                switch (G_dimm_sm_args.state)
                                {
                                    case DIMM_STATE_INITIATE_READ:
                                        if (++L_readAttempt < MAX_READ_ATTEMPT)
                                        {
                                            // The initiate_read didnt complete, retry
                                            DIMM_DBG("task_dimm_sm: initiate read didn't start (%d attempts)", L_readAttempt);
                                            // Force the read again
                                            G_dimm_state = DIMM_STATE_INITIATE_READ;
                                            nextState = G_dimm_state;
                                        }
                                        else
                                        {
                                            INTR_TRAC_ERR("task_dimm_sm: initiate read didn't start after %d attempts... forcing reset", L_readAttempt);
                                            mark_dimm_failed();
                                        }
                                        break;

                                    case DIMM_STATE_READ_TEMP:
                                        if (L_readIssued)
                                        {
                                            if (++L_readAttempt < MAX_READ_ATTEMPT)
                                            {
                                                DIMM_DBG("task_dimm_sm: read didn't complete (%d attempts)", L_readAttempt);
                                                // Force the read again
                                                G_dimm_state = DIMM_STATE_READ_TEMP;
                                                nextState = G_dimm_state;
                                            }
                                            else
                                            {
                                                INTR_TRAC_ERR("task_dimm_sm: read did not complete after %d attempts... forcing reset", L_readAttempt);
                                                mark_dimm_failed();
                                            }
                                        }
                                        break;

                                    default:
                                        // Nothing to do
                                        break;
                                }
                            }
                        }
                    }

                    if (L_occ_owns_lock)
                    {
                        if (false == G_dimm_i2c_reset_required)
                        {
                            // Handle new DIMM state
                            switch (G_dimm_state)
                            {
                                case DIMM_STATE_WRITE_MODE:
                                    // Only start a DIMM read on tick 0 or 8
                                    if ((DIMM_TICK == 0) || (DIMM_TICK == 8))
                                    {
                                        // If DIMM is not disabled start temp collection
                                        if(DIMM_SENSOR_ENABLED(L_ocmb, L_dimmIndex))
                                        {
                                            L_new_dimm_args.i2cPort = g_amec->proc[0].memctl[L_ocmb].membuf.dimm_temps[L_dimmIndex].i2c_port;
                                            L_new_dimm_args.i2cAddr = g_amec->proc[0].memctl[L_ocmb].membuf.dimm_temps[L_dimmIndex].i2c_address;
                                            L_new_dimm_args.ocmb = L_ocmb;
                                            L_new_dimm_args.dimm = L_dimmIndex;
                                            if (schedule_dimm_req(DIMM_STATE_WRITE_MODE, L_new_dimm_args))
                                            {
                                                DIMM_DBG("task_dimm_sm: Collection started for DIMM%04X at tick %d",
                                                         OCMB_AND_DIMM, DIMM_TICK);
                                                nextState = DIMM_STATE_WRITE_ADDR;
                                            }
                                        }
                                        else
                                        {
                                            // Skip current DIMM and move on to next one
                                            use_next_dimm(&L_ocmb, &L_dimmIndex);
                                        }
                                    }
                                    break;

                                case DIMM_STATE_WRITE_ADDR:
                                    if (intTriggered || (L_notReadyCount > MAX_TICK_COUNT_WAIT))
                                    {
                                        L_new_dimm_args.dimm = L_dimmIndex;
                                        L_new_dimm_args.ocmb = L_ocmb;
                                        L_new_dimm_args.i2cAddr = g_amec->proc[0].memctl[L_ocmb].membuf.dimm_temps[L_dimmIndex].i2c_address;
                                        if (schedule_dimm_req(DIMM_STATE_WRITE_ADDR, L_new_dimm_args))
                                        {
                                            nextState = DIMM_STATE_INITIATE_READ;
                                            L_readAttempt = 0;
                                            L_readIssued = false;
                                        }
                                    }
                                    break;

                                case DIMM_STATE_INITIATE_READ:
                                    if (intTriggered || (L_notReadyCount > MAX_TICK_COUNT_WAIT))
                                    {
                                        L_new_dimm_args.dimm = L_dimmIndex;
                                        L_new_dimm_args.ocmb = L_ocmb;
                                        if (schedule_dimm_req(DIMM_STATE_INITIATE_READ, L_new_dimm_args))
                                        {
                                            nextState = DIMM_STATE_READ_TEMP;
                                        }
                                    }
                                    break;

                                case DIMM_STATE_READ_TEMP:
                                    if (intTriggered || (L_notReadyCount > MAX_TICK_COUNT_WAIT))
                                    {
                                        if (schedule_dimm_req(DIMM_STATE_READ_TEMP, L_new_dimm_args))
                                        {
                                            L_readIssued = true;
                                            nextState = DIMM_STATE_WRITE_MODE;
                                        }
                                    }
                                    break;

                                default:
                                    INTR_TRAC_ERR("task_dimm_sm: INVALID STATE: 0x%02X", G_dimm_state);
                                    break;
                            }
                        }
                        else
                        {
                            // Previous op triggered reset
                            nextState = dimm_reset_sm();
                        }
                    }
                    else
                    {
                        // OCC no longer holds the i2c lock (no DIMM state change required)
                        nextState = G_dimm_state;
                    }
                }

                if (nextState != G_dimm_state)
                {
                    DIMM_DBG("task_dimm_sm: Updating state to 0x%02X (DIMM%04X) end of tick %d", nextState, (L_ocmb<<8)|L_dimmIndex, DIMM_TICK);
                    G_dimm_state = nextState;
                    L_notReadyCount = 0;
                }
            }
        }  // if G_dimm_i2c_reset_required false
    }  // if G_mem_monitoring_allowed
} // end task_dimm_sm()


