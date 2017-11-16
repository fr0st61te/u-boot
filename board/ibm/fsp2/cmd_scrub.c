/*
 * Copyright (c) International Business Machines Corp., 2013
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
 *
 * Author: Mike Kobler
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include <fsp2.h>

static int do_scrub(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	DECLARE_GLOBAL_DATA_PTR;
	unsigned long start = 64*1024; /* skip exception vectors */
	unsigned long end = gd->ram_size - 0x200000; /* FIXME size of u-boot? */

	if (argc > 1) {
		start = simple_strtoul(argv[1], NULL, 16);
		unsigned long len = simple_strtoul(argv[2], NULL, 16);
		end = start + len;
	}

	int ce = 0;
	int rc = mem_init(start, end, &ce);
	if (rc == MEM_FILLED) {
		printf("filled (UE detected)\n");
		return 1;
	}

	if (ce)
		printf("CE detected\n");

	return 0;
}

U_BOOT_CMD(scrub, 3, 0, do_scrub,
	   "Kick off a memory scrub",
	   "[start len] - Perform a memory scrub\n");
