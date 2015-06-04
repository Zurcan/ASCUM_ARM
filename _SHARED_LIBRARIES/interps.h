#ifndef __MENULIB__
#define __MENULIB__

#include "_compat.h"
#include "stdint.h"

/** @file 
Файл содержит объявления структур, необходимых для построения интерпретационных таблиц и реестра данных.
Подробнее см. \ref MainConcept
*/ 
/**@page MainConcept Основные понятия
Доступ к данным посредством \ref protocolController производится по 8-битным идентификационным
номерам, называемым индентификатором данных или TID, поэтому каждый блок данных, который может 
быть прочитан или записан посредством передачи команды в \ref protocolController, должен быть внесен
в реестр данных.
<b>Реестр данных</b> - это массив @ref DataRegistryItem_ARM_t, который служит для задания соответствия
различным блокам данных 8-битных идентификаторов и таблиц их интерпретации. Именно реестр данных
связывает разбросанные по коду таблицы интерпретации в единое целое.

При получении запроса на доступ к данным, \ref protocolController производит поиск запрошенного
идентификатора в подключенном реестре данных. Если данные с запрошенным идентификатором в реестре 
данных не найдены \ref protocolController вернет ошибку доступа к неподдерживаемому идентификатору.
Если данные найдены, тогда будет продолжен запрошенный сеанс доступа.

Пример реестра данных:
\code
struct DataRegistryItem_ARM_t sysMenus[]={                                                                                                             
{_ID_SIGNATURE  ,"Система"          ,(void*)sigMenu                        ,sizeof(sigMenu),
                                     &selfSignature  ,&selfSignature       ,sizeof(selfSignature),
                                     ff__RemProcsEn+ff__ReadOnly},
{_ID_ADDITIONAL4,"TEST"             ,(void*)testMenu                       ,sizeof(testMenu),
                                     &testStr,&testStr                     ,sizeof(testStr),
                                     ff__Dynamic  }
};
\endcode

Кроме идентификатора данным может быть сопоставленна таблица интерпретации.

<b>Таблица интерпретации</b> - это массив @ref InterpretationItem_ARM_t, описывающий состав
монолитного блока данных. С ее помощью можно произвести выделение именованных типизированных переменных
из анализируемого блока данных.

Пример таблицы интерпретации данных:
\code
__packed struct {
    char a;
    short b;
    long c;
    float d;
    char  str[128];
} testStr;

struct InterpretationItem_ARM_t  testMenu[]  = {
    {0,	"ТЕСТ.МЕНЮ"                         ,0                  ,0  ,0  ,0  ,0    ,vSub		},
    {1,	"Unlimited"                         ,0                  ,0  ,0  ,0  ,0    ,vSub		},
    {2,	  "uint8"                           ,(void*)&testStr.a  ,0  ,0  ,0  ,0    ,vUint8  +vpImdChange},
    {2,	  "int8"                            ,(void*)&testStr.a  ,0  ,0  ,0  ,0    ,vInt8   +vpImdChange},
    {2,	  "uint16"                          ,(void*)&testStr.b  ,0  ,0  ,0  ,0    ,vUint16 +vpImdChange},
    {2,	  "int16"                           ,(void*)&testStr.b  ,0  ,0  ,0  ,0    ,vInt16  +vpImdChange},
    {2,	  "int32"                           ,(void*)&testStr.c  ,0  ,0  ,0  ,0    ,vInt32  +vpImdChange},
    {2,	  "fract8"                          ,(void*)&testStr.a  ,2  ,0  ,0  ,0    ,vFract8 +vpImdChange},
    {2,	  "fract16"                         ,(void*)&testStr.b  ,3  ,0  ,0  ,0    ,vFract16+vpImdChange},
    {2,	  "float"                           ,(void*)&testStr.d  ,3  ,0  ,0  ,0    ,vFloat  +vpImdChange},
    {2,	  "vuint24"                         ,(void*)&testStr.c  ,0  ,0  ,0  ,0    ,vUint24 +vpImdChange},
    {0,	""							                    ,0                  ,0  ,0  ,0  ,0    ,NONE		}
};
\endcode

<b>Реестр процедур</b> - это массив \ref ProcedureListItem_ARM_t, связывающий функции, доступные для
удаленного вызова с 16-битными идентификаторами, необходим для развязки от реальных адресов функций. 
Пример реестра процедур:
\code
const struct ProcedureListItem_ARM_t sysProcedures[]={
{_CC_UpdateSignalSwitches     ,&doUpdateSignalSwitches},
{_CC_CancelSignalSwitches     ,&doCancelSignalSwitches}
};
\endcode
Совместное использование реестра данных, таблиц интерпретации и реестра процедур позволяет решить ряд задач:
  - абстрагировать функции обмена данными от механизмов хранения и обработки;
  - подключать универсальные интерфейсные средства для взаимодействия с устройством и их помощью;
организовывать эффективные пользовательские интерфейсы управления и контроля за параметрами устройства;
  - обеспечить именованный разбор данных, получаемый ведомыми устройствами;
  - платформенная независимость механизамов взаимодействия с устройством по протоколу MIO

\note
Структуры, описывающие реестр данных и интерпретаторы рассаматриваются со стороны пользовательской программы,
со стороны протокола MIO используются подобные структуры, но упрощенные см. \ref DataRegistryItem_RM_t и
\ref InterpretationItem_RM_t.
*/

