/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/occ_405/cmdh/cmdh_fsp.h $                                 */
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

#ifndef _CMDH_FSP_H
#define _CMDH_FSP_H

#include "cmdh_service_codes.h"
#include "errl.h"
#include "trac.h"
#include "rtls.h"
#include "occ_common.h"
#include "state.h"
#include "occhw_async.h"
#include "chip_config.h"

// Register Addresses for Mailbox 1 Doorbell Status/Control
#define MAILBOX_1_DOORBELL_STS_CTRL_REGADDR   0x00050020

// Register Addresses for (unused) Mailbox 1 Header Buffer
#define MAILBOX_1_HEADER_COMMAND_BASE         0x00050021
#define MAILBOX_1_HEADER_COMMAND_0_A_REGADDR  (0 + MAILBOX_1_HEADER_COMMAND_BASE)
#define MAILBOX_1_HEADER_COMMAND_1_A_REGADDR  (1 + MAILBOX_1_HEADER_COMMAND_BASE)
#define MAILBOX_1_HEADER_COMMAND_2_A_REGADDR  (2 + MAILBOX_1_HEADER_COMMAND_BASE)

// Register Addresses for Mailbox 1 Data Buffer
#define MAILBOX_1_DATA_AREA_A_BASE            0x00050040
#define MAILBOX_1_DATA_AREA_A_0_REGADDR       (0 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_1_REGADDR       (1 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_2_REGADDR       (2 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_3_REGADDR       (3 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_4_REGADDR       (4 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_5_REGADDR       (5 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_6_REGADDR       (6 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_7_REGADDR       (7 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_8_REGADDR       (8 + MAILBOX_1_DATA_AREA_A_BASE)
#define MAILBOX_1_DATA_AREA_A_9_REGADDR       (9 + MAILBOX_1_DATA_AREA_A_BASE)

// Command/Response Common:  DataLength Field Size - 2 bytes
#define CMDH_FSP_DATALEN_SIZE     2
// Command/Response Common:  Checksum Field Size - 2 bytes
#define CMDH_FSP_CHECKSUM_SIZE    2

// Command:  Full Buffer Size - 4 kB
#define CMDH_FSP_CMD_SIZE         4096
// Command:  Seq + Cmd - 2 bytes
#define CMDH_FSP_SEQ_CMD_SIZE     2
// Command:  Maximum "Data" Field Length
#define CMDH_FSP_CMD_DATA_SIZE    (CMDH_FSP_CMD_SIZE      -     \
        CMDH_FSP_DATALEN_SIZE  -     \
        CMDH_FSP_CHECKSUM_SIZE -     \
        CMDH_FSP_SEQ_CMD_SIZE )

// Response:  Full Buffer Size - 4 kB
#define CMDH_FSP_RSP_SIZE         4096
// Response:  Seq + Cmd + RC - 3 bytes
#define CMDH_FSP_SEQ_CMD_RC_SIZE  3
// Response:  Extra bytes TMGT needs for HWSV overhead - 8 bytes
#define CMDH_FSP_TMGT_EXTRA_SIZE  8

// Response:  Maximum "Data" Field Length
#define CMDH_FSP_RSP_DATA_SIZE     (CMDH_FSP_RSP_SIZE      -     \
        CMDH_FSP_TMGT_EXTRA_SIZE -     \
        CMDH_FSP_DATALEN_SIZE  -     \
        CMDH_FSP_CHECKSUM_SIZE -     \
        CMDH_FSP_SEQ_CMD_RC_SIZE    )

// Sender IDs of an attention to the OCC
#define ATTN_SENDER_ID_FSP        0x01
#define ATTN_SENDER_ID_HTMGT      0x10
#define ATTN_SENDER_ID_BMC        0x20

// Attention type of an attention to the OCC
#define ATTN_TYPE_CMD_WRITE       0x01

// Typedef of the various reasons why the cmdh thread wakes up
typedef enum
{
    // Success, alert was sent
    CMDH_WAKEUP_REASON_NONE                   = 0x00000000,
    CMDH_WAKEUP_FSP_COMMAND                   = 0x00000001,
} eCmdhWakeupThreadMask;

// Typedef of the various errors that can happen on alerts
typedef enum
{
    // Success, alert was sent
    OCC_ALERT_SUCCESS                  = 0,

    // SCOM Failure, Return PCB Error code
    OCC_ALERT_SCOM_FAILURE_RSVD_0      = 1,   // Resource Occupied
    OCC_ALERT_SCOM_FAILURE_RSVD_1      = 2,   // Chiplet Offline
    OCC_ALERT_SCOM_FAILURE_RSVD_2      = 3,   // Partial Good
    OCC_ALERT_SCOM_FAILURE_RSVD_4      = 4,   // Address Error
    OCC_ALERT_SCOM_FAILURE_RSVD_5      = 5,   // Clock Error
    OCC_ALERT_SCOM_FAILURE_RSVD_6      = 6,   // Packet Error
    OCC_ALERT_SCOM_FAILURE_RSVD_7      = 7,   // Timeout

    // Failure due to lbus_slaveA_pending bit being set
    // (meaning that FSP hasn't gotten last message)
    OCC_ALERT_LAST_ATTN_NOT_COMPLETE   = 8,
} eFspAlertRc;


