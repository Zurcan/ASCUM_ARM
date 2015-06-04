#ifndef __CRC32
#define __CRC32
#include "_compat.h"

#ifdef __cplusplus
extern "C"
{
#endif
	
unsigned long  CRC32_initialize(void);
unsigned long  CRC32_finalize(unsigned long CRC);
void CRC32_regenerate(void);
unsigned long  CRC32_update(unsigned long CRC, _gen_int8 d);
unsigned long  CRC32_update_16b(unsigned long CRC, unsigned short d);
unsigned long  CRC32_update_32b(unsigned long CRC, unsigned long  d);
unsigned long  CRC32_updateBuf(unsigned long CRC,  void *d, int size);


#ifdef __cplusplus
}
#endif


#endif
