/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/include/registers/cme_firmware_registers.h $              */
/*                                                                        */
/* OpenPOWER OnChipController Project                                     */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2015,2019                        */
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
#ifndef __CME_FIRMWARE_REGISTERS_H__
#define __CME_FIRMWARE_REGISTERS_H__

/// \file cme_firmware_registers.h
/// \brief C register structs for the CME unit

// *** WARNING *** - This file is generated automatically, do not edit.

#ifndef SIXTYFOUR_BIT_CONSTANT
    #ifdef __ASSEMBLER__
        #define SIXTYFOUR_BIT_CONSTANT(x) x
    #else
        #define SIXTYFOUR_BIT_CONSTANT(x) x##ull
    #endif
#endif

#ifndef __ASSEMBLER__

#include <stdint.h>




typedef union cme_scom_lfir
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t ppe_internal_error : 1;
    uint64_t ppe_external_error : 1;
    uint64_t ppe_progress_error : 1;
    uint64_t ppe_breakpoint_error : 1;
    uint64_t ppe_watchdog : 1;
    uint64_t ppe_halted : 1;
    uint64_t ppe_debug_trigger : 1;
    uint64_t sram_ue : 1;
    uint64_t sram_ce : 1;
    uint64_t sram_scrub_err : 1;
    uint64_t bce_error : 1;
    uint64_t spare11 : 1;
        uint64_t spare12 : 1;
        uint64_t c0_ivrm_dropout : 1;
        uint64_t c1_ivrm_dropout : 1;
        uint64_t cache_ivrm_dropout : 1;
        uint64_t extreme_droop_err : 1;
        uint64_t large_droop_err : 1;
        uint64_t small_droop_err : 1;
        uint64_t unexpected_droop_encode : 1;
    uint64_t fir_parity_err_dup : 1;
    uint64_t fir_parity_err : 1;
        uint64_t reserved1 : 42;
#else
        uint64_t reserved1 : 42;
    uint64_t fir_parity_err : 1;
    uint64_t fir_parity_err_dup : 1;
        uint64_t unexpected_droop_encode : 1;
        uint64_t small_droop_err : 1;
        uint64_t large_droop_err : 1;
        uint64_t extreme_droop_err : 1;
        uint64_t cache_ivrm_dropout : 1;
        uint64_t c1_ivrm_dropout : 1;
        uint64_t c0_ivrm_dropout : 1;
        uint64_t spare12 : 1;
    uint64_t spare11 : 1;
    uint64_t bce_error : 1;
    uint64_t sram_scrub_err : 1;
    uint64_t sram_ce : 1;
    uint64_t sram_ue : 1;
    uint64_t ppe_debug_trigger : 1;
    uint64_t ppe_halted : 1;
    uint64_t ppe_watchdog : 1;
    uint64_t ppe_breakpoint_error : 1;
    uint64_t ppe_progress_error : 1;
    uint64_t ppe_external_error : 1;
    uint64_t ppe_internal_error : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lfir_t;



typedef union cme_scom_lfir_and
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t ppe_internal_error : 1;
    uint64_t ppe_external_error : 1;
    uint64_t ppe_progress_error : 1;
    uint64_t ppe_breakpoint_error : 1;
    uint64_t ppe_watchdog : 1;
    uint64_t ppe_halted : 1;
    uint64_t ppe_debug_trigger : 1;
    uint64_t sram_ue : 1;
    uint64_t sram_ce : 1;
    uint64_t sram_scrub_err : 1;
    uint64_t bce_error : 1;
    uint64_t spare11 : 1;
        uint64_t spare12 : 1;
        uint64_t c0_ivrm_dropout : 1;
        uint64_t c1_ivrm_dropout : 1;
        uint64_t cache_ivrm_dropout : 1;
        uint64_t extreme_droop_err : 1;
        uint64_t large_droop_err : 1;
        uint64_t small_droop_err : 1;
        uint64_t unexpected_droop_encode : 1;
    uint64_t fir_parity_err_dup : 1;
    uint64_t fir_parity_err : 1;
        uint64_t reserved1 : 42;
#else
        uint64_t reserved1 : 42;
    uint64_t fir_parity_err : 1;
    uint64_t fir_parity_err_dup : 1;
        uint64_t unexpected_droop_encode : 1;
        uint64_t small_droop_err : 1;
        uint64_t large_droop_err : 1;
        uint64_t extreme_droop_err : 1;
        uint64_t cache_ivrm_dropout : 1;
        uint64_t c1_ivrm_dropout : 1;
        uint64_t c0_ivrm_dropout : 1;
        uint64_t spare12 : 1;
    uint64_t spare11 : 1;
    uint64_t bce_error : 1;
    uint64_t sram_scrub_err : 1;
    uint64_t sram_ce : 1;
    uint64_t sram_ue : 1;
    uint64_t ppe_debug_trigger : 1;
    uint64_t ppe_halted : 1;
    uint64_t ppe_watchdog : 1;
    uint64_t ppe_breakpoint_error : 1;
    uint64_t ppe_progress_error : 1;
    uint64_t ppe_external_error : 1;
    uint64_t ppe_internal_error : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lfir_and_t;



typedef union cme_scom_lfir_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t ppe_internal_error : 1;
    uint64_t ppe_external_error : 1;
    uint64_t ppe_progress_error : 1;
    uint64_t ppe_breakpoint_error : 1;
    uint64_t ppe_watchdog : 1;
    uint64_t ppe_halted : 1;
    uint64_t ppe_debug_trigger : 1;
    uint64_t sram_ue : 1;
    uint64_t sram_ce : 1;
    uint64_t sram_scrub_err : 1;
    uint64_t bce_error : 1;
    uint64_t spare11 : 1;
        uint64_t spare12 : 1;
        uint64_t c0_ivrm_dropout : 1;
        uint64_t c1_ivrm_dropout : 1;
        uint64_t cache_ivrm_dropout : 1;
        uint64_t extreme_droop_err : 1;
        uint64_t large_droop_err : 1;
        uint64_t small_droop_err : 1;
        uint64_t unexpected_droop_encode : 1;
    uint64_t fir_parity_err_dup : 1;
    uint64_t fir_parity_err : 1;
        uint64_t reserved1 : 42;
#else
        uint64_t reserved1 : 42;
    uint64_t fir_parity_err : 1;
    uint64_t fir_parity_err_dup : 1;
        uint64_t unexpected_droop_encode : 1;
        uint64_t small_droop_err : 1;
        uint64_t large_droop_err : 1;
        uint64_t extreme_droop_err : 1;
        uint64_t cache_ivrm_dropout : 1;
        uint64_t c1_ivrm_dropout : 1;
        uint64_t c0_ivrm_dropout : 1;
        uint64_t spare12 : 1;
    uint64_t spare11 : 1;
    uint64_t bce_error : 1;
    uint64_t sram_scrub_err : 1;
    uint64_t sram_ce : 1;
    uint64_t sram_ue : 1;
    uint64_t ppe_debug_trigger : 1;
    uint64_t ppe_halted : 1;
    uint64_t ppe_watchdog : 1;
    uint64_t ppe_breakpoint_error : 1;
    uint64_t ppe_progress_error : 1;
    uint64_t ppe_external_error : 1;
    uint64_t ppe_internal_error : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lfir_or_t;



typedef union cme_scom_lfirmask
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t fir_mask : 22;
        uint64_t reserved1 : 42;
#else
        uint64_t reserved1 : 42;
        uint64_t fir_mask : 22;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lfirmask_t;



typedef union cme_scom_lfirmask_and
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t fir_mask : 22;
        uint64_t reserved1 : 42;
#else
        uint64_t reserved1 : 42;
        uint64_t fir_mask : 22;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lfirmask_and_t;



typedef union cme_scom_lfirmask_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t fir_mask : 22;
        uint64_t reserved1 : 42;
#else
        uint64_t reserved1 : 42;
        uint64_t fir_mask : 22;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lfirmask_or_t;



typedef union cme_scom_lfiract0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t fir_action0 : 22;
        uint64_t reserved1 : 42;
#else
        uint64_t reserved1 : 42;
        uint64_t fir_action0 : 22;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lfiract0_t;



typedef union cme_scom_lfiract1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t fir_action1 : 22;
        uint64_t reserved1 : 42;
#else
        uint64_t reserved1 : 42;
        uint64_t fir_action1 : 22;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lfiract1_t;



typedef union cme_scom_cscr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t sram_access_mode : 1;
    uint64_t sram_scrub_enable : 1;
    uint64_t ecc_correct_dis : 1;
    uint64_t ecc_detect_dis : 1;
    uint64_t ecc_inject_type : 1;
    uint64_t ecc_inject_err : 1;
    uint64_t spare_6_7 : 2;
    uint64_t reserved1 : 39;
    uint64_t sram_scrub_index : 13;
    uint64_t reserved2 : 4;
#else
    uint64_t reserved2 : 4;
    uint64_t sram_scrub_index : 13;
    uint64_t reserved1 : 39;
    uint64_t spare_6_7 : 2;
    uint64_t ecc_inject_err : 1;
    uint64_t ecc_inject_type : 1;
    uint64_t ecc_detect_dis : 1;
    uint64_t ecc_correct_dis : 1;
    uint64_t sram_scrub_enable : 1;
    uint64_t sram_access_mode : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_cscr_t;



typedef union cme_scom_cscr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t sram_access_mode : 1;
    uint64_t sram_scrub_enable : 1;
    uint64_t ecc_correct_dis : 1;
    uint64_t ecc_detect_dis : 1;
    uint64_t ecc_inject_type : 1;
    uint64_t ecc_inject_err : 1;
    uint64_t spare_6_7 : 2;
    uint64_t reserved1 : 39;
    uint64_t sram_scrub_index : 13;
    uint64_t reserved2 : 4;
#else
    uint64_t reserved2 : 4;
    uint64_t sram_scrub_index : 13;
    uint64_t reserved1 : 39;
    uint64_t spare_6_7 : 2;
    uint64_t ecc_inject_err : 1;
    uint64_t ecc_inject_type : 1;
    uint64_t ecc_detect_dis : 1;
    uint64_t ecc_correct_dis : 1;
    uint64_t sram_scrub_enable : 1;
    uint64_t sram_access_mode : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_cscr_clr_t;



typedef union cme_scom_cscr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t sram_access_mode : 1;
    uint64_t sram_scrub_enable : 1;
    uint64_t ecc_correct_dis : 1;
    uint64_t ecc_detect_dis : 1;
    uint64_t ecc_inject_type : 1;
    uint64_t ecc_inject_err : 1;
    uint64_t spare_6_7 : 2;
    uint64_t reserved1 : 39;
    uint64_t sram_scrub_index : 13;
    uint64_t reserved2 : 4;
#else
    uint64_t reserved2 : 4;
    uint64_t sram_scrub_index : 13;
    uint64_t reserved1 : 39;
    uint64_t spare_6_7 : 2;
    uint64_t ecc_inject_err : 1;
    uint64_t ecc_inject_type : 1;
    uint64_t ecc_detect_dis : 1;
    uint64_t ecc_correct_dis : 1;
    uint64_t sram_scrub_enable : 1;
    uint64_t sram_access_mode : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_cscr_or_t;