// Typedef of the various 1-byte error codes that a return packet may
// contain. Returning any value except for "Success" or "Conditional
// success" requires that the return packet to TMGT be an
// errl_generic_resp_t packet.
typedef enum
{
    // Success
    ERRL_RC_SUCCESS             = 0x00,
    // Command was accepted and processed, however more processing may be needed
    ERRL_RC_CONDITIONAL_SUCCESS = 0x01,
    // The command type is invalid
    ERRL_RC_INVALID_CMD         = 0x11,
    // The command data length is invalid for the particular command
    ERRL_RC_INVALID_CMD_LEN     = 0x12,
    // The command data has an invalid value for a field
    ERRL_RC_INVALID_DATA        = 0x13,
    // The command packet checksum is not correct
    ERRL_RC_CHECKSUM_FAIL       = 0x14,
    // An error occurred within the TPMF to prevent the command processing
    ERRL_RC_INTERNAL_FAIL       = 0x15,
    // The OCC cannot accept the command in its present state
    ERRL_RC_INVALID_STATE       = 0x16,
    // The specified command is not supported in Secure Memory Facility mode
    ERRL_RC_NO_SUPPORT_IN_SMF_MODE = 0x17,
    // This is a panic response
    ERRL_RC_PANIC               = 0xE0,
    // This is a checkpoint response
    ERRL_RC_INIT_CHCKPNT        = 0xE1,
    // Halting due to OCC watchdog timer expiration
    ERRL_RC_WDOG_TIMER          = 0xE2,
    // Halting due to OCB timer expiration
    ERRL_RC_OCB_TIMER           = 0xE3,
    // Halting due to failure during init
    ERRL_RC_OCC_INIT_FAILURE    = 0xE5,
    // The command is being processed by OCC
    ERRL_RC_CMD_IN_PROGRESS     = 0xFF,
} ERRL_RC;

#define CMDH_DATALEN_FIELD_UINT16(cmdOrRspPtr) \
    (CONVERT_UINT8_ARRAY_UINT16(cmdOrRspPtr->data_length[0], \
                                cmdOrRspPtr->data_length[1]))
// Faking out an inheritable anonymous struct definition, so it works
// with the same syntax that is used in C11 version of the C-standard
// Contains TMGT command common fields (seq, cmd, data_len)
#define cmdh_fsp_cmd_header \
    __attribute__ ((packed)) { \
        uint8_t   seq; \
        uint8_t   cmd_type; \
        uint8_t   data_length[CMDH_FSP_DATALEN_SIZE]; \
    }

// Contains TMGT command common fields (seq, cmd, data_len)
typedef struct  __attribute__ ((packed))
{
    struct    cmdh_fsp_cmd_header;
} cmdh_fsp_cmd_header_t;

// Contains TMGT command fields
typedef struct __attribute__ ((packed))
{
    // Response header that is the same for all commands..seq,cmd,rc,etc
    struct    cmdh_fsp_cmd_header;
    // Data bytes (here it is the max data size)
    uint8_t   data[CMDH_FSP_CMD_DATA_SIZE];
    // 2 bytes reserved for Checksum, although the checksum usually doesn't
    // actually go here in practice
    uint8_t   __checksum_rsvd[CMDH_FSP_CHECKSUM_SIZE];
}cmdh_fsp_cmd_t;

// Faking out an inheritable anonymous struct definition, so it works
// with the same syntax that is used in C11 version of the C-standard
// Contains TMGT command common fields (seq, cmd, rc, data_len)
#define cmdh_fsp_rsp_header \
    __attribute__ ((packed)) { \
        uint8_t   seq; \
        uint8_t   cmd_type; \
        uint8_t   rc; \
        uint8_t   data_length[CMDH_FSP_DATALEN_SIZE]; \
    }

// Contains TMGT command common fields (seq, cmd, rc, data_len)
typedef struct  __attribute__ ((packed))
{
    struct    cmdh_fsp_rsp_header;
} cmdh_fsp_rsp_header_t;

// Contains TMGT command response fields
typedef struct  __attribute__ ((packed))
{
    // Response header that is the same for all commands..seq,cmd,rc,etc
    struct    cmdh_fsp_rsp_header;
    // Data bytes (here it is the max data size)
    uint8_t   data[CMDH_FSP_RSP_DATA_SIZE];
    // 2 bytes reserved for Checksum, although the checksum usually doesn't
    // actually go here in practice
    uint8_t   __checksum_rsvd[CMDH_FSP_CHECKSUM_SIZE];
}cmdh_fsp_rsp_t;

// Contains "data" fields needed to receive/parse a command from TMGT
typedef struct
{
    union
    {
        // Accessible as response fields split up..seq, cmd, etc
        cmdh_fsp_cmd_t fields;
        // Accessible as byte array for checksum, etc.
        uint8_t byte[CMDH_FSP_CMD_SIZE];
    };
} fsp_cmd_t;

