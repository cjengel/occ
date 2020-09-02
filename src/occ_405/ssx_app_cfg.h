/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/occ_405/ssx_app_cfg.h $                                   */
/*                                                                        */
/* OpenPOWER OnChipController Project                                     */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2015,2017                        */
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
#ifndef __SSX_APP_CFG_H__
#define __SSX_APP_CFG_H__

/// \file ssx_app_cfg.h
/// \brief Application specific overrides go here.
///

#include "global_app_cfg.h"

// These versions of SSX_PANIC are being changed so that they exactly
// mirror each other and are exactly structured at 8 instructions only and
// make only one branch to outside code.
#ifndef __ASSEMBLER__
#ifndef SSX_PANIC
#define SSX_PANIC(code)                                             \
do {                                                                \
    barrier();                                                      \
    asm volatile ("stw  %r3, __occ_panic_save_r3@sda21(0)");        \
    asm volatile ("mflr %r3");                                      \
    asm volatile ("stw  %r4, __occ_panic_save_r4@sda21(0)");        \
    asm volatile ("lis  %%r4, %0"::"i" (code >> 16));               \
    asm volatile ("ori  %%r4, %%r4, %0"::"i" (code & 0xffff));      \
    asm volatile ("bl   __ssx_checkpoint_panic_and_save_ffdc");     \
    asm volatile ("trap");                                          \
    asm volatile (".long %0" : : "i" (code));                       \
} while (0)
#endif // SSX_PANIC
#else  /* __ASSEMBLER__ */
#ifndef SSX_PANIC
// This macro cannot be more than 8 instructions long, but it can be less than
// 8.
#define SSX_PANIC(code) _ssx_panic code
    .macro  _ssx_panic, code
    stw     %r3, __occ_panic_save_r3@sda21(0)
    mflr    %r3
    stw     %r4, __occ_panic_save_r4@sda21(0)
    lis     %r4, \code@h
    ori     %r4, %r4, \code@l
    bl      __ssx_checkpoint_panic_and_save_ffdc
    trap
    .long   \code
    .endm
#endif // SSX_PANIC
#endif /* __ASSEMBLER__ */

/// Static configuration data for external interrupts:
///
/// IRQ#, TYPE, POLARITY, ENABLE
///
#define APPCFG_EXT_IRQS_CONFIG \
    OCCHW_IRQ_DEBUGGER                 OCCHW_IRQ_TYPE_LEVEL    OCCHW_IRQ_POLARITY_HI       OCCHW_IRQ_MASKED \
    OCCHW_IRQ_TRACE_TRIGGER_33         OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_GPE0_ERROR               OCCHW_IRQ_TYPE_LEVEL    OCCHW_IRQ_POLARITY_HI       OCCHW_IRQ_MASKED \
    OCCHW_IRQ_GPE1_ERROR               OCCHW_IRQ_TYPE_LEVEL    OCCHW_IRQ_POLARITY_HI       OCCHW_IRQ_MASKED \
    OCCHW_IRQ_CHECK_STOP_PPC405        OCCHW_IRQ_TYPE_LEVEL    OCCHW_IRQ_POLARITY_HI       OCCHW_IRQ_MASKED \
    OCCHW_IRQ_EXTERNAL_TRAP            OCCHW_IRQ_TYPE_LEVEL    OCCHW_IRQ_POLARITY_HI       OCCHW_IRQ_MASKED \
    OCCHW_IRQ_OCC_TIMER0               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_OCC_TIMER1               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_IPI4_HI_PRIORITY         OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_I2CM_INTR                OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_PBAX_OCC_SEND            OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_PBAX_OCC_PUSH0           OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_PBAX_OCC_PUSH1           OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_PBA_BCDE_ATTN            OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_PBA_BCUE_ATTN            OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_STRM0_PULL               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_STRM0_PUSH               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_STRM1_PULL               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_STRM1_PUSH               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_STRM2_PULL               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_STRM2_PUSH               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_STRM3_PULL               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_STRM3_PUSH               OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED \
    OCCHW_IRQ_IPI4_LO_PRIORITY         OCCHW_IRQ_TYPE_EDGE     OCCHW_IRQ_POLARITY_RISING   OCCHW_IRQ_MASKED

