#ifndef __MENULIB__
#define __MENULIB__

#include "_compat.h"
#include "stdint.h"

/** @file 
���� �������� ���������� ��������, ����������� ��� ���������� ����������������� ������ � ������� ������.
��������� ��. \ref MainConcept
*/ 
/**@page MainConcept �������� �������
������ � ������ ����������� \ref protocolController ������������ �� 8-������ �����������������
�������, ���������� ���������������� ������ ��� TID, ������� ������ ���� ������, ������� ����� 
���� �������� ��� ������� ����������� �������� ������� � \ref protocolController, ������ ���� ������
� ������ ������.
<b>������ ������</b> - ��� ������ @ref DataRegistryItem_ARM_t, ������� ������ ��� ������� ������������
��������� ������ ������ 8-������ ��������������� � ������ �� �������������. ������ ������ ������
��������� ������������ �� ���� ������� ������������� � ������ �����.

��� ��������� ������� �� ������ � ������, \ref protocolController ���������� ����� ������������
�������������� � ������������ ������� ������. ���� ������ � ����������� ��������������� � ������� 
������ �� ������� \ref protocolController ������ ������ ������� � ����������������� ��������������.
���� ������ �������, ����� ����� ��������� ����������� ����� �������.

������ ������� ������:
\code
struct DataRegistryItem_ARM_t sysMenus[]={                                                                                                             
{_ID_SIGNATURE  ,"�������"          ,(void*)sigMenu                        ,sizeof(sigMenu),
                                     &selfSignature  ,&selfSignature       ,sizeof(selfSignature),
                                     ff__RemProcsEn+ff__ReadOnly},
{_ID_ADDITIONAL4,"TEST"             ,(void*)testMenu                       ,sizeof(testMenu),
                                     &testStr,&testStr                     ,sizeof(testStr),
                                     ff__Dynamic  }
};
\endcode

����� �������������� ������ ����� ���� ������������� ������� �������������.

<b>������� �������������</b> - ��� ������ @ref InterpretationItem_ARM_t, ����������� ������
����������� ����� ������. � �� ������� ����� ���������� ��������� ����������� �������������� ����������
�� �������������� ����� ������.

������ ������� ������������� ������:
\code
__packed struct {
    char a;
    short b;
    long c;
    float d;
    char  str[128];
} testStr;

struct InterpretationItem_ARM_t  testMenu[]  = {
    {0,	"����.����"                         ,0                  ,0  ,0  ,0  ,0    ,vSub		},
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

<b>������ ��������</b> - ��� ������ \ref ProcedureListItem_ARM_t, ����������� �������, ��������� ���
���������� ������ � 16-������� ����������������, ��������� ��� �������� �� �������� ������� �������. 
������ ������� ��������:
\code
const struct ProcedureListItem_ARM_t sysProcedures[]={
{_CC_UpdateSignalSwitches     ,&doUpdateSignalSwitches},
{_CC_CancelSignalSwitches     ,&doCancelSignalSwitches}
};
\endcode
���������� ������������� ������� ������, ������ ������������� � ������� �������� ��������� ������ ��� �����:
  - �������������� ������� ������ ������� �� ���������� �������� � ���������;
  - ���������� ������������� ������������ �������� ��� �������������� � ����������� � �� �������;
�������������� ����������� ���������������� ���������� ���������� � �������� �� ����������� ����������;
  - ���������� ����������� ������ ������, ���������� �������� ������������;
  - ������������� ������������� ����������� �������������� � ����������� �� ��������� MIO

\note
���������, ����������� ������ ������ � �������������� ���������������� �� ������� ���������������� ���������,
�� ������� ��������� MIO ������������ �������� ���������, �� ���������� ��. \ref DataRegistryItem_RM_t �
\ref InterpretationItem_RM_t.
*/

