/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    chchecks.h
 * @brief   Configuration file checks header.
 */

#ifndef CHCHECKS_H
#define CHCHECKS_H

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/* Configuration file checks.*/
#if !defined(_CHIBIOS_RT_CONF_)
#error "invalid configuration file"
#endif

#if !defined(_CHIBIOS_RT_CONF_VER_5_1_)
#error "obsolete or unknown configuration file"
#endif

/* System timers checks.*/
#if !defined(CH_CFG_ST_RESOLUTION)
#error "CH_CFG_ST_RESOLUTION not defined in chconf.h"
#endif

#if !defined(CH_CFG_ST_FREQUENCY)
#error "CH_CFG_ST_FREQUENCY not defined in chconf.h"
#endif

#if !defined(CH_CFG_INTERVALS_SIZE)
#error "CH_CFG_INTERVALS_SIZE not defined in chconf.h"
#endif

#if !defined(CH_CFG_TIME_TYPES_SIZE)
#error "CH_CFG_TIME_TYPES_SIZE not defined in chconf.h"
#endif

#if !defined(CH_CFG_ST_TIMEDELTA)
#error "CH_CFG_ST_TIMEDELTA not defined in chconf.h"
#endif

/* Kernel parameters and options checks.*/
#if !defined(CH_CFG_TIME_QUANTUM)
#error "CH_CFG_TIME_QUANTUM not defined in chconf.h"
#endif

#if !defined(CH_CFG_MEMCORE_SIZE)
#error "CH_CFG_MEMCORE_SIZE not defined in chconf.h"
#endif

#if !defined(CH_CFG_NO_IDLE_THREAD)
#error "CH_CFG_NO_IDLE_THREAD not defined in chconf.h"
#endif

/* Performance options checks.*/
#if !defined(CH_CFG_OPTIMIZE_SPEED)
#error "CH_CFG_OPTIMIZE_SPEED not defined in chconf.h"
#endif

/* Subsystem options checks.*/
#if !defined(CH_CFG_USE_TM)
#error "CH_CFG_USE_TM not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_REGISTRY)
#error "CH_CFG_USE_REGISTRY not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_WAITEXIT)
#error "CH_CFG_USE_WAITEXIT not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_SEMAPHORES)
#error "CH_CFG_USE_SEMAPHORES not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_SEMAPHORES_PRIORITY)
#error "CH_CFG_USE_SEMAPHORES_PRIORITY not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_MUTEXES)
#error "CH_CFG_USE_MUTEXES not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_MUTEXES_RECURSIVE)
#error "CH_CFG_USE_MUTEXES_RECURSIVE not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_CONDVARS)
#error "CH_CFG_USE_CONDVARS not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_CONDVARS_TIMEOUT)
#error "CH_CFG_USE_CONDVARS_TIMEOUT not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_EVENTS)
#error "CH_CFG_USE_EVENTS not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_EVENTS_TIMEOUT)
#error "CH_CFG_USE_EVENTS_TIMEOUT not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_MESSAGES)
#error "CH_CFG_USE_MESSAGES not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_MESSAGES_PRIORITY)
#error "CH_CFG_USE_MESSAGES_PRIORITY not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_MAILBOXES)
#error "CH_CFG_USE_MAILBOXES not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_MEMCORE)
#error "CH_CFG_USE_MEMCORE not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_HEAP)
#error "CH_CFG_USE_HEAP not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_MEMPOOLS)
#error "CH_CFG_USE_MEMPOOLS not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_OBJ_FIFOS)
#error "CH_CFG_USE_OBJ_FIFOS not defined in chconf.h"
#endif

#if !defined(CH_CFG_USE_DYNAMIC)
#error "CH_CFG_USE_DYNAMIC not defined in chconf.h"
#endif

/* Objects factory options checks.*/
#if !defined(CH_CFG_USE_FACTORY)
#error "CH_CFG_USE_FACTORY not defined in chconf.h"
#endif

#if !defined(CH_CFG_FACTORY_MAX_NAMES_LENGTH)
#error "CH_CFG_FACTORY_MAX_NAMES_LENGTH not defined in chconf.h"
#endif

