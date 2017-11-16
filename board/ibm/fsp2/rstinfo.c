/*
 * Copyright (c) International Business Machines Corp., 2007, 2012
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

#include <config.h>
#include <common.h>
#include <asm/processor.h>
#include <pra.h>
#include <rstinfo.h>

/**
 * We need those string tables to print out the correct reset originator,
 * type and reason.
 */
static const char *rst_origin_str[] = {
	"Unknown", "Core", "Asic", "Power", "External",
};

static const char *rst_type_str[] = {
	"Unknown", "Core", "Chip", "System",
};

static const char *rst_reason_str[] = {
	"Unknown",
	"CoreWatchdog",
	"Restart",
	"Panic",
	"Halt",
	"PowerOff",
	"PowerCycle",
	"Pinhole",
	"Parport",
	"Bootcode",
	"HostInitiated",
	"BootWatchdog",
	"UnitCheckTimer",
	"ExternalTool",
	"PAbend",
	"ChassisInitiated",
	"PCIe",
};

void print_rstspecific(void)
{
	printf("PVR:\t\t0x%08x\n", mfspr(SPRN_PVR));
	printf("DBSR:\t\t0x%08x\n", mfspr(SPRN_DBSR));
	printf("CRCS:\t\t0x%08x\n", mfcmu(CMU_CRCS));
	printf("TSR:\t\t0x%08x\n", mfspr(SPRN_TSR));
	printf("BWTC:\t\t0x%08x\n", mfcmu(CMU_BWTC));
	printf("RST_FLAVOR:\t0x%08lx\n", pra_read(FSP_PRA_SFT_RST_FLAVOR));
	printf("PABEND:\t\t0x%08lx\n", pra_read(FSP_PRA_PABEND));
	printf("PABEND_A:\t0x%08lx\n", pra_read(FSP_PRA_PABEND_A));
	printf("PABEND_B:\t0x%08lx\n", pra_read(FSP_PRA_PABEND_B));
	printf("PABEND_C:\t0x%08lx\n", pra_read(FSP_PRA_PABEND_C));
}

void print_origrstreason(const char *pre)
{
	unsigned long tmp = pra_read(FSP_PRA_ORIG_RESET);

	printf("%sOriginal Reset Reason: %s %02ld\n", pre,
			rst_reason_str[tmp], tmp);
}

void print_rstinfo(const char *pre)
{
	struct rstinfo info;

	rstinfo(&info);
	printf("%sCode:\t%02d %02d %02d\n",
			pre, info.origin, info.type, info.reason);
	printf("%sOrigin:\t%s\n", pre, rst_origin_str[info.origin]);
	printf("%sType:\t%s\n", pre, rst_type_str[info.type]);
	printf("%sReason:\t%s\n", pre, rst_reason_str[info.reason]);
}

void rstinfo_setenv(void)
{
	struct rstinfo info;

	rstinfo(&info);
	setenv("rst_origin", rst_origin_str[info.origin]);
	setenv("rst_type", rst_type_str[info.type]);
	setenv("rst_reason", rst_reason_str[info.reason]);
}

/* get the reset information out of the PRA key, setup by the IPL */
void rstinfo(struct rstinfo *info)
{
	unsigned long orig_rstinfo = pra_read(FSP_PRA_ORIG_RSTINFO);

	info->reason = orig_rstinfo >> 16;
	info->origin = (orig_rstinfo >> 8) & 0xFF;
	info->type = orig_rstinfo & 0xFF;
}
