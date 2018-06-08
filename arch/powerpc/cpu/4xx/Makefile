#
# (C) Copyright 2000-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

extra-y	= start.o
extra-y	+= resetvec.o

obj-y	+= cache.o
obj-y	+= dcr.o
obj-y	+= kgdb.o

obj-y	+= 40x_spd_sdram.o
obj-y	+= 4xx_pci.o
obj-y	+= 4xx_pcie.o
obj-y	+= 4xx_uart.o
obj-y	+= cpu.o
obj-y	+= cpu_init.o
obj-y	+= fdt.o
obj-y	+= interrupts.o
obj-y	+= sdram.o
obj-y	+= speed.o
obj-y	+= tlb.o
obj-y	+= traps.o
obj-y	+= usb.o
obj-y	+= usb_ohci.o
obj-y	+= uic.o
obj-y	+= reginfo.o
obj-y	+= fsp2_uart.o
obj-$(CONFIG_CMD_REGINFO) += reginfo.o
obj-$(CONFIG_CMD_CHIP_CONFIG)	+= cmd_chip_config.o
ifdef CONFIG_SPL_BUILD
obj-y	+= 44x_spd_ddr.o
obj-y	+= spl_boot.o
endif