/**@addtogroup DRI  ������ ������
<b>������ ������</b> - ��� ������ @ref DataRegistryItem_ARM_t, ������� ������ ��� ������� ������������
��������� ������ ������ 8-������ ��������������� � ������ �� �������������.
������ ������� ������:
\code
struct DataRegistryItem_ARM_t sysMenus[]={                                                                                                             
{_ID_SIGNATURE  ,"�������"          ,(void*)sigMenu                        ,sizeof(sigMenu),
                                     &selfSignature  ,&selfSignature       ,sizeof(selfSignature),
                                     ff__RemProcsEn+ff__ReadOnly},
{_ID_ADDITIONAL4,"TEST"             ,(void*)testMenu                       ,sizeof(testMenu),
                                     &testStr,&testStr                     ,sizeof(testStr),
                                     ff__Dynamic  }
};
\endcode
@{*/
/**@name ��������� ������ �������� ������� ������ (DataRegistryItem_ARM_t)
@{*/
const char ff__ReadOnly                          =  0x01;   ///< ������ ������ ��� ������.
const char ff__Dynamic                           =  0x02;   ///< ������ ��������� ��������, ��������� ����������� ������������.
const char ff__RemProcsEn                        =  0x04;   ///< ��������� ��������� ���������.
const char ff__LocProcsEn                        =  0x08;   ///< ��������� ��������� ���������.
const char ff__System                            =  0x10;   ///< ��������� �������
const char ff__Debug                             =  0x20;   ///< ���������� ������
const char ff__DataResizable                     =  0x80;   ///< ���� ���������� ����� ������ �������

const long ff__PurelyNative                      =  0x8000; /**< ��������� ��� ������� ��� �� ������������ 
                                                              InterpretationItem_RM_t � �� ������� ��������������*/
const long ff__ClearRead                         =  0x4000; ///< ������� �� ����� ������
///@}
///@}


/**@addtogroup DIT  ������� �������������
<b>������� �������������</b> - ��� ������ @ref InterpretationItem_ARM_t, ����������� ������
����������� ����� ������. � �� ������� ����� ���������� ��������� ����������� �������������� ����������
�� �������������� ����� ������.

������ ������� ������������� ����������� �� ��������� ��������:
- ������ ������ ������ ����� ������� 0
- ������ ������ ������ ����� \ref target 0
- ������ ������ ������ ����� ��� \ref vSub.
- ������� 2 ��-��������� ������������ ���������.

������ ������� ������������� ������:
\code
__packed struct {
    char a;
    short b;
    long c;
    float d;
    char  str[128];
} testStr;

struct InterpretationItem_ARM_t  testMenu[]  = {
    {0,	"����.����"                         ,0                  ,0  ,0  ,0  ,0    ,vSub		},
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
��� ����������������� ��������.
���������� ��� ����� ������������������ ������� ������� �������������. ����� �� ����� \ref InterpretationItem_ARM_t
����� ������� ����� ������������.
@warning
��� �������������� ���� \ref InterpretationItem_ARM_t ������ ���� ����� 0 ��� ���������� �� ������� ��� 
����������� ��������� ����������.
\ingroup DIT
*/
enum  InterpretationItemType_t{ 
  
