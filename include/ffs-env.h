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
 */
#ifndef __FFS_ENV_H__
#define __FFS_ENV_H__

#ifndef __ASSEMBLY__

#include <linux/types.h>

typedef struct ffs_env {
	char vol;
	uint32_t begin;
	uint32_t len;
	uint32_t addr;
} ffs_env_t;
#endif
#endif /* __FFS_ENV_H__ */
