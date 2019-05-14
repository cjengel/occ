/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/occ_405/amec/amec_freq.h $                                */
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

#ifndef _AMEC_FREQ_H
#define _AMEC_FREQ_H

//*************************************************************************/
// Includes
//*************************************************************************/
#include <occ_common.h>
#include <ssx.h>
#include "occ_sys_config.h"
#include <ssx_app_cfg.h>
#include <amec_smh.h>
#include <mode.h>
#include <errl.h>

//*************************************************************************/
// Externs
//*************************************************************************/

//*************************************************************************/
// Macros
//*************************************************************************/

//*************************************************************************/
// Defines/Enums
//*************************************************************************/
#define FREQ_CHG_CHECK_TIME 4000

// This is used by the Frequency State Machine
typedef enum
{
    AMEC_CORE_FREQ_IDLE_STATE    = 0x00,
    AMEC_CORE_FREQ_PROCESS_STATE = 0x01,
}amec_freq_write_state_t;

// This is reason code used by Voting box amec_slv_voting_box
typedef enum
{
    AMEC_VOTING_REASON_INIT             = 0x00000000,
    AMEC_VOTING_REASON_PHYP             = 0x00000001,
    AMEC_VOTING_REASON_PLPM             = 0x00000002,
    AMEC_VOTING_REASON_LEGACY           = 0x00000004,
    AMEC_VOTING_REASON_SOFT_MIN         = 0x00000008,
    AMEC_VOTING_REASON_SOFT_MAX         = 0x00000010,
    AMEC_VOTING_REASON_CORE_CAP         = 0x00000020,
    AMEC_VOTING_REASON_PROC_THRM        = 0x00000040,
    AMEC_VOTING_REASON_GXHB_THRM        = 0x00000080,
    AMEC_VOTING_REASON_OVERSUB          = 0x00000100,
    AMEC_VOTING_REASON_OVER_CURRENT     = 0x00000200,
    AMEC_VOTING_REASON_OVERRIDE         = 0x00000400,
    AMEC_VOTING_REASON_CORE_GRP_MIN     = 0x00000800,
    AMEC_VOTING_REASON_PWR              = 0x00001000,
    AMEC_VOTING_REASON_PPB              = 0x00002000,
    AMEC_VOTING_REASON_PMAX             = 0x00004000,
    AMEC_VOTING_REASON_UTIL             = 0x00008000,
    AMEC_VOTING_REASON_CONN_OC          = 0x00010000,
    AMEC_VOTING_REASON_OVERRIDE_CORE    = 0x00020000,
    AMEC_VOTING_REASON_IPS              = 0x00040000,
    AMEC_VOTING_REASON_APSS_PMAX        = 0x00080000,
    AMEC_VOTING_REASON_VDD_THRM         = 0x00100000,
    AMEC_VOTING_REASON_VRM_N            = 0x00200000,
}amec_freq_voting_reason_t;


#define NON_DPS_POWER_LIMITED ( AMEC_VOTING_REASON_PWR | \
                                AMEC_VOTING_REASON_PPB | \
                                AMEC_VOTING_REASON_PMAX  \
                              )

extern BOOLEAN G_non_dps_power_limited;

// This is memory throttle reason code used by Voting box amec_slv_mem_voting_box
typedef enum
{
    AMEC_MEM_VOTING_REASON_INIT     = 0x00,
    AMEC_MEM_VOTING_REASON_MEMBUF   = 0x01,
    AMEC_MEM_VOTING_REASON_DIMM     = 0x02,
    AMEC_MEM_VOTING_REASON_SLEW     = 0x03,
}amec_mem_voting_reason_t;

// This is memory throttle reason code encoded in OPAL dynamic data
typedef enum
{
    NO_MEM_THROTTLE                 = 0x00,
    POWER_CAP                       = 0x01,
    MEMORY_OVER_TEMP                = 0x02,
}opal_mem_voting_reason_t;

// This is processor throttle reason code used by Voting box amec_slv_proc_voting_box
typedef enum {
    NO_THROTTLE                     = 0x00,
    POWERCAP                        = 0x01,
    CPU_OVERTEMP                    = 0x02,
    POWER_SUPPLY_FAILURE            = 0x03,
    OVERCURRENT                     = 0x04,
    OCC_RESET                       = 0x05,
    PCAP_EXCEED_REPORT              = 0x06,
    PROC_OVERTEMP_EXCEED_REPORT     = 0x07,
    VDD_OVERTEMP                    = 0x08,
    VDD_OVERTEMP_EXCEED_REPORT      = 0x09,
    MANUFACTURING_OVERRIDE          = 0xAA,
}amec_proc_voting_reason_t;

typedef  amec_proc_voting_reason_t opal_proc_voting_reason_t;

//*************************************************************************/
// Structures
//*************************************************************************/


//*************************************************************************/
// Globals
//*************************************************************************/

//*************************************************************************/
// Function Prototypes
//*************************************************************************/

// Used to set the freq range that amec can control between.
errlHndl_t amec_set_freq_range(const OCC_MODE i_mode);

// Voting box for handling slave processor freq votes
void amec_slv_proc_voting_box(void);

// Amec Frequency State Machine
void amec_slv_freq_smh(void);

// Voting box for handling slave memory freq votes
void amec_slv_mem_voting_box(void);

// Amec Detect and log degraded performance errors
void amec_slv_check_perf(void);

#endif

