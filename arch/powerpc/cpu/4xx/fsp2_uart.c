/*
 * (C) Copyright 2000-2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
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

#include <common.h>
#include <commproc.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <watchdog.h>
#include <serial.h>

DECLARE_GLOBAL_DATA_PTR;

/* Control 0 register */
#define cntrl0		(CNTRL_DCR_BASE + 0x3b)
#define CNTRL_DCR_BASE		0x0b0

#define UART_DATA_REG		0x00
#define UART_DL_LSB		0x00
#define UART_DL_MSB		0x01
#define UART_INT_ENABLE		0x01
#define UART_FIFO_CONTROL	0x02
#define UART_LINE_CONTROL	0x03
#define UART_MODEM_CONTROL	0x04
#define UART_LINE_STATUS	0x05
#define UART_MODEM_STATUS	0x06
#define UART_SCRATCH		0x07

#define UART0_MMIO_BASE		0xB0020000
#define OPB_BUS_CLOCK           83333333
#define SERIAL_CLOCK            (OPB_BUS_CLOCK/4)

#define DATA_READY		0x01
#define OVERRUN_ERROR		0x02
#define PARITY_ERROR		0x04
#define FRAMING_ERROR		0x08
#define BREAK_INTERRUPT		0x10
#define HOLD_EMPTY		0x20
#define TX_SHIFT_EMPTY		0x40
#define RX_FIFO_ERROR		0x80

void fsp2_setbrg(void)
{
	unsigned short bdiv;
	unsigned long udiv;
	unsigned long tmp;
	unsigned long clk;

	clk = CONFIG_SYS_EXT_SERIAL_CLOCK;
	udiv = ((mfdcr(cntrl0) & 0x3e) >> 1) + 1;
	tmp = gd->baudrate * udiv * 16;
	bdiv = (clk + tmp / 2) / tmp;

	/* set DLAB bit */
	out8(UART0_MMIO_BASE + UART_LINE_CONTROL, 0x80);
	/* set baudrate divisor */
	out8(UART0_MMIO_BASE + UART_DL_LSB, bdiv);
	/* set baudrate divisor */
	out8(UART0_MMIO_BASE + UART_DL_MSB, bdiv >> 8);
	/* clear DLAB; set 8 bits, no parity */
	out8(UART0_MMIO_BASE + UART_LINE_CONTROL, 0x03);
}

void fsp2_putc(const char c)
{
	int i;
	if (c == '\n')
		serial_putc ('\r');
	for (i = 1; i < 3500; i++) {
		if ((in8(UART0_MMIO_BASE + UART_LINE_STATUS) & 0x20) == 0x20)
			break;
		udelay (100);
	}
	/* put character out */
	out8(UART0_MMIO_BASE + UART_DATA_REG, c);
}

void fsp2_puts(const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}

int fsp2_getc(void)
{
	unsigned char status = 0;
	while (1) {
#if defined(CONFIG_HW_WATCHDOG)
	WATCHDOG_RESET ();      /* Reset HW Watchdog, if needed */
#endif  /* CONFIG_HW_WATCHDOG */
		status = in8 (UART0_MMIO_BASE + UART_LINE_STATUS);
		if ((status & DATA_READY) != 0x0) {
			break;
		}
		if ((status & ( FRAMING_ERROR |
				OVERRUN_ERROR |
				PARITY_ERROR  |
				BREAK_INTERRUPT )) != 0) {
			out8(UART0_MMIO_BASE + UART_LINE_STATUS,
			      FRAMING_ERROR |
			      OVERRUN_ERROR |
			      PARITY_ERROR  |
			      BREAK_INTERRUPT);
		}
	}
	return (0x000000ff & (int)in8(UART0_MMIO_BASE));
}

int fsp2_tstc (void)
{
	unsigned char status;
	status = in8(UART0_MMIO_BASE + UART_LINE_STATUS);
	if ((status & DATA_READY) != 0x0) {
		return (1);
	}

	if ((status & (FRAMING_ERROR | OVERRUN_ERROR |
			 PARITY_ERROR | BREAK_INTERRUPT )) != 0) {
		out8(UART0_MMIO_BASE + UART_LINE_STATUS,
				FRAMING_ERROR | OVERRUN_ERROR |
				PARITY_ERROR | BREAK_INTERRUPT);
	}

	return 0;
}

int fsp2_init (void)
{
        unsigned short bdiv;

	bdiv = (SERIAL_CLOCK/16)/gd->baudrate;
	/* set DLAB bit */
	out8(UART0_MMIO_BASE + UART_LINE_CONTROL, 0x80);
	/* set baudrate divisor */
	out8(UART0_MMIO_BASE + UART_DL_LSB, bdiv);
	/* set baudrate divisor */
	out8(UART0_MMIO_BASE + UART_DL_MSB, bdiv >> 8);
	/* clear DLAB; set 8 bits, no parity */
	out8(UART0_MMIO_BASE + UART_LINE_CONTROL, 0x03);
	/* disable FIFO */
	out8(UART0_MMIO_BASE + UART_FIFO_CONTROL, 0x00);
	/* no modem control DTR RTS */
	out8(UART0_MMIO_BASE + UART_MODEM_CONTROL, 0x00);
	/* clear line status */
	in8(UART0_MMIO_BASE + UART_LINE_STATUS);
	/* read receive buffer */
	in8(UART0_MMIO_BASE + UART_DATA_REG);
	/* set scratchpad */
	out8(UART0_MMIO_BASE + UART_SCRATCH, 0x00);
	/* set interrupt enable reg */
	out8(UART0_MMIO_BASE + UART_INT_ENABLE, 0x00);

	return 0;
}

struct serial_device serial_fsp2_device = {
	.name	= "serial_fsp2",
	.start	= fsp2_init,
	.stop	= NULL,
	.setbrg	= fsp2_setbrg,
	.getc	= fsp2_getc,
	.tstc	= fsp2_tstc,
	.putc	= fsp2_putc,
	.puts	= fsp2_puts,
};

__weak struct serial_device *default_serial_console(void)
{
	return &serial_fsp2_device;
}

void _serial_initialize(void)
{
	serial_register(&serial_fsp2_device);
}