typedef union cme_scom_csar
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t reserved1 : 3;
    uint64_t reserved2 : 13;
    uint64_t sram_address : 13;
    uint64_t reserved3 : 35;
#else
    uint64_t reserved3 : 35;
    uint64_t sram_address : 13;
    uint64_t reserved2 : 13;
    uint64_t reserved1 : 3;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_csar_t;



typedef union cme_scom_csdr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t sram_data : 64;
#else
    uint64_t sram_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_csdr_t;



typedef union cme_scom_bcecsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t busy : 1;
    uint64_t error : 1;
    uint64_t start : 1;
    uint64_t stop : 1;
    uint64_t rnw : 1;
    uint64_t barsel : 1;
    uint64_t priority : 1;
    uint64_t inject_err : 1;
    uint64_t reserved1 : 5;
    uint64_t type : 3;
    uint64_t reserved2 : 1;
    uint64_t num_blocks : 11;
    uint64_t sbase : 12;
    uint64_t reserved3 : 2;
    uint64_t mbase : 22;
#else
    uint64_t mbase : 22;
    uint64_t reserved3 : 2;
    uint64_t sbase : 12;
    uint64_t num_blocks : 11;
    uint64_t reserved2 : 1;
    uint64_t type : 3;
    uint64_t reserved1 : 5;
    uint64_t inject_err : 1;
    uint64_t priority : 1;
    uint64_t barsel : 1;
    uint64_t rnw : 1;
    uint64_t stop : 1;
    uint64_t start : 1;
    uint64_t error : 1;
    uint64_t busy : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_bcecsr_t;



typedef union cme_scom_xixcr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t xcr : 32;
        uint64_t reserved1 : 32;
#else
        uint64_t reserved1 : 32;
        uint64_t xcr : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xixcr_t;



typedef union cme_scom_xiramra
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t xcr : 32;
        uint64_t sprg0 : 32;
#else
        uint64_t sprg0 : 32;
        uint64_t xcr : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xiramra_t;



typedef union cme_scom_xiramga
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t ir : 32;
        uint64_t sprg0 : 32;
#else
        uint64_t sprg0 : 32;
        uint64_t ir : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xiramga_t;



typedef union cme_scom_xiramdbg
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t xsr : 32;
        uint64_t sprg0 : 32;
#else
        uint64_t sprg0 : 32;
        uint64_t xsr : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xiramdbg_t;



typedef union cme_scom_xiramedr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t ir : 32;
        uint64_t edr : 32;
#else
        uint64_t edr : 32;
        uint64_t ir : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xiramedr_t;



typedef union cme_scom_xidbgpro
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t xsr : 32;
        uint64_t iar : 32;
#else
        uint64_t iar : 32;
        uint64_t xsr : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xidbgpro_t;



typedef union cme_scom_xisib
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pib_addr : 32;
        uint64_t reserved0 : 1;
        uint64_t pib_r_nw : 1;
        uint64_t pib_busy : 1;
        uint64_t pib_imprecise_error_pending : 1;
        uint64_t reserved1 : 13;
        uint64_t pib_rsp_info : 3;
        uint64_t reserved2 : 9;
        uint64_t pib_reset_pending : 1;
        uint64_t pib_ifetch_pending : 1;
        uint64_t pib_dataop_pending : 1;
#else
        uint64_t pib_dataop_pending : 1;
        uint64_t pib_ifetch_pending : 1;
        uint64_t pib_reset_pending : 1;
        uint64_t reserved2 : 9;
        uint64_t pib_rsp_info : 3;
        uint64_t reserved1 : 13;
        uint64_t pib_imprecise_error_pending : 1;
        uint64_t pib_busy : 1;
        uint64_t pib_r_nw : 1;
        uint64_t reserved0 : 1;
        uint64_t pib_addr : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xisib_t;



typedef union cme_scom_ximem
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t mem_addr : 32;
        uint64_t reserved0 : 1;
        uint64_t mem_r_nw : 1;
        uint64_t mem_busy : 1;
        uint64_t mem_imprecise_error_pending : 1;
        uint64_t mem_byte_enable : 8;
        uint64_t mem_line_mode : 1;
        uint64_t reserved1 : 4;
        uint64_t mem_error : 3;
        uint64_t reserved2 : 10;
        uint64_t mem_ifetch_pending : 1;
        uint64_t mem_dataop_pending : 1;
#else
        uint64_t mem_dataop_pending : 1;
        uint64_t mem_ifetch_pending : 1;
        uint64_t reserved2 : 10;
        uint64_t mem_error : 3;
        uint64_t reserved1 : 4;
        uint64_t mem_line_mode : 1;
        uint64_t mem_byte_enable : 8;
        uint64_t mem_imprecise_error_pending : 1;
        uint64_t mem_busy : 1;
        uint64_t mem_r_nw : 1;
        uint64_t reserved0 : 1;
        uint64_t mem_addr : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_ximem_t;



typedef union cme_scom_cmexisgb
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t store_address : 32;
        uint64_t reserved0 : 3;
        uint64_t mem_imprecise_error_pending : 1;
        uint64_t sgb_byte_valid : 4;
        uint64_t reserved1 : 23;
        uint64_t sgb_flush_pending : 1;
#else
        uint64_t sgb_flush_pending : 1;
        uint64_t reserved1 : 23;
        uint64_t sgb_byte_valid : 4;
        uint64_t mem_imprecise_error_pending : 1;
        uint64_t reserved0 : 3;
        uint64_t store_address : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_cmexisgb_t;



typedef union cme_scom_xiicac
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t icache_tag_addr : 27;
        uint64_t reserved0 : 5;
        uint64_t icache_err : 1;
        uint64_t reserved1 : 1;
        uint64_t pib_ifetch_pending : 1;
        uint64_t mem_ifetch_pending : 1;
        uint64_t icache_valid : 4;
        uint64_t reserved2 : 24;
#else
        uint64_t reserved2 : 24;
        uint64_t icache_valid : 4;
        uint64_t mem_ifetch_pending : 1;
        uint64_t pib_ifetch_pending : 1;
        uint64_t reserved1 : 1;
        uint64_t icache_err : 1;
        uint64_t reserved0 : 5;
        uint64_t icache_tag_addr : 27;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xiicac_t;



typedef union cme_scom_xipcbq0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t queue_entry_valid : 1;
        uint64_t queue_r_nw : 1;
        uint64_t queue_addr : 24;
        uint64_t reserved : 38;
#else
        uint64_t reserved : 38;
        uint64_t queue_addr : 24;
        uint64_t queue_r_nw : 1;
        uint64_t queue_entry_valid : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xipcbq0_t;



typedef union cme_scom_xipcbq1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t queue_entry_valid : 1;
        uint64_t queue_r_nw : 1;
        uint64_t queue_addr : 24;
        uint64_t reserved : 38;
#else
        uint64_t reserved : 38;
        uint64_t queue_addr : 24;
        uint64_t queue_r_nw : 1;
        uint64_t queue_entry_valid : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xipcbq1_t;



typedef union cme_scom_xipcbmd0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pcb_req_vld : 1;
        uint64_t pcb_rsp_ack : 1;
        uint64_t pcbmux_eps_select : 1;
        uint64_t pcbmux_pcb_req_port : 4;
        uint64_t pcbmux_pcb_req_port_p : 1;
        uint64_t pcbmux_pcb_req_rd_not_wr : 1;
        uint64_t pcbmux_pcb_req_p : 1;
        uint64_t pcbmux_pcb_req_local_addr : 16;
        uint64_t pcbmux_pcb_req_local_addr_p : 1;
        uint64_t reserved : 37;
#else
        uint64_t reserved : 37;
        uint64_t pcbmux_pcb_req_local_addr_p : 1;
        uint64_t pcbmux_pcb_req_local_addr : 16;
        uint64_t pcbmux_pcb_req_p : 1;
        uint64_t pcbmux_pcb_req_rd_not_wr : 1;
        uint64_t pcbmux_pcb_req_port_p : 1;
        uint64_t pcbmux_pcb_req_port : 4;
        uint64_t pcbmux_eps_select : 1;
        uint64_t pcb_rsp_ack : 1;
        uint64_t pcb_req_vld : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xipcbmd0_t;



typedef union cme_scom_xipcbmd1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pcb_req_vld : 1;
        uint64_t pcb_rsp_ack : 1;
        uint64_t pcbmux_eps_select : 1;
        uint64_t pcbmux_pcb_req_port : 4;
        uint64_t pcbmux_pcb_req_port_p : 1;
        uint64_t pcbmux_pcb_req_rd_not_wr : 1;
        uint64_t pcbmux_pcb_req_p : 1;
        uint64_t pcbmux_pcb_req_local_addr : 16;
        uint64_t pcbmux_pcb_req_local_addr_p : 1;
        uint64_t reserved : 37;
#else
        uint64_t reserved : 37;
        uint64_t pcbmux_pcb_req_local_addr_p : 1;
        uint64_t pcbmux_pcb_req_local_addr : 16;
        uint64_t pcbmux_pcb_req_p : 1;
        uint64_t pcbmux_pcb_req_rd_not_wr : 1;
        uint64_t pcbmux_pcb_req_port_p : 1;
        uint64_t pcbmux_pcb_req_port : 4;
        uint64_t pcbmux_eps_select : 1;
        uint64_t pcb_rsp_ack : 1;
        uint64_t pcb_req_vld : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xipcbmd1_t;



typedef union cme_scom_xipcbmi0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pcb_req_ack : 1;
        uint64_t pcb_rsp_vld : 1;
        uint64_t pcb_rsp_error : 3;
        uint64_t pcb_rsp_info : 1;
        uint64_t pcb_rsp_p : 1;
        uint64_t reserved : 57;
#else
        uint64_t reserved : 57;
        uint64_t pcb_rsp_p : 1;
        uint64_t pcb_rsp_info : 1;
        uint64_t pcb_rsp_error : 3;
        uint64_t pcb_rsp_vld : 1;
        uint64_t pcb_req_ack : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xipcbmi0_t;



typedef union cme_scom_xipcbmi1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pcb_req_ack : 1;
        uint64_t pcb_rsp_vld : 1;
        uint64_t pcb_rsp_error : 3;
        uint64_t pcb_rsp_info : 1;
        uint64_t pcb_rsp_p : 1;
        uint64_t reserved : 57;
#else
        uint64_t reserved : 57;
        uint64_t pcb_rsp_p : 1;
        uint64_t pcb_rsp_info : 1;
        uint64_t pcb_rsp_error : 3;
        uint64_t pcb_rsp_vld : 1;
        uint64_t pcb_req_ack : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_xipcbmi1_t;



typedef union cme_scom_flags
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_flags_t;



typedef union cme_scom_flags_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_flags_clr_t;



typedef union cme_scom_flags_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_flags_or_t;



typedef union cme_scom_srtch0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_srtch0_t;



typedef union cme_scom_srtch1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_srtch1_t;



typedef union cme_scom_eisr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t data : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_eisr_t;



typedef union cme_scom_eimr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t data : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_eimr_t;



typedef union cme_scom_eipr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t data : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_eipr_t;



typedef union cme_scom_eitr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t data : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_eitr_t;



typedef union cme_scom_eistr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t data : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_eistr_t;