            vUint8,                              /**< ���� ��� �����.
                                                   - ������� - InterpretationItem_ARM_t::imin
                                                   - �������� - InterpretationItem_ARM_t::imax
                                                   - ��-��������� - InterpretationItem_ARM_t::defaultVal
                                                   
                                                   ������:
                                                   \code
                                                   {2,	"���������� ���������"  ,(void*)&measures.count, 0, 5, 250,0  ,vUint8 },
                                                   \endcode
                                                 */
            vInt8,                               ///< ���� �� ������.\n�������� ����� ����� �� ��� ��� \ref vUint8.
            vInt16,                              ///< ����� �� ������.\n�������� ����� ����� �� ��� ��� \ref vUint8.
            vUint16,                             ///< ����� ��� �����.\n�������� ����� ����� �� ��� ��� \ref vUint8.
            vInt32,                              ///< ������� ����� �� ������.\n�������� ����� ����� �� ��� ��� \ref vUint8.
            vFract8,                             /**< ���� � ������������� ������. ����� ���� 25.5. �������� ������������ ������.
                                                   - ������� - InterpretationItem_ARM_t::imin
                                                   - �������� - InterpretationItem_ARM_t::imax
                                                   - ��-��������� - InterpretationItem_ARM_t::defaultVal
                                                   - ���������� ������ ����� "," - InterpretationItem_ARM_t::mask. �������� ����������
                                                     �� 10 � ����� ������� ������ ��������, �������, �������� � ��-���������
                                                 */
            vFract16,                            /**< 16-������ ����� � ������������� ������. ����� ���� 6553.5. �������� 
                                                   ������������ ������.
                                                   - ������� - InterpretationItem_ARM_t::imin
                                                   - �������� - InterpretationItem_ARM_t::imax
                                                   - ��-��������� - InterpretationItem_ARM_t::defaultVal
                                                   - ���������� ������ ����� "," - InterpretationItem_ARM_t::mask. �������� ����������
                                                     �� 10 � ����� ������� ������ ��������, �������, �������� � ��-���������
                                                 */
            vFloat,                              /**< ����� � ��������� �������.
                                                   - ������� - InterpretationItem_ARM_t::imin / \f$10^{InterpretationItem::mask}\f$
                                                   - �������� - InterpretationItem_ARM_t::imax / \f$10^{InterpretationItem::mask}\f$
                                                   - ��-��������� - InterpretationItem_ARM_t::defaultVal
                                                   - ���������� ������ ����� "," - InterpretationItem_ARM_t::mask. �������� ����������
                                                     �� 10 � ����� ������� ������ �������, �������� � ��-���������
                                                 */
            vFlag,                               /**< ���� 1-���.
                                                   - ������� ������������ 
                                                     Value=(*(InterpretationItem_ARM_t::target)&InterpretationItem_ARM_t::mask)!=0;
                                                 */
            vList,                               /**< ������� ������ ��� ���� \ref vDropDown.
                                                   ��������� ���� ������ ����������� ������. �������� ��������� � �������� ������� �
                                                   ������������ ������� ���� \ref vDropDown.
                                                   - InterpretationItem_ARM_t::name ����� ������� � ���������� ������ ����:\n
                                                     (*(InterpretationItem_ARM_t::target) == InterpretationItem_ARM_t::mask)
                                                 */
            vTime,                               ///< �����. 32 ���. ���������� ������� time_t
            vProc,                               /**< ������������.
                                                   ������������� ���������� ��������� - InterpretationItem_ARM_t::target.
                                                 */
            vAdjustProc,                         /**< ������������, ����������� ��� �������.
                                                   - ������������ ���� ������, ���������������� ������� 
                                                   ����������������� ��������.
                                                   - ����������� ���������
                                                   - ����������� ���� ������, ���������������� ������� 
                                                   ����������������� ��������.
                                                 */
            vSub,                                /**< ���������.
                                                   ��������� ��������� ���������� ���������� ����������� ���������� � ����������� ���������.
                                                   ��������, ��������� �� ���������-���������� � ����� InterpretationItem_ARM_t::level �������
                                                   ��� � ���������, ���������� � ���.
                                                   �������� � ��������� ���� BIT_1 ������ � ��������� "��������� �����", � BIT_2 - ���.
                                                   \code
                                                     {1,"��������� �����" ,0               ,0      ,0      ,0      ,0                 ,vSub   }, 
                                                     {2,"BIT_1"   ,(void*)&stateInfo.flags ,1      ,0      ,0      ,0                 ,vFlag  },
                                                     {1,"BIT_2"   ,(void*)&stateInfo.flags ,2      ,0      ,0      ,0                 ,vFlag  },
                                                   \endcode
                                                 */
            vString,                             /**< ������ �� 255 ��������. 
                                                    - ����� ������ - InterpretationItem_ARM_t::mask
                                                 */
            vHString,                            /**< ������� ������ �� 255 �������� (��������������� "*").
                                                    - ����� ������ - InterpretationItem_ARM_t::mask
                                                 */
            vText,                               ///< ������������� ����� (�� ������������)
            vFlag8,                              /**< 8-������ ������ ������.
                                                   ��������� ��� ���������/�������������� ����� ������������ ������ InterpretationItem_ARM_t::mask.
                                                 */
            vFlag16,                             /**< 16-������ ������ ������.
                                                   ��������� ��� ���������/�������������� ����� ������������ ������ InterpretationItem_ARM_t::imin.
                                                   \warning InterpretationItem_ARM_t::mask �� ������������ � ���� ��� ������������� �����������.
                                                 */
            mUnit,                               ///< ������� ��������� (�� ������������)
            vSettingsProc,                       ///< ��������� ��������� ��������� �������� (�� ������������)
            vDropDown,                           /**< ���������� ������.
                                                   ���������� ������ ����������� ���������� ���������� ���� vList � ����� 
                                                   InterpretationItem_ARM_t::level ������� ��� � ������ vDropDown.
                                                   ����� �������� �������������� ����� ���������� ����� �� ��������� � 
                                                   InterpretationItem_ARM_t::target ��������, ��������� ����� InterpretationItem_ARM_t::mask
                                                   � ������ ���������� �������� \ref vList �� ��������� InterpretationItem_ARM_t::mask 
                                                   ������ �����������.
                                                   ��������:
                                                   \code
                                                     {2,"���������/������"      ,(void*)&apb.ConDevStatus.stage             ,0xFF,0,0,0,vDropDown},\
                                                     {3,"��������� �����������" ,(void*)&apb.ConDevStatus.stage             ,   0,0,0,0,vList},\
                                                     {3,"�������������"         ,(void*)&apb.ConDevStatus.stage             ,   1,0,0,0,vList},\
                                                     {3,"���������"             ,(void*)&apb.ConDevStatus.stage             ,   2,0,0,0,vList},\
                                                   \endcode
                                                 */
            vDivider,                            /**< �����������.
                                                   ������������ ��� ������ �����������, �� ����� ������ ���������
                                                 */
            vSerial,                             ///< �������� ����� (�� ������������)
            vSystemProc,                         /**<  ������������, ����������� ��� ������� � ����������������� ��������.
                                                   - ������������ ���� ������, ���������������� ������� ����������������� ��������.
                                                   - ����������� ���������.
                                                   - ������������ ������������ ������� ������ � ������ �������������.
                                                 */
            vVersion,                            ///< ������ � ������� VersionData.
            vButton,                             /**< ������-����. ������������� ���� � 1 ���� ������ � � 0 - ������.
                                                   � ��������� ���������� \ref vFlag.*/
            vTroubleCode,                        ///< ��� ������ (�� ������������).
            vTable,                              /**< �������.
                                                   ������� ����������� ���������� ���������� ��������� ����� � ����� 
                                                   InterpretationItem_ARM_t::level ������� ��� � ������ vTable.
                                                   - ��������� �� ��������-��������� ������ - InterpretationItem_ARM_t::target;
                                                   - ������ �������� ������ ������� - InterpretationItem_ARM_t::mask;
                                                   - �������� ������ ��������� �����-������ ������ ������ 
                                                     (32-��� �����) - InterpretationItem_ARM_t::imin;
                                                   - �������� ������ ��������� �����-������ ��������� ������ +1 
                                                     (32-��� �����) - InterpretationItem_ARM_t::imax;
                                                   
                                                   \note �� ������ ������ ������� ����� �������� � ���� ������������ ������,
                                                   �����, ����� � ��������� �� ���������� ���������.
                                                 */
            vUint24,                             ///< 24-������ ����� ��� �����.\n�������� ����� ����� �� ��� ��� \ref vUint8.
            vAdjustSwProc,                       /**< ���������� ������������ � ���������� (32-��� �����).
                                                   - �������� �������� ��������� InterpretationItem_ARM_t::imax
                                                   � ��������� InterpretationItem_ARM_t::target ������ ����� ������
                                                   - ������������ ���� ������, ���������������� ������� ����������������� ��������.
                                                   - ����������� ���������, ������������� ������� ������ � InterpretationItem_ARM_t::imin.
                                                 */
            vTroubleTable,                       ///< ������� ������ �������.
            vDTCTable,                           ///< ������� ������ J1939.
            NONE,
            vDouble,                             /** ����� � ��������� ������� 64���.
                                                   - ������� - InterpretationItem_ARM_t::imin / \f$10^{InterpretationItem::mask}\f$
                                                   - �������� - InterpretationItem_ARM_t::imax / \f$10^{InterpretationItem::mask}\f$
                                                   - ��-��������� - InterpretationItem_ARM_t::defaultVal
                                                   - ���������� ������ ����� "," - InterpretationItem_ARM_t::mask. �������� ����������
                                                     �� 10 � ����� ������� ������ �������, �������� � ��-���������
                                                 */
            tMessageCode,                       ///< ������� ������� - ������ �� ��� ���������.
            vTableStartCounter,
            vTableEndCounter,
            vRecExtConnect=120                  ///< �������������� ���������� ��� ����������� ��������. 
                                                ///����� ������� ������ ��������� ��������������� �� �����������.
};
/////////////////////////////////////////////////////////////////////////////////////////////
/**
\name ��������� ������ ���� ����������������� �������� (InterpretationItemType_t)
\ingroup DIT
@{
*/
const unsigned long vpREADONLY             =0x80000000;///< �������� ������� ��� "������ ��� ������";
const unsigned long vpHEX                  =0x40000000;///< ������ ��������� ����� ����������� ��� �����������������;
const unsigned long vpBIN                  =0x20000000;///< ������ ��������� ����� ����������� ��� ��������;
const unsigned long vpOCT                  =0x10000000;///< ������ ��������� ����� ����������� ��� ������������;
const unsigned long vpLeftJustified        =0x08000000;///< ��� \ref vFlag16 � \ref vFlag16 ������ ���� ����� ����� �������;
const unsigned long vpStartOne             =0x04000000;///< ��� \ref vFlag16 � \ref vFlag16 ������ ���� ����� � 1;
const unsigned long vpGauged               =0x02000000;///< ��� ������������ ������� ���������� ���������� ��������;
const unsigned long vpImdChange            =0x01000000;/**< ��� ���������� �������, ����������� �������� ����������� 
                                                         �������� � ����������. ��������� ��������� ��������� �������� � 
                                                         �������� �������� �������.
                                                       */
