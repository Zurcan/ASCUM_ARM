#include "CRC32.h"

unsigned long CRC32_table[256];

unsigned long CRC32_initialize(){
  return 0xFFFFFFFF;
}

unsigned long  CRC32_finalize(unsigned long CRC){
  return CRC^=0xFFFFFFFF;
}

void CRC32_regenerate(){
_gen_int8 i,j;
  unsigned long res;
  i=0;
  do{
    res=i;
    for(j=0;j<8;j++) if((char)res&0x01) res=(res>>1)^((unsigned long)0xEDB88320);
                                   else res>>=1; 
    CRC32_table[i]=res;

  }while((i++)<255);
}

unsigned long  CRC32_update(unsigned long CRC, _gen_int8 d){
  return (CRC>>8)^CRC32_table[(CRC^d)&0xFF];
}


unsigned long  CRC32_updateBuf(unsigned long CRC,  void *d, int size){
  for(int i=0;i<size;i++)
      CRC=(CRC>>8)^CRC32_table[(CRC^((unsigned char __attribute__ ((packed))*) d)[i])&0xFF];
  return CRC;
}

unsigned long  CRC32_update_16b(unsigned long CRC, unsigned short d){
  return CRC32_updateBuf(CRC,&d,2);
}
unsigned long  CRC32_update_32b(unsigned long CRC, unsigned long  d){
  return CRC32_updateBuf(CRC,&d,4);
}