typedef union cme_scom_einr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t data : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_einr_t;



typedef union cme_scom_eiir
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t debugger : 1;
        uint64_t debug_trigger : 1;
        uint64_t reserved_2_81 : 7;
        uint64_t bce_timeout : 1;
        uint64_t reserved_10_112 : 2;
        uint64_t pc_intr_pending_c0 : 1;
        uint64_t pc_intr_pending_c1 : 1;
        uint64_t special_wakeup_c0 : 1;
        uint64_t special_wakeup_c1 : 1;
        uint64_t reg_wakeup_c0 : 1;
        uint64_t reg_wakeup_c1 : 1;
        uint64_t reserved_18_193 : 2;
        uint64_t pc_pm_state_active_c0 : 1;
        uint64_t pc_pm_state_active_c1 : 1;
        uint64_t l2_purge_done : 1;
        uint64_t ncu_purge_done : 1;
        uint64_t chtm_purge_done_c0 : 1;
        uint64_t chtm_purge_done_c1 : 1;
        uint64_t reserved4 : 38;
#else
        uint64_t reserved4 : 38;
        uint64_t chtm_purge_done_c1 : 1;
        uint64_t chtm_purge_done_c0 : 1;
        uint64_t ncu_purge_done : 1;
        uint64_t l2_purge_done : 1;
        uint64_t pc_pm_state_active_c1 : 1;
        uint64_t pc_pm_state_active_c0 : 1;
        uint64_t reserved_18_193 : 2;
        uint64_t reg_wakeup_c1 : 1;
        uint64_t reg_wakeup_c0 : 1;
        uint64_t special_wakeup_c1 : 1;
        uint64_t special_wakeup_c0 : 1;
        uint64_t pc_intr_pending_c1 : 1;
        uint64_t pc_intr_pending_c0 : 1;
        uint64_t reserved_10_112 : 2;
        uint64_t bce_timeout : 1;
        uint64_t reserved_2_81 : 7;
        uint64_t debug_trigger : 1;
        uint64_t debugger : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_eiir_t;



typedef union cme_scom_vccr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t small_event_threshold : 16;
        uint64_t large_event_threshold : 12;
        uint64_t extreme_event_threshold : 8;
        uint64_t droop_profile_type : 2;
        uint64_t droop_timer_mode : 1;
        uint64_t droop_char_mode : 1;
        uint64_t droop_notify_enable : 1;
        uint64_t spare41_43 : 3;
        uint64_t reserved1 : 15;
        uint64_t droop_sample_rate : 5;
#else
        uint64_t droop_sample_rate : 5;
        uint64_t reserved1 : 15;
        uint64_t spare41_43 : 3;
        uint64_t droop_notify_enable : 1;
        uint64_t droop_char_mode : 1;
        uint64_t droop_timer_mode : 1;
        uint64_t droop_profile_type : 2;
        uint64_t extreme_event_threshold : 8;
        uint64_t large_event_threshold : 12;
        uint64_t small_event_threshold : 16;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_vccr_t;



typedef union cme_scom_idcr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t dropout_event_threshold : 24;
        uint64_t dropout_inarow_threshold : 8;
        uint64_t dropout_timer_mode : 1;
        uint64_t dropout_char_mode : 1;
        uint64_t sibling_core_dropout_enable : 2;
        uint64_t core_dropout_enable : 2;
        uint64_t cache_dropout_enable : 1;
        uint64_t spare : 1;
        uint64_t dropout_notify_enable : 1;
        uint64_t spare41_43 : 3;
        uint64_t reserved1 : 15;
        uint64_t dropout_sample_rate : 5;
#else
        uint64_t dropout_sample_rate : 5;
        uint64_t reserved1 : 15;
        uint64_t spare41_43 : 3;
        uint64_t dropout_notify_enable : 1;
        uint64_t spare : 1;
        uint64_t cache_dropout_enable : 1;
        uint64_t core_dropout_enable : 2;
        uint64_t sibling_core_dropout_enable : 2;
        uint64_t dropout_char_mode : 1;
        uint64_t dropout_timer_mode : 1;
        uint64_t dropout_inarow_threshold : 8;
        uint64_t dropout_event_threshold : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_idcr_t;



typedef union cme_scom_cidsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t c0_dropout_event_count : 24;
        uint64_t c0_dropout_inarow_count : 8;
        uint64_t c1_dropout_event_count : 24;
        uint64_t c1_dropout_inarow_count : 8;
#else
        uint64_t c1_dropout_inarow_count : 8;
        uint64_t c1_dropout_event_count : 24;
        uint64_t c0_dropout_inarow_count : 8;
        uint64_t c0_dropout_event_count : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_cidsr_t;



typedef union cme_scom_qidsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t cache_dropout_event_count : 24;
        uint64_t cache_dropout_inarow_count : 8;
        uint64_t dropout_sample : 3;
        uint64_t reserved1 : 29;
#else
        uint64_t reserved1 : 29;
        uint64_t dropout_sample : 3;
        uint64_t cache_dropout_inarow_count : 8;
        uint64_t cache_dropout_event_count : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_qidsr_t;



typedef union cme_scom_bcebar0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t reserved1 : 8;
        uint64_t base : 36;
        uint64_t reserved2 : 13;
        uint64_t rd_scope : 2;
        uint64_t wr_scope : 1;
        uint64_t vg_target_sel : 1;
        uint64_t size : 3;
#else
        uint64_t size : 3;
        uint64_t vg_target_sel : 1;
        uint64_t wr_scope : 1;
        uint64_t rd_scope : 2;
        uint64_t reserved2 : 13;
        uint64_t base : 36;
        uint64_t reserved1 : 8;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_bcebar0_t;



typedef union cme_scom_bcebar1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t reserved1 : 8;
        uint64_t base : 36;
        uint64_t reserved2 : 13;
        uint64_t rd_scope : 2;
        uint64_t wr_scope : 1;
        uint64_t vg_target_sel : 1;
        uint64_t size : 3;
#else
        uint64_t size : 3;
        uint64_t vg_target_sel : 1;
        uint64_t wr_scope : 1;
        uint64_t rd_scope : 2;
        uint64_t reserved2 : 13;
        uint64_t base : 36;
        uint64_t reserved1 : 8;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_bcebar1_t;



typedef union cme_scom_qfmr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t timebase : 32;
        uint64_t cycles : 32;
#else
        uint64_t cycles : 32;
        uint64_t timebase : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_qfmr_t;



typedef union cme_scom_afsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t inst_cycle_sample : 20;
        uint64_t reserved1 : 12;
        uint64_t avg_cycle_sample : 20;
        uint64_t reserved2 : 11;
        uint64_t sample_valid : 1;
#else
        uint64_t sample_valid : 1;
        uint64_t reserved2 : 11;
        uint64_t avg_cycle_sample : 20;
        uint64_t reserved1 : 12;
        uint64_t inst_cycle_sample : 20;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_afsr_t;



typedef union cme_scom_aftr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t max_cycle_sample : 20;
        uint64_t reserved1 : 12;
        uint64_t min_cycle_sample : 20;
        uint64_t reserved2 : 12;
#else
        uint64_t reserved2 : 12;
        uint64_t min_cycle_sample : 20;
        uint64_t reserved1 : 12;
        uint64_t max_cycle_sample : 20;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_aftr_t;



typedef union cme_scom_vdcr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t vdm_extreme_droop_ctr : 16;
        uint64_t vdm_large_droop_ctr : 24;
        uint64_t vdm_small_droop_ctr : 24;
#else
        uint64_t vdm_small_droop_ctr : 24;
        uint64_t vdm_large_droop_ctr : 24;
        uint64_t vdm_extreme_droop_ctr : 16;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_vdcr_t;



typedef union cme_scom_vncr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t reserved1 : 16;
        uint64_t vdm_no_droop_ctr : 24;
        uint64_t vdm_overvolt_ctr : 24;
#else
        uint64_t vdm_overvolt_ctr : 24;
        uint64_t vdm_no_droop_ctr : 24;
        uint64_t reserved1 : 16;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_vncr_t;



typedef union cme_scom_vdsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t instant_vdm_control_summary : 4;
        uint64_t instant_cache_vdm_data : 4;
        uint64_t instant_core0_vdm_data : 4;
        uint64_t instant_core1_vdm_data : 4;
        uint64_t instant_core2_vdm_data : 4;
        uint64_t instant_core3_vdm_data : 4;
        uint64_t reserved1 : 8;
        uint64_t sticky_vdm_control_summary : 4;
        uint64_t sticky_cache_vdm_data : 4;
        uint64_t sticky_core0_vdm_data : 4;
        uint64_t sticky_core1_vdm_data : 4;
        uint64_t sticky_core2_vdm_data : 4;
        uint64_t sticky_core3_vdm_data : 4;
        uint64_t reserved2 : 8;
#else
        uint64_t reserved2 : 8;
        uint64_t sticky_core3_vdm_data : 4;
        uint64_t sticky_core2_vdm_data : 4;
        uint64_t sticky_core1_vdm_data : 4;
        uint64_t sticky_core0_vdm_data : 4;
        uint64_t sticky_cache_vdm_data : 4;
        uint64_t sticky_vdm_control_summary : 4;
        uint64_t reserved1 : 8;
        uint64_t instant_core3_vdm_data : 4;
        uint64_t instant_core2_vdm_data : 4;
        uint64_t instant_core1_vdm_data : 4;
        uint64_t instant_core0_vdm_data : 4;
        uint64_t instant_cache_vdm_data : 4;
        uint64_t instant_vdm_control_summary : 4;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_vdsr_t;



typedef union cme_scom_vecr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t total_droop_event_ctr : 16;
        uint64_t small_event_profile_ctr : 16;
        uint64_t larger_droop_event_ctr : 12;
        uint64_t large_event_profile_ctr : 12;
        uint64_t extreme_droop_event_ctr : 8;
#else
        uint64_t extreme_droop_event_ctr : 8;
        uint64_t large_event_profile_ctr : 12;
        uint64_t larger_droop_event_ctr : 12;
        uint64_t small_event_profile_ctr : 16;
        uint64_t total_droop_event_ctr : 16;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_vecr_t;



typedef union cme_scom_vctr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t vdm_extreme_droop_threshold : 16;
        uint64_t vdm_large_droop_threshold : 24;
        uint64_t vdm_small_droop_threshold : 24;
#else
        uint64_t vdm_small_droop_threshold : 24;
        uint64_t vdm_large_droop_threshold : 24;
        uint64_t vdm_extreme_droop_threshold : 16;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_vctr_t;



