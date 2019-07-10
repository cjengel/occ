/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/occ_405/cmdh/cmdh_fsp_cmds_datacnfg.c $                   */
/*                                                                        */
/* OpenPOWER OnChipController Project                                     */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2011,2019                        */
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

#include "ssx.h"
#include "cmdh_service_codes.h"
#include "cmdh_fsp_cmds_datacnfg.h"
#include "errl.h"
#include "trac.h"
#include "rtls.h"
#include "dcom.h"
#include "occ_common.h"
#include "state.h"
#include "cmdh_fsp_cmds.h"
#include "cmdh_dbug_cmd.h"
#include "proc_pstate.h"
#include <amec_data.h>
#include "amec_amester.h"
#include "amec_service_codes.h"
#include "amec_sys.h"
#include <centaur_data.h>
#include "dimm.h"
#include "memory.h"
#include <avsbus.h>
#include "p9_pstates_occ.h"
#include <wof.h>
#include <i2c.h>

#define FREQ_FORMAT_BASE_DATA_SZ   (sizeof(cmdh_store_mode_freqs_t) - sizeof(cmdh_fsp_cmd_header_t))

#define FREQ_FORMAT_20_NUM_FREQS   6
#define DATA_FREQ_VERSION_20       0x20
#define FREQ_FORMAT_21_NUM_FREQS   8
#define DATA_FREQ_VERSION_21       0x21

#define DATA_PCAP_VERSION_20       0x20

#define DATA_SYS_VERSION_20        0x20
#define DATA_SYS_VERSION_21        0x21

#define DATA_APSS_VERSION20        0x20

#define DATA_THRM_THRES_VERSION_20 0x20
#define THRM_THRES_BASE_DATA_SZ_20 5

#define DATA_IPS_VERSION           0

#define DATA_MEM_CFG_VERSION_20    0x20
#define DATA_MEM_CFG_VERSION_21    0x21

#define DATA_MEM_THROT_VERSION_20  0x20

#define DATA_VRM_FAULT_VERSION     0x01

extern uint8_t G_occ_interrupt_type;

extern uint16_t G_proc_fmax_mhz;      // Maximum frequency (uturbo if WOF enabled, otherwise turbo)
extern OCCPstateParmBlock G_oppb;     // OCC Pstate Parameters Block Structure
extern uint32_t G_first_proc_gpu_config;
extern uint32_t G_first_num_gpus_sys;
extern uint32_t G_curr_num_gpus_sys;
extern uint32_t G_curr_proc_gpu_config;
extern bool     G_gpu_config_done;
extern bool     G_gpu_monitoring_allowed;
extern task_t   G_task_table[TASK_END];
extern bool     G_pgpe_shared_sram_V_I_readings;

typedef struct data_req_table
{
   uint32_t mask;
   uint8_t  format;
} data_req_table_t;

data_cnfg_t G_data_cnfg_static_obj = {0};

data_cnfg_t * G_data_cnfg = &G_data_cnfg_static_obj;

const data_req_table_t G_data_pri_table[] =
{
    {DATA_MASK_SYS_CNFG,              DATA_FORMAT_SYS_CNFG}, //Need this first so we can use correct huid's for callouts
    {DATA_MASK_APSS_CONFIG,           DATA_FORMAT_APSS_CONFIG}, //need apss config data prior to role data
    {DATA_MASK_AVSBUS_CONFIG,         DATA_FORMAT_AVSBUS_CONFIG},
    {DATA_MASK_SET_ROLE,              DATA_FORMAT_SET_ROLE},
    {DATA_MASK_MEM_CFG,               DATA_FORMAT_MEM_CFG},
    {DATA_MASK_GPU,                   DATA_FORMAT_GPU},
    {DATA_MASK_THRM_THRESHOLDS,       DATA_FORMAT_THRM_THRESHOLDS},
    {DATA_MASK_FREQ_PRESENT,          DATA_FORMAT_FREQ},
    {DATA_MASK_PCAP_PRESENT,          DATA_FORMAT_POWER_CAP},
    {DATA_MASK_MEM_THROT,             DATA_FORMAT_MEM_THROT},
};

cmdh_ips_config_data_t G_ips_config_data = {0};

bool G_mem_monitoring_allowed = FALSE;

// Save which voltage the GPU is using (1 = default (12V), 2 = 2nd voltage (54V))
uint8_t G_gpu_volt_type[MAX_GPU_DOMAINS][MAX_NUM_GPU_PER_DOMAIN] = {{0}};
bool    G_found_volt2 = FALSE;

// Will get set when receiving APSS config data
PWR_READING_TYPE G_pwr_reading_type = PWR_READING_TYPE_NONE;

// Function Specification
//
// Name:  DATA_get_present_cnfgdata
//
// Description:  Accessor function for external access
//
// End Function Specification
uint32_t DATA_get_present_cnfgdata(void)
{
    return G_data_cnfg->data_mask;
}

errlHndl_t DATA_get_thrm_thresholds(cmdh_thrm_thresholds_t **o_thrm_thresh)
{
    errlHndl_t                  l_err = NULL;

    if(G_data_cnfg->data_mask & DATA_MASK_THRM_THRESHOLDS)
    {
        *o_thrm_thresh = &(G_data_cnfg->thrm_thresh);
    }
    else
    {
        CMDH_TRAC_ERR("DATA_get_thrm_thresholds: Thermal Threshold data is unavailable! data_mask[0x%X]",
                 G_data_cnfg->data_mask);
        /* @
         * @errortype
         * @moduleid    DATA_GET_THRM_THRESHOLDS
         * @reasoncode  INTERNAL_FAILURE
         * @userdata1   data mask showing which data OCC has received
         * @userdata4   ERC_CMDH_THRM_DATA_MISSING
         * @devdesc     Someone is asking for the thermal control threholds
         *              and OCC hasn't received them yet from the FSP!
         */
        l_err = createErrl(DATA_GET_THRM_THRESHOLDS,
                           INTERNAL_FAILURE,
                           ERC_CMDH_THRM_DATA_MISSING,
                           ERRL_SEV_PREDICTIVE,
                           NULL,
                           DEFAULT_TRACE_SIZE,
                           G_data_cnfg->data_mask,
                           0);
    }

    return l_err;
}

errlHndl_t DATA_get_ips_cnfg(cmdh_ips_config_data_t **o_ips_cnfg)
{
    errlHndl_t                  l_err = NULL;

    if(G_data_cnfg->data_mask & DATA_MASK_IPS_CNFG)
    {
        *o_ips_cnfg = &G_ips_config_data;
    }
    else
    {
        CMDH_TRAC_ERR("DATA_get_ips_cnfg: IPS Config data is unavailable! data_mask[0x%X]",
                 G_data_cnfg->data_mask);

        /* @
         * @errortype
         * @moduleid    DATA_GET_IPS_DATA
         * @reasoncode  INTERNAL_FAILURE
         * @userdata1   data mask showing which data OCC has received
         * @userdata4   ERC_CMDH_IPS_DATA_MISSING
         * @devdesc     Someone is asking for the Idle Power Save config data
         *              and OCC hasn't received them yet from the FSP!
         */
        l_err = createErrl(DATA_GET_IPS_DATA,
                           INTERNAL_FAILURE,
                           ERC_CMDH_IPS_DATA_MISSING,
                           ERRL_SEV_PREDICTIVE,
                           NULL,
                           DEFAULT_TRACE_SIZE,
                           G_data_cnfg->data_mask,
                           0);
    }

    return l_err;
}

// Function Specification
//
// Name:  DATA_request_cnfgdata
//
// Description: Determine what config data should be requested from TMGT
//
// End Function Specification
uint8_t DATA_request_cnfgdata ()
{
    uint8_t                        l_req         = 0x00; // Data to request
    uint16_t                       i             = 0;
    uint16_t                       l_array_size  = 0;

    l_array_size = sizeof(G_data_pri_table) / sizeof(data_req_table_t);

    for(i=0;i<l_array_size;i++)
    {
        // Skip requesting memory throttle values if memory monitoring
        // is not being allowed by TMGT.
        if((G_data_pri_table[i].format == DATA_FORMAT_MEM_THROT) &&
            !G_mem_monitoring_allowed)
        {
            continue;
        }

        // Skip whenever we are trying to request pcap or freq as a slave
        if(((G_data_pri_table[i].format == DATA_FORMAT_POWER_CAP) ||
            (G_data_pri_table[i].format == DATA_FORMAT_FREQ)) &&
            (G_occ_role == OCC_SLAVE))
        {
            continue;
        }

        // Go through priority table and request first data found which has
        // not been provided
        if(!(G_data_cnfg->data_mask & G_data_pri_table[i].mask))
        {
            l_req = G_data_pri_table[i].format;
            break;
        }
    }

    return(l_req);
}