// Contains "data" fields needed to respond to a command from TMGT
typedef struct
{
    union
    {
        // Accessible as response fields split up..seq, cmd, rc, etc
        cmdh_fsp_rsp_t fields;
        // Accessible as byte array for checksum, etc.
        uint8_t byte[CMDH_FSP_CMD_SIZE];
    };
} fsp_rsp_t;

// Contains "data" needed to handle a command to/from TMGT
typedef struct __attribute__ ((packed))
{
    // Pointer to FSP->OCC Command Buffer
    fsp_cmd_t * cmd;
    // Pointer to FSP->OCC Response Buffer
    fsp_rsp_t * rsp;
    // Placeholder for the 8 bytes of doorbell data that is automatically
    // sent as part of the doorbell from FSP
    uint8_t doorbell[8];
} fsp_msg_t;

extern fsp_msg_t G_fsp_msg;

// Typedef of a generic failure response packet to TMGT. Any command
// handler may return this packet in place of its normal return packet.
typedef struct errl_generic_resp {
    // Header that is the same for any TMGT response
    struct    cmdh_fsp_rsp_header;
    // Any non-zero value indicates the log id associated with a TPMF error log
    uint8_t   log_id;
    // Command Checksum, supplied by CMDH
    uint8_t   checksum[2];
} errl_generic_resp_t;

// Breakdown of the Mailbox1 Status/Control Reg, which OCC uses
// to alert TMGT.
typedef struct
{
    union
    {
        struct {
#if 1
            uint64_t    permission_to_send   :1;
            uint64_t    abort                :1;
            uint64_t    lbus_slaveA_pending  :1;
            uint64_t    pib_slaveB_pending   :1;
            uint64_t    _reserved_1          :1;
            uint64_t    xdn                  :1;
            uint64_t    xup                  :1;
            uint64_t    _reserved_2          :1;
            uint64_t    lbus_slaveA_hdr_cnt  :4;
            uint64_t    lbus_slaveA_data_cnt :8;
            uint64_t    pib_slaveB_hdr_cnt   :4;
            uint64_t    pib_slaveB_data_cnt  :8;
            uint64_t    _reserved_0          :32;
#else
            uint64_t    _reserved_0          :32;
            uint64_t    lbus_slaveA_data_cnt :8;
            uint64_t    lbus_slaveA_hdr_cnt  :4;
            uint64_t    pib_slaveB_data_cnt  :8;
            uint64_t    pib_slaveB_hdr_cnt   :4;
            uint64_t    _reserved_2          :1;
            uint64_t    xup                  :1;
            uint64_t    xdn                  :1;
            uint64_t    _reserved_1          :1;
            uint64_t    pib_slaveB_pending   :1;
            uint64_t    lbus_slaveA_pending  :1;
            uint64_t    abort                :1;
            uint64_t    permission_to_send   :1;
#endif
        };
        uint64_t doubleword;
    };
} doorbl_stsctrl_reg_t;

extern eCmdhWakeupThreadMask G_cmdh_thread_wakeup_mask;
extern fsp_cmd_t G_htmgt_cmd_buffer;
extern fsp_rsp_t G_htmgt_rsp_buffer;
extern uint8_t  G_rsp_status;

// Defines for Internal flags used for debug
// To set flags:  tmgtclient -X 0x40 --data 0x1f<4 byte value for G_internal_flags>
extern uint32_t G_internal_flags;
#define INT_FLAG_DISABLE_24X7               0x00000001
#define INT_FLAG_ENABLE_VDD_CURRENT_READ    0x00000008  // only applies if have at least PGPE P9' support
#define INT_FLAG_ENABLE_OCS_HOLD_NEW        0x00000010  // only applies if P10_OCS is enabled
#define INT_FLAG_ENABLE_P10_OCS             0x00000020  // will really only be enabled if also have at least PGPE P9' support
#define INT_FLAG_DISABLE_CEFF_TRACKING      0x00000040  // enabled by default with PGPE P9' support
#define INT_FLAG_ENABLE_WOF_CHAR_TEST       0x00000080  // special WOF testing mode requested by Frank
#define INT_FLAG_ENABLE_MEMORY_CONFIG       0x00000100  // temporary flag to re-enable memory until testing completed

void notifyCmdhWakeupCondition(eCmdhWakeupThreadMask i_cond);
void clearCmdhWakeupCondition(eCmdhWakeupThreadMask i_cond);
int cmdh_thread_wait_for_wakeup(void);

errlHndl_t cmdh_fsp_cmd_hndler(void);

void cmdh_comm_init(void);

void cmdh_build_errl_rsp(const cmdh_fsp_cmd_t * i_cmd_ptr,
                         cmdh_fsp_rsp_t       * o_rsp_ptr,
                         ERRL_RC                i_rc,
                         errlHndl_t           * io_errlHndl);

#endif

