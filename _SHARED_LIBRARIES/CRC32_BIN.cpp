#include "CRC32.h"

unsigned long  CRC32_initialize(){
  return 0x9226F562;
}
void CRC32_regenerate(){
;
}

unsigned long  CRC32_update(unsigned long CRC, _gen_int8 d){
#ifdef __AVR__AVR__
 asm("    ldi r21,9      ");
 asm("    ldi r22,0x20   ");
 asm("    ldi r23,0x83   ");
 asm("    ldi r24,0xB8   ");
 asm("    ldi r25,0xED   ");
 asm("lpl:               ");
 asm("    dec r21        ");
 asm("    breq lple      ");
 asm("    lsr r20        ");
 asm("    ror r19        ");
 asm("    ror r18        ");
 asm("    ror r17        ");
 asm("    ror r16        ");
 asm("    brcc lpl      ");
 asm("      eor r16,r22  ");
 asm("      eor r17,r23  ");
 asm("      eor r18,r24  ");
 asm("      eor r19,r25  ");
 asm("      rjmp lpl     ");
 asm("lple:     ");
#else
 for(_gen_int8 i=0;i<8;i++){
    if(CRC & 0x01) CRC=((CRC>>1)|(((unsigned long)d)<<31))^0xEDB88320;
              else CRC=((CRC>>1)|(((unsigned long)d)<<31));
    d>>=1;
  }
  return CRC;
#endif  
}

unsigned long  CRC32_finalize(unsigned long CRC){
#ifdef __AVR__AVR__
 asm("    ldi r21,33      ");
 asm("    ldi r22,0x20   ");
 asm("    ldi r23,0x83   ");
 asm("    ldi r24,0xB8   ");
 asm("    ldi r25,0xED   ");
 asm("lpl2:               ");
 asm("    dec r21        ");
 asm("    breq lple2      ");
 asm("    lsr r19        ");
 asm("    ror r18        ");
 asm("    ror r17        ");
 asm("    ror r16        ");
 asm("    brcc lpl2      ");
 asm("      eor r16,r22  ");
 asm("      eor r17,r23  ");
 asm("      eor r18,r24  ");
 asm("      eor r19,r25  ");
 asm("      rjmp lpl2     ");
 asm("lple2:     ");
 asm("   com r16");
 asm("   com r17");
 asm("   com r18");
 asm("   com r19");
#else
 for(_gen_int8 i=0;i<32;i++){
    if(CRC & 0x01) CRC=((CRC>>1)^0xEDB88320);
              else CRC=((CRC>>1));
  }
  return ~CRC;
#endif  
}

unsigned long  CRC32_updateBuf(unsigned long CRC, void *d, int size){
  for(int i=0;i<size;i++)
      CRC=CRC32_update(CRC,((unsigned char __attribute__ ((packed))*) d)[i]);
  return CRC;
}

unsigned long  CRC32_update_16b(unsigned long CRC, unsigned short d){
  return CRC32_updateBuf(CRC,&d,2);
}
unsigned long  CRC32_update_32b(unsigned long CRC, unsigned long  d){
  return CRC32_updateBuf(CRC,&d,4);
}