// Function Specification
//
// Name:  data_store_freq_data
//
// Description: Write all of the frequency points from TMGT into G_sysConfigData
//
// End Function Specification
errlHndl_t data_store_freq_data(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                cmdh_fsp_rsp_t       * o_rsp_ptr)
{
    errlHndl_t                      l_err = NULL;
    cmdh_store_mode_freqs_t*        l_cmdp = (cmdh_store_mode_freqs_t*)i_cmd_ptr;
    uint8_t*                        l_buf = ((uint8_t*)(l_cmdp)) + sizeof(cmdh_store_mode_freqs_t);
    uint16_t                        l_data_length;
    uint32_t                        l_mode_data_sz;
    uint16_t                        l_freq = 0;
    uint16_t                        l_table[OCC_MODE_COUNT] = {0};
    uint16_t                        l_pgpe_max_freq_mhz = (G_oppb.frequency_max_khz / 1000);

    do
    {
        l_data_length  = CMDH_DATALEN_FIELD_UINT16(l_cmdp);
        l_mode_data_sz = l_data_length - FREQ_FORMAT_BASE_DATA_SZ;

        // Sanity Checks
        // If the datapacket is bigger than what we can store, OR
        // if the version doesn't equal what we expect, OR
        // if the expected data length does not agree with the actual data length
        if( (l_data_length < FREQ_FORMAT_BASE_DATA_SZ) ||
            ( (DATA_FREQ_VERSION_20 == l_cmdp->version) && (l_mode_data_sz != (FREQ_FORMAT_20_NUM_FREQS * 2)) ) ||
            ( (DATA_FREQ_VERSION_21 == l_cmdp->version) && (l_mode_data_sz != (FREQ_FORMAT_21_NUM_FREQS * 2)) ) )
        {
            CMDH_TRAC_ERR("Invalid Frequency Data packet: data_length[%u] version[%u] l_mode_data_sz[%u]",
                     l_data_length, l_cmdp->version, l_mode_data_sz);
            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
            break;
        }

        if(OCC_MASTER != G_occ_role)
        {
            // We want to ignore this cnfg data if we are not the master.
            CMDH_TRAC_INFO("Received a Frequncy Data Packet on a Slave OCC: Ignore!");
            break;
        }

        // store frequency data common to all versions
        // 1) Nominal, 2) Turbo, 3) Minimum,
        // 4) Ultra Turbo, 5) Static PS, 6) FFO
        // store under the existing enums.

        // Bytes 3-4 Nominal Frequency Point
        l_freq = (l_buf[0] << 8 | l_buf[1]);

        //  nominal can not be 0
        if(!l_freq)
        {
            CMDH_TRAC_ERR("Nominal Frequency is 0!!!");
            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
            break;
        }

        // This should never happen but verify that nominal frequency is <= OPPB max
        if(l_freq > l_pgpe_max_freq_mhz)
        {
            CMDH_TRAC_ERR("Nominal Frequency[%d] (MHz)) is higher than "
                          "OPPB max[%d], clipping Nominal Frequency",
                          l_freq, l_pgpe_max_freq_mhz);
            l_freq = l_pgpe_max_freq_mhz;
        }

        l_table[OCC_MODE_NOMINAL] = l_freq;
        CMDH_TRAC_INFO("Nominal frequency = %d MHz", l_freq);

        // Bytes 5-6 Turbo Frequency Point:
        // also store for DPS modes
        l_freq = (l_buf[2] << 8 | l_buf[3]);
        // Verify that turbo frequency is not zero, if it is set to nominal
        if(!l_freq)
        {
            CMDH_TRAC_ERR("Turbo Frequency is 0 setting to nominal %dMHz ",
                           l_table[OCC_MODE_NOMINAL]);
            l_freq = l_table[OCC_MODE_NOMINAL];
        }
        // Verify that turbo frequency is <= OPPB max
        else if(l_freq > l_pgpe_max_freq_mhz)
        {
            CMDH_TRAC_ERR("Turbo Frequency[%d] (MHz)) is higher than "
                          "OPPB max[%d], clip Turbo Frequency",
                          l_freq, l_pgpe_max_freq_mhz);
            l_freq = l_pgpe_max_freq_mhz;
        }
        l_table[OCC_MODE_TURBO] = l_freq;
        CMDH_TRAC_INFO("Turbo frequency = %d MHz", l_freq);

        // Bytes 7-8 Minimum Frequency Point
        l_freq = (l_buf[4] << 8 | l_buf[5]);
        // Verify that minimum frequency is >= G_oppb.frequency_min_khz
        if(l_freq * 1000 < G_oppb.frequency_min_khz)
        {
            CMDH_TRAC_ERR("Minimum Frequency[%d] (Mhz)  is lower than PGPE's "
                          "G_oppb.frequency_min_khz[%d], clip Minimum Frequency",
                           l_freq, G_oppb.frequency_min_khz);
            l_freq = G_oppb.frequency_min_khz / 1000;
        }
        l_table[OCC_MODE_MIN_FREQUENCY] = l_freq;
        CMDH_TRAC_INFO("Minimum frequency = %d MHz", l_freq);

        // Bytes 9-10 Ultr Turbo Frequency Point
        l_freq = (l_buf[6] << 8 | l_buf[7]);
        // Verify that ultra turbo frequency is <= OPPB max
        if(l_freq  > l_pgpe_max_freq_mhz)
        {
            CMDH_TRAC_ERR("Ultra Turbo Frequency[%d] (MHz) is higher than PGPE's "
                          "Max freq (OPPB max[%d]) clip Ultra Turbo Frequency",
                          l_freq, l_pgpe_max_freq_mhz);
            l_freq = l_pgpe_max_freq_mhz;
        }

        // Check if (H)TMGT will let WOF run, else clear flags
        switch( l_freq )
        {
            case WOF_MISSING_ULTRA_TURBO:
                CMDH_TRAC_INFO("WOF Disabled due to 0 UT value.");
                set_clear_wof_disabled( SET,
                                        WOF_RC_UTURBO_IS_ZERO,
                                        ERC_WOF_UTURBO_IS_ZERO );
                l_freq = 0;
                break;

            case WOF_SYSTEM_DISABLED:
                CMDH_TRAC_INFO("WOF Disabled due to SYSTEM_WOF_DISABLE");
                set_clear_wof_disabled( SET,
                                        WOF_RC_SYSTEM_WOF_DISABLE,
                                        ERC_WOF_SYSTEM_WOF_DISABLE );
                l_freq = 0;
                break;

            case WOF_RESET_LIMIT_REACHED:
                CMDH_TRAC_INFO("WOF Disabled due to reset limit");
                set_clear_wof_disabled( SET,
                                        WOF_RC_RESET_LIMIT_REACHED,
                                        ERC_WOF_RESET_LIMIT_REACHED );
                l_freq = 0;
                break;

            case WOF_UNSUPPORTED_FREQ:
                CMDH_TRAC_INFO("WOF Disabled due to unsupported frequency");
                set_clear_wof_disabled( SET,
                                        WOF_RC_UNSUPPORTED_FREQUENCIES,
                                        ERC_WOF_UNSUPPORTED_FREQUENCIES );
                l_freq = 0;
                break;

            default:
                CMDH_TRAC_INFO("WOF is Enabled! so far...");
                set_clear_wof_disabled( CLEAR,
                                        WOF_RC_UTURBO_IS_ZERO,
                                        ERC_WOF_UTURBO_IS_ZERO );
                set_clear_wof_disabled( CLEAR,
                                        WOF_RC_SYSTEM_WOF_DISABLE,
                                        ERC_WOF_SYSTEM_WOF_DISABLE );
                set_clear_wof_disabled( CLEAR,
                                        WOF_RC_RESET_LIMIT_REACHED,
                                        ERC_WOF_SYSTEM_WOF_DISABLE );
                set_clear_wof_disabled( CLEAR,
                                        WOF_RC_UNSUPPORTED_FREQUENCIES,
                                        ERC_WOF_UNSUPPORTED_FREQUENCIES );
                set_clear_wof_disabled( CLEAR,
                                        WOF_RC_OCC_WOF_DISABLED,
                                        ERC_WOF_OCC_WOF_DISABLED );
                break;
        }

        l_table[OCC_MODE_UTURBO] = l_freq;
        CMDH_TRAC_INFO("UT frequency = %d MHz", l_freq);

        // clip G_proc_fmax_mhz to TMGT's MAX(turbo, ultra turbo) frequency point
        if(l_table[OCC_MODE_UTURBO] > l_table[OCC_MODE_TURBO])
        {
            G_proc_fmax_mhz = l_table[OCC_MODE_UTURBO];
        }
        else
        {
            G_proc_fmax_mhz = l_table[OCC_MODE_TURBO];
        }

        // Set dynamic power save frequencies
        l_table[OCC_MODE_DYN_POWER_SAVE] = G_proc_fmax_mhz;
        l_table[OCC_MODE_DYN_POWER_SAVE_FP] = G_proc_fmax_mhz;

        // Bytes 11-12 Static Power Save Frequency Point
        l_freq = (l_buf[8] << 8 | l_buf[9]);
        // in case min freq was clipped verify power save not below min
        if(l_freq < l_table[OCC_MODE_MIN_FREQUENCY])
        {
            l_freq = l_table[OCC_MODE_MIN_FREQUENCY];
        }

        l_table[OCC_MODE_PWRSAVE] = l_freq;
        CMDH_TRAC_INFO("Static Power Save frequency = %d MHz", l_freq);

        // Bytes 13-14 FFO Frequency Point
        l_freq = (l_buf[10] << 8 | l_buf[11]);
        if (l_freq != 0)
        {
            // Check and make sure that FFO freq is within valid range
            const uint16_t l_req_freq = l_freq;
            if (l_freq  < l_table[OCC_MODE_MIN_FREQUENCY])
            {
                l_freq = l_table[OCC_MODE_MIN_FREQUENCY];
            }
            else if (l_freq > G_proc_fmax_mhz)
            {
                l_freq = G_proc_fmax_mhz;
            }

            // Log an error if we could not honor the requested FFO frequency, but keep going.
            if (l_req_freq != l_freq)
            {
                TRAC_ERR("FFO Frequency out of range. requested %d MHz, but using %d MHz",
                          l_req_freq,  l_freq);
                /* @
                 * @errortype
                 * @moduleid    DATA_STORE_FREQ_DATA
                 * @reasoncode  INVALID_INPUT_DATA
                 * @userdata1   requested frequency
                 * @userdata2   frequency used
                 * @userdata4   OCC_NO_EXTENDED_RC
                 * @devdesc     OCC recieved an invalid FFO frequency
                 */
                l_err = createErrl(DATA_STORE_FREQ_DATA,
                                   INVALID_INPUT_DATA,
                                   OCC_NO_EXTENDED_RC,
                                   ERRL_SEV_INFORMATIONAL,
                                   NULL,
                                   DEFAULT_TRACE_SIZE,
                                   l_req_freq,
                                   l_freq);
                commitErrl(&l_err);
            }
        }
        l_table[OCC_MODE_FFO] = l_freq;
       CMDH_TRAC_INFO("FFO Frequency = %d Mhz", l_freq);

        // Only version 0x21 has additional oversubscription freq
        if(DATA_FREQ_VERSION_21 == l_cmdp->version)
        {
            // Bytes 15-16 Oversubscription Max Frequency
            l_freq = (l_buf[12] << 8 | l_buf[13]);
            l_table[OCC_MODE_OVERSUB] = l_freq;
            // Bytes 17-18 VRM N mode Max Frequency
            l_freq = (l_buf[14] << 8 | l_buf[15]);
            l_table[OCC_MODE_VRM_N] = l_freq;
        }
        else
        {
            // Version 0x20 limit oversubscription and VRM N mode frequency to turbo
            l_table[OCC_MODE_OVERSUB] = l_table[OCC_MODE_TURBO];
            l_table[OCC_MODE_VRM_N] = l_table[OCC_MODE_TURBO];
        }

        CMDH_TRAC_INFO("Oversubscription max frequency = %d MHz", l_table[OCC_MODE_OVERSUB]);
        CMDH_TRAC_INFO("VRM N mode max frequency = %d MHz", l_table[OCC_MODE_VRM_N]);

        // inconsistent Frequency Points?
        if((l_table[OCC_MODE_UTURBO] < l_table[OCC_MODE_TURBO] && l_table[OCC_MODE_UTURBO]) ||
           l_table[OCC_MODE_TURBO]   < l_table[OCC_MODE_NOMINAL] ||
           l_table[OCC_MODE_NOMINAL] < l_table[OCC_MODE_PWRSAVE] ||
           l_table[OCC_MODE_PWRSAVE] < l_table[OCC_MODE_MIN_FREQUENCY])
        {
            CMDH_TRAC_ERR("Inconsistent Frequency points - UT-T=0x%x, NOM-PS=0x%x, MIN=0x%x",
                          (l_table[OCC_MODE_UTURBO] << 16)  + l_table[OCC_MODE_TURBO],
                          (l_table[OCC_MODE_NOMINAL] << 16) + l_table[OCC_MODE_PWRSAVE],
                          l_table[OCC_MODE_MIN_FREQUENCY]);
        }

    }while(0);



    // Change Data Request Mask to indicate we got this data
    if(!l_err && (G_occ_role == OCC_MASTER))
    {
        // Copy all of the frequency updates to the global and notify
        // dcom of the new frequenies.
        memcpy(G_sysConfigData.sys_mode_freq.table, l_table, sizeof(l_table));
        G_sysConfigData.sys_mode_freq.update_count++;
        G_data_cnfg->data_mask |= DATA_MASK_FREQ_PRESENT;
    }

    return l_err;
}

// Function Specification
//
// Name:  apss_store_adc_channel
//
// Description: Matches the functional ID (from MRW) to the APSS ADC channel
//
// End Function Specification
errlHndl_t apss_store_adc_channel(const eApssAdcChannelAssignments i_func_id, const uint8_t i_channel_num )
{
    errlHndl_t l_err = NULL;
    bool l_gpu_volt_conflict = FALSE;

    // Check function ID and channel number
    if ( (i_func_id >= NUM_ADC_ASSIGNMENT_TYPES) ||
         (i_channel_num >= MAX_APSS_ADC_CHANNELS) )
    {
        CMDH_TRAC_ERR("apss_store_adc_channel: Invalid function ID or channel number (id:0x%x, channel:%d)", i_func_id, i_channel_num);

        /* @
         * @errortype
         * @moduleid    DATA_STORE_APSS_DATA
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata1   function ID
         * @userdata2   channel number
         * @userdata4   ERC_APSS_ADC_OUT_OF_RANGE_FAILURE
         * @devdesc     Invalid function ID or channel number
         */
        l_err = createErrl(DATA_STORE_APSS_DATA,
                           INVALID_INPUT_DATA,
                           ERC_APSS_ADC_OUT_OF_RANGE_FAILURE,
                           ERRL_SEV_UNRECOVERABLE,
                           NULL,
                           DEFAULT_TRACE_SIZE,
                           (uint32_t)i_func_id,
                           (uint32_t)i_channel_num);

        // Callout firmware
        addCalloutToErrl(l_err,
                         ERRL_CALLOUT_TYPE_COMPONENT_ID,
                         ERRL_COMPONENT_ID_FIRMWARE,
                         ERRL_CALLOUT_PRIORITY_HIGH);
    }
    else
    {
        uint8_t *l_adc_function=NULL;
        switch (i_func_id)
        {
            case ADC_RESERVED:
                // Do nothing
                break;

            case ADC_MEMORY_PROC_0:
            case ADC_MEMORY_PROC_1:
            case ADC_MEMORY_PROC_2:
            case ADC_MEMORY_PROC_3:
                l_adc_function = &G_sysConfigData.apss_adc_map.memory[i_func_id-ADC_MEMORY_PROC_0][0];
                break;

            case ADC_MEMORY_PROC_0_0:
                l_adc_function = &G_sysConfigData.apss_adc_map.memory[0][1];
                break;
            case ADC_MEMORY_PROC_0_1:
                l_adc_function = &G_sysConfigData.apss_adc_map.memory[0][2];
                break;
            case ADC_MEMORY_PROC_0_2:
                l_adc_function = &G_sysConfigData.apss_adc_map.memory[0][3];
                break;
            case ADC_VDD_PROC_0:
            case ADC_VDD_PROC_1:
            case ADC_VDD_PROC_2:
            case ADC_VDD_PROC_3:
                l_adc_function = &G_sysConfigData.apss_adc_map.vdd[i_func_id-ADC_VDD_PROC_0];
                break;

            case ADC_VCS_VIO_VPCIE_PROC_0:
            case ADC_VCS_VIO_VPCIE_PROC_1:
            case ADC_VCS_VIO_VPCIE_PROC_2:
            case ADC_VCS_VIO_VPCIE_PROC_3:
                l_adc_function = &G_sysConfigData.apss_adc_map.vcs_vio_vpcie[i_func_id-ADC_VCS_VIO_VPCIE_PROC_0];
                break;

            case ADC_IO_A:
            case ADC_IO_B:
            case ADC_IO_C:
                l_adc_function = &G_sysConfigData.apss_adc_map.io[i_func_id-ADC_IO_A];
                break;

            case ADC_FANS_A:
            case ADC_FANS_B:
                l_adc_function = &G_sysConfigData.apss_adc_map.fans[i_func_id-ADC_FANS_A];
                break;

            case ADC_STORAGE_A:
            case ADC_STORAGE_B:
                l_adc_function = &G_sysConfigData.apss_adc_map.storage_media[i_func_id-ADC_STORAGE_A];
                break;

            case ADC_12V_SENSE:
                l_adc_function = &G_sysConfigData.apss_adc_map.sense_12v;
                break;

            case ADC_VOLT_SENSE_2:
                l_adc_function = &G_sysConfigData.apss_adc_map.sense_volt2;
                break;

            case ADC_GND_REMOTE_SENSE:
                l_adc_function = &G_sysConfigData.apss_adc_map.remote_gnd;
                break;

            case ADC_TOTAL_SYS_CURRENT:
                l_adc_function = &G_sysConfigData.apss_adc_map.total_current_12v;
                break;

            case ADC_TOTAL_SYS_CURRENT_2:
                l_adc_function = &G_sysConfigData.apss_adc_map.total_current_volt2;
                break;

            case ADC_MEM_CACHE:
                l_adc_function = &G_sysConfigData.apss_adc_map.mem_cache;
                break;

            case ADC_12V_STANDBY_CURRENT:
                l_adc_function = &G_sysConfigData.apss_adc_map.current_12v_stby;
                break;

            case ADC_GPU_0_0:
                if (G_gpu_volt_type[0][0] != 2)
                {
                    G_gpu_volt_type[0][0] = 1;
                    l_adc_function = &G_sysConfigData.apss_adc_map.gpu[0][0];
                }
                else
                {
                    l_gpu_volt_conflict = TRUE;
                }
                break;

            case ADC_GPU_0_1:
                if (G_gpu_volt_type[0][1] != 2)
                {
                    G_gpu_volt_type[0][1] = 1;
                    l_adc_function = &G_sysConfigData.apss_adc_map.gpu[0][1];
                }
                else
                {
                    l_gpu_volt_conflict = TRUE;
                }
                break;

            case ADC_GPU_0_2:
                l_adc_function = &G_sysConfigData.apss_adc_map.gpu[0][2];
                break;

            case ADC_GPU_1_0:
                if (G_gpu_volt_type[1][0] != 2)
                {
                    G_gpu_volt_type[1][0] = 1;
                    l_adc_function = &G_sysConfigData.apss_adc_map.gpu[1][0];
                }
                else
                {
                    l_gpu_volt_conflict = TRUE;
                }
                break;

            case ADC_GPU_1_1:
                if (G_gpu_volt_type[1][1] != 2)
                {
                    G_gpu_volt_type[1][1] = 1;
                    l_adc_function = &G_sysConfigData.apss_adc_map.gpu[1][1];
                }
                else
                {
                    l_gpu_volt_conflict = TRUE;
                }
                break;

            case ADC_GPU_1_2:
                l_adc_function = &G_sysConfigData.apss_adc_map.gpu[1][2];
                break;

            case ADC_GPU_VOLT2_0_0:
                if (G_gpu_volt_type[0][0] != 1)
                {
                    G_found_volt2 = TRUE;
                    G_gpu_volt_type[0][0] = 2;
                    l_adc_function = &G_sysConfigData.apss_adc_map.gpu[0][0];
                }
                else
                {
                    l_gpu_volt_conflict = TRUE;
                }
                break;

            case ADC_GPU_VOLT2_0_1:
                if (G_gpu_volt_type[0][1] != 1)
                {
                    G_found_volt2 = TRUE;
                    G_gpu_volt_type[0][1] = 2;
                    l_adc_function = &G_sysConfigData.apss_adc_map.gpu[0][1];
                }
                else
                {
                    l_gpu_volt_conflict = TRUE;
                }
                break;

            case ADC_GPU_VOLT2_1_0:
                if (G_gpu_volt_type[1][0] != 1)
                {
                    G_found_volt2 = TRUE;
                    G_gpu_volt_type[1][0] = 2;
                    l_adc_function = &G_sysConfigData.apss_adc_map.gpu[1][0];
                }
                else
                {
                    l_gpu_volt_conflict = TRUE;
                }
                break;

            case ADC_GPU_VOLT2_1_1:
                if (G_gpu_volt_type[1][1] != 1)
                {
                    G_found_volt2 = TRUE;
                    G_gpu_volt_type[1][1] = 2;
                    l_adc_function = &G_sysConfigData.apss_adc_map.gpu[1][1];
                }
                else
                {
                    l_gpu_volt_conflict = TRUE;
                }
                break;

            default:
                // It should never happen
                CMDH_TRAC_ERR("apss_store_adc_channel: Invalid function ID: 0x%x", i_func_id);
                break;
        }

        if(NULL != l_adc_function)
        {
            // Check if this function already have ADC channel assigned
            if( SYSCFG_INVALID_ADC_CHAN == *l_adc_function)
            {
                *l_adc_function = i_channel_num;
                G_apss_ch_to_function[i_channel_num] = i_func_id;
                CNFG_DBG("apss_store_adc_channel: func_id[0x%02X] stored as 0x%02X for channel %d",
                         i_func_id, G_apss_ch_to_function[i_channel_num], *l_adc_function);
            }
            else
            {
                CMDH_TRAC_ERR("apss_store_adc_channel: Function ID is duplicated (id:0x%x, channel:%d)", i_func_id, i_channel_num);

                /* @
                 * @errortype
                 * @moduleid    DATA_STORE_APSS_DATA
                 * @reasoncode  INVALID_INPUT_DATA
                 * @userdata1   function ID
                 * @userdata2   channel number
                 * @userdata4   ERC_APSS_ADC_DUPLICATED_FAILURE
                 * @devdesc     Function ID is duplicated
                 */
                l_err = createErrl(DATA_STORE_APSS_DATA,
                                   INVALID_INPUT_DATA,
                                   ERC_APSS_ADC_DUPLICATED_FAILURE,
                                   ERRL_SEV_UNRECOVERABLE,
                                   NULL,
                                   DEFAULT_TRACE_SIZE,
                                   (uint32_t)i_func_id,
                                   (uint32_t)i_channel_num);

                // Callout firmware
                addCalloutToErrl(l_err,
                                 ERRL_CALLOUT_TYPE_COMPONENT_ID,
                                 ERRL_COMPONENT_ID_FIRMWARE,
                                 ERRL_CALLOUT_PRIORITY_HIGH);
            }
        }
        else if (l_gpu_volt_conflict)
        {
            CMDH_TRAC_ERR("apss_store_adc_channel: GPU has conflicting voltage function ids (0x%02X)", i_func_id);
            /* @
             * @errortype
             * @moduleid    DATA_STORE_APSS_DATA
             * @reasoncode  INVALID_INPUT_DATA
             * @userdata1   function ID
             * @userdata2   channel number
             * @userdata4   ERC_APSS_GPU_VOLTAGE_CONFLICT
             * @devdesc     Function ID conflict for GPU voltage
             */
            l_err = createErrl(DATA_STORE_APSS_DATA,
                               INVALID_INPUT_DATA,
                               ERC_APSS_GPU_VOLTAGE_CONFLICT,
                               ERRL_SEV_UNRECOVERABLE,
                               NULL,
                               DEFAULT_TRACE_SIZE,
                               (uint32_t)i_func_id,
                               (uint32_t)i_channel_num);

            // Callout firmware
            addCalloutToErrl(l_err,
                             ERRL_CALLOUT_TYPE_COMPONENT_ID,
                             ERRL_COMPONENT_ID_FIRMWARE,
                             ERRL_CALLOUT_PRIORITY_HIGH);
        }
    }

    return l_err;
}