typedef union cme_scom_lmcr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pmcr_override_en : 1;
        uint64_t pscr_override_en : 1;
        uint64_t pmsr_override_en : 1;
        uint64_t bcecsr_override_en : 1;
        uint64_t idr_lcl_sample_en : 1;
        uint64_t vdm_lcl_sample_en : 1;
        uint64_t freq_lcl_sample_en : 1;
        uint64_t lock_pcb_on_err : 1;
        uint64_t queued_wr_en : 1;
        uint64_t queued_rd_en : 1;
        uint64_t mask_purge_interface : 1;
        uint64_t auto_block_reg_wakeup_disable : 1;
        uint64_t c0_auto_special_wakeup_disable : 1;
        uint64_t c1_auto_special_wakeup_disable : 1;
        uint64_t c0_halted_stop_override_disable : 1;
        uint64_t c1_halted_stop_override_disable : 1;
        uint64_t stop_override_mode : 1;
        uint64_t stop_active_mask : 1;
        uint64_t auto_stop1_disable : 1;
        uint64_t stop1_active_enable : 1;
        uint64_t fence_eisr : 1;
        uint64_t pc_disable_droop : 1;
        uint64_t spare_22_23 : 2;
        uint64_t avg_freq_tsel : 4;
        uint64_t spare_28_31 : 4;
        uint64_t reset_imprecise_qerr : 1;
        uint64_t set_ecc_inject_err : 1;
        uint64_t reserved1 : 30;
#else
        uint64_t reserved1 : 30;
        uint64_t set_ecc_inject_err : 1;
        uint64_t reset_imprecise_qerr : 1;
        uint64_t spare_28_31 : 4;
        uint64_t avg_freq_tsel : 4;
        uint64_t spare_22_23 : 2;
        uint64_t pc_disable_droop : 1;
        uint64_t fence_eisr : 1;
        uint64_t stop1_active_enable : 1;
        uint64_t auto_stop1_disable : 1;
        uint64_t stop_active_mask : 1;
        uint64_t stop_override_mode : 1;
        uint64_t c1_halted_stop_override_disable : 1;
        uint64_t c0_halted_stop_override_disable : 1;
        uint64_t c1_auto_special_wakeup_disable : 1;
        uint64_t c0_auto_special_wakeup_disable : 1;
        uint64_t auto_block_reg_wakeup_disable : 1;
        uint64_t mask_purge_interface : 1;
        uint64_t queued_rd_en : 1;
        uint64_t queued_wr_en : 1;
        uint64_t lock_pcb_on_err : 1;
        uint64_t freq_lcl_sample_en : 1;
        uint64_t vdm_lcl_sample_en : 1;
        uint64_t idr_lcl_sample_en : 1;
        uint64_t bcecsr_override_en : 1;
        uint64_t pmsr_override_en : 1;
        uint64_t pscr_override_en : 1;
        uint64_t pmcr_override_en : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lmcr_t;



typedef union cme_scom_lmcr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pmcr_override_en : 1;
        uint64_t pscr_override_en : 1;
        uint64_t pmsr_override_en : 1;
        uint64_t bcecsr_override_en : 1;
        uint64_t idr_lcl_sample_en : 1;
        uint64_t vdm_lcl_sample_en : 1;
        uint64_t freq_lcl_sample_en : 1;
        uint64_t lock_pcb_on_err : 1;
        uint64_t queued_wr_en : 1;
        uint64_t queued_rd_en : 1;
        uint64_t mask_purge_interface : 1;
        uint64_t auto_block_reg_wakeup_disable : 1;
        uint64_t c0_auto_special_wakeup_disable : 1;
        uint64_t c1_auto_special_wakeup_disable : 1;
        uint64_t c0_halted_stop_override_disable : 1;
        uint64_t c1_halted_stop_override_disable : 1;
        uint64_t stop_override_mode : 1;
        uint64_t stop_active_mask : 1;
        uint64_t auto_stop1_disable : 1;
        uint64_t stop1_active_enable : 1;
        uint64_t fence_eisr : 1;
        uint64_t pc_disable_droop : 1;
        uint64_t spare_22_23 : 2;
        uint64_t avg_freq_tsel : 4;
        uint64_t spare_28_31 : 4;
        uint64_t reset_imprecise_qerr : 1;
        uint64_t set_ecc_inject_err : 1;
        uint64_t reserved1 : 30;
#else
        uint64_t reserved1 : 30;
        uint64_t set_ecc_inject_err : 1;
        uint64_t reset_imprecise_qerr : 1;
        uint64_t spare_28_31 : 4;
        uint64_t avg_freq_tsel : 4;
        uint64_t spare_22_23 : 2;
        uint64_t pc_disable_droop : 1;
        uint64_t fence_eisr : 1;
        uint64_t stop1_active_enable : 1;
        uint64_t auto_stop1_disable : 1;
        uint64_t stop_active_mask : 1;
        uint64_t stop_override_mode : 1;
        uint64_t c1_halted_stop_override_disable : 1;
        uint64_t c0_halted_stop_override_disable : 1;
        uint64_t c1_auto_special_wakeup_disable : 1;
        uint64_t c0_auto_special_wakeup_disable : 1;
        uint64_t auto_block_reg_wakeup_disable : 1;
        uint64_t mask_purge_interface : 1;
        uint64_t queued_rd_en : 1;
        uint64_t queued_wr_en : 1;
        uint64_t lock_pcb_on_err : 1;
        uint64_t freq_lcl_sample_en : 1;
        uint64_t vdm_lcl_sample_en : 1;
        uint64_t idr_lcl_sample_en : 1;
        uint64_t bcecsr_override_en : 1;
        uint64_t pmsr_override_en : 1;
        uint64_t pscr_override_en : 1;
        uint64_t pmcr_override_en : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lmcr_clr_t;



typedef union cme_scom_lmcr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pmcr_override_en : 1;
        uint64_t pscr_override_en : 1;
        uint64_t pmsr_override_en : 1;
        uint64_t bcecsr_override_en : 1;
        uint64_t idr_lcl_sample_en : 1;
        uint64_t vdm_lcl_sample_en : 1;
        uint64_t freq_lcl_sample_en : 1;
        uint64_t lock_pcb_on_err : 1;
        uint64_t queued_wr_en : 1;
        uint64_t queued_rd_en : 1;
        uint64_t mask_purge_interface : 1;
        uint64_t auto_block_reg_wakeup_disable : 1;
        uint64_t c0_auto_special_wakeup_disable : 1;
        uint64_t c1_auto_special_wakeup_disable : 1;
        uint64_t c0_halted_stop_override_disable : 1;
        uint64_t c1_halted_stop_override_disable : 1;
        uint64_t stop_override_mode : 1;
        uint64_t stop_active_mask : 1;
        uint64_t auto_stop1_disable : 1;
        uint64_t stop1_active_enable : 1;
        uint64_t fence_eisr : 1;
        uint64_t pc_disable_droop : 1;
        uint64_t spare_22_23 : 2;
        uint64_t avg_freq_tsel : 4;
        uint64_t spare_28_31 : 4;
        uint64_t reset_imprecise_qerr : 1;
        uint64_t set_ecc_inject_err : 1;
        uint64_t reserved1 : 30;
#else
        uint64_t reserved1 : 30;
        uint64_t set_ecc_inject_err : 1;
        uint64_t reset_imprecise_qerr : 1;
        uint64_t spare_28_31 : 4;
        uint64_t avg_freq_tsel : 4;
        uint64_t spare_22_23 : 2;
        uint64_t pc_disable_droop : 1;
        uint64_t fence_eisr : 1;
        uint64_t stop1_active_enable : 1;
        uint64_t auto_stop1_disable : 1;
        uint64_t stop_active_mask : 1;
        uint64_t stop_override_mode : 1;
        uint64_t c1_halted_stop_override_disable : 1;
        uint64_t c0_halted_stop_override_disable : 1;
        uint64_t c1_auto_special_wakeup_disable : 1;
        uint64_t c0_auto_special_wakeup_disable : 1;
        uint64_t auto_block_reg_wakeup_disable : 1;
        uint64_t mask_purge_interface : 1;
        uint64_t queued_rd_en : 1;
        uint64_t queued_wr_en : 1;
        uint64_t lock_pcb_on_err : 1;
        uint64_t freq_lcl_sample_en : 1;
        uint64_t vdm_lcl_sample_en : 1;
        uint64_t idr_lcl_sample_en : 1;
        uint64_t bcecsr_override_en : 1;
        uint64_t pmsr_override_en : 1;
        uint64_t pscr_override_en : 1;
        uint64_t pmcr_override_en : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_lmcr_or_t;



typedef union cme_scom_sicr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t data : 40;
        uint64_t reserved1 : 24;
#else
        uint64_t reserved1 : 24;
        uint64_t data : 40;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_sicr_t;



typedef union cme_scom_sicr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t data : 40;
        uint64_t reserved1 : 24;
#else
        uint64_t reserved1 : 24;
        uint64_t data : 40;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_sicr_clr_t;



typedef union cme_scom_sicr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t data : 40;
        uint64_t reserved1 : 24;
#else
        uint64_t reserved1 : 24;
        uint64_t data : 40;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_sicr_or_t;



typedef union cme_scom_pmsrs0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 64;
#else
    uint64_t data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pmsrs0_t;



typedef union cme_scom_pmsrs1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 64;
#else
    uint64_t data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pmsrs1_t;



typedef union cme_scom_pmcrs0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 64;
#else
    uint64_t data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pmcrs0_t;



typedef union cme_scom_pmcrs1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 64;
#else
    uint64_t data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pmcrs1_t;



typedef union cme_scom_pscrs00
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t spare_0 : 1;
    uint64_t sd_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t ec_a_n : 1;
    uint64_t psll_a_n : 4;
    uint64_t hyp_virt_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t hmi_exit_enable : 1;
    uint64_t tr_a_n : 2;
    uint64_t mtl_a_n : 4;
    uint64_t rl_a_n : 4;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t rl_a_n : 4;
    uint64_t mtl_a_n : 4;
    uint64_t tr_a_n : 2;
    uint64_t hmi_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_virt_exit_enable : 1;
    uint64_t psll_a_n : 4;
    uint64_t ec_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t sd_a_n : 1;
    uint64_t spare_0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pscrs00_t;



typedef union cme_scom_pscrs01
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t spare_0 : 1;
    uint64_t sd_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t ec_a_n : 1;
    uint64_t psll_a_n : 4;
    uint64_t hyp_virt_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t hmi_exit_enable : 1;
    uint64_t tr_a_n : 2;
    uint64_t mtl_a_n : 4;
    uint64_t rl_a_n : 4;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t rl_a_n : 4;
    uint64_t mtl_a_n : 4;
    uint64_t tr_a_n : 2;
    uint64_t hmi_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_virt_exit_enable : 1;
    uint64_t psll_a_n : 4;
    uint64_t ec_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t sd_a_n : 1;
    uint64_t spare_0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pscrs01_t;



typedef union cme_scom_pscrs02
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t spare_0 : 1;
    uint64_t sd_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t ec_a_n : 1;
    uint64_t psll_a_n : 4;
    uint64_t hyp_virt_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t hmi_exit_enable : 1;
    uint64_t tr_a_n : 2;
    uint64_t mtl_a_n : 4;
    uint64_t rl_a_n : 4;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t rl_a_n : 4;
    uint64_t mtl_a_n : 4;
    uint64_t tr_a_n : 2;
    uint64_t hmi_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_virt_exit_enable : 1;
    uint64_t psll_a_n : 4;
    uint64_t ec_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t sd_a_n : 1;
    uint64_t spare_0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pscrs02_t;



