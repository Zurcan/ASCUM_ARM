#include "coder.h"
//#define __SENSELOCK

#ifndef __SENSELOCK
#include "sha1.h"
#define BYTE        char
char x1=217;
char x2=213;
#else
#include "ses_v3.h"
#define SHA1Context HashContext
#define SHA1Reset   _sha1_init
#define SHA1Input   _sha1_update
#define SHA1Result  _sha1_final
char x1=217;
char x2=213;
#endif

char strd[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
unsigned short accDeviceSalt =0;

unsigned short accReqAnswerCode(char *s,int len,char accLvl){
SHA1Context shaCtx;
char i;
unsigned char x;
unsigned long d1,d2,d3;
unsigned long hash[5];
   x=((char*)&accDeviceSalt)[1];
   if(len==14){
     if(accFromReq(s,&d1,&d2,&d3)){
       SHA1Reset(&shaCtx);
       for(i=0;i<64;i++){
         x=x*x1+x2;
         SHA1Input(&shaCtx,(BYTE*)&x,1);
       }
       SHA1Input(&shaCtx,(BYTE*)&accDeviceSalt,2);
       SHA1Input(&shaCtx,(BYTE*)&accLvl,1);
       SHA1Input(&shaCtx,(BYTE*)&d1,3);
       SHA1Input(&shaCtx,(BYTE*)&d2,3);
       SHA1Input(&shaCtx,(BYTE*)&d3,3);
       for(i=0;i<64;i++){
         x=x*x2+x1;
         SHA1Input(&shaCtx,(BYTE*)&x,1);
       }
       SHA1Result(&shaCtx,(BYTE*)hash);
       return (hash[0]&0xFFFF)^(hash[0] >>16)^ 0xAAAA;
     }
   }
   //return 0;
   SHA1Reset(&shaCtx);
   for(i=0;i<64;i++){
     x=x*x1+x2;
     SHA1Input(&shaCtx,(BYTE*)&x,1);
   }
   SHA1Input(&shaCtx,(BYTE*)&accDeviceSalt,4);
   SHA1Input(&shaCtx,(BYTE*)&accLvl,1);
   SHA1Input(&shaCtx,(BYTE*)s,len);
   for(i=0;i<64;i++){
     x=x*x2+x1;
     SHA1Input(&shaCtx,(BYTE*)&x,1);
   }
   SHA1Result(&shaCtx,(BYTE*)hash);
   return (hash[0]&0xFFFF)^(hash[0] >>16)^ 0xA5AA;
}

#ifndef __SENSELOCK
void accToReq(char * s,unsigned long d1,unsigned long d2,unsigned long d3){
int i;
unsigned short k;
char n;
    d1=((d1 & 0xFFFFF)     )|
       ((d2 & 0xFFFFF)<< 20);
    d2=((d2 & 0xFFFFF)>> 12)|
       ((d3 & 0xFFFFF)<< 8 );
    k=0xAA;
    for(i=0;i<=11;i++){
        n=d1&0x1F;
        d1=(d1 >> 5)|(d2 << 27);
        d2=(d2 >> 5);
        k=(k+strd[n]+247)% 1024;
        s[11-i]=strd[(n+k)% 32];
    }
    s[12]=strd[((k & 0x3E0) >> 5)];
    s[13]=strd[ (k & 0x1F)       ];
    s[14]=0;
}
#endif

int findChar(char c){
char i;
    for(i=0;i<32;i++){
        if(strd[i]==c)return i;
    }
    return 0;
}

int accFromReq(char * s, unsigned long *d1,unsigned long *d2,unsigned long *d3){
unsigned short k,n;
char i;
char vb[20];
    if(!s)return 0;
    k=(findChar(s[12])<<5)|findChar(s[13]);
    for(i=0;i<=11;i++){
        n=findChar(s[i]);
        vb[i]=(unsigned short)(n-k)%32;
        k=(k-strd[vb[i]]-247)%1024;
    }
    if ((k & 0xFF)==0xAA){
        *d3=(vb[0] <<15)|
            (vb[1] <<10)|
            (vb[2] <<5)|
            (vb[3]);
        *d2=(vb[4] <<15)|
            (vb[5] <<10)|
            (vb[6] <<5)|
            (vb[7]);
        *d1=(vb[8] <<15)|
            (vb[9] <<10)|
            (vb[10]<<5)|
            (vb[11]);
        return 1;
    }else return 0;
}