// Function Specification
//
// Name:  apss_store_ipmi_sensor_id
//
// Description: Writes the given ipmi sensor ID provided by tmgt to the
//              associated power sensor.
//
// End Function Specification
void apss_store_ipmi_sensor_id(const uint16_t i_channel, const apss_cfg_adc_v20_t *i_adc)
{
    // Get current processor id.
    uint8_t l_proc  = G_pbax_id.chip_id;

    switch (i_adc->assignment)
    {
        case ADC_RESERVED:
            // Do nothing; given channel is not utilized.
            break;
        case ADC_MEMORY_PROC_0:
        case ADC_MEMORY_PROC_1:
        case ADC_MEMORY_PROC_2:
        case ADC_MEMORY_PROC_3:
            if (l_proc == (i_adc->assignment - ADC_MEMORY_PROC_0))
            {
                AMECSENSOR_PTR(PWRMEM)->ipmi_sid = i_adc->ipmisensorId;
            }
            break;

        case ADC_IO_A:
        case ADC_IO_B:
        case ADC_IO_C:
        case ADC_FANS_A:
        case ADC_FANS_B:
        case ADC_STORAGE_A:
        case ADC_STORAGE_B:
            //None
            break;

        case ADC_12V_SENSE:
        case ADC_VOLT_SENSE_2:
            //None
            break;

        case ADC_GND_REMOTE_SENSE:
            //None
            break;

        case ADC_TOTAL_SYS_CURRENT:
        case ADC_TOTAL_SYS_CURRENT_2:
            //None
            break;

        case ADC_MEM_CACHE:
            //None
            break;

        case ADC_12V_STANDBY_CURRENT:
            //None
            break;

        case ADC_GPU_0_0:
        case ADC_GPU_0_1:
        case ADC_GPU_0_2:
        case ADC_GPU_VOLT2_0_0:
        case ADC_GPU_VOLT2_0_1:
            if((i_adc->ipmisensorId != 0) && (l_proc == 0))
            {
                AMECSENSOR_PTR(PWRGPU)->ipmi_sid = i_adc->ipmisensorId;
            }
            break;

        case ADC_GPU_1_0:
        case ADC_GPU_1_1:
        case ADC_GPU_1_2:
        case ADC_GPU_VOLT2_1_0:
        case ADC_GPU_VOLT2_1_1:
            if((i_adc->ipmisensorId != 0) && (l_proc == 1))
            {
                AMECSENSOR_PTR(PWRGPU)->ipmi_sid = i_adc->ipmisensorId;
            }
            break;

        default:
            break;
    }

    //Write sensor ID to channel sensors.  If the assignment(function id) is 0, that means
    //the channel is not being utilized.
    if ((i_channel < MAX_APSS_ADC_CHANNELS) && (i_adc->assignment != ADC_RESERVED))
    {
        if ((i_adc->ipmisensorId == 0) && (G_occ_interrupt_type != FSP_SUPPORTED_OCC))
        {
            // Sensor IDs are not required and only used for BMC based systems
            CMDH_TRAC_INFO("apss_store_ipmi_sensor_id: No Sensor ID for channel %i.",i_channel);
            //We need to generate a generic sensor ID if we want channels with functionIDs but
            //no sensor IDs to be reported in the poll command.
        }

        //Only store sensor ids for power sensors.  voltage and gnd remote sensors do not report power used.
        if ((i_adc->assignment != ADC_12V_SENSE) &&
            (i_adc->assignment != ADC_GND_REMOTE_SENSE) &&
            (i_adc->assignment != ADC_12V_STANDBY_CURRENT) &&
            (i_adc->assignment != ADC_VOLT_SENSE_2))
        {
            AMECSENSOR_PTR(PWRAPSSCH0 + i_channel)->ipmi_sid = i_adc->ipmisensorId;
            CNFG_DBG("apss_store_ipmi_sensor_id: SID[0x%08X] stored as 0x%08X for channel %d",
                     i_adc->ipmisensorId, AMECSENSOR_PTR(PWRAPSSCH0 + i_channel)->ipmi_sid, i_channel);
        }
    }
}

// Function Specification
//
// Name:  apss_store_gpio_pin
//
// Description: Matches the functional ID (from MRW) to the APSS GPIO pin
//
// End Function Specification
errlHndl_t apss_store_gpio_pin(const eApssGpioAssignments i_func_id, const uint8_t i_gpio_num )
{
    errlHndl_t l_err = NULL;

    // Check function ID and channel number
    if ( (i_func_id >= NUM_GPIO_ASSIGNMENT_TYPES) ||
         ( i_gpio_num >= (MAX_APSS_GPIO_PORTS*NUM_OF_APSS_PINS_PER_GPIO_PORT) ) )
    {
        CMDH_TRAC_ERR("apss_store_gpio_pin: Invalid function ID or gpio number (id:0x%x, pin:%d)", i_func_id, i_gpio_num);

        /* @
         * @errortype
         * @moduleid    DATA_STORE_APSS_DATA
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata1   function ID
         * @userdata2   gpio number
         * @userdata4   ERC_APSS_GPIO_OUT_OF_RANGE_FAILURE
         * @devdesc     Invalid function ID or gpio number
         */
        l_err = createErrl(DATA_STORE_APSS_DATA,
                           INVALID_INPUT_DATA,
                           ERC_APSS_GPIO_OUT_OF_RANGE_FAILURE,
                           ERRL_SEV_UNRECOVERABLE,
                           NULL,
                           DEFAULT_TRACE_SIZE,
                           (uint32_t)i_func_id,
                           (uint32_t)i_gpio_num);

        // Callout firmware
        addCalloutToErrl(l_err,
                         ERRL_CALLOUT_TYPE_COMPONENT_ID,
                         ERRL_COMPONENT_ID_FIRMWARE,
                         ERRL_CALLOUT_PRIORITY_HIGH);
    }
    else
    {
        uint8_t *l_gpio_function = NULL;
        switch (i_func_id)
        {
            case GPIO_RESERVED:
                // Do nothing
                break;

            case GPIO_FAN_WATCHDOG_ERROR:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.fans_watchdog_error;
                break;

            case GPIO_FAN_FULL_SPEED:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.fans_full_speed;
                break;

            case GPIO_FAN_ERROR:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.fans_error;
                break;

            case GPIO_FAN_RESERVED:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.fans_reserved;
                 break;

            case GPIO_VR_HOT_MEM_PROC_0:
            case GPIO_VR_HOT_MEM_PROC_1:
            case GPIO_VR_HOT_MEM_PROC_2:
            case GPIO_VR_HOT_MEM_PROC_3:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.vr_fan[i_func_id-GPIO_VR_HOT_MEM_PROC_0];
                break;
            case GPIO_CENT_EN_VCACHE0:
            case GPIO_CENT_EN_VCACHE1:
            case GPIO_CENT_EN_VCACHE2:
            case GPIO_CENT_EN_VCACHE3:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.cent_en_vcache[i_func_id-GPIO_CENT_EN_VCACHE0];
                break;

            case CME_THROTTLE_N:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.cme_throttle_n;
                break;

            case GND_OC_N:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.gnd_oc_n;
                break;

            case DOM_A_OC_LATCH:
            case DOM_B_OC_LATCH:
            case DOM_C_OC_LATCH:
            case DOM_D_OC_LATCH:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.dom_oc_latch[i_func_id-DOM_A_OC_LATCH];
                break;

            case PSU_FAN_DISABLE_N:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.psu_fan_disable;
                break;

            case GPU_0_0_PRSNT_N:
            case GPU_0_1_PRSNT_N:
            case GPU_0_2_PRSNT_N:
            case GPU_1_0_PRSNT_N:
            case GPU_1_1_PRSNT_N:
            case GPU_1_2_PRSNT_N:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.gpu[i_func_id-GPU_0_0_PRSNT_N];
                break;

            case NVDIMM_EPOW_N:
                l_gpio_function = &G_sysConfigData.apss_gpio_map.nvdimm_epow;
                break;

            default:
                // It should never happen
                CMDH_TRAC_ERR("apss_store_gpio_pin: Invalid function ID: 0x%x", i_func_id);
                break;
        }

        if(NULL != l_gpio_function)
        {
            // Check if this function already have ADC channel assigned
            if( SYSCFG_INVALID_PIN == *l_gpio_function)
            {
                *l_gpio_function = i_gpio_num;
                CNFG_DBG("apss_store_gpio_pin: func_id[0x%02X] is mapped to pin 0x%02X", i_func_id, *l_gpio_function);
            }
            else
            {
                CMDH_TRAC_ERR("apss_store_gpio_pin: Function ID is duplicated (id:0x%x, pin:%d)", i_func_id, i_gpio_num);

                /* @
                 * @errortype
                 * @moduleid    DATA_STORE_APSS_DATA
                 * @reasoncode  INVALID_INPUT_DATA
                 * @userdata1   function ID
                 * @userdata2   gpio number
                 * @userdata4   ERC_APSS_GPIO_DUPLICATED_FAILURE
                 * @devdesc     Invalid function ID or channel number
                 */
                l_err = createErrl(DATA_STORE_APSS_DATA,
                                   INVALID_INPUT_DATA,
                                   ERC_APSS_GPIO_DUPLICATED_FAILURE,
                                   ERRL_SEV_UNRECOVERABLE,
                                   NULL,
                                   DEFAULT_TRACE_SIZE,
                                   (uint32_t)i_func_id,
                                   (uint32_t)i_gpio_num);

                // Callout firmware
                addCalloutToErrl(l_err,
                                 ERRL_CALLOUT_TYPE_COMPONENT_ID,
                                 ERRL_COMPONENT_ID_FIRMWARE,
                                 ERRL_CALLOUT_PRIORITY_HIGH);
            }
        }
    }

    return l_err;
}


// Function Specification
//
// Name:  data_store_apss_config_v20
//
// Description: Configuration required for APSS
//
// End Function Specification
errlHndl_t data_store_apss_config_v20(const cmdh_apss_config_v20_t * i_cmd_ptr,
                                            cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t              l_err = NULL;
    uint16_t l_channel = 0, l_port = 0, l_pin = 0, l_num_channels = MAX_APSS_ADC_CHANNELS;

    // ADC channels info
    if(G_pwr_reading_type == PWR_READING_TYPE_2_CHANNEL)
       l_num_channels = 2;
    else
    {
       // This must be APSS type, however it is possible that xml and/or HTMGT doesn't support
       // indication of no APSS so we will default to none and then set to APSS if valid channel found
       G_pwr_reading_type = PWR_READING_TYPE_NONE;
    }

    bool l_found_volt2_sense = FALSE;
    for(l_channel=0;(l_channel < l_num_channels) && (NULL == l_err);l_channel++)
    {
        G_sysConfigData.apss_cal[l_channel].gnd_select = i_cmd_ptr->adc[l_channel].gnd_select;
        G_sysConfigData.apss_cal[l_channel].gain       = i_cmd_ptr->adc[l_channel].gain;
        G_sysConfigData.apss_cal[l_channel].offset     = i_cmd_ptr->adc[l_channel].offset;

        // Assign the ADC channels
        l_err = apss_store_adc_channel(i_cmd_ptr->adc[l_channel].assignment, l_channel);
        if (l_err == NULL)
        {
            if (i_cmd_ptr->adc[l_channel].assignment == ADC_VOLT_SENSE_2)
            {
                l_found_volt2_sense = TRUE;
            }

            //Write sensor IDs to the appropriate powr sensors.
            apss_store_ipmi_sensor_id(l_channel, &(i_cmd_ptr->adc[l_channel]));

            // APSS is present if there is at least one channel with a valid assignment
            if( (i_cmd_ptr->adc[l_channel].assignment != ADC_RESERVED) &&
                (G_pwr_reading_type == PWR_READING_TYPE_NONE) )
            {
                G_pwr_reading_type = PWR_READING_TYPE_APSS;
            }
        }
        CNFG_DBG("data_store_apss_config_v20: Channel %d: FuncID[0x%02X] SID[0x%08X]",
                 l_channel, i_cmd_ptr->adc[l_channel].assignment, i_cmd_ptr->adc[l_channel].ipmisensorId);
        CNFG_DBG("data_store_apss_config_v20: Channel %d: GND[0x%02X] Gain[0x%08X] Offst[0x%08X]",
                 l_channel, G_sysConfigData.apss_cal[l_channel].gnd_select, G_sysConfigData.apss_cal[l_channel].gain,
                 G_sysConfigData.apss_cal[l_channel].offset);
    }

    if ((NULL == l_err) && G_found_volt2 && (!l_found_volt2_sense))
    {
        CMDH_TRAC_ERR("data_store_apss_config_v20: Found GPU using 2nd voltage but no ADC_VOLT_SENSE_2 supplied");
        /* @
         * @errortype
         * @moduleid    DATA_STORE_APSS_DATA
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata4   ERC_APSS_MISSING_ADC_VOLT_SENSE_2
         * @devdesc     ADC_VOLT_SENSE_2 was not provided
         */
        l_err = createErrl(DATA_STORE_APSS_DATA,
                           INVALID_INPUT_DATA,
                           ERC_APSS_MISSING_ADC_VOLT_SENSE_2,
                           ERRL_SEV_UNRECOVERABLE,
                           NULL,
                           DEFAULT_TRACE_SIZE,
                           0,
                           0);
        // Callout firmware
        addCalloutToErrl(l_err,
                         ERRL_CALLOUT_TYPE_COMPONENT_ID,
                         ERRL_COMPONENT_ID_FIRMWARE,
                         ERRL_CALLOUT_PRIORITY_HIGH);
    }

    if( (NULL == l_err) && (G_pwr_reading_type == PWR_READING_TYPE_APSS) ) // only APSS has GPIO config
    {

        // GPIO Ports
        for(l_port=0;(l_port < MAX_APSS_GPIO_PORTS) && (NULL == l_err);l_port++)
        {
            // GPIO mode
            G_sysConfigData.apssGpioPortsMode[l_port] = i_cmd_ptr->gpio[l_port].mode;

            // For each pin
            for(l_pin=0; (l_pin < NUM_OF_APSS_PINS_PER_GPIO_PORT) && (NULL == l_err);l_pin++)
            {
                // Assign the GPIO number
                l_err = apss_store_gpio_pin( i_cmd_ptr->gpio[l_port].assignment[l_pin],
                                             (l_port*NUM_OF_APSS_PINS_PER_GPIO_PORT)+l_pin);
            }

        }
    }

    return l_err;
}