typedef union cme_scom_pscrs03
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t spare_0 : 1;
    uint64_t sd_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t ec_a_n : 1;
    uint64_t psll_a_n : 4;
    uint64_t hyp_virt_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t hmi_exit_enable : 1;
    uint64_t tr_a_n : 2;
    uint64_t mtl_a_n : 4;
    uint64_t rl_a_n : 4;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t rl_a_n : 4;
    uint64_t mtl_a_n : 4;
    uint64_t tr_a_n : 2;
    uint64_t hmi_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_virt_exit_enable : 1;
    uint64_t psll_a_n : 4;
    uint64_t ec_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t sd_a_n : 1;
    uint64_t spare_0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pscrs03_t;



typedef union cme_scom_pscrs10
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t spare_0 : 1;
    uint64_t sd_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t ec_a_n : 1;
    uint64_t psll_a_n : 4;
    uint64_t hyp_virt_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t hmi_exit_enable : 1;
    uint64_t tr_a_n : 2;
    uint64_t mtl_a_n : 4;
    uint64_t rl_a_n : 4;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t rl_a_n : 4;
    uint64_t mtl_a_n : 4;
    uint64_t tr_a_n : 2;
    uint64_t hmi_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_virt_exit_enable : 1;
    uint64_t psll_a_n : 4;
    uint64_t ec_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t sd_a_n : 1;
    uint64_t spare_0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pscrs10_t;



typedef union cme_scom_pscrs11
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t spare_0 : 1;
    uint64_t sd_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t ec_a_n : 1;
    uint64_t psll_a_n : 4;
    uint64_t hyp_virt_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t hmi_exit_enable : 1;
    uint64_t tr_a_n : 2;
    uint64_t mtl_a_n : 4;
    uint64_t rl_a_n : 4;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t rl_a_n : 4;
    uint64_t mtl_a_n : 4;
    uint64_t tr_a_n : 2;
    uint64_t hmi_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_virt_exit_enable : 1;
    uint64_t psll_a_n : 4;
    uint64_t ec_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t sd_a_n : 1;
    uint64_t spare_0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pscrs11_t;



typedef union cme_scom_pscrs12
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t spare_0 : 1;
    uint64_t sd_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t ec_a_n : 1;
    uint64_t psll_a_n : 4;
    uint64_t hyp_virt_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t hmi_exit_enable : 1;
    uint64_t tr_a_n : 2;
    uint64_t mtl_a_n : 4;
    uint64_t rl_a_n : 4;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t rl_a_n : 4;
    uint64_t mtl_a_n : 4;
    uint64_t tr_a_n : 2;
    uint64_t hmi_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_virt_exit_enable : 1;
    uint64_t psll_a_n : 4;
    uint64_t ec_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t sd_a_n : 1;
    uint64_t spare_0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pscrs12_t;



typedef union cme_scom_pscrs13
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t spare_0 : 1;
    uint64_t sd_a_n : 1;
    uint64_t esl_a_n : 1;
    uint64_t ec_a_n : 1;
    uint64_t psll_a_n : 4;
    uint64_t hyp_virt_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
    uint64_t hyp_db_exit_enable : 1;
    uint64_t ext_exit_enable : 1;
    uint64_t dec_exit_enable : 1;
    uint64_t hmi_exit_enable : 1;
    uint64_t tr_a_n : 2;
    uint64_t mtl_a_n : 4;
    uint64_t rl_a_n : 4;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
        uint64_t rl_a_n : 4;
        uint64_t mtl_a_n : 4;
        uint64_t tr_a_n : 2;
        uint64_t hmi_exit_enable : 1;
        uint64_t dec_exit_enable : 1;
        uint64_t ext_exit_enable : 1;
        uint64_t hyp_db_exit_enable : 1;
        uint64_t uv_db_exit_enable : 1;
        uint64_t hyp_virt_exit_enable : 1;
        uint64_t psll_a_n : 4;
        uint64_t ec_a_n : 1;
        uint64_t esl_a_n : 1;
        uint64_t sd_a_n : 1;
        uint64_t spare_0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_pscrs13_t;



typedef union cme_scom_sisr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t data : 32;
        uint64_t reserved1 : 32;
#else
        uint64_t reserved1 : 32;
        uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_sisr_t;



typedef union cme_scom_icrr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t data : 32;
        uint64_t reserved1 : 32;
#else
        uint64_t reserved1 : 32;
        uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_scom_icrr_t;



typedef union cme_lcl_eisr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t debugger : 1;
    uint64_t debug_trigger : 1;
    uint64_t quad_checkstop : 1;
    uint64_t pvref_fail : 1;
    uint64_t occ_heartbeat_lost : 1;
    uint64_t core_checkstop : 1;
        uint64_t dropout_detect : 1;
        uint64_t intercme_direct_in0 : 1;
    uint64_t bce_busy_high : 1;
    uint64_t bce_timeout : 1;
    uint64_t doorbell3_c0 : 1;
    uint64_t doorbell3_c1 : 1;
    uint64_t pc_intr_pending_c0 : 1;
    uint64_t pc_intr_pending_c1 : 1;
    uint64_t special_wakeup_c0 : 1;
    uint64_t special_wakeup_c1 : 1;
    uint64_t reg_wakeup_c0 : 1;
    uint64_t reg_wakeup_c1 : 1;
    uint64_t doorbell2_c0 : 1;
    uint64_t doorbell2_c1 : 1;
    uint64_t pc_pm_state_active_c0 : 1;
    uint64_t pc_pm_state_active_c1 : 1;
    uint64_t l2_purge_done : 1;
    uint64_t ncu_purge_done : 1;
    uint64_t chtm_purge_done_c0 : 1;
    uint64_t chtm_purge_done_c1 : 1;
    uint64_t bce_busy_low : 1;
        uint64_t final_vdm_data01 : 2;
    uint64_t comm_recvd : 1;
    uint64_t comm_send_ack : 1;
    uint64_t comm_send_nack : 1;
        uint64_t block_reg_wakeup_c0 : 1;
        uint64_t block_reg_wakeup_c1 : 1;
    uint64_t pmcr_update_c0 : 1;
    uint64_t pmcr_update_c1 : 1;
    uint64_t doorbell0_c0 : 1;
    uint64_t doorbell0_c1 : 1;
        uint64_t intercme_direct_in12 : 2;
    uint64_t doorbell1_c0 : 1;
    uint64_t doorbell1_c1 : 1;
    uint64_t reserved_42_431 : 2;
    uint64_t reserved2 : 20;
#else
    uint64_t reserved2 : 20;
    uint64_t reserved_42_431 : 2;
    uint64_t doorbell1_c1 : 1;
    uint64_t doorbell1_c0 : 1;
        uint64_t intercme_direct_in12 : 2;
    uint64_t doorbell0_c1 : 1;
    uint64_t doorbell0_c0 : 1;
    uint64_t pmcr_update_c1 : 1;
    uint64_t pmcr_update_c0 : 1;
        uint64_t block_reg_wakeup_c1 : 1;
        uint64_t block_reg_wakeup_c0 : 1;
    uint64_t comm_send_nack : 1;
    uint64_t comm_send_ack : 1;
    uint64_t comm_recvd : 1;
        uint64_t final_vdm_data01 : 2;
    uint64_t bce_busy_low : 1;
    uint64_t chtm_purge_done_c1 : 1;
    uint64_t chtm_purge_done_c0 : 1;
    uint64_t ncu_purge_done : 1;
    uint64_t l2_purge_done : 1;
    uint64_t pc_pm_state_active_c1 : 1;
    uint64_t pc_pm_state_active_c0 : 1;
    uint64_t doorbell2_c1 : 1;
    uint64_t doorbell2_c0 : 1;
    uint64_t reg_wakeup_c1 : 1;
    uint64_t reg_wakeup_c0 : 1;
    uint64_t special_wakeup_c1 : 1;
    uint64_t special_wakeup_c0 : 1;
    uint64_t pc_intr_pending_c1 : 1;
    uint64_t pc_intr_pending_c0 : 1;
    uint64_t doorbell3_c1 : 1;
    uint64_t doorbell3_c0 : 1;
    uint64_t bce_timeout : 1;
    uint64_t bce_busy_high : 1;
        uint64_t intercme_direct_in0 : 1;
        uint64_t dropout_detect : 1;
    uint64_t core_checkstop : 1;
    uint64_t occ_heartbeat_lost : 1;
    uint64_t pvref_fail : 1;
    uint64_t quad_checkstop : 1;
    uint64_t debug_trigger : 1;
    uint64_t debugger : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eisr_t;



typedef union cme_lcl_eisr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t debugger : 1;
    uint64_t debug_trigger : 1;
    uint64_t quad_checkstop : 1;
    uint64_t pvref_fail : 1;
    uint64_t occ_heartbeat_lost : 1;
    uint64_t core_checkstop : 1;
        uint64_t dropout_detect : 1;
        uint64_t intercme_direct_in0 : 1;
    uint64_t bce_busy_high : 1;
    uint64_t bce_timeout : 1;
    uint64_t doorbell3_c0 : 1;
    uint64_t doorbell3_c1 : 1;
    uint64_t pc_intr_pending_c0 : 1;
    uint64_t pc_intr_pending_c1 : 1;
    uint64_t special_wakeup_c0 : 1;
    uint64_t special_wakeup_c1 : 1;
    uint64_t reg_wakeup_c0 : 1;
    uint64_t reg_wakeup_c1 : 1;
    uint64_t doorbell2_c0 : 1;
    uint64_t doorbell2_c1 : 1;
    uint64_t pc_pm_state_active_c0 : 1;
    uint64_t pc_pm_state_active_c1 : 1;
    uint64_t l2_purge_done : 1;
    uint64_t ncu_purge_done : 1;
    uint64_t chtm_purge_done_c0 : 1;
    uint64_t chtm_purge_done_c1 : 1;
    uint64_t bce_busy_low : 1;
        uint64_t final_vdm_data01 : 2;
    uint64_t comm_recvd : 1;
    uint64_t comm_send_ack : 1;
    uint64_t comm_send_nack : 1;
        uint64_t block_reg_wakeup_c0 : 1;
        uint64_t block_reg_wakeup_c1 : 1;
    uint64_t pmcr_update_c0 : 1;
    uint64_t pmcr_update_c1 : 1;
    uint64_t doorbell0_c0 : 1;
    uint64_t doorbell0_c1 : 1;
        uint64_t intercme_direct_in12 : 2;
    uint64_t doorbell1_c0 : 1;
    uint64_t doorbell1_c1 : 1;
    uint64_t reserved_42_431 : 2;
    uint64_t reserved2 : 20;
