#ifndef __MENULIB__
#define __MENULIB__
#include "_compat.h"
#include "stdint.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// ���� ��������� ����        //

#define vpREADONLY                              0x80000000
#define vpHEX                                   0x40000000
#define vpBIN                                   0x20000000
#define vpOCT                                   0x10000000
#define vpLeftJustified                         0x08000000
#define vpStartOne                              0x04000000
#define vpGauged                                0x02000000
#define vpImdChange                             0x01000000
#define vpLangLink                              0x00800000
#define vpIconizeName                           0x00400000

#define ff__ReadOnly                            0x01
#define ff__Dynamic                             0x02
#define ff__RemProcsEn                          0x04
#define ff__LocProcsEn                          0x08
#define ff__System                              0x10
#define ff__Debug                               0x20
#define ff__ClearRead                           0x80

#define ff__PurelyNative                        0x8000

enum  TMenuItType{
            vUint8,                              // ���� ��� �����
            vInt8,                               // ���� �� ������
            vInt16,                              // ����� �� ������
            vUint16,                             // ����� ��� �����
            vInt32,                              // ������� ����� �� ������
            vFract8,                             // ����� ���� 25.5. �������� ������������ ������.
            vFract16,                            // ����� ���� 6553.5 �������� ������������ ������.
            vFloat,                              // ����� � ��������� �������
            vFlag,                               // ����. 1���. ������������� ������.
            vList,                               // ������� ������
            vTime,                               // �����. 32 ���. ���������� �������
            vProc,                               // ������������
            vAdjustProc,                         // ������������, ����������� ��� �������, ������������ 
                                                 // ��������� ������� �������� �������� � ������� �����������
            vSub,                                // �������
            vString,                             // ������ �� 255 ��������
            vHString,                            // ������� ������
            vText,                               // ������������� �����
            vFlag8,                              // ����
            vFlag16,                             // ����
            mUnit,                               // ������� ���������
            vSettingsProc,                       // ��������� ��������� ��������� ��������
            vDropDown,                           //
            vDivider,                            //
            vSerial,                             //
            vSystemProc,                         //
            vVersion,                            //
            vButton,                             //
            vTroubleCode,                        //
            vTable,
            vUint24,
            vAdjustSwProc,
            vTroubleTable,
            vDTCTable,
            NONE};                 

__packed struct TAVRMenuItem{                    //
  uint8_t                    level;              // ������� �������
  char                       name[32];           // ��� ������ ����
   __packed void             *target;            // ����� ���������� � RAM
  struct TMenuItem __flash   *units;             // ����� ������ ������ ���������
  uint8_t                    mask;               // ����� - ��� ������: *target|=mask;  ��� ��.������ *target=mask;
  __packed union {                               //
    int32_t                  imin;               //
    float                    fmin;               //
  };                                             //
  __packed union {                               //
    int32_t                  imax;               //
    float                    fmax;               //
  };                                             //
  uint32_t                   defaultVal;         //
  uint32_t                   type;               // ��� �������� ����
};                                               //

__packed struct TAVRProcRec{                     //
  void *  PID;                                   //
  void (*procAddress)();                         //
};                                               
                                                 
__packed struct TAVRTableRec{                    //
  uint8_t                    TID;                //
  uint8_t                    name[20];           //
  void __flash               *adr;               //
  uint16_t                   tableSize;          //
  void                       *readAdr;           //
  void                       *writeAdr;          //
  uint16_t                   dataSize;           //
  uint8_t                    flags;              //
};

__packed struct TARMMenuItem{                    //
  uint8_t                 level;                 // ������� �������
  char                    name[32];              // ��� ������ ����
  void                    *target;               // ����� ���������� � RAM
  uint8_t                 mask;                  // ����� - ��� ������: *target|=mask;  ��� ��.������ *target=mask;
  __packed union{                                // 
    int32_t               imin;                  // ����������� �������� ��� ����� ��� vFlag16 vFlag32
    int32_t               mask;                  //
    float                 fmin;                  //
  }rmin;                                         //
  __packed union{                                //
    int32_t               imax;                  // ����������� ��������
    float                 fmax;                  //
  }rmax;                                         //
  uint32_t                defaultVal;            // �������� �� ���������, ������������ ��� ��������
  uint32_t                type;                  // ��� �������� ����
  uint8_t                 reserv1;               //
  uint8_t                 reserv2;               //
  uint8_t                 reserv3;               //
};                                               //
                                                 //
__packed struct TARMProcRec{                     //
  void *  PID;                                   //
  void (*procAddress)();                         //
};                                               //
                                                 //
__packed struct TARMTableRec{                    //
  uint8_t  TID;                                  //
  uint8_t  name[20];                             //
  void   *tableAddr;                             //
  uint16_t tableSize;                            //
  void   *readAdr;                               //
  void   *writeAdr;                              //
  uint16_t dataSize;                             //
  uint16_t flags;                                //
};                                               //
                                                 //
__packed struct compTTableRec{                   //
  uint8_t  TID;                                  //
  uint8_t  name[20];                             //
  uint16_t adr;                                  //
  uint16_t tableSize;                            //
  uint16_t readAdr;                              //
  uint16_t writeAdr;                             //
  uint16_t dataSize;                             //
  uint8_t  flags;                                //
};                                               //
                                                 //
__packed struct compTMenuItem{                   //
  uint8_t                   level;               // ������� �������
  char                    name[32];              // ��� ������ ����
  uint16_t                  target;              // ����� ���������� � RAM
  uint16_t                  units;               // ����� ������ ������ ���������
  uint8_t                   mask;                // ����� - ��� ������: *target|=mask;  ��� ��.������ *target=mask;
  __packed union {                               //
    int32_t                 imin;                // ���. ��������
    float                 fmin;                  //  
  };                                             //
  __packed union {                               //
    int32_t                 imax;                // ����. ��������
    float                 fmax;                  // 
  };                                             //
  uint32_t                  defaultVal;          // �������� �� ���������
  uint32_t type;                                 // ��� �������� ����
};                                               //
                     
extern void TMenuItemToCompTMenuItem(compTMenuItem *nmi,uint32_t targetOffs,TARMMenuItem *mi);
extern void TARMTableRecToCompTTableRec(compTTableRec *ctr, TARMTableRec *tr);


#endif

