#ifndef __version
#define __version
#include "_compat.h"

struct __attribute__ ((packed)) versionNumber{
    unsigned char  major;
    unsigned char  minor;
    unsigned char  beta;
    unsigned short build;
    unsigned long  date;
};

struct __attribute__ ((packed)) versionStorage{
    char           storageHDR[5];
    char           name[33];
    struct         versionNumber  number;
    unsigned short HWID;
    char           reserv;
    unsigned long  size;
    unsigned long  CRC32;
    char           storageTAIL[6];
};

struct __attribute__ ((packed)) compatibilityDescriptor{
    char count;
    unsigned short HWIDs[64];
};

#if defined(__arm__arm__)||defined(__ATOM__ATOM__)

#define COMPARTIBLE_LIST(count)\
 const  __packed unsigned char  __attribute__((section("VERID"))) _compHdr[8]={'<','C','L','I','S','T','>',count};\
 const  __packed unsigned short __attribute__((section("VERID"))) _compatiblities[count]={

#define END_COMPARTIBLE_LIST\
 };\
 const  __packed unsigned long  __attribute__((section("VERID"))) _compCRC32=0xFFFFFFFF;\
 const  __packed unsigned char  __attribute__((section("VERID"))) _compTail[]={'<','/','C','L','I','S','T','>'};

#define HW_COMPARTIBLE_LIST(count)\
 const  __packed unsigned short __attribute__((section("VERID"))) hw_compatiblities[count]={

#define HW_END_COMPARTIBLE_LIST\
 };
#define VERSION(nm,mj,mn,bt, ID)\
const  struct /*__attribute__ ((packed))*/ versionStorage __attribute__((section("VERID"))) _versionID={{'<','V','E','R','>'},nm,{mj,mn,bt,0xFFFF,0xFFFFFFFF},ID,'.',0xFFFFFFFF,0xffffffff,{'<','/','V','E','R','>'}};\
struct /*__attribute__ ((packed))*/ versionStorage *  versionID=(versionStorage*)&_versionID

#else

#define VERSION(nm,mj,mn,bt, ID)\
  struct  versionStorage __flash versionID={'<','V','E','R','>',nm,mj,mn,bt,0xFFFF,0xFFFFFFFF,ID,'.',0xFFFFFFFF,0xffffffff,'<','/','V','E','R','>'};

#define VERSION_FAR(nm,mj,mn,bt, ID)\
  struct  versionStorage __farflash versionID={'<','V','E','R','>',nm,mj,mn,bt,0xFFFF,0xFFFFFFFF,ID,'.',0xFFFFFFFF,0xffffffff,'<','/','V','E','R','>'};

#define VERSION_RAM(nm,mj,mn,bt, ID)\
  struct  versionStorage versionID={'<','V','E','R','>',nm,mj,mn,bt,0xFFFF,0xFFFFFFFF,ID,'.',0xFFFFFFFF,0xffffffff,'<','/','V','E','R','>'};

#endif

#endif
