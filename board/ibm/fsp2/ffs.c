/*
 * Copyright (c) International Business Machines Corp., 2012
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
 * Author: Mike Kobler <mkobler@us.ibm.com>
 */

#include <config.h>
#include <ffs-fsp.h>
#include <pra.h>
#include <sfc.h>

/* FIXME use common version in apps/clib/src/checksum.c */
static uint32_t checksum(void *__src, size_t __n)
{
	uint8_t sum[4] = {0,};
	size_t i;

	for (i = 0; i < __n; i++)
		sum[i & 3] ^= ((uint8_t *)__src)[i];

	return (sum[0] << 24) | (sum[1] << 16) | (sum[2] << 8) | sum[3];
}

int ffs_vol_addr(int vol_id, ulong *addr)
{
	int i;
	struct ffs_hdr hdr;
	int entry_off = pra_read(FSP_PRA_ANCHOR_FFS) +
				offsetof(struct ffs_hdr, entries);

	sfc_read(pra_read(FSP_PRA_ANCHOR_FFS), sizeof(hdr), (uchar *)&hdr);

	/* Assume IPL checked header checksum */
	for (i = 0; i < hdr.entry_count; i++) {
		struct ffs_entry ent;
		uint32_t csum;

		sfc_read(entry_off, FFS_ENTRY_SIZE, (uchar *)&ent);
		entry_off += FFS_ENTRY_SIZE;

		csum = checksum(&ent, FFS_ENTRY_SIZE_CSUM);
		if (ent.checksum != csum)
			continue;

		if (ent.type != FFS_TYPE_DATA)
			continue;

		if (vol_id != ent.user.data[USER_DATA_VOL])
			continue;

		*addr = ent.base * hdr.block_size;
		return ent.user.data[USER_DATA_SIZE];
	}

	return -1;
}
