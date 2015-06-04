#ifndef __CRC16
#define __CRC16
#include "_compat.h"


//extern unsigned short *CRC16_table;

extern unsigned short CRC16_initialize(); //  CRC=0xFFFF
extern unsigned short CRC16_finalize(unsigned short CRC);   //  CRC
extern void CRC16_regenerate();
extern unsigned short  CRC16_update(unsigned short CRC, _gen_int8);
extern unsigned short  CRC16_updateBuf(unsigned short CRC, void *d, int size);

#endif