/**@addtogroup DRI  Реестр данных
<b>Реестр данных</b> - это массив @ref DataRegistryItem_ARM_t, который служит для задания соответствия
различным блокам данных 8-битных идентификаторов и таблиц их интерпретации.
Пример реестра данных:
\code
struct DataRegistryItem_ARM_t sysMenus[]={                                                                                                             
{_ID_SIGNATURE  ,"Система"          ,(void*)sigMenu                        ,sizeof(sigMenu),
                                     &selfSignature  ,&selfSignature       ,sizeof(selfSignature),
                                     ff__RemProcsEn+ff__ReadOnly},
{_ID_ADDITIONAL4,"TEST"             ,(void*)testMenu                       ,sizeof(testMenu),
                                     &testStr,&testStr                     ,sizeof(testStr),
                                     ff__Dynamic  }
};
\endcode
@{*/
/**@name Константы флагов элемента реестра данных (DataRegistryItem_ARM_t)
@{*/
const char ff__ReadOnly                          =  0x01;   ///< Данные только для чтения.
const char ff__Dynamic                           =  0x02;   ///< Данные динамично меняются, требуется циклическая перезагрузка.
const char ff__RemProcsEn                        =  0x04;   ///< Удаленные процедуры разрешены.
const char ff__LocProcsEn                        =  0x08;   ///< Локальные процедуры разрешены.
const char ff__System                            =  0x10;   ///< Системные даннные
const char ff__Debug                             =  0x20;   ///< Отладочные данные
const char ff__DataResizable                     =  0x80;   ///< Флаг переменной длины данных таблицы

const long ff__PurelyNative                      =  0x8000; /**< Указывает что таблица уже из транспортных 
                                                              InterpretationItem_RM_t и не требует преобразования*/
const long ff__ClearRead                         =  0x4000; ///< Очищать по факту чтения
///@}
///@}


/**@addtogroup DIT  Таблица интерпретации
<b>Таблица интерпретации</b> - это массив @ref InterpretationItem_ARM_t, описывающий состав
монолитного блока данных. С ее помощью можно произвести выделение именованных типизированных переменных
из анализируемого блока данных.

Массив таблицы интерпретации формируется по следующим правилам:
- первая запись должна иметь уровень 0
- первая запись должна иметь \ref target 0
- первая запись должна иметь тип \ref vSub.
- уровень 2 по-умолчанию отображается свернутым.

Пример таблицы интерпретации данных:
\code
__packed struct {
    char a;
    short b;
    long c;
    float d;
    char  str[128];
} testStr;

struct InterpretationItem_ARM_t  testMenu[]  = {
    {0,	"ТЕСТ.МЕНЮ"                         ,0                  ,0  ,0  ,0  ,0    ,vSub		},
    {1,	"Unlimited"                         ,0                  ,0  ,0  ,0  ,0    ,vSub		},
    {2,	  "uint8"                           ,(void*)&testStr.a  ,0  ,0  ,0  ,0    ,vUint8  +vpImdChange},
    {2,	  "int8"                            ,(void*)&testStr.a  ,0  ,0  ,0  ,0    ,vInt8   +vpImdChange},
    {2,	  "uint16"                          ,(void*)&testStr.b  ,0  ,0  ,0  ,0    ,vUint16 +vpImdChange},
    {2,	  "int16"                           ,(void*)&testStr.b  ,0  ,0  ,0  ,0    ,vInt16  +vpImdChange},
    {2,	  "int32"                           ,(void*)&testStr.c  ,0  ,0  ,0  ,0    ,vInt32  +vpImdChange},
    {2,	  "fract8"                          ,(void*)&testStr.a  ,2  ,0  ,0  ,0    ,vFract8 +vpImdChange},
    {2,	  "fract16"                         ,(void*)&testStr.b  ,3  ,0  ,0  ,0    ,vFract16+vpImdChange},
    {2,	  "float"                           ,(void*)&testStr.d  ,3  ,0  ,0  ,0    ,vFloat  +vpImdChange},
    {2,	  "vuint24"                         ,(void*)&testStr.c  ,0  ,0  ,0  ,0    ,vUint24 +vpImdChange},
};
\endcode
*/
/**
Тип интерпретирующего элемента.
Определяет как будет интерпретироваться элемент таблицы интерпретации. Какие из полей \ref InterpretationItem_ARM_t
каким образом будут использованы.
@warning
Все неиспользуемые поля \ref InterpretationItem_ARM_t должны быть равны 0 для исключения их влияния при 
последующей доработке библиотеки.
\ingroup DIT
*/
enum  InterpretationItemType_t{ 
  