#if !defined(CH_CFG_FACTORY_OBJECTS_REGISTRY)
#error "CH_CFG_FACTORY_OBJECTS_REGISTRY not defined in chconf.h"
#endif

#if !defined(CH_CFG_FACTORY_GENERIC_BUFFERS)
#error "CH_CFG_FACTORY_GENERIC_BUFFERS not defined in chconf.h"
#endif

#if !defined(CH_CFG_FACTORY_SEMAPHORES)
#error "CH_CFG_FACTORY_SEMAPHORES not defined in chconf.h"
#endif

#if !defined(CH_CFG_FACTORY_MAILBOXES)
#error "CH_CFG_FACTORY_MAILBOXES not defined in chconf.h"
#endif

#if !defined(CH_CFG_FACTORY_OBJ_FIFOS)
#error "CH_CFG_FACTORY_OBJ_FIFOS not defined in chconf.h"
#endif

/* Debug options checks.*/
#if !defined(CH_DBG_STATISTICS)
#error "CH_DBG_STATISTICS not defined in chconf.h"
#endif

#if !defined(CH_DBG_SYSTEM_STATE_CHECK)
#error "CH_DBG_SYSTEM_STATE_CHECK not defined in chconf.h"
#endif

#if !defined(CH_DBG_ENABLE_CHECKS)
#error "CH_DBG_ENABLE_CHECKS not defined in chconf.h"
#endif

#if !defined(CH_DBG_ENABLE_ASSERTS)
#error "CH_DBG_ENABLE_ASSERTS not defined in chconf.h"
#endif

#if !defined(CH_DBG_TRACE_MASK)
#error "CH_DBG_TRACE_MASK not defined in chconf.h"
#endif

#if !defined(CH_DBG_TRACE_BUFFER_SIZE)
#error "CH_DBG_TRACE_BUFFER_SIZE not defined in chconf.h"
#endif

#if !defined(CH_DBG_ENABLE_STACK_CHECK)
#error "CH_DBG_ENABLE_STACK_CHECK not defined in chconf.h"
#endif

#if !defined(CH_DBG_FILL_THREADS)
#error "CH_DBG_FILL_THREADS not defined in chconf.h"
#endif

#if !defined(CH_DBG_THREADS_PROFILING)
#error "CH_DBG_THREADS_PROFILING not defined in chconf.h"
#endif

/* System hooks checks.*/
#if !defined(CH_CFG_SYSTEM_INIT_HOOK)
#error "CH_CFG_SYSTEM_INIT_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_SYSTEM_EXTRA_FIELDS)
#error "CH_CFG_SYSTEM_EXTRA_FIELDS not defined in chconf.h"
#endif

#if !defined(CH_CFG_THREAD_EXTRA_FIELDS)
#error "CH_CFG_THREAD_EXTRA_FIELDS not defined in chconf.h"
#endif

#if !defined(CH_CFG_THREAD_INIT_HOOK)
#error "CH_CFG_THREAD_INIT_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_THREAD_EXIT_HOOK)
#error "CH_CFG_THREAD_EXIT_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_CONTEXT_SWITCH_HOOK)
#error "CH_CFG_CONTEXT_SWITCH_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_IRQ_PROLOGUE_HOOK)
#error "CH_CFG_IRQ_PROLOGUE_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_IRQ_EPILOGUE_HOOK)
#error "CH_CFG_IRQ_EPILOGUE_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_IDLE_ENTER_HOOK)
#error "CH_CFG_IDLE_ENTER_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_IDLE_LEAVE_HOOK)
#error "CH_CFG_IDLE_LEAVE_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_IDLE_LOOP_HOOK)
#error "CH_CFG_IDLE_LOOP_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_SYSTEM_TICK_HOOK)
#error "CH_CFG_SYSTEM_TICK_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_SYSTEM_HALT_HOOK)
#error "CH_CFG_SYSTEM_HALT_HOOK not defined in chconf.h"
#endif

#if !defined(CH_CFG_TRACE_HOOK)
#error "CH_CFG_TRACE_HOOK not defined in chconf.h"
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* CHCHECKS_H */