// Function Specification
//
// Name:  data_store_apss_config
//
// Description: Configuration required for APSS
//
// End Function Specification
errlHndl_t data_store_apss_config(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                        cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t              l_err = NULL;
    bool                    l_invalid_data = FALSE;
    cmdh_apss_config_v20_t *l_cmd_ptr = (cmdh_apss_config_v20_t *)i_cmd_ptr;
    uint16_t                l_data_length = CMDH_DATALEN_FIELD_UINT16(l_cmd_ptr); //Command length
    uint32_t                l_v20_data_sz = sizeof(cmdh_apss_config_v20_t) - sizeof(cmdh_fsp_cmd_header_t);


    // Set to default values
    memset(&G_sysConfigData.apss_adc_map, SYSCFG_INVALID_ADC_CHAN, sizeof(G_sysConfigData.apss_adc_map));
    memset(&G_sysConfigData.apss_gpio_map, SYSCFG_INVALID_PIN, sizeof(G_sysConfigData.apss_gpio_map));
    memset(G_gpu_volt_type, 0, sizeof(G_gpu_volt_type));
    G_found_volt2 = FALSE;

    // only version 0x20 supported and data length must be at least 4
    if( (l_cmd_ptr->version != DATA_APSS_VERSION20) || (l_data_length < 4))
    {
       l_invalid_data = TRUE;
    }
    else
    {
       // verify the data length and process the data based on power reading type
       // PWR_READING_TYPE_APSS --> full size of structure
       // PWR_READING_TYPE_2_CHANNEL --> 0x20 bytes (2 ADC channels, no GPIOs)
       // PWR_READING_TYPE_NONE --> 4 bytes (no channel or GPIO data)

       G_pwr_reading_type = l_cmd_ptr->type;

       if( ( (G_pwr_reading_type == PWR_READING_TYPE_2_CHANNEL) && (l_data_length == 0x20) ) ||
                ( (G_pwr_reading_type == PWR_READING_TYPE_APSS) && (l_v20_data_sz == l_data_length) ) )
       {
          l_err = data_store_apss_config_v20(l_cmd_ptr, o_rsp_ptr);
       }
       else if( (G_pwr_reading_type != PWR_READING_TYPE_NONE) || (l_data_length != 4) )
       {
          l_invalid_data = TRUE;
       }
    }

    if(l_invalid_data)
    {
        G_pwr_reading_type = PWR_READING_TYPE_NONE;
        CMDH_TRAC_ERR("data_store_apss_config: Invalid APSS Config Data packet. Given Version:0x%02X length:0x%04X",
                 l_cmd_ptr->version, l_data_length);

        /* @
         * @errortype
         * @moduleid    DATA_STORE_APSS_DATA
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata1   data size
         * @userdata2   packet version
         * @userdata4   OCC_NO_EXTENDED_RC
         * @devdesc     OCC recieved an invalid data packet from the FSP
         */
        cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
    }
    else if(NULL == l_err)
    {
        // Change Data Request Mask to indicate we got this data
        G_data_cnfg->data_mask |= DATA_MASK_APSS_CONFIG;
        CMDH_TRAC_IMP("Got valid APSS Config data via TMGT; Pwr reading type = %d", G_pwr_reading_type);
    }

    return l_err;
}

// Function Specification
//
// Name:  data_store_avsbus_config
//
// Description: Configuration required to read power/current from AVS Bus
//
// End Function Specification
errlHndl_t data_store_avsbus_config(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                    cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t l_err = NULL;
    const uint8_t  AVSBUS_VERSION_1 = 0x01;
    const uint8_t  AVSBUS_VERSION_2 = 0x02;
    const uint16_t AVSBUS_V1_LENGTH = sizeof(cmdh_avsbus_config_t) - sizeof(cmdh_fsp_cmd_header_t);
    const uint16_t AVSBUS_V2_LENGTH = sizeof(cmdh_avsbus_v2_config_t) - sizeof(cmdh_fsp_cmd_header_t);
    bool l_invalid_data = FALSE;

    cmdh_avsbus_config_t *l_cmd_ptr = (cmdh_avsbus_config_t *)i_cmd_ptr;
    uint16_t l_data_length = CMDH_DATALEN_FIELD_UINT16(l_cmd_ptr);

    if ( ((AVSBUS_VERSION_1 == l_cmd_ptr->version) && (AVSBUS_V1_LENGTH == l_data_length)) ||
         ((AVSBUS_VERSION_2 == l_cmd_ptr->version) && (AVSBUS_V2_LENGTH == l_data_length)) )
    {
        // common code for all versions
        // Validate Vdd
        if ((l_cmd_ptr->vdd_bus == 0) || (l_cmd_ptr->vdd_bus == 1))
        {
            if ((l_cmd_ptr->vdd_rail >= 0) && (l_cmd_ptr->vdd_rail <= 15))
            {
                // may be getting Vdd from PGPE but this could be enabled with internal flag
                // for OCC to handle overflow, that checking will be done in amec_update_avsbus_sensors()
                G_avsbus_vdd_monitoring = TRUE;
                G_sysConfigData.avsbus_vdd.bus = l_cmd_ptr->vdd_bus;
                G_sysConfigData.avsbus_vdd.rail = l_cmd_ptr->vdd_rail;
                CNFG_DBG("data_store_avsbus_config: Vdd bus[%d] rail[%d]",
                         G_sysConfigData.avsbus_vdd.bus, G_sysConfigData.avsbus_vdd.rail);
            }
            else
            {
                CMDH_TRAC_ERR("data_store_avsbus_config: Invalid AVS Bus Vdd rail 0x%02X",
                              l_cmd_ptr->vdd_rail);
                l_invalid_data = TRUE;
            }
        }
        else
        {
            if (l_cmd_ptr->vdd_bus != 0xFF)
            {
                CMDH_TRAC_ERR("data_store_avsbus_config: Invalid AVS Bus Vdd bus 0x%02X",
                              l_cmd_ptr->vdd_bus);
                l_invalid_data = TRUE;
            }
            else
            {
                CMDH_TRAC_INFO("data_store_avsbus_config: Vdd will not be monitored via AVS Bus");
                G_avsbus_vdd_monitoring = FALSE;
            }
        }

        // Validate Vdn
        if ((l_cmd_ptr->vdn_bus == 0) || (l_cmd_ptr->vdn_bus == 1))
        {
            if ((l_cmd_ptr->vdn_rail >= 0) && (l_cmd_ptr->vdn_rail <= 15))
            {
                if(G_pgpe_shared_sram_V_I_readings)
                {
                    // going to be getting Vdn from PGPE and no way to enable from AVSbus
                    CMDH_TRAC_INFO("Reading Vdn from PGPE turning off Vdn monitoring");
                    G_avsbus_vdn_monitoring = FALSE;
                }

                else
                {
                    G_avsbus_vdn_monitoring = TRUE;
                    G_sysConfigData.avsbus_vdn.bus = l_cmd_ptr->vdn_bus;
                    G_sysConfigData.avsbus_vdn.rail = l_cmd_ptr->vdn_rail;
                    CNFG_DBG("data_store_avsbus_config: Vdn bus[%d] rail[%d]",
                             G_sysConfigData.avsbus_vdn.bus, G_sysConfigData.avsbus_vdn.rail);

                    if (G_avsbus_vdd_monitoring &&
                        (G_sysConfigData.avsbus_vdd.bus == G_sysConfigData.avsbus_vdn.bus))
                    {
                        CMDH_TRAC_ERR("data_store_avsbus_config: Vdd and Vdn can not use the same AVS bus");
                        l_invalid_data = TRUE;
                    }
                }
            }
            else
            {
                CMDH_TRAC_ERR("data_store_avsbus_config: Invalid AVS Bus Vdn rail 0x%02X",
                              l_cmd_ptr->vdn_rail);
                l_invalid_data = TRUE;
            }
        }
        else
        {
            if (l_cmd_ptr->vdn_bus != 0xFF)
            {
                CMDH_TRAC_ERR("data_store_avsbus_config: Invalid Vdn data (%d / %d)",
                              l_cmd_ptr->vdn_bus, l_cmd_ptr->vdn_rail);
                l_invalid_data = TRUE;
            }
            else
            {
                CMDH_TRAC_INFO("data_store_avsbus_config: Vdn will not be monitored via AVS Bus");
                G_avsbus_vdn_monitoring = FALSE;
            }
        }
    }
    else
    {
        CMDH_TRAC_ERR("data_store_avsbus_config: Invalid AVS Bus version/length (0x%02X/0x%04X))",
                      l_cmd_ptr->version, l_data_length);
        l_invalid_data = TRUE;
    }

    if( (l_invalid_data) ||
        ( !G_pgpe_shared_sram_V_I_readings && (!G_avsbus_vdd_monitoring || !G_avsbus_vdn_monitoring) ) )
    {
        cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
        G_avsbus_vdd_monitoring = FALSE;
        G_avsbus_vdn_monitoring = FALSE;

        CMDH_TRAC_ERR("WOF Disabled! Invalid VDD/VDN");
        // If cannot use vdd/vdn, cannot run wof algorithm.
        set_clear_wof_disabled( SET,
                                WOF_RC_INVALID_VDD_VDN,
                                ERC_WOF_INVALID_VDD_VDN );

    }
    else
    {
        G_sysConfigData.proc_power_adder = l_cmd_ptr->proc_power_adder;

        // Vdd Current roll over workaround is enabled if we received Version 2
        if(AVSBUS_VERSION_2 == l_cmd_ptr->version)
        {
            cmdh_avsbus_v2_config_t *l_cmd_ptr_v2 = (cmdh_avsbus_v2_config_t *)i_cmd_ptr;
            G_sysConfigData.vdd_current_rollover_10mA = (uint32_t)l_cmd_ptr_v2->vdd_current_rollover;
            G_sysConfigData.vdd_max_current_10mA = (uint32_t)l_cmd_ptr_v2->vdd_max_current;
        }
        else
        {
            // Vdd Current roll over workaround is disabled
            G_sysConfigData.vdd_current_rollover_10mA = 0xFFFF;  // no rollover
            G_sysConfigData.vdd_max_current_10mA = 0xFFFF;
        }

        CMDH_TRAC_INFO("data_store_avsbus_config: Vdd Current roll over at 0x%08X max 0x%08X",
                        G_sysConfigData.vdd_current_rollover_10mA, G_sysConfigData.vdd_max_current_10mA);

        // We can use vdd/vdn. Clear NO_VDD_VDN_READ mask
        set_clear_wof_disabled( CLEAR,
                                WOF_RC_INVALID_VDD_VDN,
                                ERC_WOF_INVALID_VDD_VDN );
        avsbus_init();
    }

    if(!l_err)
    {
        // If there were no errors, indicate that we got this data
        G_data_cnfg->data_mask |= DATA_MASK_AVSBUS_CONFIG;
        CMDH_TRAC_IMP("data_store_avsbus_config: Got valid AVS Bus data packet");
    }

    return l_err;

} // end data_store_avsbus_config()