            vUint8,                              /**< Байт без знака.
                                                   - минимум - InterpretationItem_ARM_t::imin
                                                   - максимум - InterpretationItem_ARM_t::imax
                                                   - по-умолчанию - InterpretationItem_ARM_t::defaultVal
                                                   
                                                   Пример:
                                                   \code
                                                   {2,	"Количество измерений"  ,(void*)&measures.count, 0, 5, 250,0  ,vUint8 },
                                                   \endcode
                                                 */
            vInt8,                               ///< Байт со знаком.\nЗначения полей такие же как для \ref vUint8.
            vInt16,                              ///< Слово со знаком.\nЗначения полей такие же как для \ref vUint8.
            vUint16,                             ///< Слово без знака.\nЗначения полей такие же как для \ref vUint8.
            vInt32,                              ///< Двойное слово со знаком.\nЗначения полей такие же как для \ref vUint8.
            vFract8,                             /**< Байт с фиксированной точкой. Число типа 25.5. Точность заказывается маской.
                                                   - минимум - InterpretationItem_ARM_t::imin
                                                   - максимум - InterpretationItem_ARM_t::imax
                                                   - по-умолчанию - InterpretationItem_ARM_t::defaultVal
                                                   - количество знаков после "," - InterpretationItem_ARM_t::mask. Параметр определяет
                                                     на 10 в какой степени делить величину, минимум, максимум и по-умолчанию
                                                 */
            vFract16,                            /**< 16-битное слово с фиксированной точкой. Число типа 6553.5. Точность 
                                                   заказывается маской.
                                                   - минимум - InterpretationItem_ARM_t::imin
                                                   - максимум - InterpretationItem_ARM_t::imax
                                                   - по-умолчанию - InterpretationItem_ARM_t::defaultVal
                                                   - количество знаков после "," - InterpretationItem_ARM_t::mask. Параметр определяет
                                                     на 10 в какой степени делить величину, минимум, максимум и по-умолчанию
                                                 */
            vFloat,                              /**< Число с плавающей запятой.
                                                   - минимум - InterpretationItem_ARM_t::imin / \f$10^{InterpretationItem::mask}\f$
                                                   - максимум - InterpretationItem_ARM_t::imax / \f$10^{InterpretationItem::mask}\f$
                                                   - по-умолчанию - InterpretationItem_ARM_t::defaultVal
                                                   - количество знаков после "," - InterpretationItem_ARM_t::mask. Параметр определяет
                                                     на 10 в какой степени делить минимум, максимум и по-умолчанию
                                                 */
            vFlag,                               /**< Флаг 1-бит.
                                                   - начение определяется 
                                                     Value=(*(InterpretationItem_ARM_t::target)&InterpretationItem_ARM_t::mask)!=0;
                                                 */
            vList,                               /**< Элемент выбора для поля \ref vDropDown.
                                                   Описывает одну строку выпадающего списка. Является вложенной в иерархии таблицы в
                                                   родительский элемент типа \ref vDropDown.
                                                   - InterpretationItem_ARM_t::name будет показан в выпадающем списке если:\n
                                                     (*(InterpretationItem_ARM_t::target) == InterpretationItem_ARM_t::mask)
                                                 */
            vTime,                               ///< Время. 32 бит. Переменная времени time_t
            vProc,                               /**< Подпрограмма.
                                                   Идентификатор вызываемой процедуры - InterpretationItem_ARM_t::target.
                                                 */
            vAdjustProc,                         /**< Подпрограмма, выполняемая над данными.
                                                   - отправляется блок данных, интерпретируемый текущей 
                                                   интерпретационной таблицей.
                                                   - выполняется процедура
                                                   - загружается блок данных, интерпретируемый текущей 
                                                   интерпретационной таблицей.
                                                 */
            vSub,                                /**< Подгруппа.
                                                   Подгруппы позволяют произвести логическую группировку параметров в древовидную структуру.
                                                   Элементы, следующие за элементом-подгруппой с полем InterpretationItem_ARM_t::level большим
                                                   чем у подгруппы, включаются в нее.
                                                   Например в следующем коде BIT_1 входит в подгруппу "Системные флаги", а BIT_2 - нет.
                                                   \code
                                                     {1,"Системные флаги" ,0               ,0      ,0      ,0      ,0                 ,vSub   }, 
                                                     {2,"BIT_1"   ,(void*)&stateInfo.flags ,1      ,0      ,0      ,0                 ,vFlag  },
                                                     {1,"BIT_2"   ,(void*)&stateInfo.flags ,2      ,0      ,0      ,0                 ,vFlag  },
                                                   \endcode
                                                 */
            vString,                             /**< Строка до 255 символов. 
                                                    - длина строки - InterpretationItem_ARM_t::mask
                                                 */
            vHString,                            /**< Скрытая строка до 255 символов (замаскированная "*").
                                                    - длина строки - InterpretationItem_ARM_t::mask
                                                 */
            vText,                               ///< Многострочный текст (не используется)
            vFlag8,                              /**< 8-битный массив флагов.
                                                   Доступные для просмотра/редактирования флаги определяются маской InterpretationItem_ARM_t::mask.
                                                 */
            vFlag16,                             /**< 16-битный массив флагов.
                                                   Доступные для просмотра/редактирования флаги определяются маской InterpretationItem_ARM_t::imin.
                                                   \warning InterpretationItem_ARM_t::mask не используется в силу его недостаточной разрядности.
                                                 */
            mUnit,                               ///< Единица измерения (не используется)
            vSettingsProc,                       ///< Процедура обработки изменений настроек (не используется)
            vDropDown,                           /**< Выпадающий список.
                                                   Выпадающий список наполняется вложенными элементами типа vList с полем 
                                                   InterpretationItem_ARM_t::level большим чем у самого vDropDown.
                                                   Выбор элемента осуществляется путем считывания байта по заданному в 
                                                   InterpretationItem_ARM_t::target смещению, наложения маски InterpretationItem_ARM_t::mask
                                                   и поиска вложенного элемента \ref vList со значением InterpretationItem_ARM_t::mask 
                                                   равным полученному.
                                                   Например:
                                                   \code
                                                     {2,"Состояние/стадия"      ,(void*)&apb.ConDevStatus.stage             ,0xFF,0,0,0,vDropDown},\
                                                     {3,"ожидается подключение" ,(void*)&apb.ConDevStatus.stage             ,   0,0,0,0,vList},\
                                                     {3,"инициализация"         ,(void*)&apb.ConDevStatus.stage             ,   1,0,0,0,vList},\
                                                     {3,"подключен"             ,(void*)&apb.ConDevStatus.stage             ,   2,0,0,0,vList},\
                                                   \endcode
                                                 */
            vDivider,                            /**< Разделитель.
                                                   Отображается как полоса разделитель, не имеет других параметов
                                                 */
            vSerial,                             ///< Серийный номер (не используется)
            vSystemProc,                         /**<  Подпрограмма, выполняемая над данными и интерпретационной таблицей.
                                                   - отправляется блок данных, интерпретируемый текущей интерпретационной таблицей.
                                                   - выполняется процедура.
                                                   - производится перезагрузка реестра данных и таблиц интерпретации.
                                                 */
            vVersion,                            ///< Версия в формате VersionData.
            vButton,                             /**< Кнопка-флаг. Устанавливает флаг в 1 пока нажата и в 0 - отжата.
                                                   в остальном аналогична \ref vFlag.*/
            vTroubleCode,                        ///< Код ошибки (не используется).
            vTable,                              /**< Таблица.
                                                   Таблица наполняется вложенными элементами различных типов с полем 
                                                   InterpretationItem_ARM_t::level большим чем у самого vTable.
                                                   - указатель на сруктуру-хранилище данных - InterpretationItem_ARM_t::target;
                                                   - размер элемента строки таблицы - InterpretationItem_ARM_t::mask;
                                                   - Смещение внутри хранилища байта-номера первой строки 
                                                     (32-бит слово) - InterpretationItem_ARM_t::imin;
                                                   - Смещение внутри хранилища байта-номера последней строки +1 
                                                     (32-бит слово) - InterpretationItem_ARM_t::imax;
                                                   
                                                   \note На данный момент таблицы могут включать в себя нумерические данные,
                                                   флаги, время и сообщения из библиотеки сообщений.
                                                 */
            vUint24,                             ///< 24-битное слово без знака.\nЗначения полей такие же как для \ref vUint8.
            vAdjustSwProc,                       /**< Выполнение подпрограммы с аргументом (32-бит слово).
                                                   - вносится значение аргумента InterpretationItem_ARM_t::imax
                                                   в указанную InterpretationItem_ARM_t::target ячейку блока данных
                                                   - отправляется блок данных, интерпретируемый текущей интерпретационной таблицей.
                                                   - выполняется процедура, идентификатор которой указан в InterpretationItem_ARM_t::imin.
                                                 */
            vTroubleTable,                       ///< Таблица ошибок системы.
            vDTCTable,                           ///< Таблица ошибок J1939.
            NONE,
            vDouble,                             /** Число с плавающей запятой 64бит.
                                                   - минимум - InterpretationItem_ARM_t::imin / \f$10^{InterpretationItem::mask}\f$
                                                   - максимум - InterpretationItem_ARM_t::imax / \f$10^{InterpretationItem::mask}\f$
                                                   - по-умолчанию - InterpretationItem_ARM_t::defaultVal
                                                   - количество знаков после "," - InterpretationItem_ARM_t::mask. Параметр определяет
                                                     на 10 в какой степени делить минимум, максимум и по-умолчанию
                                                 */
            tMessageCode,                       ///< Элемент таблицы - ссылка на код сообщения.
            vTableStartCounter,
            vTableEndCounter,
            vRecExtConnect=120                  ///< Дополнительная информация для предыдущего элемента. 
                                                ///Такой элемент должен следовать непосредственно за расширяемым.
};
/////////////////////////////////////////////////////////////////////////////////////////////
/**
\name Константы флагов типа интерпретирующего элемента (InterpretationItemType_t)
\ingroup DIT
@{
*/
const unsigned long vpREADONLY             =0x80000000;///< Помечает элемент как "только для чтения";
const unsigned long vpHEX                  =0x40000000;///< Задает начальный режим отображения как шестнадцатиричный;
const unsigned long vpBIN                  =0x20000000;///< Задает начальный режим отображения как двоичный;
const unsigned long vpOCT                  =0x10000000;///< Задает начальный режим отображения как восьмиричный;
const unsigned long vpLeftJustified        =0x08000000;///< Для \ref vFlag16 и \ref vFlag16 задает счет битов слева направо;
const unsigned long vpStartOne             =0x04000000;///< Для \ref vFlag16 и \ref vFlag16 задает счет битов с 1;
const unsigned long vpGauged               =0x02000000;///< Для нумерических величин отображать столбцовую диграмму;
const unsigned long vpImdChange            =0x01000000;/**< Для изменяемых величин, немедленная отправка измененного 
                                                         значения в устройство. Позволяет управлять значением величины в 
                                                         реальном масштабе времени.
                                                       */