const unsigned long vpHidden               =0x00100000;///< ��� ��������� ������, �� ������� ������������;
const unsigned long thIsHumanized          =0x00080000;///< ��������� ��� ������� ��� ����������� � ��������������� ����.
const unsigned long vpDominant             =0x00040000;///< ��������� ��� ������� �����������
const unsigned long vpDominantDiag         =0x00020000;///< ��������� ��� ��������������� ��� ������������ ��������
const unsigned long spFolded               =0x40000000;///< ���� ��� ���� vSub. ��������� ��� ������� ������ ���� �������� ���������.
/**
@}
\name ��������� ������ ������������� ����������������� ��������
\ingroup DIT
@{            
*/
const unsigned long thHumanize             =0x00200000;///< ��������� ��� ������� ������ ���� ������������� � ��������������� ����.
const unsigned long thIconizeName          =0x00400000;///< ��������� ��� ����� ������������ �����������.
const unsigned long thLangLink             =0x00800000;///< ��������� ��� ������� �������� � �������� �������.
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

/**������� ������� ������������� ��� �������������.
����������� ���������� ����� ������ � ��� ��� ��������� ���������� ��������� 
��������  �����.
\ingroup DIT
*/
struct __attribute__ ((packed)) InterpretationItem_ARM_t{
  unsigned char                 level;                 ///< ������� �������� � �������� �������.
/**< 
  - ���� [0..2] - ����� ������ � �������� �������.
  - ���� [3..7] - ����� ������ ������� ������������ ��� ������� � ��������.
  ������ ����������� �� 4 �����:
        ("A") - ��������������� ������. �������� ������ ��� ��������� ������������.
  ��� 3 ("T") - ������ � �������� � ������ ��������������� ��� �������� ����������������� �������� (������������) ������������ � �������
  ��� 4 ("U") - ������ � �������� � ������ ��������������� ��� ������� �������� (������������) ������������
  ��� 5 ("S") - ������ � �������� � ������ ��� ������������� ��������� ���������� �� ������� ������������
  ��� 6 ("D") - ������ � �������� � ������ ��������������� ��� ��������, ��������� ���������  ����������/�������
  ��� 7 ("V") - ������ � �������� � ������ ��������������� ��� ��������� ������ ����������
*/
  char                          name[32];              ///< ��� ��������
  void                          *target;               ///< ��������� �� ������� ����� ������
  unsigned char                 mask;                  ///< �����
  union __attribute__ ((packed)){
    signed long                 imin;                  ///< ����������� ��������
    signed long                 mask;                  
    float                       fmin;                  
  }rmin;                                               
  union __attribute__ ((packed)){
    signed long                 imax;                  ///< ������������ ��������
    float                       fmax;                  
  }rmax;                                               
  unsigned long                 defaultVal;            ///< �������� �� ���������
  unsigned long                 type;                  ///< ��� �������� @ref InterpretationItemType_t � ��������������
  unsigned char                 reserv1;               //
  unsigned char                 reserv2;               //
  unsigned char                 reserv3;               //
};                                                     //
                                                       //