// Function Specification
//
// Name:  data_store_gpu
//
// Description: GPU information
//
// End Function Specification
errlHndl_t data_store_gpu(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t l_err = NULL;
    uint8_t i = 0;
    uint8_t l_gpu_num = 0;
    cmdh_gpu_config_v2_t *l_cmd_ptr = (cmdh_gpu_config_v2_t *)i_cmd_ptr;
    uint16_t l_data_length = CMDH_DATALEN_FIELD_UINT16((&l_cmd_ptr->header));
    uint16_t l_gpu_data_length = 0;
    uint8_t  l_present_bit_mask = 0;  // Bit mask for present GPUs behind this OCC

    // parse data based on version. Version byte is located at same offset for all versions
    if(l_cmd_ptr->header.version == 1)
    {
        cmdh_gpu_config_t *l_cmd_ptr_v1 = (cmdh_gpu_config_t *)i_cmd_ptr;
        l_data_length = CMDH_DATALEN_FIELD_UINT16(l_cmd_ptr_v1);
        l_gpu_data_length = sizeof(cmdh_gpu_config_t) - sizeof(cmdh_fsp_cmd_header_t);
        if(l_gpu_data_length == l_data_length)
        {
            G_sysConfigData.total_non_gpu_max_pwr_watts = l_cmd_ptr_v1->total_non_gpu_max_pwr_watts;
            G_sysConfigData.total_proc_mem_pwr_drop_watts = l_cmd_ptr_v1->total_proc_mem_pwr_drop_watts;

            AMECSENSOR_PTR(TEMPGPU0)->ipmi_sid = l_cmd_ptr_v1->gpu0_temp_sid;
            AMECSENSOR_PTR(TEMPGPU0MEM)->ipmi_sid = l_cmd_ptr_v1->gpu0_mem_temp_sid;
            G_sysConfigData.gpu_sensor_ids[0]  = l_cmd_ptr_v1->gpu0_sid;

            AMECSENSOR_PTR(TEMPGPU1)->ipmi_sid = l_cmd_ptr_v1->gpu1_temp_sid;
            AMECSENSOR_PTR(TEMPGPU1MEM)->ipmi_sid = l_cmd_ptr_v1->gpu1_mem_temp_sid;
            G_sysConfigData.gpu_sensor_ids[1]  = l_cmd_ptr_v1->gpu1_sid;

            AMECSENSOR_PTR(TEMPGPU2)->ipmi_sid = l_cmd_ptr_v1->gpu2_temp_sid;
            AMECSENSOR_PTR(TEMPGPU2MEM)->ipmi_sid = l_cmd_ptr_v1->gpu2_mem_temp_sid;
            G_sysConfigData.gpu_sensor_ids[2]  = l_cmd_ptr_v1->gpu2_sid;

            G_data_cnfg->data_mask |= DATA_MASK_GPU;
            CMDH_TRAC_IMP("data_store_gpu: Got valid GPU data packet");
        }
        else
        {
            CMDH_TRAC_ERR("data_store_gpu: GPU version 1 invalid length Expected: 0x%04X  Received: 0x%04X",
                          l_gpu_data_length, l_data_length);
            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_CMD_LEN, &l_err);
        }
    } // if version 1
    else if(l_cmd_ptr->header.version == 2)
    {
        l_gpu_data_length = sizeof(cmdh_gpu_cfg_header_v2_t) - sizeof(cmdh_fsp_cmd_header_t);
        l_gpu_data_length += (l_cmd_ptr->header.num_data_sets * sizeof(cmdh_gpu_set_v2_t));

        if(l_gpu_data_length == l_data_length)
        {
            if( (l_cmd_ptr->header.gpu_i2c_engine == PIB_I2C_ENGINE_C) &&
                ((l_cmd_ptr->header.gpu_i2c_bus_voltage == 0) || (l_cmd_ptr->header.gpu_i2c_bus_voltage == 18)) )
            {
                G_sysConfigData.gpu_i2c_engine = l_cmd_ptr->header.gpu_i2c_engine;
                G_sysConfigData.gpu_i2c_bus_voltage = l_cmd_ptr->header.gpu_i2c_bus_voltage;
                CMDH_TRAC_IMP("data_store_gpu: I2C engine = 0x%02X I2C bus voltage = %d deci volts",
                               G_sysConfigData.gpu_i2c_engine, G_sysConfigData.gpu_i2c_bus_voltage);

                G_sysConfigData.total_non_gpu_max_pwr_watts = l_cmd_ptr->header.total_non_gpu_max_pwr_watts;
                G_sysConfigData.total_proc_mem_pwr_drop_watts = l_cmd_ptr->header.total_proc_mem_pwr_drop_watts;

                // Store the individual GPU data
                for(i=0; i<l_cmd_ptr->header.num_data_sets; i++)
                {
                    // Get the GPU number data is for
                    l_gpu_num = l_cmd_ptr->gpu_data[i].gpu_num;

                    if( (l_gpu_num >= 0) && (l_gpu_num < MAX_NUM_GPU_PER_DOMAIN) )
                    {
                        G_sysConfigData.gpu_i2c_info[l_gpu_num].port = l_cmd_ptr->gpu_data[i].i2c_port;
                        G_sysConfigData.gpu_i2c_info[l_gpu_num].address = l_cmd_ptr->gpu_data[i].i2c_addr;

                        // if port or i2c address is 0xFF the GPU will not be monitored
                        if( (G_sysConfigData.gpu_i2c_info[l_gpu_num].port != 0xFF) &&
                           (G_sysConfigData.gpu_i2c_info[l_gpu_num].address != 0xFF) )
                        {
                            CMDH_TRAC_IMP("data_store_gpu: GPU%d I2C port = 0x%02X address = 0x%02X", l_gpu_num,
                                           G_sysConfigData.gpu_i2c_info[l_gpu_num].port,
                                           G_sysConfigData.gpu_i2c_info[l_gpu_num].address);

                            AMECSENSOR_PTR(TEMPGPU0 + l_gpu_num)->ipmi_sid = l_cmd_ptr->gpu_data[i].gpu_temp_sid;
                            AMECSENSOR_PTR(TEMPGPU0MEM + l_gpu_num)->ipmi_sid = l_cmd_ptr->gpu_data[i].gpu_mem_temp_sid;
                            G_sysConfigData.gpu_sensor_ids[l_gpu_num]  = l_cmd_ptr->gpu_data[i].gpu_sid;

                            // If there is no APSS this data is giving GPU presence, mark this GPU as present
                            if(G_pwr_reading_type != PWR_READING_TYPE_APSS)
                            {
                                l_present_bit_mask |= (0x01 << l_gpu_num);
                            }
                        }
                        else
                        {
                            CMDH_TRAC_ERR("data_store_gpu: GPU%d NOT monitored Invalid I2C port = 0x%02X I2C address = 0x%02X",
                                           l_gpu_num, G_sysConfigData.gpu_i2c_info[l_gpu_num].port,
                                           G_sysConfigData.gpu_i2c_info[l_gpu_num].address);
                        }
                    }
                    else
                    {
                        // We got an invalid GPU number
                        CMDH_TRAC_ERR("data_store_gpu: Received invalid GPU number %d", l_gpu_num);
                        cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                        break;
                    }
                } // for each GPU data set

                // if there is no APSS for GPU presence then this data is the GPU presence
                if(G_pwr_reading_type != PWR_READING_TYPE_APSS)
                {
                    if(l_err == NULL)
                    {
                        G_first_num_gpus_sys = l_cmd_ptr->header.total_num_gpus_system;
                        G_curr_num_gpus_sys = G_first_num_gpus_sys;
                        G_first_proc_gpu_config = l_present_bit_mask;
                        G_curr_proc_gpu_config = G_first_proc_gpu_config;
                        G_gpu_config_done = TRUE;

                        if(G_first_proc_gpu_config)
                        {
                            // GPUs are present enable monitoring
                            G_gpu_monitoring_allowed = TRUE;
                            G_task_table[TASK_ID_GPU_SM].flags = GPU_RTL_FLAGS;
                        }

                        CMDH_TRAC_IMP("data_store_gpu: This OCC GPUs present mask = 0x%02X Total number GPUs present in system = %d",
                                       G_first_proc_gpu_config, G_first_num_gpus_sys);

                        G_data_cnfg->data_mask |= DATA_MASK_GPU;
                        CMDH_TRAC_IMP("data_store_gpu: Got valid GPU data packet");
                    }
                    else
                    {
                        G_first_num_gpus_sys = 0;
                        G_curr_num_gpus_sys = 0;
                        G_first_proc_gpu_config = 0;
                        G_curr_proc_gpu_config = 0;
                        G_gpu_config_done = FALSE;
                    }
                }
                else if(l_err == NULL)
                {
                    G_data_cnfg->data_mask |= DATA_MASK_GPU;
                    CMDH_TRAC_IMP("data_store_gpu: Got valid GPU data packet");
                }
            }  // valid i2c engine and voltage
            else
            {
                // We got an invalid I2C Engine and/or voltage
                CMDH_TRAC_ERR("data_store_gpu: Received invalid I2C Engine/Voltage 0x%02X / %d",
                               l_cmd_ptr->header.gpu_i2c_engine, l_cmd_ptr->header.gpu_i2c_bus_voltage);
                cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
            }
        } // if length valid
        else
        {
            CMDH_TRAC_ERR("data_store_gpu: GPU version 2 invalid length Expected: 0x%04X  Received: 0x%04X",
                          l_gpu_data_length, l_data_length);
            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_CMD_LEN, &l_err);
        }
    } //else if version 2
    else
    {
        CMDH_TRAC_ERR("data_store_gpu: Invalid GPU version 0x%02X", l_cmd_ptr->header.version);
        cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
    }

    return l_err;

} // end data_store_gpu()

// Function Specification
//
// Name:   data_store_role
//
// Description: Tell the OCC if it should run as a master or slave.  HTMGT knows
//              which OCC is the master from the MRW.  To be the master OCC
//              requires a connection to the APSS.  Until an OCC is told a role
//              it should default to running as a slave
//
// End Function Specification
errlHndl_t data_store_role(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                 cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t l_errlHndl = NULL;
    uint8_t    l_new_role = OCC_SLAVE;
    uint8_t    l_old_role = G_occ_role;
    ERRL_RC    l_rc       = ERRL_RC_SUCCESS;

    // Cast the command to the struct for this format
    cmdh_set_role_t * l_cmd_ptr = (cmdh_set_role_t *)i_cmd_ptr;

    // Set the OCC role
    l_new_role = l_cmd_ptr->role;

    // Must be in standby state before we can change roles
    if ( CURRENT_STATE() == OCC_STATE_STANDBY )
    {
        if( OCC_MASTER == l_new_role )
        {
            G_occ_role = OCC_MASTER;

            // Run master initializations if we just became master
            extern void  master_occ_init(void);
            master_occ_init();

            // Turn off anything slave related since we are a master
            rtl_clr_run_mask_deferred(RTL_FLAG_NOTMSTR);
            rtl_set_run_mask_deferred(RTL_FLAG_MSTR);

            // Allow APSS tasks to run on OCC master if APSS is present
            if(G_pwr_reading_type == PWR_READING_TYPE_APSS)
               rtl_clr_run_mask_deferred(RTL_FLAG_APSS_NOT_INITD);

            CMDH_TRAC_IMP("data_store_role: OCC Role set to Master via TMGT");

            // Change Data Request Mask to indicate we got this data
            G_data_cnfg->data_mask |= DATA_MASK_SET_ROLE;

            // Make sure return code is success
            l_rc = ERRL_RC_SUCCESS;
        }
        else if( (OCC_SLAVE == l_new_role ) ||
                 (OCC_BACKUP_MASTER == l_new_role))
        {
            if(OCC_MASTER == l_old_role)
            {
                G_occ_role = OCC_SLAVE;

                // Turn off anything master related since we are a slave
                rtl_clr_run_mask_deferred(RTL_FLAG_MSTR);
                rtl_set_run_mask_deferred(RTL_FLAG_NOTMSTR);

                // Slave code will automatically recognize we no longer
                // have a master.
            }

            // If this is a backup master occ, we need to be checking the APSS health
            if(OCC_BACKUP_MASTER == l_new_role)
            {
                l_errlHndl = initialize_apss();

                // Initialize APSS communication on the backup OCC (retries internally)
                if( NULL != l_errlHndl )
                {
                    // Don't request due to a backup apss failure. Just log the error.
                    CMDH_TRAC_ERR("data_store_role: APSS init applet returned error: l_rc: 0x%x", l_errlHndl->iv_reasonCode);
                    commitErrl(&l_errlHndl);
                }

                // Allow APSS tasks to run on OCC backup
                if(G_pwr_reading_type == PWR_READING_TYPE_APSS)
                   rtl_clr_run_mask_deferred(RTL_FLAG_APSS_NOT_INITD);
                CMDH_TRAC_IMP("data_store_role: OCC Role set to Backup Master via TMGT");
            }
            else
            {
                // NOTE: slave initialization is done on all
                //       OCC's during OCC initialization.
                CMDH_TRAC_IMP("data_store_role: OCC Role set to Slave via TMGT");
            }

            // Change Data Request Mask to indicate we got this data
            G_data_cnfg->data_mask |= DATA_MASK_SET_ROLE;

            // Make sure return code is success
            l_rc = ERRL_RC_SUCCESS;

        }
        else
        {
            CMDH_TRAC_ERR("data_store_role: OCC Role from FSP is not recognized by OCC. role = %d", l_new_role);

            l_rc = ERRL_RC_INVALID_DATA;

            /* @
             * @errortype
             * @moduleid    DATA_STORE_GENERIC_DATA
             * @reasoncode  INVALID_INPUT_DATA
             * @userdata1   Reason input data failed
             * @userdata2   Requested role
             * @userdata4   ERC_INVALID_INPUT_DATA
             * @devdesc     Bad config data passed to OCC
             */
            l_errlHndl = createErrl(DATA_STORE_GENERIC_DATA,      //modId
                                    INVALID_INPUT_DATA,           //reasoncode
                                    ERC_INVALID_INPUT_DATA,       //Extended reason code
                                    ERRL_SEV_INFORMATIONAL,       //Severity
                                    NULL,                         //Trace Buf
                                    DEFAULT_TRACE_SIZE,           //Trace Size
                                    l_rc,                         //userdata1
                                    l_new_role);                  //userdata2
        }
    }
    else
    {
        CMDH_TRAC_ERR("data_store_role: Role change requested while OCC is not in standby state. role=%d, state=%d",
                      l_new_role, CURRENT_STATE());

        l_rc = ERRL_RC_INVALID_STATE;

        /* @
         * @errortype
         * @moduleid    DATA_STORE_GENERIC_DATA
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata1   Reason input data failed
         * @userdata2   current state
         * @userdata4   OCC_NO_EXTENDED_RC
         * @devdesc     Bad config data passed to OCC
         */
        l_errlHndl = createErrl(DATA_STORE_GENERIC_DATA,  //modId
                INVALID_INPUT_DATA,                       //reasoncode
                OCC_NO_EXTENDED_RC,                       //Extended reason code
                ERRL_SEV_INFORMATIONAL,                   //Severity
                NULL,                                     //Trace Buf
                DEFAULT_TRACE_SIZE,                       //Trace Size
                l_rc,                                     //userdata1
                CURRENT_STATE());                         //userdata2
    }

    if( ERRL_RC_SUCCESS != l_rc  )
    {
        // Send back an error response to TMGT
        cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, l_rc, &l_errlHndl);
    }

    return l_errlHndl;
}

