#ifndef _CODER_
#define _CODER_

#ifdef __cplusplus
extern "C"{
#endif

extern char strd[];

extern unsigned short accDeviceSalt;

extern void accToReq(char * s,unsigned long d1,unsigned long d2,unsigned long d3);
extern int accFromReq(char * s, unsigned long *d1,unsigned long *d2,unsigned long *d3);
extern unsigned short accReqAnswerCode(char *s,int len,char accLvl);
extern int findChar(char c);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_CODER_
