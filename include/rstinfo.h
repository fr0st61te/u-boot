/*
 * Copyright (c) International Business Machines Corp., 2007,2013
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __RSTINFO_H__
#define __RSTINFO_H__

#ifndef __ASSEMBLY__

/*
 * Note that following 3 enums must match kernel version, stored in
 *   kernel/linux/include/linux/fsp/reset.h
 */

/**
 * Specified reset originators.
 */
typedef enum {
	RST_ORIG_UNKNOWN = 0,
	RST_ORIG_CORE,
	RST_ORIG_ASIC,
	RST_ORIG_POWER,
	RST_ORIG_EXTERNAL,
} rst_origin_t;

/**
 * Specified reset types.
 */
typedef enum {
	RST_TYPE_UNKNOWN = 0,
	RST_TYPE_CORE,
	RST_TYPE_CHIP,
	RST_TYPE_SYSTEM,
} rst_type_t;

/**
 * Specified reset reasons.
 */
typedef enum {
	RST_REASON_UNKNOWN = 0,
	RST_REASON_CORE_WATCHDOG,
	RST_REASON_RESTART,
	RST_REASON_PANIC,
	RST_REASON_HALT,
	RST_REASON_POWER_OFF,
	RST_REASON_POWER_CYCLE,
	RST_REASON_PINHOLE,
	RST_REASON_PARPORT,		/* No longer used */
	RST_REASON_BOOTCODE,
	RST_REASON_HOST_INITIATED,
	RST_REASON_BOOT_WATCHDOG,
	RST_REASON_UNIT_CHECK_TIMER,	/* No longer used */
	RST_REASON_EXT_TOOL,
	RST_REASON_PABEND,
	RST_REASON_CHASSIS,
	RST_REASON_PCIE,
} rst_reason_t;

struct rstinfo {
	rst_origin_t origin;
	rst_type_t type;
	rst_reason_t reason;
};

void print_origrstreason(const char *);
void print_rstspecific(void);
void print_rstinfo(const char *);
void rstinfo_setenv(void);
void rstinfo(struct rstinfo *info);

#endif /*  __ASSEMBLY__ */

#endif /* __RSTINFO_H__ */