// Function Specification
//
// Name:  data_store_power_cap
//
// Description: This function should only be run by MASTER OCC when
//              power cap data is received from TMGT.
//
// End Function Specification
errlHndl_t data_store_power_cap(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                        cmdh_fsp_rsp_t * i_rsp_ptr)
{
    errlHndl_t                      l_err = NULL;

    // Cast the command to the struct for this format
    cmdh_pcap_config_t * l_cmd_ptr = (cmdh_pcap_config_t *)i_cmd_ptr;
    uint16_t                        l_data_length = 0;
    uint32_t                        l_pcap_data_sz = 0;
    bool                            l_invalid_input = TRUE; //Assume bad input

    l_data_length = CONVERT_UINT8_ARRAY_UINT16(l_cmd_ptr->data_length[0], l_cmd_ptr->data_length[1]);

    // Check version and length
    if(l_cmd_ptr->version == DATA_PCAP_VERSION_20)
    {
        l_pcap_data_sz = sizeof(cmdh_pcap_config_t) - sizeof(cmdh_fsp_cmd_header_t);
        if(l_pcap_data_sz == l_data_length)
        {
            l_invalid_input = FALSE;
        }
    }

    // This is the master OCC and packet data length and version are valid?
    // TMGT should never send this packet to a slave OCC.
    // if the OCC is not master, OR
    // if the version doesn't equal what we expect (0x20), OR
    // if the expected data length does not agree with the actual data length...
    if((OCC_MASTER != G_occ_role) || l_invalid_input)
    {
        CMDH_TRAC_ERR("data_store_power_cap: Invalid Pcap Data packet! OCC_role[%d] Version[0x%02X] Data_size[%u]",
                 G_occ_role, l_cmd_ptr->version, l_data_length);

        /* @
         * @errortype
         * @moduleid    DATA_STORE_PCAP_DATA
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata1   data size
         * @userdata2   packet version (Bytes 0-1) / role (Bytes 2-3)
         * @userdata4   OCC_NO_EXTENDED_RC
         * @devdesc     OCC recieved an invalid data packet from the FSP or OCC role is not MASTER
         */
        l_err = createErrl(DATA_STORE_PCAP_DATA,
                           INVALID_INPUT_DATA,
                           OCC_NO_EXTENDED_RC,
                           ERRL_SEV_UNRECOVERABLE,
                           NULL,
                           0,
                           l_data_length,
                           ((uint32_t)l_cmd_ptr->version)<<16 | G_occ_role);

        // Callout firmware
        addCalloutToErrl(l_err,
                         ERRL_CALLOUT_TYPE_COMPONENT_ID,
                         ERRL_COMPONENT_ID_FIRMWARE,
                         ERRL_CALLOUT_PRIORITY_HIGH);

    }
    else
    {
        if(l_cmd_ptr->version == DATA_SYS_VERSION_20)
        {
            // Copy power cap limits data into G_master_pcap_data
            cmdh_pcap_config_t * l_cmd2_ptr = (cmdh_pcap_config_t *)i_cmd_ptr;
            G_master_pcap_data.soft_min_pcap   = l_cmd2_ptr->pcap_config.soft_min_pcap;
            G_master_pcap_data.hard_min_pcap   = l_cmd2_ptr->pcap_config.hard_min_pcap;
            G_master_pcap_data.max_pcap        = l_cmd2_ptr->pcap_config.sys_max_pcap;
            G_master_pcap_data.oversub_pcap    = l_cmd2_ptr->pcap_config.qpd_pcap;
            G_master_pcap_data.system_pcap     = l_cmd2_ptr->pcap_config.sys_max_pcap;

            // NOTE: The customer power cap will be set via a separate command
            // from BMC/(H)TMGT or OPAL.
        }

        // The last byte in G_master_pcap_data is a counter that needs to be incremented.
        // It tells the master and slave code that there is new
        // pcap data.  This should not be incremented until
        // after the packet data has been copied into G_master_pcap_data.
        G_master_pcap_data.pcap_data_count++;

        // Change Data Request Mask to indicate we got the data
        // G_data_cnfg->data_mask |= DATA_MASK_PCAP_PRESENT;
        // will update data mask when slave code acquires data
        CMDH_TRAC_IMP("data store pcap: Got valid PCAP Config data via TMGT. Count:%i, Data Cfg mask[%x]",G_master_pcap_data.pcap_data_count, G_data_cnfg->data_mask);
    }
    return l_err;
}

// Function Specification
//
// Name:  data_store_sys_config
//
// Description: Store system configuration data from TMGT
//
// End Function Specification
errlHndl_t data_store_sys_config(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                       cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t                      l_err = NULL;

    // Cast the command to the struct for this format
    cmdh_sys_config_v21_t * l_cmd_ptr = (cmdh_sys_config_v21_t *)i_cmd_ptr;
    uint16_t                        l_data_length = 0;
    uint32_t                        l_sys_data_sz = 0;
    bool                            l_invalid_input = TRUE; //Assume bad input
    uint8_t                         l_coreIndex = 0;

    l_data_length = CMDH_DATALEN_FIELD_UINT16(l_cmd_ptr);

    // Check length and version
    if(l_cmd_ptr->version == DATA_SYS_VERSION_20)
    {
        l_sys_data_sz = sizeof(cmdh_sys_config_v20_t) - sizeof(cmdh_fsp_cmd_header_t);
        if(l_sys_data_sz == l_data_length)
        {
            l_invalid_input = FALSE;
        }
    }
    else if(l_cmd_ptr->version == DATA_SYS_VERSION_21)
    {
        l_sys_data_sz = sizeof(cmdh_sys_config_v21_t) - sizeof(cmdh_fsp_cmd_header_t);
        if(l_sys_data_sz == l_data_length)
        {
            l_invalid_input = FALSE;
        }
    }

    if(l_invalid_input)
    {
        CMDH_TRAC_ERR("data_store_sys_config: Invalid System Data packet! Version[0x%02X] Data_size[%u]",
                 l_cmd_ptr->version,
                 l_data_length);

        /* @
         * @errortype
         * @moduleid    DATA_STORE_SYS_DATA
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata1   data size
         * @userdata2   packet version
         * @userdata4   OCC_NO_EXTENDED_RC
         * @devdesc     OCC recieved an invalid data packet from the FSP
         */
        l_err = createErrl(DATA_STORE_SYS_DATA,
                           INVALID_INPUT_DATA,
                           OCC_NO_EXTENDED_RC,
                           ERRL_SEV_UNRECOVERABLE,
                           NULL,
                           DEFAULT_TRACE_SIZE,
                           l_data_length,
                           (uint32_t)l_cmd_ptr->version);

        // Callout firmware
        addCalloutToErrl(l_err,
                         ERRL_CALLOUT_TYPE_COMPONENT_ID,
                         ERRL_COMPONENT_ID_FIRMWARE,
                         ERRL_CALLOUT_PRIORITY_HIGH);
    }
    else  // version and length is valid, store the data
    {
        // Copy data that is common to all versions
        G_sysConfigData.system_type.byte    = l_cmd_ptr->sys_config.system_type;
        G_sysConfigData.backplane_huid      = l_cmd_ptr->sys_config.backplane_sid;
        G_sysConfigData.apss_huid           = l_cmd_ptr->sys_config.apss_sid;
        G_sysConfigData.proc_huid           = l_cmd_ptr->sys_config.proc_sid;
        CNFG_DBG("data_store_sys_config: SystemType[0x%02X] BPSID[0x%08X] APSSSID[0x%08X] ProcSID[0x%08X]",
                  G_sysConfigData.system_type.byte, G_sysConfigData.backplane_huid, G_sysConfigData.apss_huid,
                  G_sysConfigData.proc_huid);

        // Check to see if we have to disable WOF due to no mode set yet on PowerVM
        if( !G_sysConfigData.system_type.kvm &&
           (CURRENT_MODE() == OCC_MODE_NOCHANGE) )
        {
            set_clear_wof_disabled(SET,
                                   WOF_RC_MODE_NO_SUPPORT_MASK,
                                   ERC_WOF_MODE_NO_SUPPORT_MASK);
        }

        //Write core temp and freq sensor ids
        //Core Temp and Freq sensors are always in sequence in the table
        for (l_coreIndex = 0; l_coreIndex < MAX_CORES; l_coreIndex++)
        {
            AMECSENSOR_PTR(TEMPPROCTHRMC0 + l_coreIndex)->ipmi_sid = l_cmd_ptr->sys_config.core_sid[(l_coreIndex * 2)];
            AMECSENSOR_PTR(FREQAC0 + l_coreIndex)->ipmi_sid = l_cmd_ptr->sys_config.core_sid[(l_coreIndex * 2) + 1];
            CNFG_DBG("data_store_sys_config: Core[%d] TempSID[0x%08X] FreqSID[0x%08X]", l_coreIndex,
                     AMECSENSOR_PTR(TEMPPROCTHRMC0 + l_coreIndex)->ipmi_sid, AMECSENSOR_PTR(FREQAC0 + l_coreIndex)->ipmi_sid);
        }

        if(l_cmd_ptr->version == DATA_SYS_VERSION_21)
        {
            // Copy the additional data for version 21
            G_sysConfigData.vrm_vdd_huid      = l_cmd_ptr->vrm_vdd_sid;
            AMECSENSOR_PTR(TEMPVDD)->ipmi_sid = l_cmd_ptr->vrm_vdd_temp_sid;
        }

        // Change Data Request Mask to indicate we got this data
        G_data_cnfg->data_mask |= DATA_MASK_SYS_CNFG;
        CMDH_TRAC_IMP("Got valid System Config data via TMGT for system type: 0x%02X", l_cmd_ptr->sys_config.system_type);
    }

    return l_err;

} // end data_store_sys_config()


// Function Specification
//
// Name:   data_store_thrm_thresholds
//
// Description: Store the thermal control thresholds sent by TMGT. This data is
// sent to all OCCs.
//
// End Function Specification
errlHndl_t data_store_thrm_thresholds(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                            cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t                      l_err = NULL;
    uint16_t                        i = 0;
    uint16_t                        l_data_length = 0;
    uint16_t                        l_exp_data_length = 0;
    uint8_t                         l_frutype = 0;
    cmdh_thrm_thresholds_v20_t*     l_cmd_ptr = (cmdh_thrm_thresholds_v20_t*)i_cmd_ptr;
    uint8_t                         l_num_data_sets = 0;
    bool                            l_invalid_input = TRUE; //Assume bad input

    do
    {
        l_data_length = CMDH_DATALEN_FIELD_UINT16(l_cmd_ptr);

        // Sanity checks on input data, break if:
        //  * data packet is smaller than the base size, OR
        //  * the version doesn't match what we expect,  OR
        //  * the actual data length does not match the expected data length, OR
        //  * the core and quad weights are both zero.
        if(l_cmd_ptr->version == DATA_THRM_THRES_VERSION_20)
        {
            l_num_data_sets = l_cmd_ptr->num_data_sets;
            l_exp_data_length = THRM_THRES_BASE_DATA_SZ_20 +
                (l_num_data_sets * sizeof(cmdh_thrm_thresholds_set_v20_t));

            if((l_exp_data_length == l_data_length) &&
               (l_data_length >= THRM_THRES_BASE_DATA_SZ_20) &&
               (l_cmd_ptr->proc_core_weight || l_cmd_ptr->proc_quad_weight))
            {
                l_invalid_input = FALSE;
            }
        }

        if(l_invalid_input)
        {
            CMDH_TRAC_ERR("data_store_thrm_thresholds: Invalid Thermal Control Threshold Data packet: data_length[%u] version[0x%02X] num_data_sets[%u]",
                     l_data_length,
                     l_cmd_ptr->version,
                     l_num_data_sets);
            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
            break;
        }

        // clear all FRU types to 0xFF (not defined) to prevent errors when (H)TMGT doesn't send thresholds for a FRU type
        for(i=0; i<DATA_FRU_MAX; i++)
        {
            G_data_cnfg->thrm_thresh.data[i].fru_type = i;
            G_data_cnfg->thrm_thresh.data[i].dvfs     = 0xFF;
            G_data_cnfg->thrm_thresh.data[i].error    = 0xFF;
            G_data_cnfg->thrm_thresh.data[i].pm_dvfs  = 0xFF;
            G_data_cnfg->thrm_thresh.data[i].pm_error = 0xFF;
            G_data_cnfg->thrm_thresh.data[i].max_read_timeout = 0xFF;
        }

        // Store the base data
        G_data_cnfg->thrm_thresh.version          = l_cmd_ptr->version;
        G_data_cnfg->thrm_thresh.proc_core_weight = l_cmd_ptr->proc_core_weight;
        G_data_cnfg->thrm_thresh.proc_quad_weight = l_cmd_ptr->proc_quad_weight;
        G_data_cnfg->thrm_thresh.num_data_sets    = l_cmd_ptr->num_data_sets;

        // Store the FRU related data
        for(i=0; i<l_cmd_ptr->num_data_sets; i++)
        {
            // Get the FRU type
            l_frutype = l_cmd_ptr->data[i].fru_type;

            if((l_frutype >= 0) && (l_frutype < DATA_FRU_MAX))
            {
                // Copy FRU data
                G_data_cnfg->thrm_thresh.data[l_frutype].fru_type = l_frutype;
                G_data_cnfg->thrm_thresh.data[l_frutype].dvfs     = l_cmd_ptr->data[i].dvfs;
                G_data_cnfg->thrm_thresh.data[l_frutype].error    = l_cmd_ptr->data[i].error;
                G_data_cnfg->thrm_thresh.data[l_frutype].pm_dvfs  = l_cmd_ptr->data[i].pm_dvfs;
                G_data_cnfg->thrm_thresh.data[l_frutype].pm_error = l_cmd_ptr->data[i].pm_error;
                G_data_cnfg->thrm_thresh.data[l_frutype].max_read_timeout =
                    l_cmd_ptr->data[i].max_read_timeout;

                // VRM OT status is no longer supported since the OCC supports reading Vdd temperature
                // Trace if VRM OT status FRU type is received and just ignore it
                if(l_frutype == DATA_FRU_VRM_OT_STATUS)
                {
                    CMDH_TRAC_IMP("data_store_thrm_thresholds: Received deprecated VRM OT STATUS type will be ignored");
                }

                // Useful trace for debugging
                //CMDH_TRAC_INFO("data_store_thrm_thresholds: FRU_type[0x%.2X] T_control[%u] DVFS[%u] Error[%u]",
                //          G_data_cnfg->thrm_thresh.data[l_frutype].fru_type,
                //          G_data_cnfg->thrm_thresh.data[l_frutype].t_control,
                //          G_data_cnfg->thrm_thresh.data[l_frutype].dvfs,
                //          G_data_cnfg->thrm_thresh.data[l_frutype].error);
            }
            else
            {
                // We got an invalid FRU type
                CMDH_TRAC_ERR("data_store_thrm_thresholds: Received an invalid FRU type[0x%.2X] max_FRU_number[0x%.2X]",
                              l_frutype,
                              DATA_FRU_MAX);
                cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                break;
            }
        }

    } while(0);

    if(!l_err)
    {
        // If there were no errors, indicate that we got this data
        G_data_cnfg->data_mask |= DATA_MASK_THRM_THRESHOLDS;
        CMDH_TRAC_IMP("data_store_thrm_thresholds: Got valid Thermal Control Threshold data packet");
    }

    return l_err;
}


