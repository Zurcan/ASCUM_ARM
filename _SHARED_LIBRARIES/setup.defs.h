#ifndef __MENULIB__
#define __MENULIB__
#include "_compat.h"
#include "stdint.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// Типы элементов меню        //

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
            vUint8,                              // Байт без знака
            vInt8,                               // Байт со знаком
            vInt16,                              // Слово со знаком
            vUint16,                             // Слово без знака
            vInt32,                              // Двойное слово со знаком
            vFract8,                             // Число типа 25.5. Точность заказывается маской.
            vFract16,                            // Число типа 6553.5 Точность заказывается маской.
            vFloat,                              // Число с плавающей запятой
            vFlag,                               // Флаг. 1Бит. Накладывается маской.
            vList,                               // Элемент выбора
            vTime,                               // Время. 32 бит. Переменная времени
            vProc,                               // Подпрограмма
            vAdjustProc,                         // Подпрограмма, выполняемая над данными, предваряется 
                                                 // отправкой текущих значений структур в которых упоминается
            vSub,                                // Подменю
            vString,                             // Строка до 255 символов
            vHString,                            // Скрытая строка
            vText,                               // Многострочный текст
            vFlag8,                              // Флаг
            vFlag16,                             // Флаг
            mUnit,                               // Единица измерения
            vSettingsProc,                       // Процедура обработки изменений настроек
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
  uint8_t                    level;              // Уровень подменю
  char                       name[32];           // Имя пункта меню
   __packed void             *target;            // адрес переменной в RAM
  struct TMenuItem __flash   *units;             // адрес строки единиц измерения
  uint8_t                    mask;               // маска - для флагов: *target|=mask;  для эл.выбора *target=mask;
  __packed union {                               //
    int32_t                  imin;               //
    float                    fmin;               //
  };                                             //
  __packed union {                               //
    int32_t                  imax;               //
    float                    fmax;               //
  };                                             //
  uint32_t                   defaultVal;         //
  uint32_t                   type;               // тип элемента меню
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
  uint8_t                 level;                 // Уровень подменю
  char                    name[32];              // Имя пункта меню
  void                    *target;               // адрес переменной в RAM
  uint8_t                 mask;                  // маска - для флагов: *target|=mask;  для эл.выбора *target=mask;
  __packed union{                                // 
    int32_t               imin;                  // минимальное значение или маска для vFlag16 vFlag32
    int32_t               mask;                  //
    float                 fmin;                  //
  }rmin;                                         //
  __packed union{                                //
    int32_t               imax;                  // минимальное значение
    float                 fmax;                  //
  }rmax;                                         //
  uint32_t                defaultVal;            // значение по умолчанию, используется для настроек
  uint32_t                type;                  // тип элемента меню
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
  uint8_t                   level;               // Уровень подменю
  char                    name[32];              // Имя пункта меню
  uint16_t                  target;              // адрес переменной в RAM
  uint16_t                  units;               // адрес строки единиц измерения
  uint8_t                   mask;                // маска - для флагов: *target|=mask;  для эл.выбора *target=mask;
  __packed union {                               //
    int32_t                 imin;                // мин. значение
    float                 fmin;                  //  
  };                                             //
  __packed union {                               //
    int32_t                 imax;                // макс. значение
    float                 fmax;                  // 
  };                                             //
  uint32_t                  defaultVal;          // значение по умолчанию
  uint32_t type;                                 // тип элемента меню
};                                               //
                     
extern void TMenuItemToCompTMenuItem(compTMenuItem *nmi,uint32_t targetOffs,TARMMenuItem *mi);
extern void TARMTableRecToCompTTableRec(compTTableRec *ctr, TARMTableRec *tr);


#endif

