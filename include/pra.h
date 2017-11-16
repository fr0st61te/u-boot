/*
 * Copyright (c) International Business Machines Corp., 2006, 2012
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
 * PRA Persistent Register Area
 *
 * The contents are defined in the PRA architecture. The official document
 * containing the key-names is the Building Block Architecture Document.
 *
 * NOTE: These values are also defined in ipl and kernel code.  They must be
 * kept in sync!
 */

#ifndef __PRA_H__
#define __PRA_H__

/* Architecture specific locations for PRA */
#if defined(CONFIG_440)
/* We are using the last 384 bytes of the SPAD for the PRA */
#define PRA_START	0xb0025e80
#define PRA_END		0xb0025fff
#else
#error Unsupported Board
#endif

/* Filled into the FSP_PRA_SFT_RST_FLAVOR pra entry */
#define LINUX_REBOOT_CMD_TOOLRESET      0xF5900011
#define LINUX_REBOOT_CMD_HOSTINIT	0xc0febabe
#define LINUX_REBOOT_CMD_BOOTCODE	0xdeadbeef
#define LINUX_REBOOT_CMD_RESTART	0x01234567
#define LINUX_REBOOT_CMD_HALT		0xCDEF0123
#define LINUX_REBOOT_CMD_POWER_OFF	0x4321FEDC
#define LINUX_REBOOT_CMD_RESTART2	0xA1B2C3D4
#define LINUX_REBOOT_CMD_PINHOLE	0xFFFFFFFF

#define FSP_PRA_CHECKSUM               0
#define FSP_PRA_CALLOUT                1
#define FSP_PRA_BCU_STATE              2
#define FSP_PRA_RR_COUNT               3
#define FSP_PRA_SFT_RST_FLAVOR         4
#define FSP_PRA_CHKPT                  5
#define FSP_PRA_MEM_INIT               6
#define FSP_PRA_MEM_INIT_STATIC        7
#define FSP_PRA_USER0                  8
#define FSP_PRA_USER1                  9
#define FSP_PRA_USER2                 10
#define FSP_PRA_USER3                 11
#define FSP_PRA_USER4                 12
#define FSP_PRA_USER5                 13
#define FSP_PRA_USER6                 14
#define FSP_PRA_USER7                 15
#define FSP_PRA_BOOT_FLAGS            16
#define FSP_PRA_ANCHOR_SND            17
#define FSP_PRA_BOOTSCRIPT            18
#define FSP_PRA_BOOT_STATUS           19
#define FSP_PRA_FFDC_LR               20
#define FSP_PRA_BOOT_DUMP             21
#define FSP_PRA_PABEND                22
#define FSP_PRA_PABEND_A              23
#define FSP_PRA_PABEND_B              24
#define FSP_PRA_PABEND_C              25
#define FSP_PRA_ORIG_RESET            26
#define FSP_PRA_NETBOOT_DHCP_ERR      27
#define FSP_PRA_NETBOOT_TFTP_ERR      28
#define FSP_PRA_BOOT_ERR_VALUE        29
#define FSP_PRA_BOOT_ERR_FLAGS        30
#define FSP_PRA_BOOT_THRESHOLD_TIME   31
#define FSP_PRA_BOOT_THRESHOLD_COUNT  32
#define FSP_PRA_ANCHOR_FFS            33
#define FSP_PRA_ANCHOR_ALT_FFS        34
#define FSP_PRA_ORIG_RSTINFO          35
#define FSP_PRA_BOOT_RR_COUNT         36
#define FSP_PRA_NUMENTRIES            37 /* This must be the largest key */

/*
 * FSP_PRA_CALLOUT
 *
 * 0000.0000.0011.1111.1111.2222.2222.2233
 * 0123.4567.8901.2345.6789.0123.4567.8901
 *			     TTT XXXX XXXX
 *			     ||| callout summary: SW,HW,ECC error ...
 *			     ||icache parity error
 *			     |dcache parity error
 *			     tlb parity error
 */

#define FSP_PRA_SWERR		 0 /* SW error	   */
#define FSP_PRA_HWERR		 1 /* HW error	   */
#define FSP_PRA_HWSWERR		 2 /* HW or SW error */
#define FSP_PRA_ECCERR		 3 /* Uncorrectable ECC error */
#define FSP_PRA_TLBCACHEERR	 4 /* TLB cache parity error */

#define FSP_PRA_MASK_SUMMARY	 0xff /* mask for callout summary */

/* The following bits are or'ed into FSP_PRA_CALLOUT, if the error occurs */
#define FSP_PRA_CALLOUT_ICACHE	 0x00000100 /* icache parity error */
#define FSP_PRA_CALLOUT_DCACHE	 0x00000200 /* dcache parity error */
#define FSP_PRA_CALLOUT_TLB	 0x00000400 /* tlb parity error */

#if !defined(__ASSEMBLY__)
unsigned long pra_read(unsigned long key);
void pra_write(unsigned long key, unsigned long val);
unsigned long pra_prev_read(unsigned long key);

unsigned long get_boot_status(void);
void set_boot_status(unsigned long);
#endif /* __ASSEMBLY__ */

#endif /* __PRA_H__ */