// Function Specification
//
// Name:   data_store_mem_cfg
//
// Description: Store the memory configuration for centaurs and/or dimms. This data is
// sent to each OCC individually.
//
// End Function Specification
errlHndl_t data_store_mem_cfg(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                    cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t                      l_err = NULL;
    cmdh_mem_cfg_v21_t*             l_cmd_ptr = (cmdh_mem_cfg_v21_t*)i_cmd_ptr;
    uint16_t                        l_data_length = 0;
    uint16_t                        l_exp_data_length = 0;
    uint8_t                         l_num_mem_bufs = 0;
    uint8_t                         l_num_dimms = 0;
    uint8_t                         l_i2c_engine;
    uint8_t                         l_i2c_port;
    uint8_t                         l_i2c_addr = 0;
    uint8_t                         l_dimm_num = 0;
    uint8_t                         num_data_sets = 0;
    cmdh_mem_cfg_data_set_t*        data_sets_ptr;
    int                             i;

    do
    {
        l_data_length = CMDH_DATALEN_FIELD_UINT16((&l_cmd_ptr->header));

        // Clear all sensor IDs (hw and temperature)
        memset(G_sysConfigData.dimm_huids, 0, sizeof(G_sysConfigData.dimm_huids));
        int memctl, dimm;
        for(memctl=0; memctl < MAX_NUM_MEM_CONTROLLERS; ++memctl)
        {
            g_amec->proc[0].memctl[memctl].centaur.temp_sid = 0;
            for(dimm=0; dimm < NUM_DIMMS_PER_MEM_CONTROLLER; ++dimm)
            {
                g_amec->proc[0].memctl[memctl].centaur.dimm_temps[dimm].temp_sid = 0;
            }
        }

        // Process data based on version
        if( l_cmd_ptr->header.version == DATA_MEM_CFG_VERSION_20 ||
            l_cmd_ptr->header.version == DATA_MEM_CFG_VERSION_21 )
        {
            if(l_cmd_ptr->header.version == DATA_MEM_CFG_VERSION_21)
            {
                G_sysConfigData.ips_mem_pwr_ctl = l_cmd_ptr->header.ips_mem_pwr_ctl;
                G_sysConfigData.default_mem_pwr_ctl = l_cmd_ptr->header.default_mem_pwr_ctl;

                num_data_sets = ((cmdh_mem_cfg_v21_t*) l_cmd_ptr)->header.num_data_sets;
                data_sets_ptr = ((cmdh_mem_cfg_v21_t*) l_cmd_ptr)->data_set;

                // Verify the actual data length matches the expected data length for this version
                l_exp_data_length = sizeof(cmdh_mem_cfg_header_v21_t) - sizeof(cmdh_fsp_cmd_header_t) +
                    (num_data_sets * sizeof(cmdh_mem_cfg_data_set_t));

            }

            else if(l_cmd_ptr->header.version == DATA_MEM_CFG_VERSION_20)
            {
                // OFF memory power control means none of the
                //  memory control registers are ever updated.
                G_sysConfigData.ips_mem_pwr_ctl     = MEM_PWR_CTL_NO_SUPPORT;
                G_sysConfigData.default_mem_pwr_ctl = MEM_PWR_CTL_NO_SUPPORT;

                num_data_sets = ((cmdh_mem_cfg_v20_t*) l_cmd_ptr)->header.num_data_sets;
                data_sets_ptr = ((cmdh_mem_cfg_v20_t*) l_cmd_ptr)->data_set;

                // Verify the actual data length matches the expected data length for this version
                l_exp_data_length = sizeof(cmdh_mem_cfg_header_v20_t) - sizeof(cmdh_fsp_cmd_header_t) +
                    (num_data_sets * sizeof(cmdh_mem_cfg_data_set_t));
            }


            if(l_exp_data_length != l_data_length)
            {
               CMDH_TRAC_ERR("data_store_mem_cfg: Invalid mem config data packet: "
                             "data_length[%u] exp_length[%u] version[0x%02X] num_data_sets[%u]",
                             l_data_length,
                             l_exp_data_length,
                             l_cmd_ptr->header.version,
                             num_data_sets);

               cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
               break;
            }

            if (num_data_sets > 0)
            {
                // Store the memory type.  Memory must all be the same type, save from first and verify remaining
                G_sysConfigData.mem_type = data_sets_ptr[0].memory_type;
                unsigned int max_membuf = MAX_NUM_CENTAURS;
                unsigned int max_dimms_per_membuf = NUM_DIMMS_PER_CENTAUR;
                if(G_sysConfigData.mem_type == MEM_TYPE_NIMBUS)
                {
                    // Nimbus type -- dimm_info1 is I2C engine which must be the same
                    // save from first entry and verify remaining
                    G_sysConfigData.dimm_i2c_engine = data_sets_ptr[0].dimm_info1;
                }
                else if (IS_OCM_MEM_TYPE(G_sysConfigData.mem_type))
                {
                    G_sysConfigData.mem_type = MEM_TYPE_OCM;
                    max_membuf = MAX_NUM_OCMBS;
                    max_dimms_per_membuf = NUM_DIMMS_PER_OCMB;
                }
                else
                {
                    G_sysConfigData.mem_type = MEM_TYPE_CUMULUS;
                }

                // Store the hardware sensor ID and the temperature sensor ID
                for(i=0; i<num_data_sets; i++)
                {
                    cmdh_mem_cfg_data_set_t* l_data_set;

                    if(l_cmd_ptr->header.version == DATA_MEM_CFG_VERSION_21)
                    {
                        cmdh_mem_cfg_v21_t*      l_cmd2_ptr = (cmdh_mem_cfg_v21_t*)i_cmd_ptr;
                        l_data_set = &l_cmd2_ptr->data_set[i];
                    }
                    else       // DATA_MEM_CFG_VERSION_20
                    {
                        cmdh_mem_cfg_v20_t*      l_cmd2_ptr = (cmdh_mem_cfg_v20_t*)i_cmd_ptr;
                        l_data_set = &l_cmd2_ptr->data_set[i];
                    }

                    // Verify matching memory type and process based on memory type
                    if ((G_sysConfigData.mem_type == MEM_TYPE_NIMBUS) &&
                        (l_data_set->memory_type  == MEM_TYPE_NIMBUS))
                    {
                        // Nimbus type:  dimm info is I2C Engine, I2C Port, I2C Address
                        l_i2c_engine = l_data_set->dimm_info1;
                        l_i2c_port = l_data_set->dimm_info2;
                        l_i2c_addr = l_data_set->dimm_info3;

                        // Validate the i2c info for this data set.  Any failure will result in error and
                        // memory monitoring disabled.

                        // Only support engine C, D, or E
                        if((l_i2c_engine != PIB_I2C_ENGINE_C) &&
                           (l_i2c_engine != PIB_I2C_ENGINE_D) &&
                           (l_i2c_engine != PIB_I2C_ENGINE_E))
                        {
                            CMDH_TRAC_ERR("data_store_mem_cfg: Invalid I2C engine. entry=%d, engine=%d",
                                          i,
                                          l_i2c_engine);
                            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                            break;
                        }

                        // Engine must be the same for all DIMMs
                        if (l_i2c_engine != G_sysConfigData.dimm_i2c_engine)
                        {
                            CMDH_TRAC_ERR("data_store_mem_cfg: I2c engine mismatch. entry=%d, engine=%d, expected=%d",
                                          i,
                                          l_i2c_engine,
                                          G_sysConfigData.dimm_i2c_engine);
                            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                            break;
                        }

                        // Port must be 0 or 1.
                        if((l_i2c_port != 0) && (l_i2c_port != 1))
                        {
                            CMDH_TRAC_ERR("data_store_mem_cfg: Invalid I2C port. entry=%d, port=%d",
                                          i,
                                          l_i2c_port);
                            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                            break;
                        }

                        // I2C addr must be 0x3z where z is even
                        if( ( (l_i2c_addr & 0xF0) != 0x30) ||
                            ( (l_i2c_addr & 0x01) != 0 ) )
                        {
                            CMDH_TRAC_ERR("data_store_mem_cfg: Invalid I2C address. entry=%d, addr=%d",
                                          i,
                                          l_i2c_addr);
                            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                            break;
                        }

                        // DIMM info is good for this DIMM, save the sensor IDs for the DIMM
                        // The location of the HW sensor ID in the 2D dimm_huids array is used to know i2c port
                        // and i2c address for reading the DIMM.  "centaur num" index is port "dimm num" is
                        // translated from i2c address, we already verified the i2c addr is 0x3z above
                        l_dimm_num = (l_i2c_addr & 0x0F) >> 1;

                        // Store the hardware sensor ID
                        G_sysConfigData.dimm_huids[l_i2c_port][l_dimm_num] = l_data_set->hw_sensor_id;
                        // Set bit vector of present DIMM sensors (they will be enabled in task_dimm_sm)
                        G_dimm_present_sensors.bytes[l_i2c_port] |= 0x80 >> l_dimm_num;

                        // Store the temperature sensor ID
                        g_amec->proc[0].memctl[l_i2c_port].centaur.dimm_temps[l_dimm_num].temp_sid =
                            l_data_set->temp_sensor_id;

                        l_num_dimms++;

                    } // end Nimbus
                    else if ((G_sysConfigData.mem_type == MEM_TYPE_OCM) ||
                             (G_sysConfigData.mem_type == MEM_TYPE_CUMULUS))
                    {
                        unsigned int l_membuf_num = l_data_set->memory_type;
                        l_dimm_num = l_data_set->dimm_info1;
                        bool l_type_mismatch = FALSE;

                        if (IS_OCM_MEM_TYPE(l_data_set->memory_type))
                        {
                            // Get the physical location from type
                            l_membuf_num &= OCMB_TYPE_LOCATION_MASK;
                            if (G_sysConfigData.mem_type != MEM_TYPE_OCM)
                            {
                                l_type_mismatch = TRUE;
                            }
                        }
                        else if (G_sysConfigData.mem_type != MEM_TYPE_CUMULUS)
                        {
                            l_type_mismatch = TRUE;
                        }

                        // Validate the memory buffer and dimm count for this data set
                        if ((l_type_mismatch) || (l_membuf_num >= max_membuf) ||
                            ((l_dimm_num != 0xFF) && (l_dimm_num >= max_dimms_per_membuf)))
                        {
                            CMDH_TRAC_ERR("data_store_mem_cfg: Invalid memory data for type 0x%02X "
                                          "(entry %d: type/mem_buf[0x%02X], dimm[0x%02X])",
                                          G_sysConfigData.mem_type, i, l_data_set->memory_type, l_dimm_num);
                            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                            break;
                        }

                        if(l_dimm_num == 0xFF) // sensors are for the Memory Buffer itself (Centaur/OCMB)
                        {
                            // Store the hardware sensor ID
                            G_sysConfigData.centaur_huids[l_membuf_num] = l_data_set->hw_sensor_id;

                            // Store the temperature sensor ID
                            g_amec->proc[0].memctl[l_membuf_num].centaur.temp_sid = l_data_set->temp_sensor_id;

                            l_num_mem_bufs++;
                        }
                        else // individual DIMM
                        {
                            // Store the hardware sensor ID
                            G_sysConfigData.dimm_huids[l_membuf_num][l_dimm_num] = l_data_set->hw_sensor_id;

                            // Store the temperature sensor ID
                            g_amec->proc[0].memctl[l_membuf_num].centaur.dimm_temps[l_dimm_num].temp_sid =
                                l_data_set->temp_sensor_id;

                            l_num_dimms++;
                        }
                    } // end CENTAUR/OCMB
                    else
                    {
                        // MISMATCH ON MEMORY TYPE!!
                        CMDH_TRAC_ERR("data_store_mem_cfg: Mismatched memory types at index %d (0x%02X vs 0x%02X)",
                                      i, G_sysConfigData.mem_type, l_data_set->memory_type);

                        cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                        break;
                    }
                } // for each data set
            } // else no data sets given
        } // version 0x20
        else  // version not supported
        {
            CMDH_TRAC_ERR("data_store_mem_cfg: Invalid mem config data packet: version[0x%02X]",
                          l_cmd_ptr->header.version);

            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
        }
    } while(0);

    if(!l_err)
    {
        // If there were no errors, indicate that we got this data
        G_data_cnfg->data_mask |= DATA_MASK_MEM_CFG;
        CMDH_TRAC_IMP("data_store_mem_cfg: Got valid mem cfg packet. type=0x%02X, #mem bufs=%d, #dimm=%d",
                      G_sysConfigData.mem_type, l_num_mem_bufs, l_num_dimms);

        // No errors so we can enable memory monitoring if the data indicates it should be enabled
        if(num_data_sets == 0)  // num data sets of 0 indicates memory monitoring disabled
        {
            CMDH_TRAC_IMP("Memory monitoring is not allowed (mem config data sets = 0), ");
        }
        else
        {
            // This notifies other code that we need to request the mem throttle packet
            // and we need to enable memory monitoring when we enter observation state
            G_mem_monitoring_allowed = TRUE;

            // Require the mem throt packet for going to active state
            SMGR_VALIDATE_DATA_ACTIVE_MASK |= DATA_MASK_MEM_THROT;

            CMDH_TRAC_IMP("Memory monitoring is allowed (mem config data sets = %d,"
                          " ips_mem_pwr_ctl = %d, default_mem_pwr_ctl = %d)",
                          num_data_sets, G_sysConfigData.ips_mem_pwr_ctl,
                          G_sysConfigData.default_mem_pwr_ctl);
        }
    }
    else
    {
        // Error with data don't enable memory monitoring
        CMDH_TRAC_IMP("data_store_mem_cfg: Memory monitoring not allowed due to error");
    }

    return l_err;

} // end data_store_mem_cfg()


