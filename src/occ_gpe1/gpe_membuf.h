/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/occ_gpe1/gpe_membuf.h $                                   */
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
#if !defined(_GPE_MEMBUF_H)
#define _GPE_MEMBUF_H

#include "ipc_structs.h"
#include "membuf_structs.h"


// Which GPE controls the PBASLAVE
#define OCI_MASTER_ID_GPE1 1


#define INBAND_ACCESS_READ 1
#define INBAND_ACCESS_WRITE 2


extern uint32_t g_inband_access_state;


// IPC interface
void gpe_membuf_scom(ipc_msg_t* i_cmd, void* i_arg);
void gpe_membuf_data(ipc_msg_t* i_cmd, void* i_arg);
void gpe_membuf_init(ipc_msg_t* i_cmd, void* i_arg);

// HCODE interfaces
/**
 * Reset the PBA slave controller
 * @param[in] pba_parms
 */
void pbaslvctl_reset(GpePbaParms* i_pba_parms);

/**
 * Configure the PBA Slave
 * @param[in] pba_parms
 */
uint64_t pbaslvctl_setup(GpePbaParms* i_pba_parms);


/**
 * Access the MEMBUF mmio over the PBA slave.
 * @param[in] Memory buffer configuration
 * @param[in] The membuf ordinal number
 * @param[in] The OCI mapped address
 * @param[io] The data to move
 * @param[in] The operation to perform
 */
int inband_access(MemBufConfiguration_t* i_config,
                   uint32_t i_instance,
                   uint32_t i_oci_addr,
                   uint64_t * io_data,
                   int      i_read_write);

/**
 * Scom one or more membuf modules
 * @param[in] The MemBufConfiguration object
 * @param[in/out] The Scom Parms object
 * @return The return code is part of the MemBufScomParms object
 */
void gpe_inband_scom(MemBufConfiguration_t* i_config,
                     MemBufScomParms_t* i_parms);


/**
 * Populate a MemBufConfiguration object for ocmb
 * @param[out] 8 byte aligned pointer to the MemBufConfiguration object.
 * @return  [0 | return code]
 * @note  The MemBufConfiguration object is shared with the 405 so
 * it needs to be in non-cacheable sram.
 */
int gpe_ocmb_configuration_create(MemBufConfiguration_t * o_config);

/**
 * Send SYNC to ocmb to effectuate the thottle values
 * @param[in] the membuf configuration
 */
int ocmb_throttle_sync(MemBufConfiguration_t* i_config);

int get_ocmb_sensorcache(MemBufConfiguration_t* i_config,
                             MemBufGetMemDataParms_t* i_parms);


#endif