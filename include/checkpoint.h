/*
 * Copyright (c) International Business Machines Corp., 2006,2012
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Author: Frank Haverkamp
 *
 * Please reflect any change or any additional checkpoint in the
 * system wide checkpoint design documentation. Thanks.
 */

#ifndef __CHECKPOINTS_H__
#define __CHECKPOINTS_H__

#include <common.h>

#if defined(CONFIG_CMD_CHECKPOINT)

#define CHKP_IPL_PREFIX		0x00000000
#define CHKP_SPL_PREFIX		0x10000000
#define CHKP_OS_PREFIX		0x20000000
#define CHKP_APP_PREFIX		0x30000000

/**
 * SPL checkpoints
 */
#define CHKP_BOARD_INIT		(0x00004000 + CHKP_SPL_PREFIX)
#define CHKP_ENV_INIT		(0x00004001 + CHKP_SPL_PREFIX)
#define CHKP_ENV_RELOC		(0x00004002 + CHKP_SPL_PREFIX)
#define CHKP_ENV_MISSING	(0x00006000 + CHKP_SPL_PREFIX)
#define CHKP_RRCOUNT		(0x00004003 + CHKP_SPL_PREFIX)
#define CHKP_CONSOLE_INIT	(0x00004004 + CHKP_SPL_PREFIX)
#define CHKP_INT_INIT		(0x00004005 + CHKP_SPL_PREFIX)
#define CHKP_NETWORK		(0x00004006 + CHKP_SPL_PREFIX)
#define CHKP_MONITOR		(0x00004007 + CHKP_SPL_PREFIX)
#define CHKP_BOOTX		(0x00004100 + CHKP_SPL_PREFIX)
#define CHKP_NANDERR		(0x00004200 + CHKP_SPL_PREFIX)
#define CHKP_RRCOUNT_EXCEEDED	(0x00004300 + CHKP_SPL_PREFIX)
#define CHKP_BOOTY		(0x00004400 + CHKP_SPL_PREFIX)
#define CHKP_NETLOOP_START	(0x00005000 + CHKP_SPL_PREFIX)
#define CHKP_NETLOOP_SUCCESS	(0x00005001 + CHKP_SPL_PREFIX)
#define CHKP_NETLOOP_RESTART	(0x00005002 + CHKP_SPL_PREFIX)
#define CHKP_NETLOOP_FAIL	(0x00005003 + CHKP_SPL_PREFIX)
#define CHKP_SERIAL_INIT	(0x00007001 + CHKP_SPL_PREFIX)
#define CHKP_MMC_INIT		(0x00007002 + CHKP_SPL_PREFIX)
#define CHKP_MEM_SCRUB		(0x00008000 + CHKP_SPL_PREFIX)
#define CHKP_MEM_FILL		(0x00008001 + CHKP_SPL_PREFIX)
#define CHKP_TERMINATE		(0x00009000 + CHKP_SPL_PREFIX)

#if !defined(__ASSEMBLY__)
void checkpoint(unsigned long cpoint);
#endif

#else
#define checkpoint(cpoint)	/* compile it out */
#endif
#endif /* CONFIG_CMD_CHECKPOINT */