const unsigned long vpHidden               =0x00100000;///< Для сервисных частей, не видимых пользователю;
const unsigned long thIsHumanized          =0x00080000;///< Указывает что элемент уже представлен в человекоудобном виде.
const unsigned long vpDominant             =0x00040000;///< Указывает что элемент доминантный
const unsigned long vpDominantDiag         =0x00020000;///< Указывает что диагностический для доминантного элемента
const unsigned long spFolded               =0x40000000;///< Флаг для типа vSub. Указывает что элемент должен быть показанн свернутым.
/**
@}
\name Константы флагов заголовочного интерпретирующего элемента
\ingroup DIT
@{            
*/
const unsigned long thHumanize             =0x00200000;///< Указывает что таблица должна быть представленна в человекоудобном виде.
const unsigned long thIconizeName          =0x00400000;///< Указывает что можно использовать пиктограммы.
const unsigned long thLangLink             =0x00800000;///< Указывает что таблица связанна с языковым списком.
///@}

//#ifndef RIGHTS_CONTROL_IGNORE
#define arT      0x08+
#define arU      0x10+
#define arS      0x20+
#define arD      0x40+
#define arV      0x80+
/*#else
#define aT      
#define aU      
#define aS      
#define aD      
#define aV      
#endif //RIGHTS_CONTROL_IGNORE*/

