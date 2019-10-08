/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/occ_405/trac/trac.h $                                     */
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

#ifndef _trac_h
#define _trac_h
//*************************************************************************/
// Includes
//*************************************************************************/
#include <trac_interface.h>
//*************************************************************************/
// Externs
//*************************************************************************/

//*************************************************************************/
// Macros
//*************************************************************************/

//*************************************************************************/
// Defines/Enums
//*************************************************************************/
#ifndef NO_TRAC_STRINGS

#define ERR_MRK         "ERR: "
#define INFO_MRK        "INF: "
#define IMP_MRK         "IMP: "
#define DBG_MRK         "DBG: "

#define MAIN_MRK        "MAIN: "
#define CMDH_MRK        "CMDH: "
#define DCOM_MRK        "DCOM: "
#define INTR_MRK        "INTR: "
#define SNPS_MRK        "SNPS: "

//NOTE: TRAC_ERR must be used for tracing error related information only
//      TRAC_IMP must be used for tracing important OCC state/status that
//               changes once or twice OCC lifetime. It must NOT be used
//               for tracing anything that seems important to particular
//               developer. This trace buffer must not wrap so use it with
//               caution.
//      TRAC_INFO must be used for anything that does not fall under
//               TRAC_ERR or TRAC_IMP. Any debug or informational traces.
//      TRAC_DBG must be used for debug purpose only. This traces will be
//               turned OFF with product code.
#if TRAC_TO_SIMICS