class ProtocolController;
/**������� ������� ��������.
��������� ID ��������� � ���������� �� ���������� ������� void (*)(void)
*/
struct __attribute__ ((packed)) ProcedureListItem_ARM_t{               //
  void *  PID;                                         ///< ID ���������
  void (*procAddress)(ProtocolController *);           ///< ��������� �� �������
};                                                     //
                                                       //
/**������� ������� ������
��������� ID ������ � ���������� �������� �������������, ������ ������ � 
�������, ������ ��� �������.

���� DataRegistryItem_ARM_t::readAdr � DataRegistryItem_ARM_t::writeAdr ��������� 
��������� ����� ������ ��� ������ � ������ ��� ��������� ������ (DataRegistryItem_ARM_t::writeAdr=0).
\ingroup DRI
*/
enum dataUpdatedWith{duwRead,duwWrite};                ///<
typedef void (*dataUpdatedNotifyProc)(void * sender, dataUpdatedWith duw, unsigned char TID);

struct __attribute__ ((packed)) DataRegistryItem_ARM_t{
  unsigned char  TID;                                  ///< ������������� ������
  unsigned char  name[20];                             ///< ������������ ��� ������� � ����� ������
  void          *tableAddr;                            ///< ��������� �� ������� �������������
  unsigned short tableSize;                            ///< ������ ������� �������������
  void          *readAddr;                             ///< ��������� �� ���� ������ ��� ������
  unsigned short dataSize;                             ///< ������ ����� ������
  void          *writeAddr;                            ///< ��������� �� ���� ������ ��� ������
  unsigned short writeBufferSize;                      ///< ������ ��������� ������� ��� ������ ������
  unsigned short flags;                                ///< ����� ������� �������������
  dataUpdatedNotifyProc updateNotify;                  ///< ��������� �� ������� ����������� �� ���������
  void           *userPtr;
};                                                     

