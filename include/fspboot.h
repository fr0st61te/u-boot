/*
 * Copyright (c) International Business Machines Corp., 2007,2012
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*
 * FSP Boot status constants
 */

#ifndef _FSP_BOOT_H
#define _FSP_BOOT_H

/*
 * FSP boot status constants
 *
 * The boot status register is set to 0 after a power on reset. Any
 * other reset type preserves the status. The IPL entry code shifts
 * the lower 16 bits of the status register into the upper 16 bit.
 *
 * Bit	0 - 15: Current boot status
 * Bit 16 - 31: Previous boot status
 *
 * Bit 0-7:	Progress counter
 * Bit 8:	SPL selector
 * Bit 9:	OS selector
 */

#define FSP_BOOTSEL_SPL		0x0001
#define FSP_BOOTSEL_OS		0x0002

#define FSP_BOOT_PROGRESS_MASK	0xFF00

#define FSP_BOOT_STATUS_MASK	0xFFFF

/* Boot phase constants */
enum boot_phase {
	FSP_IPL_RUNNING = 0,
	FSP_SPL_START,
	FSP_OS_START,
	FSP_OS_RUNNING,
};

#define BSTAT_CURR_SPL         0x00000001 /* which SPL was choosen? */
#define BSTAT_CURR_OS          0x00000002 /* which OS was choosen */
#define BSTAT_CURR_PROGR       0x0000ff00 /* current boot phase */
#define BSTAT_PREV_SPL         0x00010000
#define BSTAT_PREV_OS          0x00020000
#define BSTAT_PREV_PROGR       0xff000000 /* previous boot phase */
#define BSTAT_SPL_MASK         0xffff0001 /* do not modify previous,
                                             and SPL selection */

#endif