// Function Specification
//
// Name:   data_store_mem_throt
//
// Description: Store min/max mem throttle settings. This data is
// sent to each OCC individually.
//
// End Function Specification
errlHndl_t data_store_mem_throt(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                      cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t                      l_err = NULL;
    cmdh_mem_throt_t*               l_cmd_ptr = (cmdh_mem_throt_t*)i_cmd_ptr;
    uint16_t                        l_data_length = 0;
    uint16_t                        l_exp_data_length = 0;
    uint8_t                         i;
    uint16_t                        l_configured_mbas = 0;
    bool                            l_invalid_input = TRUE; //Assume bad input
    uint32_t                        l_total_turbo_mem_power = 0;
    uint32_t                        l_total_nominal_mem_power = 0;
    uint32_t                        l_total_pcap_mem_power = 0;

    do
    {
        l_data_length = CMDH_DATALEN_FIELD_UINT16((&l_cmd_ptr->header));

        // Sanity checks on input data, break if:
        //  * the version doesn't match what we expect,  OR
        //  * the actual data length does not match the expected data length.
        if(l_cmd_ptr->header.version == DATA_MEM_THROT_VERSION_20)
        {
            l_exp_data_length = sizeof(cmdh_mem_throt_header_t) - sizeof(cmdh_fsp_cmd_header_t) +
                (l_cmd_ptr->header.num_data_sets * sizeof(cmdh_mem_throt_data_set_t));

            if(l_exp_data_length == l_data_length)
            {
                l_invalid_input = FALSE;
            }
        }

        if(l_invalid_input)
        {
            CMDH_TRAC_ERR("data_store_mem_throt: Invalid mem throttle data packet: "
                          "data_length[%u] exp_length[%u] version[0x%02X] num_data_sets[%u]",
                          l_data_length,
                          l_exp_data_length,
                          l_cmd_ptr->header.version,
                          l_cmd_ptr->header.num_data_sets);
            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
            break;
        }

        // Store the memory throttle settings
        for(i=0; i<l_cmd_ptr->header.num_data_sets; i++)
        {
            mem_throt_config_data_t    l_temp_set;
            cmdh_mem_throt_data_set_t* l_data_set = &l_cmd_ptr->data_set[i];
            uint16_t * l_n_ptr;

            uint8_t mc=-1, port=-1, mem_buf=-1, mba=-1; // dimm/centaur Info Parameters
            unsigned int max_membuf = MAX_NUM_CENTAURS;
            unsigned int max_mbas_per_membuf = NUM_MBAS_PER_CENTAUR;

            if (MEM_TYPE_NIMBUS == G_sysConfigData.mem_type)
            {
                mc   = l_data_set->mem_throt_info.nimbus.mc_num;
                port = l_data_set->mem_throt_info.nimbus.port_num;

                // Validate the Nimbus Info parameters:
                // - MC num (0 for MC01, and 1 for MC23)
                // - and Port Number (0-3)
                if((mc   >= NUM_NIMBUS_MC_PAIRS) ||
                   (port >= MAX_NUM_MCU_PORTS))
                {
                    CMDH_TRAC_ERR("data_store_mem_throt: Invalid MC or Port numbers."
                                  " entry=%d, mc=%d, port=%d",
                                  i, mc, port);
                    cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                    break;
                }
            }
            else if ((MEM_TYPE_CUMULUS == G_sysConfigData.mem_type) ||
                     (MEM_TYPE_OCM == G_sysConfigData.mem_type))
            {
                if (MEM_TYPE_OCM == G_sysConfigData.mem_type)
                {
                    max_membuf = MAX_NUM_OCMBS;
                    max_mbas_per_membuf = NUM_MBAS_PER_OCMB;
                }

                mem_buf = l_data_set->mem_throt_info.membuf.membuf_num;
                mba  = l_data_set->mem_throt_info.membuf.mba_num;

                // Validate parameters
                if((mem_buf >= max_membuf) ||
                   (mba >= max_mbas_per_membuf))
                {
                    CMDH_TRAC_ERR("data_store_mem_throt: Invalid memory data for type 0x%02X "
                                  "(entry %d: mem_buf[%d], mba[%d])",
                                  G_sysConfigData.mem_type, i, mem_buf, mba);
                    cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                    break;
                }
            }

            // Copy into a temporary buffer while we check for N values of 0
            memcpy(&l_temp_set, &(l_data_set->min_n_per_mba), sizeof(mem_throt_config_data_t));

            // A 0 for any power or N value is an error
            unsigned int l_index = 0;
            for(l_n_ptr = &l_temp_set.min_n_per_mba; l_n_ptr <= &l_temp_set.nom_mem_power; l_n_ptr++)
            {
                if(!(*l_n_ptr))
                {
                    if(MEM_TYPE_NIMBUS == G_sysConfigData.mem_type)
                    {
                        CMDH_TRAC_ERR("data_store_mem_throt: RDIMM Throttle value[%d] is 0!"
                                      " mc[%d] port[%d]", l_index, mc, port);
                    }
                    else
                    {
                        CMDH_TRAC_ERR("data_store_mem_throt: DIMM Throttle N value is 0!"
                                      " mem_buf[%d] mba[%d]", mem_buf, mba);
                    }
                    cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, ERRL_RC_INVALID_DATA, &l_err);
                    break;
                }
                ++l_index;
            }

            if(l_err)  // zero N Value?
            {
                break;
            }

            if(MEM_TYPE_NIMBUS ==  G_sysConfigData.mem_type)
            {
                memcpy(&G_sysConfigData.mem_throt_limits[mc][port],
                       &(l_data_set->min_n_per_mba),
                       sizeof(mem_throt_config_data_t));

                CONFIGURE_NIMBUS_DIMM_THROTTLING(l_configured_mbas, mc, port);
            }
            else if ((MEM_TYPE_CUMULUS == G_sysConfigData.mem_type) ||
                     (MEM_TYPE_OCM == G_sysConfigData.mem_type))
            {
                memcpy(&G_sysConfigData.mem_throt_limits[mem_buf][mba],
                       &(l_data_set->min_n_per_mba),
                       sizeof(mem_throt_config_data_t));

                l_configured_mbas |= 1 << ((mem_buf * max_mbas_per_membuf) + mba);
            }

            // Add memory power
            l_total_turbo_mem_power += l_data_set->turbo_mem_power;
            l_total_nominal_mem_power += l_data_set->nom_mem_power;
            l_total_pcap_mem_power += l_data_set->pcap_mem_power;

        } // data_sets for loop

    } while(0);

    if(!l_err)
    {
        // If there were no errors, indicate that we got this data
        G_data_cnfg->data_mask |= DATA_MASK_MEM_THROT;
        CMDH_TRAC_IMP("data_store_mem_throt: Got valid mem throt packet. configured_mba_bitmap=0x%04x",
                 l_configured_mbas);

        // Update the configured mba bitmap and save the total memory powers
        G_configured_mbas = l_configured_mbas;
        // g_amec is in Watts, config data is in cW
        g_amec->pcap.nominal_mem_pwr = l_total_nominal_mem_power / 100;
        g_amec->pcap.turbo_mem_pwr = l_total_turbo_mem_power / 100;
        g_amec->pcap.pcap1_mem_pwr = l_total_pcap_mem_power / 100;
    }

    return l_err;

} // end data_store_mem_throt()


// Function Specification
//
// Name:  data_store_ips_config
//
// Description: Store IPS config data from TMGT
//
// End Function Specification
errlHndl_t data_store_ips_config(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                       cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t          l_err = NULL;
    cmdh_ips_config_t   *l_cmd_ptr = (cmdh_ips_config_t *)i_cmd_ptr; // Cast the command to the struct for this format
    uint16_t            l_data_length = CMDH_DATALEN_FIELD_UINT16(l_cmd_ptr);
    uint32_t            l_ips_data_sz = sizeof(cmdh_ips_config_t) - sizeof(cmdh_fsp_cmd_header_t);


    // Check if this is the Master OCC. Check length and version
    if((OCC_MASTER != G_occ_role) ||
       (l_cmd_ptr->iv_version != DATA_IPS_VERSION) ||
       ( l_ips_data_sz != l_data_length) )
    {
        CMDH_TRAC_ERR("data_store_ips_config: Invalid IPS Data packet");

        /* @
         * @errortype
         * @moduleid    DATA_STORE_IPS_DATA
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata1   data size
         * @userdata2   packet version
         * @userdata4   OCC_NO_EXTENDED_RC
         * @devdesc     OCC recieved an invalid data packet from the FSP
         */
        l_err = createErrl(DATA_STORE_IPS_DATA,
                           INVALID_INPUT_DATA,
                           OCC_NO_EXTENDED_RC,
                           ERRL_SEV_UNRECOVERABLE,
                           NULL,
                           DEFAULT_TRACE_SIZE,
                           l_data_length,
                           (uint32_t)l_cmd_ptr->iv_version);

        // Callout firmware
        addCalloutToErrl(l_err,
                         ERRL_CALLOUT_TYPE_COMPONENT_ID,
                         ERRL_COMPONENT_ID_FIRMWARE,
                         ERRL_CALLOUT_PRIORITY_HIGH);
    }
    else
    {
        // Copy data somewhere
        memcpy(&G_ips_config_data, &l_cmd_ptr->iv_ips_config, sizeof(cmdh_ips_config_data_t));

        // Change Data Request Mask to indicate we got this data
        G_data_cnfg->data_mask |= DATA_MASK_IPS_CNFG;

        CMDH_TRAC_IMP("Got valid Idle Power Save Config data via TMGT: ipsEnabled[%d] Delay Time to enter IPS[%d], exit IPS[%d]. Utilization to enter IPS[%d], exit IPS[%d]",
                 l_cmd_ptr->iv_ips_config.iv_ipsEnabled,
                 l_cmd_ptr->iv_ips_config.iv_delayTimeforEntry,
                 l_cmd_ptr->iv_ips_config.iv_delayTimeforExit,
                 l_cmd_ptr->iv_ips_config.iv_utilizationForEntry,
                 l_cmd_ptr->iv_ips_config.iv_utilizationForExit );
    }

    return l_err;
}

// Function Specification
//
// Name:  data_store_vrm_fault
//
// Description: Store VRM fault status from TMGT
//
// End Function Specification
errlHndl_t data_store_vrm_fault(const cmdh_fsp_cmd_t * i_cmd_ptr,
                                      cmdh_fsp_rsp_t * o_rsp_ptr)
{
    errlHndl_t          l_err = NULL;
    cmdh_vrm_fault_t   *l_cmd_ptr = (cmdh_vrm_fault_t *)i_cmd_ptr; // Cast the command to the struct for this format
    uint16_t            l_data_length = CMDH_DATALEN_FIELD_UINT16(l_cmd_ptr);
    uint32_t            l_data_sz = sizeof(cmdh_vrm_fault_t) - sizeof(cmdh_fsp_cmd_header_t);


    // Check length and version
    if((l_cmd_ptr->version != DATA_VRM_FAULT_VERSION) ||
       ( l_data_sz != l_data_length) )
    {
        CMDH_TRAC_ERR("data_store_vrm_fault: Invalid version[%d] expected[%d] or length[%d] expected[%d]",
                       l_cmd_ptr->version, DATA_VRM_FAULT_VERSION, l_data_length, l_data_sz);

        /* @
         * @errortype
         * @moduleid    DATA_STORE_VRM_FAULT
         * @reasoncode  INVALID_INPUT_DATA
         * @userdata1   data size
         * @userdata2   packet version
         * @userdata4   OCC_NO_EXTENDED_RC
         * @devdesc     OCC recieved an invalid VRM fault data packet from the FSP
         */
        l_err = createErrl(DATA_STORE_VRM_FAULT,
                           INVALID_INPUT_DATA,
                           OCC_NO_EXTENDED_RC,
                           ERRL_SEV_UNRECOVERABLE,
                           NULL,
                           DEFAULT_TRACE_SIZE,
                           l_data_length,
                           (uint32_t)l_cmd_ptr->version);

        // Callout firmware
        addCalloutToErrl(l_err,
                         ERRL_CALLOUT_TYPE_COMPONENT_ID,
                         ERRL_COMPONENT_ID_FIRMWARE,
                         ERRL_CALLOUT_PRIORITY_HIGH);
    }
    else
    {
        // Save the VRM fault status
        g_amec->sys.vrm_fault_status = l_cmd_ptr->vrm_fault_status;

        // Change Data Request Mask to indicate we got this data
        G_data_cnfg->data_mask |= DATA_MASK_VRM_FAULT;

        CMDH_TRAC_IMP("Got VRM fault status = 0x%02X", g_amec->sys.vrm_fault_status);
    }

    return l_err;
} // end data_store_vrm_fault()

// Function Specification
//
// Name:   DATA_store_cnfgdata
//
// Description: Process Set Configuration Data cmd based on format (type) byte
//
// End Function Specification
errlHndl_t DATA_store_cnfgdata (const cmdh_fsp_cmd_t * i_cmd_ptr,
                                cmdh_fsp_rsp_t       * o_rsp_ptr)
{
    errlHndl_t                      l_errlHndl = NULL;
    UINT32                          l_new_data = 0;
    ERRL_RC                         l_rc       = ERRL_RC_INTERNAL_FAIL;

    CMDH_TRAC_IMP("Data Config Packet Received Type: 0x%02x",i_cmd_ptr->data[0]);

    switch (i_cmd_ptr->data[0])
    {
        case DATA_FORMAT_FREQ:
            l_errlHndl = data_store_freq_data(i_cmd_ptr , o_rsp_ptr);
            if(NULL == l_errlHndl)
            {
                // New Frequency config data packet received with no error logs: set the
                // DATA_MASK_FREQ_PRESENT to flag that we received the frequency from TMGT
                l_new_data = DATA_MASK_FREQ_PRESENT;
            }
            break;

        case DATA_FORMAT_SET_ROLE:
            // Initialze our role to either be a master of a slave
            // We must be in Standby State for this command to be
            // accepted.

            l_errlHndl = data_store_role(i_cmd_ptr, o_rsp_ptr);
            if(NULL == l_errlHndl)
            {
                // Set this in case AMEC needs to know about this
                l_new_data = DATA_MASK_SET_ROLE;
            }
            break;

        case DATA_FORMAT_APSS_CONFIG:
            // Initialze APSS settings so that OCC can correctly interpret
            // the data that it gets from the APSS
            l_errlHndl = data_store_apss_config(i_cmd_ptr, o_rsp_ptr);

            if(NULL == l_errlHndl)
            {
                // Set this in case AMEC needs to know about this
                l_new_data = DATA_MASK_APSS_CONFIG;
            }
            break;

        case DATA_FORMAT_AVSBUS_CONFIG:
            // Store AVSBUS settings so that OCC can retrieve the
            // voltage/current and initialize the AVS Bus for reading
            l_errlHndl = data_store_avsbus_config(i_cmd_ptr, o_rsp_ptr);
            if(NULL == l_errlHndl)
            {
                // Notify AMEC of the new data
                l_new_data = DATA_MASK_AVSBUS_CONFIG;
            }
            break;

        case DATA_FORMAT_GPU:
            // Store GPU information
            l_errlHndl = data_store_gpu(i_cmd_ptr, o_rsp_ptr);
            if(NULL == l_errlHndl)
            {
                // Notify AMEC of the new data
                l_new_data = DATA_MASK_GPU;
            }
            break;

        case DATA_FORMAT_POWER_CAP:
            // Store the pcap data in G_master_pcap_data
            l_errlHndl = data_store_power_cap(i_cmd_ptr, o_rsp_ptr);

            if(NULL == l_errlHndl)
            {
                // Set this in case AMEC needs to know about this
                l_new_data = DATA_MASK_PCAP_PRESENT;
            }
            break;

        case DATA_FORMAT_SYS_CNFG:
            // Store the system config data in G_sysConfigData
            l_errlHndl = data_store_sys_config(i_cmd_ptr, o_rsp_ptr);

            if(NULL == l_errlHndl)
            {
                // Set this in case AMEC needs to know about this
                l_new_data = DATA_MASK_SYS_CNFG;
            }
            break;

        case DATA_FORMAT_IPS_CNFG:
            // Store the system config data in G_sysConfigData
            l_errlHndl = data_store_ips_config(i_cmd_ptr, o_rsp_ptr);

            if(NULL == l_errlHndl)
            {
                // Set this in case AMEC needs to know about this
                l_new_data = DATA_MASK_IPS_CNFG;
            }
            break;

        case DATA_FORMAT_THRM_THRESHOLDS:
            // Store the thermal control thresholds sent by TMGT
            l_errlHndl = data_store_thrm_thresholds(i_cmd_ptr, o_rsp_ptr);

            if(NULL == l_errlHndl)
            {
                // Set this in case AMEC needs to know about this
                l_new_data = DATA_MASK_THRM_THRESHOLDS;
            }
            break;

        case DATA_FORMAT_MEM_CFG:
            // Store memory configuration for present centaurs and/or dimms to monitor
            l_errlHndl = data_store_mem_cfg(i_cmd_ptr, o_rsp_ptr);

            if(NULL == l_errlHndl)
            {
                l_new_data = DATA_MASK_MEM_CFG;
            }
            break;

        case DATA_FORMAT_MEM_THROT:
            // Store memory throttle limits
            l_errlHndl = data_store_mem_throt(i_cmd_ptr, o_rsp_ptr);

            if(NULL == l_errlHndl)
            {
                l_new_data = DATA_MASK_MEM_THROT;
            }
            break;

        case DATA_FORMAT_VRM_FAULT:
            // Handle VRM fault status
            l_errlHndl = data_store_vrm_fault(i_cmd_ptr, o_rsp_ptr);

            if(NULL == l_errlHndl)
            {
                l_new_data = DATA_MASK_VRM_FAULT;
            }
            break;

        default:
            // Build Error Response packet, we are calling this here
            // to generate the error log, it will get called again, below but
            // that's ok, as long as we set l_rc here.
            l_rc = ERRL_RC_INVALID_DATA;
            cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, l_rc, &l_errlHndl);
            break;
    }

    if((!l_errlHndl) && (l_new_data))
    {
        // Notify AMEC component of new data
        l_errlHndl = AMEC_data_change(l_new_data);
    }

    if(l_errlHndl)
    {
        // Build Error Response packet
        cmdh_build_errl_rsp(i_cmd_ptr, o_rsp_ptr, l_rc, &l_errlHndl);
    }
    else
    {
        /// Build Response Packet - all formats return success with no data
        o_rsp_ptr->data_length[0] = 0;
        o_rsp_ptr->data_length[1] = 0;
        G_rsp_status = ERRL_RC_SUCCESS;
    }

    return(l_errlHndl);
}