/// The Instance ID of the occ processor that this application is intended to run on
/// 0-3 -> GPE, 4 -> 405
#define APPCFG_OCC_INSTANCE_ID 4

// Common configuration groups for verification. Bypass time-consuming setup
// or setup done by procedures for simulation environments, and set up special
// I/O configurations for simulation environments.

#ifndef VERIFICATION
#define VERIFICATION 0
#endif

#ifndef OCC_UNIT_VERIFICATION
#define OCC_UNIT_VERIFICATION 0
#endif

#ifndef EPM_VERIFICATION
#define EPM_VERIFICATION 0
#endif

#ifndef VBU_VERIFICATION
#define VBU_VERIFICATION 0
#endif

#ifndef LAB_VALIDATION
#define LAB_VALIDATION 0
#endif

#if VERIFICATION || LAB_VALIDATION

#if !LAB_VALIDATION
#define SSX_STACK_CHECK    0
#endif

#define SIMICS_ENVIRONMENT 0

#else

#define INITIALIZE_PBA_SLAVES 1
#define INITIALIZE_PBA_BARS 1

#endif  /* VERIFICATION */


#if OCC_UNIT_VERIFICATION
#define USE_RTX_IO 1
#endif

#if EPM_VERIFICATION
#define USE_EPM_IO 1
#endif

// VBU and the lab use trace buffer I/O.  The DBCR0 is left untouched so VBU
// can use instruction/data breakpoints.

#if VBU_VERIFICATION || LAB_VALIDATION
#define USE_TRACE_IO 1
#define NO_INIT_DBCR0 1
#endif

// Default initializations for validation that affect SSX and library code
#define PROCESSOR_EC_LEVEL

#ifndef SIMICS_ENVIRONMENT
#define SIMICS_ENVIRONMENT 0
#endif

#if SIMICS_ENVIRONMENT
#pragma message "Building for Simics!"
#ifndef USE_SIMICS_IO
#define USE_SIMICS_IO 1
#endif
#endif

#ifndef USE_SIMICS_IO
#define USE_SIMICS_IO 0
#endif

#ifndef USE_RTX_IO
#define USE_RTX_IO 0
#endif

#ifndef USE_TRACE_IO
#define USE_TRACE_IO 0
#endif

#ifndef USE_EPM_IO
#define USE_EPM_IO 0
#endif

/// The buffer used for 'ssxout' in VBU and lab applications
///
/// The buffer is defined to be quite large in order to accomodate full kernel
/// and application dumps in the event of problems.
#ifndef SSXOUT_TRACE_BUFFER_SIZE
#define SSXOUT_TRACE_BUFFER_SIZE (8 * 1024)
#endif

#ifndef APPCFG_USE_EXT_TIMEBASE_FOR_TRACE
#define APPCFG_USE_EXT_TIMEBASE_FOR_TRACE 1
#endif

#ifndef PPC405_TIMEBASE_HZ
#define PPC405_TIMEBASE_HZ DEFAULT_OCC405_FREQ_HZ
#endif

// This applies to SSX_TRACE
#if APPCFG_USE_EXT_TIMEBASE_FOR_TRACE
#define SSX_TRACE_TIMEBASE_HZ DEFAULT_EXT_CLK_FREQ_HZ
#else
#define SSX_TRACE_TIMEBASE_HZ __ssx_timebase_frequency_hz
#endif /* APPCFG_USE_EXT_TIMEBASE_FOR_TRACE */

#if SSX_USE_INIT_SECTION
#define INIT_SEC_NM_STR     "initSection"
#define INIT_SECTION __attribute__ ((section (INIT_SEC_NM_STR)))
#else
#define INIT_SECTION
#endif

#endif /*__SSX_APP_CFG_H__*/