#else
    uint64_t reserved2 : 20;
    uint64_t reserved_42_431 : 2;
    uint64_t doorbell1_c1 : 1;
    uint64_t doorbell1_c0 : 1;
        uint64_t intercme_direct_in12 : 2;
    uint64_t doorbell0_c1 : 1;
    uint64_t doorbell0_c0 : 1;
    uint64_t pmcr_update_c1 : 1;
    uint64_t pmcr_update_c0 : 1;
        uint64_t block_reg_wakeup_c1 : 1;
        uint64_t block_reg_wakeup_c0 : 1;
    uint64_t comm_send_nack : 1;
    uint64_t comm_send_ack : 1;
    uint64_t comm_recvd : 1;
        uint64_t final_vdm_data01 : 2;
    uint64_t bce_busy_low : 1;
    uint64_t chtm_purge_done_c1 : 1;
    uint64_t chtm_purge_done_c0 : 1;
    uint64_t ncu_purge_done : 1;
    uint64_t l2_purge_done : 1;
    uint64_t pc_pm_state_active_c1 : 1;
    uint64_t pc_pm_state_active_c0 : 1;
    uint64_t doorbell2_c1 : 1;
    uint64_t doorbell2_c0 : 1;
    uint64_t reg_wakeup_c1 : 1;
    uint64_t reg_wakeup_c0 : 1;
    uint64_t special_wakeup_c1 : 1;
    uint64_t special_wakeup_c0 : 1;
    uint64_t pc_intr_pending_c1 : 1;
    uint64_t pc_intr_pending_c0 : 1;
    uint64_t doorbell3_c1 : 1;
    uint64_t doorbell3_c0 : 1;
    uint64_t bce_timeout : 1;
    uint64_t bce_busy_high : 1;
        uint64_t intercme_direct_in0 : 1;
        uint64_t dropout_detect : 1;
    uint64_t core_checkstop : 1;
    uint64_t occ_heartbeat_lost : 1;
    uint64_t pvref_fail : 1;
    uint64_t quad_checkstop : 1;
    uint64_t debug_trigger : 1;
    uint64_t debugger : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eisr_or_t;



typedef union cme_lcl_eisr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t debugger : 1;
    uint64_t debug_trigger : 1;
    uint64_t quad_checkstop : 1;
    uint64_t pvref_fail : 1;
    uint64_t occ_heartbeat_lost : 1;
    uint64_t core_checkstop : 1;
        uint64_t dropout_detect : 1;
        uint64_t intercme_direct_in0 : 1;
    uint64_t bce_busy_high : 1;
    uint64_t bce_timeout : 1;
    uint64_t doorbell3_c0 : 1;
    uint64_t doorbell3_c1 : 1;
    uint64_t pc_intr_pending_c0 : 1;
    uint64_t pc_intr_pending_c1 : 1;
    uint64_t special_wakeup_c0 : 1;
    uint64_t special_wakeup_c1 : 1;
    uint64_t reg_wakeup_c0 : 1;
    uint64_t reg_wakeup_c1 : 1;
    uint64_t doorbell2_c0 : 1;
    uint64_t doorbell2_c1 : 1;
    uint64_t pc_pm_state_active_c0 : 1;
    uint64_t pc_pm_state_active_c1 : 1;
    uint64_t l2_purge_done : 1;
    uint64_t ncu_purge_done : 1;
    uint64_t chtm_purge_done_c0 : 1;
    uint64_t chtm_purge_done_c1 : 1;
    uint64_t bce_busy_low : 1;
        uint64_t final_vdm_data01 : 2;
    uint64_t comm_recvd : 1;
    uint64_t comm_send_ack : 1;
    uint64_t comm_send_nack : 1;
        uint64_t block_reg_wakeup_c0 : 1;
        uint64_t block_reg_wakeup_c1 : 1;
    uint64_t pmcr_update_c0 : 1;
    uint64_t pmcr_update_c1 : 1;
    uint64_t doorbell0_c0 : 1;
    uint64_t doorbell0_c1 : 1;
        uint64_t intercme_direct_in12 : 2;
    uint64_t doorbell1_c0 : 1;
    uint64_t doorbell1_c1 : 1;
    uint64_t reserved_42_431 : 2;
    uint64_t reserved2 : 20;
#else
    uint64_t reserved2 : 20;
    uint64_t reserved_42_431 : 2;
    uint64_t doorbell1_c1 : 1;
    uint64_t doorbell1_c0 : 1;
        uint64_t intercme_direct_in12 : 2;
    uint64_t doorbell0_c1 : 1;
    uint64_t doorbell0_c0 : 1;
    uint64_t pmcr_update_c1 : 1;
    uint64_t pmcr_update_c0 : 1;
        uint64_t block_reg_wakeup_c1 : 1;
        uint64_t block_reg_wakeup_c0 : 1;
    uint64_t comm_send_nack : 1;
    uint64_t comm_send_ack : 1;
    uint64_t comm_recvd : 1;
        uint64_t final_vdm_data01 : 2;
    uint64_t bce_busy_low : 1;
    uint64_t chtm_purge_done_c1 : 1;
    uint64_t chtm_purge_done_c0 : 1;
    uint64_t ncu_purge_done : 1;
    uint64_t l2_purge_done : 1;
    uint64_t pc_pm_state_active_c1 : 1;
    uint64_t pc_pm_state_active_c0 : 1;
    uint64_t doorbell2_c1 : 1;
    uint64_t doorbell2_c0 : 1;
    uint64_t reg_wakeup_c1 : 1;
    uint64_t reg_wakeup_c0 : 1;
    uint64_t special_wakeup_c1 : 1;
    uint64_t special_wakeup_c0 : 1;
    uint64_t pc_intr_pending_c1 : 1;
    uint64_t pc_intr_pending_c0 : 1;
    uint64_t doorbell3_c1 : 1;
    uint64_t doorbell3_c0 : 1;
    uint64_t bce_timeout : 1;
    uint64_t bce_busy_high : 1;
        uint64_t intercme_direct_in0 : 1;
        uint64_t dropout_detect : 1;
    uint64_t core_checkstop : 1;
    uint64_t occ_heartbeat_lost : 1;
    uint64_t pvref_fail : 1;
    uint64_t quad_checkstop : 1;
    uint64_t debug_trigger : 1;
    uint64_t debugger : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eisr_clr_t;



typedef union cme_lcl_eimr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_mask : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_mask : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eimr_t;



typedef union cme_lcl_eimr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_mask : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_mask : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eimr_or_t;



typedef union cme_lcl_eimr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_mask : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_mask : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eimr_clr_t;



typedef union cme_lcl_eipr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_polarity : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_polarity : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eipr_t;



typedef union cme_lcl_eipr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_polarity : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_polarity : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eipr_or_t;



typedef union cme_lcl_eipr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_polarity : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_polarity : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eipr_clr_t;



typedef union cme_lcl_eitr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_type : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_type : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eitr_t;



typedef union cme_lcl_eitr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_type : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_type : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eitr_or_t;



typedef union cme_lcl_eitr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_type : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_type : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eitr_clr_t;



typedef union cme_lcl_eistr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_status : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_status : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_eistr_t;



typedef union cme_lcl_einr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t interrupt_input : 44;
    uint64_t reserved1 : 20;
#else
    uint64_t reserved1 : 20;
    uint64_t interrupt_input : 44;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_einr_t;



typedef union cme_lcl_tsel
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t fit_sel : 4;
    uint64_t watchdog_sel : 4;
    uint64_t reserved1 : 56;
#else
    uint64_t reserved1 : 56;
    uint64_t watchdog_sel : 4;
    uint64_t fit_sel : 4;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_tsel_t;



typedef union cme_lcl_dbg
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t en_dbg : 1;
    uint64_t halt_on_xstop : 1;
    uint64_t halt_on_trig : 1;
        uint64_t reserved3 : 1;
    uint64_t en_intr_addr : 1;
    uint64_t en_trace_extra : 1;
    uint64_t en_trace_stall : 1;
    uint64_t en_wait_cycles : 1;
    uint64_t en_full_speed : 1;
        uint64_t reserved9 : 1;
        uint64_t trace_mode_sel : 2;
        uint64_t reserved12_151 : 4;
    uint64_t fir_trigger : 1;
    uint64_t mib_gpio : 3;
        uint64_t trace_data_sel : 4;
    uint64_t halt_input : 1;
        uint64_t reserved2 : 39;
#else
        uint64_t reserved2 : 39;
    uint64_t halt_input : 1;
        uint64_t trace_data_sel : 4;
    uint64_t mib_gpio : 3;
    uint64_t fir_trigger : 1;
        uint64_t reserved12_151 : 4;
        uint64_t trace_mode_sel : 2;
        uint64_t reserved9 : 1;
    uint64_t en_full_speed : 1;
    uint64_t en_wait_cycles : 1;
    uint64_t en_trace_stall : 1;
    uint64_t en_trace_extra : 1;
    uint64_t en_intr_addr : 1;
        uint64_t reserved3 : 1;
    uint64_t halt_on_trig : 1;
    uint64_t halt_on_xstop : 1;
    uint64_t en_dbg : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_dbg_t;



typedef union cme_lcl_dbg_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t en_dbg : 1;
    uint64_t halt_on_xstop : 1;
    uint64_t halt_on_trig : 1;
        uint64_t reserved3 : 1;
    uint64_t en_intr_addr : 1;
    uint64_t en_trace_extra : 1;
    uint64_t en_trace_stall : 1;
    uint64_t en_wait_cycles : 1;
    uint64_t en_full_speed : 1;
        uint64_t reserved9 : 1;
        uint64_t trace_mode_sel : 2;
        uint64_t reserved12_151 : 4;
    uint64_t fir_trigger : 1;
    uint64_t mib_gpio : 3;
        uint64_t trace_data_sel : 4;
    uint64_t halt_input : 1;
        uint64_t reserved2 : 39;
#else
        uint64_t reserved2 : 39;
    uint64_t halt_input : 1;
        uint64_t trace_data_sel : 4;
    uint64_t mib_gpio : 3;
    uint64_t fir_trigger : 1;
        uint64_t reserved12_151 : 4;
        uint64_t trace_mode_sel : 2;
        uint64_t reserved9 : 1;
    uint64_t en_full_speed : 1;
    uint64_t en_wait_cycles : 1;
    uint64_t en_trace_stall : 1;
    uint64_t en_trace_extra : 1;
    uint64_t en_intr_addr : 1;
        uint64_t reserved3 : 1;
    uint64_t halt_on_trig : 1;
    uint64_t halt_on_xstop : 1;
    uint64_t en_dbg : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_dbg_or_t;



typedef union cme_lcl_dbg_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t en_dbg : 1;
    uint64_t halt_on_xstop : 1;
    uint64_t halt_on_trig : 1;
        uint64_t reserved3 : 1;
    uint64_t en_intr_addr : 1;
    uint64_t en_trace_extra : 1;
    uint64_t en_trace_stall : 1;
    uint64_t en_wait_cycles : 1;
    uint64_t en_full_speed : 1;
        uint64_t reserved9 : 1;
        uint64_t trace_mode_sel : 2;
        uint64_t reserved12_151 : 4;
    uint64_t fir_trigger : 1;
    uint64_t mib_gpio : 3;
        uint64_t trace_data_sel : 4;
    uint64_t halt_input : 1;
        uint64_t reserved2 : 39;
#else
        uint64_t reserved2 : 39;
    uint64_t halt_input : 1;
        uint64_t trace_data_sel : 4;
    uint64_t mib_gpio : 3;
    uint64_t fir_trigger : 1;
        uint64_t reserved12_151 : 4;
        uint64_t trace_mode_sel : 2;
        uint64_t reserved9 : 1;
    uint64_t en_full_speed : 1;
    uint64_t en_wait_cycles : 1;
    uint64_t en_trace_stall : 1;
    uint64_t en_trace_extra : 1;
    uint64_t en_intr_addr : 1;
        uint64_t reserved3 : 1;
    uint64_t halt_on_trig : 1;
    uint64_t halt_on_xstop : 1;
    uint64_t en_dbg : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_dbg_clr_t;