#define TRAC_ERR(frmt,args...)  \
        printf(ERR_MRK "%s: "frmt "\n",__FUNCTION__,##args); \
        TRACE(&g_des_array[ERR_TRACE_DESCRIPTOR],frmt,##args)
#define TRAC_INFO(frmt,args...)  \
        printf(INFO_MRK "%s: "frmt "\n",__FUNCTION__,##args); \
        TRACE(&g_des_array[INF_TRACE_DESCRIPTOR],frmt,##args)
#define TRAC_IMP(frmt,args...)  \
        printf(IMP_MRK "%s: "frmt "\n",__FUNCTION__,##args); \
        TRACE(&g_des_array[IMP_TRACE_DESCRIPTOR],frmt,##args)
#define DBG_PRINT(fmt,args...)  \
        printf(DBG_MRK "%s: "fmt "\n",__FUNCTION__,##args); \
        TRACEBIN(&g_des_array[INF_TRACE_DESCRIPTOR], string, data,len)

extern void dumpHexString(const void *i_data, const unsigned int len, const char *string);
#define DEBUG_HEXDUMP(data, len, string)  \
        dumpHexString(data, len, string)

#else  //TRAC_TO_SIMICS


#define TRAC_ERR(frmt,args...)  \
        TRACE(&g_des_array[ERR_TRACE_DESCRIPTOR],frmt,##args)
#define TRAC_INFO(frmt,args...)  \
        TRACE(&g_des_array[INF_TRACE_DESCRIPTOR],frmt,##args)
#define TRAC_IMP(frmt,args...)  \
        TRACE(&g_des_array[IMP_TRACE_DESCRIPTOR],frmt,##args)
#define DBG_PRINT(fmt,args...)  \
        TRACE(&g_des_array[INF_TRACE_DESCRIPTOR],DBG_MRK fmt,##args)
#define DEBUG_HEXDUMP(data, len, string)  \
        TRACE(&g_des_array[INF_TRACE_DESCRIPTOR],DBG_MRK string " %d byte HEX DUMP", len)

#endif  //TRAC_TO_SIMICS

// Tracing for main thread (call home, health monitor, fir data, thermal)
#define MAIN_TRAC_ERR(frmt,args...) \
        TRAC_ERR(MAIN_MRK frmt, ##args)

#define MAIN_TRAC_INFO(frmt,args...) \
        TRAC_INFO(MAIN_MRK frmt, ##args)

#define MAIN_TRAC_IMP(frmt,args...) \
        TRAC_IMP(MAIN_MRK frmt, ##args)

// Tracing for command handler thread
#define CMDH_TRAC_ERR(frmt,args...) \
        TRAC_ERR(CMDH_MRK frmt, ##args)

#define CMDH_TRAC_INFO(frmt,args...) \
        TRAC_INFO(CMDH_MRK frmt, ##args)

#define CMDH_TRAC_IMP(frmt,args...) \
        TRAC_IMP(CMDH_MRK frmt, ##args)

// Tracing for dcom thread
#define DCOM_TRAC_ERR(frmt,args...) \
        TRAC_ERR(DCOM_MRK frmt, ##args)

#define DCOM_TRAC_INFO(frmt,args...) \
        TRAC_INFO(DCOM_MRK frmt, ##args)

#define DCOM_TRAC_IMP(frmt,args...) \
        TRAC_IMP(DCOM_MRK frmt, ##args)

// Tracing for the snapshot thread
#define SNPS_TRAC_ERR(frmt,args...) \
        TRAC_ERR(SNPS_MRK frmt, ##args)

#define SNPS_TRAC_INFO(frmt,args...) \
        TRAC_INFO(SNPS_MRK frmt, ##args)

#define SNPS_TRAC_IMP(frmt,args...) \
        TRAC_IMP(SNPS_MRK frmt, ##args)

// Tracing for interrupts (RTL, oversubscription, etc)
#define INTR_TRAC_ERR(frmt,args...) \
        TRAC_ERR(INTR_MRK frmt, ##args)

#define INTR_TRAC_INFO(frmt,args...) \
        TRAC_INFO(INTR_MRK frmt, ##args)

#define INTR_TRAC_IMP(frmt,args...) \
        TRAC_IMP(INTR_MRK frmt, ##args)



#ifdef MAIN_DEBUG
  #define MAIN_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define MAIN_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define MAIN_DBG(frmt,args...)
  #define MAIN_DBG_HEXDUMP(data, len, string)
#endif

#ifdef RTLS_DEBUG
  #define RTLS_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define RTLS_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define RTLS_DBG(frmt,args...)
  #define RTLS_DBG_HEXDUMP(data, len, string)
#endif

#ifdef PROC_DEBUG
  #define PROC_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define PROC_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define PROC_DBG(frmt,args...)
  #define PROC_DBG_HEXDUMP(data, len, string)
#endif

#ifdef AMEC_DEBUG
  #define AMEC_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define AMEC_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define AMEC_DBG(frmt,args...)
  #define AMEC_DBG_HEXDUMP(data, len, string)
#endif

#ifdef DCOM_DEBUG
  #define DCOM_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define DCOM_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define DCOM_DBG(frmt,args...)
  #define DCOM_DBG_HEXDUMP(data, len, string)
#endif

#ifdef APSS_DEBUG
  #define APSS_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define APSS_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define APSS_DBG(frmt,args...)
  #define APSS_DBG_HEXDUMP(data, len, string)
#endif

#ifdef CMDH_DEBUG
  #define CMDH_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define CMDH_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define CMDH_DBG(frmt,args...)
  #define CMDH_DBG_HEXDUMP(data, len, string)
#endif

#ifdef SNSR_DEBUG
  #define SNSR_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define SNSR_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define SNSR_DBG(frmt,args...)
  #define SNSR_DBG_HEXDUMP(data, len, string)
#endif

#ifdef CNFG_DEBUG
  #define CNFG_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define CNFG_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define CNFG_DBG(frmt,args...)
  #define CNFG_DBG_HEXDUMP(data, len, string)
#endif

#ifdef MEM_DEBUG
  #define MEM_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
  #define MEM_DBG_HEXDUMP(data, len, string)  \
          DEBUG_HEXDUMP(data, len, string)
#else
  #define MEM_DBG(frmt,args...)
  #define MEM_DBG_HEXDUMP(data, len, string)
#endif

#ifdef PGPE_DEBUG
  #define PGPE_DBG(frmt,args...)  \
          DBG_PRINT(frmt,##args)
#else
  #define PGPE_DBG(frmt,args...)
#endif

#else // NO_TRAC_STRINGS

#define TRAC_ERR(frmt,args...)
#define TRAC_INFO(frmt,args...)
#define TRAC_IMP(frmt,args...)

#define MAIN_DBG(frmt,args...)
#define RTLS_DBG(frmt,args...)
#define PROC_DBG(frmt,args...)
#define AMEC_DBG(frmt,args...)
#define DCOM_DBG(frmt,args...)
#define CMDH_DBG(frmt,args...)
#define APSS_DBG(frmt,args...)
#define SNSR_DBG(frmt,args...)
#define CNFG_DBG(frmt,args...)

#define MAIN_DBG_HEXDUMP(frmt,args...)
#define RTLS_DBG_HEXDUMP(frmt,args...)
#define PROC_DBG_HEXDUMP(frmt,args...)
#define AMEC_DBG_HEXDUMP(frmt,args...)
#define DCOM_DBG_HEXDUMP(frmt,args...)
#define CMDH_DBG_HEXDUMP(frmt,args...)
#define APSS_DBG_HEXDUMP(frmt,args...)
#define SNSR_DBG_HEXDUMP(frmt,args...)
#define CNFG_DBG_HEXDUMP(frmt,args...)

#endif

//*************************************************************************
// Structures
//*************************************************************************

//*************************************************************************
// Globals
//*************************************************************************

//*************************************************************************
// Function Prototypes
//*************************************************************************

//*************************************************************************
// Functions
//*************************************************************************

#endif // _trac_h