#define arTU     (aT+aU 0)+
#define arTS     (aT+aS 0)+
#define arTD     (aT+aD 0)+
#define arTV     (aT+aV 0)+
#define arUS     (aU+aS 0)+
#define arUD     (aU+aD 0)+
#define arUV     (aU+aV 0)+
#define arSD     (aS+aD 0)+
#define arSV     (aS+aV 0)+
#define arDV     (aD+aV 0)+

#define arTUS    (aT+aU+aS 0)+
#define arTUD    (aT+aU+aD 0)+
#define arTSD    (aT+aS+aD 0)+
#define arUSD    (aU+aS+aD 0)+

#define arUSDV   (aU+aS+aD+aV 0)+
#define arTSDV   (aT+aS+aD+aV 0)+
#define arTUDV   (aT+aU+aD+aV 0)+
#define arTUSV   (aT+aU+aS+aV 0)+
#define arTUSD   (aT+aU+aS+aD 0)+

#define aTUSDV   (aT+aU+aS+aD+aV 0)+

/**Элемент таблицы интерпретации или интерпретатор.
Информирует получателя блока данных о том как конкретно трактовать указанный 
фрагмент  блока.
\ingroup DIT
*/
struct __attribute__ ((packed)) InterpretationItem_ARM_t{
  unsigned char                 level;                 ///< Уровень элемента в иерархии таблицы.
/**< 
  - биты [0..2] - номер уровня в иерархии таблицы.
  - биты [3..7] - номер уровня доступа необходимого для доступа к элементу.
  Доступ разделяется на 4 части:
        ("A") - Диагностический доступ. Просмотр данных для конечного пользователя.
  бит 3 ("T") - Доступ к функциям и данным предназначенным для проверки работоспособности целевого (управляемого) оборудования и системы
  бит 4 ("U") - Доступ к функциям и данным предназначенным для наладки целевого (управляемого) оборудования
  бит 5 ("S") - Доступ к функциям и данным для осуществления настройки устройства на целевое оборудование
  бит 6 ("D") - Доступ к функциям и данным предназначенным для проверки, системной настройки  устройства/системы
  бит 7 ("V") - Доступ к функциям и данным предназначенным для настройки данных статистики
*/
  char                          name[32];              ///< Имя элемента
  void                          *target;               ///< Указатель на элемент блока данных
  unsigned char                 mask;                  ///< Маска
  union __attribute__ ((packed)){
    signed long                 imin;                  ///< Минимальное значение
    signed long                 mask;                  
    float                       fmin;                  
  }rmin;                                               
  union __attribute__ ((packed)){
    signed long                 imax;                  ///< Максимальное значение
    float                       fmax;                  
  }rmax;                                               
  unsigned long                 defaultVal;            ///< Значение по умолчанию
  unsigned long                 type;                  ///< Тип элемента @ref InterpretationItemType_t с модификаторами
  unsigned char                 reserv1;               //
  unsigned char                 reserv2;               //
  unsigned char                 reserv3;               //
};                                                     //
                                                       //
