/*
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

#ifndef __FFDC_DATA_H__
#define __FFDC_DATA_H__

#include <common.h>

#define FFDC_MAGIC	0xFFDCFFDC

/* FIXME add plb6, plb4, opb error regs */
struct ffdc_data {
	unsigned long magic;
	unsigned long lr;
	unsigned long gpr1;
	unsigned long gpr2;
	unsigned long gpr3;
	unsigned long srr0;
	unsigned long csrr0;
	unsigned long mcsrr0;

	unsigned long tbl;
	unsigned long tbu;
};

struct ffdc_data *get_ffdc_data_ptr(void);

#endif
