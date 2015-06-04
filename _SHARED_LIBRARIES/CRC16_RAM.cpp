#include "CRC16.h"

unsigned short CRC16_table[256];

unsigned short CRC16_initialize(unsigned short CRC){
  return 0xFFFF;
}
unsigned short CRC16_finalize(unsigned short CRC){
  return CRC;
}

void CRC16_regenerate(){
unsigned short o;
_gen_int8 i,j;
  i=0;
  do{
    o=i;
    for(j=0;j<8;j++) if(o&0x01) o=(o>>1)^0xA001;
                           else o>>=1;
    CRC16_table[i]=(o>>8)|(o<<8);
  }while((i++)<255);
}

unsigned short  CRC16_update(unsigned short CRC, _gen_int8 d){
  return (CRC<<8)^CRC16_table[(CRC>>8)^d];
}

unsigned short  CRC16_updateBuf(unsigned short CRC, void *d, int size){
  for(int i=0;i<size;i++)
      CRC=(CRC<<8)^CRC16_table[(CRC>>8)^((unsigned char __attribute__ ((packed))*) d)[i]];
  return CRC;
}
