#include <asm/ffdc_data.h>

/* FIXME taken from ipl, make common? */
#define SRAM_FFDC_START	0xB0024800

struct ffdc_data *get_ffdc_data_ptr(void)
{
	return (struct ffdc_data*)SRAM_FFDC_START;
}
