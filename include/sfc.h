#ifndef __SFC_H__
#define __SFC_H__

#include <common.h>

int sfc_read(unsigned addr, int size, uchar *buf);
void sfc_disable_ecc_range(int addr, int range, int *prvAdr, int *prvRng);
void sfc_set_mmio_window(int addr, int range, int *prvAdr, int *prvRng);

#endif /* __SFC_H__ */