class ProtocolController;
/**Элемент реестра процедур.
Связывает ID процедуры с указателем на конкретную функцию void (*)(void)
*/
struct __attribute__ ((packed)) ProcedureListItem_ARM_t{               //
  void *  PID;                                         ///< ID процедуры
  void (*procAddress)(ProtocolController *);           ///< Указатель на функцию
};                                                     //
                                                       //
/**Элемент реестра данных
Связывает ID данных с конкретной таблицей интерпретации, блоком данных и 
флагами, общими для таблицы.

Поля DataRegistryItem_ARM_t::readAdr и DataRegistryItem_ARM_t::writeAdr позволяют 
разделить блоки данных для записи и чтения или запретить запись (DataRegistryItem_ARM_t::writeAdr=0).
\ingroup DRI
*/
enum dataUpdatedWith{duwRead,duwWrite};                ///<
typedef void (*dataUpdatedNotifyProc)(void * sender, dataUpdatedWith duw, unsigned char TID);

struct __attribute__ ((packed)) DataRegistryItem_ARM_t{
  unsigned char  TID;                                  ///< Идентификатор данных
  unsigned char  name[20];                             ///< Отображаемое имя таблицы и блока данных
  void          *tableAddr;                            ///< Указатель на таблицу интерпретации
  unsigned short tableSize;                            ///< Размер таблицы интерпретации
  void          *readAddr;                             ///< Указатель на блок данных для чтения
  unsigned short dataSize;                             ///< Размер блока данных
  void          *writeAddr;                            ///< Указатель на блок данных для записи
  unsigned short writeBufferSize;                      ///< Размер приемного буффера при записи данных
  unsigned short flags;                                ///< Флаги таблицы идентификации
  dataUpdatedNotifyProc updateNotify;                  ///< Указатель на функцию уведомления об изменении
  void           *userPtr;
};                                                     