typedef union cme_lcl_tbr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t timebase : 32;
    uint64_t cycles : 32;
#else
    uint64_t cycles : 32;
    uint64_t timebase : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_tbr_t;



typedef union cme_lcl_afsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t inst_cycle_sample : 20;
    uint64_t reserved1 : 12;
    uint64_t avg_cycle_sample : 20;
    uint64_t reserved2 : 11;
    uint64_t sample_valid : 1;
#else
    uint64_t sample_valid : 1;
    uint64_t reserved2 : 11;
    uint64_t avg_cycle_sample : 20;
    uint64_t reserved1 : 12;
    uint64_t inst_cycle_sample : 20;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_afsr_t;



typedef union cme_lcl_aftr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t max_cycle_sample : 20;
    uint64_t reserved1 : 12;
    uint64_t min_cycle_sample : 20;
    uint64_t reserved2 : 12;
#else
    uint64_t reserved2 : 12;
    uint64_t min_cycle_sample : 20;
    uint64_t reserved1 : 12;
    uint64_t max_cycle_sample : 20;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_aftr_t;



typedef union cme_lcl_lmcr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t scom_lmcr_data : 64;
#else
        uint64_t scom_lmcr_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_lmcr_t;



typedef union cme_lcl_lmcr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t scom_lmcr_data : 64;
#else
        uint64_t scom_lmcr_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_lmcr_or_t;



typedef union cme_lcl_lmcr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t scom_lmcr_data : 64;
#else
        uint64_t scom_lmcr_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_lmcr_clr_t;



typedef union cme_lcl_bcecsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t bce_data : 64;
#else
    uint64_t bce_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_bcecsr_t;



typedef union cme_lcl_pmsrs0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 64;
#else
    uint64_t data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pmsrs0_t;



typedef union cme_lcl_pmsrs1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 64;
#else
    uint64_t data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pmsrs1_t;



typedef union cme_lcl_pmcrs0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 64;
#else
    uint64_t data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pmcrs0_t;



typedef union cme_lcl_pmcrs1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 64;
#else
    uint64_t data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pmcrs1_t;



typedef union cme_lcl_pecesr0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t pece_cn_t0 : 6;
    uint64_t reserved1 : 2;
    uint64_t pece_cn_t1 : 6;
    uint64_t reserved2 : 2;
    uint64_t pece_cn_t2 : 6;
    uint64_t reserved3 : 2;
    uint64_t pece_cn_t3 : 6;
    uint64_t reserved4 : 2;
    uint64_t use_pece : 4;
        uint64_t reserved5 : 28;
#else
        uint64_t reserved5 : 28;
    uint64_t use_pece : 4;
    uint64_t reserved4 : 2;
    uint64_t pece_cn_t3 : 6;
    uint64_t reserved3 : 2;
    uint64_t pece_cn_t2 : 6;
    uint64_t reserved2 : 2;
    uint64_t pece_cn_t1 : 6;
    uint64_t reserved1 : 2;
    uint64_t pece_cn_t0 : 6;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pecesr0_t;



typedef union cme_lcl_pecesr1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t pece_cn_t0 : 6;
    uint64_t reserved1 : 2;
    uint64_t pece_cn_t1 : 6;
    uint64_t reserved2 : 2;
    uint64_t pece_cn_t2 : 6;
    uint64_t reserved3 : 2;
    uint64_t pece_cn_t3 : 6;
    uint64_t reserved4 : 2;
    uint64_t use_pece : 4;
        uint64_t reserved5 : 28;
#else
        uint64_t reserved5 : 28;
    uint64_t use_pece : 4;
    uint64_t reserved4 : 2;
    uint64_t pece_cn_t3 : 6;
    uint64_t reserved3 : 2;
    uint64_t pece_cn_t2 : 6;
    uint64_t reserved2 : 2;
    uint64_t pece_cn_t1 : 6;
    uint64_t reserved1 : 2;
    uint64_t pece_cn_t0 : 6;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pecesr1_t;



typedef union cme_lcl_pscrs00
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 24;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t data : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pscrs00_t;



typedef union cme_lcl_pscrs10
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 24;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t data : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pscrs10_t;



typedef union cme_lcl_pscrs20
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 24;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t data : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pscrs20_t;



typedef union cme_lcl_pscrs30
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 24;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t data : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pscrs30_t;



typedef union cme_lcl_pscrs01
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 24;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t data : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pscrs01_t;



typedef union cme_lcl_pscrs11
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 24;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t data : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pscrs11_t;



typedef union cme_lcl_pscrs21
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 24;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t data : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pscrs21_t;



typedef union cme_lcl_pscrs31
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 24;
    uint64_t reserved1 : 40;
#else
    uint64_t reserved1 : 40;
    uint64_t data : 24;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_pscrs31_t;



typedef union cme_lcl_flags
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_flags_t;



typedef union cme_lcl_flags_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_flags_or_t;



typedef union cme_lcl_flags_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_flags_clr_t;



typedef union cme_lcl_srtch0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_srtch0_t;



typedef union cme_lcl_srtch1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t data : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t data : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_srtch1_t;



typedef union cme_lcl_sicr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pm_entry_ack_c0 : 1;
        uint64_t pm_entry_ack_c1 : 1;
        uint64_t pm_block_interrupts_c0 : 1;
        uint64_t pm_block_interrupts_c1 : 1;
        uint64_t pm_exit_c0 : 1;
        uint64_t pm_exit_c1 : 1;
    uint64_t pcc_core_intf_quiesce_c0 : 1;
        uint64_t pcc_core_intf_quiesce_c1 : 1;
    uint64_t l2_core_intf_quiesce_c0 : 1;
        uint64_t l2_core_intf_quiesce_c1 : 1;
        uint64_t pcbmux_req_c0 : 1;
    uint64_t pcbmux_req_c1 : 1;
        uint64_t reserved_12_15 : 4;
    uint64_t special_wkup_done_c0 : 1;
    uint64_t special_wkup_done_c1 : 1;
    uint64_t l2_purge : 1;
    uint64_t l2_purge_abort : 1;
        uint64_t pc_throttle_req : 1;
    uint64_t ncu_tlbie_quiesce : 1;
    uint64_t ncu_purge : 1;
    uint64_t ncu_purge_abort : 1;
    uint64_t chtm_purge_c0 : 1;
    uint64_t chtm_purge_c1 : 1;
    uint64_t hmi_request_c0 : 1;
    uint64_t hmi_request_c1 : 1;
    uint64_t ppm_spare_out_c0 : 1;
    uint64_t ppm_spare_out_c1 : 1;
        uint64_t pc_spare_out : 2;
        uint64_t reserved1 : 32;
#else
        uint64_t reserved1 : 32;
        uint64_t pc_spare_out : 2;
    uint64_t ppm_spare_out_c1 : 1;
    uint64_t ppm_spare_out_c0 : 1;
    uint64_t hmi_request_c1 : 1;
    uint64_t hmi_request_c0 : 1;
    uint64_t chtm_purge_c1 : 1;
    uint64_t chtm_purge_c0 : 1;
    uint64_t ncu_purge_abort : 1;
    uint64_t ncu_purge : 1;
    uint64_t ncu_tlbie_quiesce : 1;
        uint64_t pc_throttle_req : 1;
    uint64_t l2_purge_abort : 1;
    uint64_t l2_purge : 1;
    uint64_t special_wkup_done_c1 : 1;
    uint64_t special_wkup_done_c0 : 1;
        uint64_t reserved_12_15 : 4;
        uint64_t pcbmux_req_c1 : 1;
        uint64_t pcbmux_req_c0 : 1;
    uint64_t l2_core_intf_quiesce_c1 : 1;
        uint64_t l2_core_intf_quiesce_c0 : 1;
    uint64_t pcc_core_intf_quiesce_c1 : 1;
    uint64_t pcc_core_intf_quiesce_c0 : 1;
        uint64_t pm_exit_c1 : 1;
        uint64_t pm_exit_c0 : 1;
        uint64_t pm_block_interrupts_c1 : 1;
        uint64_t pm_block_interrupts_c0 : 1;
        uint64_t pm_entry_ack_c1 : 1;
        uint64_t pm_entry_ack_c0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_sicr_t;



typedef union cme_lcl_sicr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pm_entry_ack_c0 : 1;
        uint64_t pm_entry_ack_c1 : 1;
        uint64_t pm_block_interrupts_c0 : 1;
        uint64_t pm_block_interrupts_c1 : 1;
        uint64_t pm_exit_c0 : 1;
        uint64_t pm_exit_c1 : 1;
    uint64_t pcc_core_intf_quiesce_c0 : 1;
        uint64_t pcc_core_intf_quiesce_c1 : 1;
    uint64_t l2_core_intf_quiesce_c0 : 1;
        uint64_t l2_core_intf_quiesce_c1 : 1;
        uint64_t pcbmux_req_c0 : 1;
    uint64_t pcbmux_req_c1 : 1;
        uint64_t reserved_12_15 : 4;
    uint64_t special_wkup_done_c0 : 1;
    uint64_t special_wkup_done_c1 : 1;
    uint64_t l2_purge : 1;
    uint64_t l2_purge_abort : 1;
        uint64_t pc_throttle_req : 1;
    uint64_t ncu_tlbie_quiesce : 1;
    uint64_t ncu_purge : 1;
    uint64_t ncu_purge_abort : 1;
    uint64_t chtm_purge_c0 : 1;
    uint64_t chtm_purge_c1 : 1;
    uint64_t hmi_request_c0 : 1;
    uint64_t hmi_request_c1 : 1;
    uint64_t ppm_spare_out_c0 : 1;
    uint64_t ppm_spare_out_c1 : 1;
        uint64_t pc_spare_out : 2;
        uint64_t reserved1 : 32;
#else
        uint64_t reserved1 : 32;
        uint64_t pc_spare_out : 2;
    uint64_t ppm_spare_out_c1 : 1;
    uint64_t ppm_spare_out_c0 : 1;
    uint64_t hmi_request_c1 : 1;
    uint64_t hmi_request_c0 : 1;
    uint64_t chtm_purge_c1 : 1;
    uint64_t chtm_purge_c0 : 1;
    uint64_t ncu_purge_abort : 1;
    uint64_t ncu_purge : 1;
    uint64_t ncu_tlbie_quiesce : 1;
        uint64_t pc_throttle_req : 1;
    uint64_t l2_purge_abort : 1;
    uint64_t l2_purge : 1;
    uint64_t special_wkup_done_c1 : 1;
    uint64_t special_wkup_done_c0 : 1;
        uint64_t reserved_12_15 : 4;
        uint64_t pcbmux_req_c1 : 1;
        uint64_t pcbmux_req_c0 : 1;
    uint64_t l2_core_intf_quiesce_c1 : 1;
        uint64_t l2_core_intf_quiesce_c0 : 1;
    uint64_t pcc_core_intf_quiesce_c1 : 1;
    uint64_t pcc_core_intf_quiesce_c0 : 1;
        uint64_t pm_exit_c1 : 1;
        uint64_t pm_exit_c0 : 1;
        uint64_t pm_block_interrupts_c1 : 1;
        uint64_t pm_block_interrupts_c0 : 1;
        uint64_t pm_entry_ack_c1 : 1;
        uint64_t pm_entry_ack_c0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_sicr_or_t;