/**������������ ������� ������� ������.
������ ��� ����������������� ������ \ref DataRegistryItem_RM_t �� ��������� MIO. ��� ��������
������� ������ ���������������� � ������������ ��������� � ������ ����� ����������
�� ��������� MIO
\ingroup DRI
*/
struct __attribute__ ((packed)) DataRegistryItem_RM_t{
  unsigned char  TID;                                  ///< ������������� ������
  unsigned char  name[20];                             ///< ������������ ��� ������� � ����� ������
  unsigned short _reserv1;                             ///< =0.
  unsigned short tableSize;                            ///< ������ ������� �������������
  unsigned short _reserv2;                             ///< =0.
  unsigned short _reserv3;                             ///< =0.
  unsigned short dataSize;                             ///< ������ ����� ������
  unsigned char  flags;                                ///< ����� ������� �������������
};                                                     //
                                                       //
/**������������ ������� ������� �������������.
������ ��� ����������������� ������ \ref InterpretationItem_ARM_t �� ��������� MIO. ��� ��������
������ ������������� ������ ���������������� � ������������ ��������� � ������ ����� ����������
�� ��������� MIO
����������� ���������� ����� ������ � ��� ��� ��������� ���������� ��������� 
��������  �����.
\ingroup DIT
*/
struct __attribute__ ((packed)) InterpretationItem_RM_t{               //
  unsigned char    level;                              ///< ������� �������� � �������� �������
/**< 
  - ���� [0..3] - ����� ������ � �������� �������.
  - ���� [4..7] - ����� ������ ������� ������������ ��� ������� � ��������.
  - ���� ���� 4..7 = 1, �.�. ���� >0xF0, ������������ ��� ���� ����������� ������. ����� ������ ������ ��������� ��������������� �� �����������.

  ��������:
  - 255 - ������ ���������� ���������� � ���������� �����������.
*/
  char             name[32];                           ///< ��� ��������
  unsigned short   target;                             ///< �������� �������� �� ������ ����� ������
  unsigned short   hintCode;                           ///< ������ ���������
  unsigned char    mask;                               ///< �����
  signed long      imin;                               ///< ����������� ��������
  signed long      imax;                               ///< ������������ ��������
  unsigned long    defaultVal;                         ///< �������� �� ���������
  unsigned long    type;                               ///< ��� �������� @ref InterpretationItemType_t � ��������������
};                                               
                     
/**������� ������������ �������������� ������������-��������� \ref DataRegistryItem_ARM_t � ������������
\ref DataRegistryItem_RM_t.
\param[out] nmi - ������������ \ref InterpretationItem_RM_t
\param[in] targetOffs - ����� ��������� ������ ����������� � ������� �������������
\param[in] mi - ������������-��������� \ref InterpretationItem_ARM_t
\ingroup DIT
*/
extern void toInterpretationItem        (InterpretationItem_RM_t *nmi,unsigned long targetOffs,InterpretationItem_ARM_t *mi);

/**������� ������������ �������������� ������������-��������� \ref DataRegistryItem_ARM_t � ������������
\ref DataRegistryItem_RM_t.
\param[out] ctr - ������������ \ref DataRegistryItem_RM_t
\param[in] tr - ������������-��������� \ref DataRegistryItem_ARM_t
\ingroup DRI
*/
extern void toDataRegistryItem          (DataRegistryItem_RM_t *ctr, DataRegistryItem_ARM_t *tr);


#endif