/**Транспортный элемент реестра данных.
Служит для транспортирования данных \ref DataRegistryItem_RM_t по протоколу MIO. Все элементы
реестра данных преобразовываюся к транспортным элементам и только потом передаются
по протоколу MIO
\ingroup DRI
*/
struct __attribute__ ((packed)) DataRegistryItem_RM_t{
  unsigned char  TID;                                  ///< Идентификатор данных
  unsigned char  name[20];                             ///< Отображаемое имя таблицы и блока данных
  unsigned short _reserv1;                             ///< =0.
  unsigned short tableSize;                            ///< Размер таблицы интерпретации
  unsigned short _reserv2;                             ///< =0.
  unsigned short _reserv3;                             ///< =0.
  unsigned short dataSize;                             ///< Размер блока данных
  unsigned char  flags;                                ///< Флаги таблицы идентификации
};                                                     //
                                                       //
/**Транспортный элемент таблицы интерпретации.
Служит для транспортирования данных \ref InterpretationItem_ARM_t по протоколу MIO. Все элементы
таблиц интерпретации данных преобразовываюся к транспортным элементам и только потом передаются
по протоколу MIO
Информирует получателя блока данных о том как конкретно трактовать указанный 
фрагмент  блока.
\ingroup DIT
*/
struct __attribute__ ((packed)) InterpretationItem_RM_t{               //
  unsigned char    level;                              ///< Уровень элемента в иерархии таблицы
/**< 
  - биты [0..3] - номер уровня в иерархии таблицы.
  - биты [4..7] - номер уровня доступа необходимого для доступа к элементу.
  - если биты 4..7 = 1, т.е. если >0xF0, используется как флаг расширяющей записи. Такая запись должна следовать непосредственно за расширяемой.

  Например:
  - 255 - запись расширения информации о физическом подключении.
*/
  char             name[32];                           ///< Имя элемента
  unsigned short   target;                             ///< Смещение элемента от начала блока данных
  unsigned short   hintCode;                           ///< Индекс подсказки
  unsigned char    mask;                               ///< Маска
  signed long      imin;                               ///< Минимальное значение
  signed long      imax;                               ///< Максимальное значение
  unsigned long    defaultVal;                         ///< Значение по умолчанию
  unsigned long    type;                               ///< Тип элемента @ref InterpretationItemType_t с модификаторами
};                                               
                     
/**Функция обеспечивает преобразование платформенно-зависимой \ref DataRegistryItem_ARM_t в транспортную
\ref DataRegistryItem_RM_t.
\param[out] nmi - транспортная \ref InterpretationItem_RM_t
\param[in] targetOffs - адрес структуры данных привязанной к таблице интерпретации
\param[in] mi - платформенно-зависимая \ref InterpretationItem_ARM_t
\ingroup DIT
*/
extern void toInterpretationItem        (InterpretationItem_RM_t *nmi,unsigned long targetOffs,InterpretationItem_ARM_t *mi);

/**Функция обеспечивает преобразование платформенно-зависимой \ref DataRegistryItem_ARM_t в транспортную
\ref DataRegistryItem_RM_t.
\param[out] ctr - транспортная \ref DataRegistryItem_RM_t
\param[in] tr - платформенно-зависимая \ref DataRegistryItem_ARM_t
\ingroup DRI
*/
extern void toDataRegistryItem          (DataRegistryItem_RM_t *ctr, DataRegistryItem_ARM_t *tr);


#endif