typedef union cme_lcl_sicr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pm_entry_ack_c0 : 1;
        uint64_t pm_entry_ack_c1 : 1;
        uint64_t pm_block_interrupts_c0 : 1;
        uint64_t pm_block_interrupts_c1 : 1;
        uint64_t pm_exit_c0 : 1;
        uint64_t pm_exit_c1 : 1;
    uint64_t pcc_core_intf_quiesce_c0 : 1;
        uint64_t pcc_core_intf_quiesce_c1 : 1;
    uint64_t l2_core_intf_quiesce_c0 : 1;
        uint64_t l2_core_intf_quiesce_c1 : 1;
        uint64_t pcbmux_req_c0 : 1;
    uint64_t pcbmux_req_c1 : 1;
        uint64_t reserved_12_15 : 4;
    uint64_t special_wkup_done_c0 : 1;
    uint64_t special_wkup_done_c1 : 1;
    uint64_t l2_purge : 1;
    uint64_t l2_purge_abort : 1;
        uint64_t pc_throttle_req : 1;
    uint64_t ncu_tlbie_quiesce : 1;
    uint64_t ncu_purge : 1;
    uint64_t ncu_purge_abort : 1;
    uint64_t chtm_purge_c0 : 1;
    uint64_t chtm_purge_c1 : 1;
    uint64_t hmi_request_c0 : 1;
    uint64_t hmi_request_c1 : 1;
    uint64_t ppm_spare_out_c0 : 1;
    uint64_t ppm_spare_out_c1 : 1;
        uint64_t pc_spare_out : 2;
        uint64_t reserved1 : 32;
#else
        uint64_t reserved1 : 32;
        uint64_t pc_spare_out : 2;
    uint64_t ppm_spare_out_c1 : 1;
    uint64_t ppm_spare_out_c0 : 1;
    uint64_t hmi_request_c1 : 1;
    uint64_t hmi_request_c0 : 1;
    uint64_t chtm_purge_c1 : 1;
    uint64_t chtm_purge_c0 : 1;
    uint64_t ncu_purge_abort : 1;
    uint64_t ncu_purge : 1;
    uint64_t ncu_tlbie_quiesce : 1;
        uint64_t pc_throttle_req : 1;
    uint64_t l2_purge_abort : 1;
    uint64_t l2_purge : 1;
    uint64_t special_wkup_done_c1 : 1;
    uint64_t special_wkup_done_c0 : 1;
        uint64_t reserved_12_15 : 4;
        uint64_t pcbmux_req_c1 : 1;
        uint64_t pcbmux_req_c0 : 1;
    uint64_t l2_core_intf_quiesce_c1 : 1;
        uint64_t l2_core_intf_quiesce_c0 : 1;
    uint64_t pcc_core_intf_quiesce_c1 : 1;
    uint64_t pcc_core_intf_quiesce_c0 : 1;
        uint64_t pm_exit_c1 : 1;
        uint64_t pm_exit_c0 : 1;
        uint64_t pm_block_interrupts_c1 : 1;
        uint64_t pm_block_interrupts_c0 : 1;
        uint64_t pm_entry_ack_c1 : 1;
        uint64_t pm_entry_ack_c0 : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_sicr_clr_t;



typedef union cme_lcl_sisr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t pm_entry_ack_c0_actual : 1;
        uint64_t pm_entry_ack_c1_actual : 1;
        uint64_t pm_block_interrupts_c0_actual : 1;
        uint64_t pm_block_interrupts_c1_actual : 1;
        uint64_t pm_exit_c0_actual : 1;
        uint64_t pm_exit_c1_actual : 1;
        uint64_t reserved1 : 3;
        uint64_t pc_fused_core_mode : 1;
    uint64_t pcbmux_grant_c0 : 1;
    uint64_t pcbmux_grant_c1 : 1;
        uint64_t reserved2 : 4;
        uint64_t special_wakeup_done_c0_actual : 1;
        uint64_t special_wakeup_done_c1_actual : 1;
        uint64_t reserved3 : 12;
        uint64_t l2_intf_quiesce_done_lvl01 : 2;
        uint64_t pc_unmasked_attn_c0 : 1;
    uint64_t pc_unmasked_attn_c1 : 1;
        uint64_t pm_state_active_c0 : 1;
    uint64_t pm_state_active_c1 : 1;
        uint64_t pm_state_c0 : 4;
    uint64_t pm_state_c1 : 4;
        uint64_t pm_state_all_hv_c0 : 1;
        uint64_t pm_state_all_hv_c1 : 1;
        uint64_t pc_instr_running_c0 : 1;
        uint64_t pc_instr_running_c1 : 1;
        uint64_t pc_non_hv_running_c0 : 4;
        uint64_t pc_non_hv_running_c1 : 4;
        uint64_t allow_reg_wakeup_c0 : 1;
    uint64_t allow_reg_wakeup_c1 : 1;
        uint64_t reserved4 : 6;
#else
        uint64_t reserved4 : 6;
        uint64_t allow_reg_wakeup_c1 : 1;
        uint64_t allow_reg_wakeup_c0 : 1;
    uint64_t pc_non_hv_running_c1 : 4;
        uint64_t pc_non_hv_running_c0 : 4;
        uint64_t pc_instr_running_c1 : 1;
        uint64_t pc_instr_running_c0 : 1;
        uint64_t pm_state_all_hv_c1 : 1;
        uint64_t pm_state_all_hv_c0 : 1;
    uint64_t pm_state_c1 : 4;
        uint64_t pm_state_c0 : 4;
    uint64_t pm_state_active_c1 : 1;
        uint64_t pm_state_active_c0 : 1;
    uint64_t pc_unmasked_attn_c1 : 1;
        uint64_t pc_unmasked_attn_c0 : 1;
        uint64_t l2_intf_quiesce_done_lvl01 : 2;
        uint64_t reserved3 : 12;
        uint64_t special_wakeup_done_c1_actual : 1;
        uint64_t special_wakeup_done_c0_actual : 1;
        uint64_t reserved2 : 4;
    uint64_t pcbmux_grant_c1 : 1;
    uint64_t pcbmux_grant_c0 : 1;
        uint64_t pc_fused_core_mode : 1;
        uint64_t reserved1 : 3;
        uint64_t pm_exit_c1_actual : 1;
        uint64_t pm_exit_c0_actual : 1;
        uint64_t pm_block_interrupts_c1_actual : 1;
        uint64_t pm_block_interrupts_c0_actual : 1;
        uint64_t pm_entry_ack_c1_actual : 1;
        uint64_t pm_entry_ack_c0_actual : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_sisr_t;



typedef union cme_lcl_xipcbmd0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t pcbm_data : 64;
#else
    uint64_t pcbm_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_xipcbmd0_t;



typedef union cme_lcl_xipcbmd1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t pcbm_data : 64;
#else
    uint64_t pcbm_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_xipcbmd1_t;



typedef union cme_lcl_xipcbmi0
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t pcbm_info : 64;
#else
    uint64_t pcbm_info : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_xipcbmi0_t;



typedef union cme_lcl_xipcbmi1
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t pcbm_info : 64;
#else
    uint64_t pcbm_info : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_xipcbmi1_t;



typedef union cme_lcl_vdcr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t vdm_droop_data : 64;
#else
        uint64_t vdm_droop_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_vdcr_t;



typedef union cme_lcl_vncr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t vdm_nondroop_data : 64;
#else
        uint64_t vdm_nondroop_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_vncr_t;



typedef union cme_lcl_vdsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t vdm_sample_data : 64;
#else
        uint64_t vdm_sample_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_vdsr_t;



typedef union cme_lcl_vecr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t vdm_event_data : 64;
#else
        uint64_t vdm_event_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_vecr_t;



typedef union cme_lcl_vccr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t dropout_config_data : 64;
#else
        uint64_t dropout_config_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_vccr_t;



typedef union cme_lcl_idcr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t dropout_config_data : 64;
#else
        uint64_t dropout_config_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_idcr_t;



typedef union cme_lcl_cidsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t cidsr_sample_data : 64;
#else
        uint64_t cidsr_sample_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_cidsr_t;



typedef union cme_lcl_qidsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
        uint64_t qidsr_sample_data : 64;
#else
        uint64_t qidsr_sample_data : 64;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_qidsr_t;



typedef union cme_lcl_iccr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t cme_comm_ack : 1;
    uint64_t cme_comm_nack : 1;
        uint64_t reserved1 : 3;
        uint64_t intercme_direct_out : 3;
        uint64_t reserved2 : 1;
        uint64_t intercme_direct_in : 3;
        uint64_t reserved3 : 52;
#else
        uint64_t reserved3 : 52;
        uint64_t intercme_direct_in : 3;
        uint64_t reserved2 : 1;
        uint64_t intercme_direct_out : 3;
        uint64_t reserved1 : 3;
    uint64_t cme_comm_nack : 1;
    uint64_t cme_comm_ack : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_iccr_t;



typedef union cme_lcl_iccr_or
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t cme_comm_ack : 1;
    uint64_t cme_comm_nack : 1;
        uint64_t reserved1 : 3;
        uint64_t intercme_direct_out : 3;
        uint64_t reserved2 : 1;
        uint64_t intercme_direct_in : 3;
        uint64_t reserved3 : 52;
#else
        uint64_t reserved3 : 52;
        uint64_t intercme_direct_in : 3;
        uint64_t reserved2 : 1;
        uint64_t intercme_direct_out : 3;
        uint64_t reserved1 : 3;
    uint64_t cme_comm_nack : 1;
    uint64_t cme_comm_ack : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_iccr_or_t;



typedef union cme_lcl_iccr_clr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t cme_comm_ack : 1;
    uint64_t cme_comm_nack : 1;
        uint64_t reserved1 : 3;
        uint64_t intercme_direct_out : 3;
        uint64_t reserved2 : 1;
        uint64_t intercme_direct_in : 3;
        uint64_t reserved3 : 52;
#else
        uint64_t reserved3 : 52;
        uint64_t intercme_direct_in : 3;
        uint64_t reserved2 : 1;
        uint64_t intercme_direct_out : 3;
        uint64_t reserved1 : 3;
    uint64_t cme_comm_nack : 1;
    uint64_t cme_comm_ack : 1;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_iccr_clr_t;



typedef union cme_lcl_icsr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t cme_comm_send : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t cme_comm_send : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_icsr_t;



typedef union cme_lcl_icrr
{

    uint64_t value;
    struct
    {
#ifdef _BIG_ENDIAN
        uint32_t high_order;
        uint32_t low_order;
#else
        uint32_t low_order;
        uint32_t high_order;
#endif // _BIG_ENDIAN
    } words;
    struct
    {
#ifdef _BIG_ENDIAN
    uint64_t cme_comm_recv : 32;
    uint64_t reserved1 : 32;
#else
    uint64_t reserved1 : 32;
    uint64_t cme_comm_recv : 32;
#endif // _BIG_ENDIAN
    } fields;
} cme_lcl_icrr_t;


#endif // __ASSEMBLER__
#endif // __CME_FIRMWARE_REGISTERS_H__

