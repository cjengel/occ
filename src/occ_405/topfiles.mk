# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: src/occ_405/topfiles.mk $
#
# OpenPOWER OnChipController Project
#
# Contributors Listed Below - COPYRIGHT 2015,2019
# [+] International Business Machines Corp.
#
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied. See the License for the specific language governing
# permissions and limitations under the License.
#
# IBM_PROLOG_END_TAG
TOP-C-SOURCES = amec/amec_controller.c \
                amec/amec_data.c \
                amec/amec_dps.c \
                amec/amec_freq.c \
                amec/amec_health.c \
                amec/amec_init.c \
                amec/amec_amester.c \
                amec/amec_master_smh.c \
                amec/amec_oversub.c \
                amec/amec_parm.c \
                amec/amec_parm_table.c \
                amec/amec_part.c \
                amec/amec_pcap.c \
                amec/amec_perfcount.c \
                amec/amec_sensors_fw.c \
                amec/amec_sensors_power.c \
                amec/amec_sensors_ocmb.c \
                amec/amec_sensors_core.c \
                amec/amec_slave_smh.c \
                amec/amec_tasks.c \
                amec/sensor_power.c \
                cmdh/cmdh_dbug_cmd.c \
                cmdh/cmdh_fsp_cmds_datacnfg.c \
                cmdh/cmdh_fsp_cmds.c \
                cmdh/cmdh_fsp.c \
                cmdh/cmdh_mnfg_intf.c \
                cmdh/cmdh_snapshot.c \
                cmdh/cmdh_thread.c \
                cmdh/cmdh_tunable_parms.c \
                cmdh/ffdc.c \
                common.c \
                dcom/dcom.c \
                dcom/dcom_thread.c \
                dcom/dcomMasterRx.c \
                dcom/dcomMasterTx.c \
                dcom/dcomSlaveRx.c \
                dcom/dcomSlaveTx.c \
                errl/errl.c \
                gpu/gpu.c \
                homer.c \
                lock/lock.c \
                main.c \
                mem/memory.c \
                mem/memory_data.c \
                mem/ocmb_control.c \
                mem/ocmb_data.c \
                mode.c \
                occ_sys_config.c \
                occbuildname.c \
                pgpe/pgpe_interface.c \
                proc/proc_data.c \
                proc/proc_data_control.c \
                proc/proc_pstate.c \
                pss/apss.c \
                pss/avsbus.c \
                pss/dpss.c \
                reset.c \
                rtls/rtls_tables.c \
                rtls/rtls.c \
                scom.c \
                sensor/sensor_get_tod_task.c \
                sensor/sensor_inband_cmd.c \
                sensor/sensor_info.c \
                sensor/sensor_main_memory.c \
                sensor/sensor_query_list.c \
                sensor/sensor_table.c \
                sensor/sensor.c \
                state.c \
                thread/chom.c \
                thread/threadSch.c \
                timer/timer.c \
                trac/trac_interface.c \
                wof/wof.c

TOP-S-SOURCES = cmdh/ll_ffdc.S \


TOP_OBJECTS = $(TOP-C-SOURCES:.c=.o) $(TOP-S-SOURCES:.S=.o)
