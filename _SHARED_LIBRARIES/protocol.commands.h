#ifndef __DEVCMDS_
#define __DEVCMDS_

//=========================================================================
//�������� ��������� ������ MIObyDIZ
//=========================================================================
//
//  1. ��������
//
// �������� ������ MIObyDIZ �������� �������� ���������� � ��������� �����������
// �������. ��������� ����� ������ �������� ����� ����� 3.5 ����.
//
// ����� ������ ������ ������� �/��� ������:
// addr func [dataID|procID|subfunc][PN][datacounter data...] CRC16L CRC16H
//
// 1���� addr - 0    - 63 - ������ ��������� �����
//        64-          ����������������� ������ ������ ��������� (������ �������)
//        65-127     - ���������������
//        128+addr   - ������ ��������� � ��������� ��������� �����
// 1���� dataID|procID|subfunc - ������������� ������/�������� ��� ����������
// 1���� PN          -      ����� �������� �������. ������ �������� - 128 ����
// 1���� datacounter - ����� ����� ������������ ������
// datacounter ���� data... - ���� ������
// 1���� CRC16L      - ������� ����� CRC ������
// 1���� CRC16H      - ������� ����� CRC ������
// 
// ��� ������ � ��������������� _ID_FLASH ����� ���� PN ������������� �� 2� ����
//=========================================================================
//�������� ������� � ���������� ��������� ������
//=========================================================================
// �������� ������ � ���������������� ������
#define         CMD_READ_DATA               0x03    /* ������ ������ �� ����������              */
    //Q:ADR CMD ID pageNum CRC_16bit
    //A:ADR CMD ID pageNum rdlen databuffer CRC_16bit
    struct __attribute__ ((packed)) CMD_READ_DATA_t{
      char ADR,CMD,ID;
      char pageNum;
    };
#define         CMD_WRITE_DATA              0x10    /* ������ ������ � ����������               */
    //Q:ADR CMD ID pageNum wrLen databuffer CRC_16bit
    //A:ADR CMD ID pageNum CRC_16bit

#define         CMD_QUERY_SIZE              0x05    /* ������ ������� ������ � ��������� �� 128�*/
    //Q:ADR CMD ID CRC_16bit
    //A:ADR CMD ID dataSize_16bit CRC_16bit
   
#define         CMD_QUERY_DATA_CRC32_HASH   0x09    /* ������ �������� CRC32 ������, ��� ������-*/
                                                    /* ����� ������������� ����������           */
#define         CMD_QUERY_TAB_SIZE          0x07    /* ������ ������� ������ � ��������� �� 128�*/
    //Q:ADR CMD ID CRC_16bit
    //A:ADR CMD ID dataSize_16bit CRC_16bit
                                                    /* ���������� ���������� �� ������ �����-   */
                                                    /* ����� ��������                           */
    #define         _ID_RESULT                  0x01    /* ��������� / �� ����������            */
    #define         _ID_CONTROL                 0x02    /* ���������� �����������               */
    #define         _ID_DIAG                    0x08    /* ��������������� ����������           */
    #define         _ID_SIGNATURE               0x11    /* ��������� ����������                 */
	  #define         _ID_GREETING                0x12
    #define         _ID_SIGNALS_IN_BLOCKS       0x1E    /* ��������� ����������                 */
    #define         _ID_SIGNALS                 0x1F    /* ��������� ����������                 */
    #define         _ID_SETUP                   0x20    /* ��������� ����������                 */
    #define         _ID_CONSTANTS               0x21    /* ������������� ������ ����������      */
    #define         _ID_ADDITIONAL              0x22    /* ���. ������ ����������. ����������   */
    #define         _ID_ADDITIONAL2             0x23    /* ���. ������ ����������. ����������   */
    #define         _ID_ADDITIONAL3             0x24    /* ���. ������ ����������. ����������   */
    #define         _ID_ADDITIONAL4             0x25    /* ���. ������ ����������. ����������   */
    #define         _ID_ADDITIONAL5             0x26    /* ���. ������ ����������. ����������   */
    #define         _ID_ADDITIONAL_STATUS       0x27    /* ������ ���������� ����� �������      */
    #define         _ID_CONFIG                  0x28    /*                                      */
    #define         _ID_SYNCHRONIZATION         0x29    /* ������ ������������� �����.����������*/
    #define         _ID_DEBUG                   0x2A
    #define         _ID_USBDEVDATA              0x2B
    #define         _ID_RF_COM_STATISTIC        0x30    /*                                      */
	  #define         _ID_GLB_CONNECTIONS_STATUS  0x31 
    #define         _ID_MESSAGE_CODE            0x32
    #define         _ID_ENGINE_DIAG_DATA        0x33
    #define         _ID_STAT                    0x34
    #define         _ID_MESSAGES_ARC            0x35
    #define         _ID_TEXT_MESSAGE_LIBRARY    0x60
    #define         _ID_DIAG_INTERPRETATION     0x61
    #define         _ID_TROUBLES                0x62    /* ��������������� ����������           */
    #define         _ID_TRB_ADD1                0x63
    #define         _ID_TROUBLES_ARCH           0x64    /* ��������������� ����������           */
    #define         _ID_TRB_ADD2                0x65
    #define         _ID_TRB_ADD3                0x66
    #define         _ID_LOG_CONFIG              0x70
    #define         _ID_LOG_SEGMENT_ID          0x71
    #define         _ID_LOG_DATA                0x72
        //==[Bootloader identifiers]===============================================
    #define         _ID_FLASH                   0x91    /* ���� ������                          */
    #define         _ID_EEPROM                  0x92    /* ������ ������                        */
    #define         _ID_PROG_INFO               0x93    /* ���������� � ����������� ���������   */
    #define         _ID_FLASH_LBA               0x98
    //=========================================================================
    //#define         _SID_SYSTEM_COMMAND         0xF0
    #define         _SID_CONTROL_COMMAND        0xF1
    #define         _SID_ACCESS_CODE            0xF2
    #define         _SID_ACCESS_MODE            0xF3
    #define         _SID_HW_COMPARTIBLE_CHECK   0xF4
    #define         _SID_FW_COMPARTIBLE_CHECK   0xF5
    #define         _SID_ENTER_BOOTLOAD         0xF6
    #define         _SID_INCOMPARTIBLE          0xF7
    
    #define         _SID_CONSOLE_MAIN           0xFA

#define         CMD_READ_TABLES             0x06    /* ������       			        */
    #define		_ID_SYS_TABLE           0x81    /* ������ ��������� �������             */
    //Q:ADR CMD ID PN CRC_16bit
    //A:ADR CMD ID PN dataSize datablock CRC_16bit
    #define		_ID_INTERPTABLE         0x82    /* ������ ����������������� �������     */
    //Q:ADR CMD 82 ID PN CRC_16bit
    //A:ADR CMD 82 ID PN dataSize dataBlock CRC_16bit

// ������ � ���������������� �������
#define         CMD_CONTROL                 0x0A    /* ������ �������� ����������       */
    //Q:ADR CMD PID CRC_16bit
    //A:ADR CMD PID CRC_16bit
    #define         _CC_SAVE_SETUP             (void*)0x20    /* ��������� ���������              */
    #define         _CC_LOAD_DEFAULT_SETUP     (void*)0x21    /* ��������� ���������              */
    #define         _CC_SETNAME                (void*)0x22
    #define         _CC_SETADDRESS             (void*)0x23
    #define         _CC_LOAD_SETUP             (void*)0x24
    #define         _CC_VISUAL_DEFINITION      (void*)0x30    /* ��������� ���������              */
    #define         _CC_CHECK_INDICATION       (void*)0x31    /* ��������� ���������              */
    #define         _CC_CHECK_OUTS             (void*)0x32
    #define         _CC_CHECK_OUTS2            (void*)0x33
    #define         _CC_SET_DIAG_MODE          (void*)0x3F
    #define         _CC_SET_CONTROL            (void*)0x40
    #define         _CC_CALIBRATE              (void*)0x41
    #define         _CC_SET_NORM_MODE          (void*)0x42
    #define         _CC_SET_SERIAL             (void*)0x43
    #define         _CC_SET_TECH_SERIAL        (void*)0x44
    #define         _CC_SYNCH_PDU              (void*)0x46
    #define         _CC_SET_RCS_ID             (void*)0x47
    #define         _CC_RESET_RF_COM_STATISTIC (void*)0x50
    #define         _CC_RESET_CONNECTED_RFS    (void*)0x51
    #define         _CC_SET_STAT               (void*)0x52
    #define         _CC_RESET_STAT             (void*)0x53
    #define         _CC_ResetMessageLog        (void*)0x54
    #define         _CC_SAVE_CONFIG            (void*)0x55    /* ��������� ������������ ������������ */
    #define         _CC_LOAD_DEFAULT_CONFIG    (void*)0x56    /* ��������� ������������ ������������ ��-���������*/
    #define         _CC_LOAD_CONFIG            (void*)0x57    /* ��������� ������������ ������������ */
    
    #define         _CC_ANG_SET_1              (void*)0xC0
    #define         _CC_ANG_SET_2              (void*)0xC1
    #define         _CC_ANG_SET_3              (void*)0xC2
    #define         _CC_SignalImitationOnCMD   (void*)0xC8
    #define         _CC_SignalImitationOffCMD  (void*)0xC9
    #define         _CC_LEAVE_COMP_MODE        (void*)0xD0
    #define         _CC_SET_COMP_MODE1         (void*)0xD1
   
    #define         _CC_RESET_CMD_SYSTEM       (void*)0xE0
    #define         _CC_UpdateSignalSwitches   (void*)0xF0
    #define         _CC_ExecuteCMD             (void*)0xF1
    #define         _CC_SetClockCMD            (void*)0xF2
    #define         _CC_RestoreClockCMD        (void*)0xF3
    #define         _CC_CancelSignalSwitches   (void*)0xF4
    #define         _CC_ResetErrorLog          (void*)0xFA

    #define         _CC_DEBUG1                 (void*)0x60
    #define         _CC_DEBUG2                 (void*)0x61
    #define         _CC_DEBUG3                 (void*)0x62
    #define         _CC_DEBUG4                 (void*)0x63
    #define         _CC_DEBUG5                 (void*)0x64
    #define         _CC_DEBUG6                 (void*)0x65
   


#define         CMD_ASK_SYS_FUNC            0x0D        /* ���������� ��������� �������        */
    //Q:ADR CMD SF CRC_16bit
    //A:ADR CMD SF CRC_16bit
    #define         _SFSF_PROG_STATUS       0x94        /* -���������� � ����������� ��������� */
    #define         _SFSF_ENTERBLOAD        0x95        /* -����� � Bootloader                 */
    #define         _SFSF_COMPATIBLE_CHECK  0x96        /* -��������� �������������            */
    #define         _SFSF_ERASE_FLASH       0x97        /* -�������� FLASH                     */
    #define         _SFSF_RESET             0x98        /* -�������� ����������                */
    #define         _SFSF_DISCONNECT        0x99        /* -������� � ��������� �����          */
    #define         _SFSF_GATEWAY_ON        0x9A        /* -�������� ����� �����               */
    #define         _SFSF_CONNECT           0x9B        /* -�������� ��������� �����           */
    #define         _SFSF_FW_COMPATIBLE_CHECK    0x9C   /* -��������� �������������            */
    #define         _SFSF_INCOMPATIBLE_STATEMENT 0x9D   /* -��������� �������������            */
    #define         _SFSF_COMPATIBLE_CHECK_BLK   0x9E   /* -��������� �������������            */
    #define         _SFSF_READ_DATA         0xA0
    #define         _SFSF_WRITE_DATA        0xA1
    #define         _SFSF_BTLDR_CMD         0xB0
    #define         _SFSF_ACCESS_CODE       0xB2        /* -������ �� ���� ������� � ������    */
    #define         _SFSF_ACCESS_MODE       0xB3        /* -������ �� ��������� ������ ������� */
    #define         _SFSF_SIMULATE_MODE     0xB4
                                                        /***************************************/
#define         CMD_SIGNATURE               0x11        /* ������ ��������� ���������� (IDREC) */
    //Q:ADR CMD CRC_16bit
    //A:ADR CMD dataSize dataBlcok CRC_16bit
#define         CMD_GREETING                0x12        /* Invitation to connect.Master info   */
                                                        /***************************************/

//SELF SYNCHRONIZING CMDS
//
#define         CMD_MAIN_CONSOLE_IO_WR      0x24        /* �������� �������                      */
    //Q:ADR CMD pklen_16bit writelen_16bit datablock CRC_16bit
    //A:ADR CMD pklen_16bit CRC_16bit
    struct __attribute__ ((packed)) CMD_MAIN_CONSOLE_IO_WR_t{
      char ADR,CMD;
      unsigned short pklen_16bit,writelen_16bit;
    };
#define         CMD_MAIN_CONSOLE_IO_RD      0x25        /* �������� �������                      */
    //Q:ADR CMD pklen_16bit POS_32bit CRC_16bit
    //A:ADR CMD pklen_16bit readLen_16bit consoleBuffer_t CRC_16bit
    struct __attribute__ ((packed)) CMD_MAIN_CONSOLE_IO_RD_t{
      char ADR,CMD;
      unsigned short pklen_16bit;
      unsigned long  POS_32bit;
    };
#define         CMD_READ_DATA_LBA           0x23    /* ������ ������ �� ����������              */
    //Q:ADR CMD pklen_16bit ID pageNum_16bit readLen_16bit CRC_16bit
    //A:ADR CMD pklen_16bit ID pageNum_16bit readLen_16bit datablock CRC_CRC_32_Bit CRC_16bit
    struct __attribute__ ((packed)) CMD_READ_DATA_LBA_t{
      char ADR,CMD;
      unsigned short pklen_16bit;
      char ID;
      unsigned short pageNum_16bit,readLen_16bit;
    };
#define         CMD_WRITE_DATA_LBA          0x20    /* ������ ������ � ����������               */
    //Q:ADR CMD pklen_16bit ID pageNum_16bit writeLen_16bit datablock CRC_CRC_32_Bit CRC_16bit
    //A:ADR CMD pklen_16bit ID pageNum_16bit writeLen_16bit CRC_16bit
    struct __attribute__ ((packed)) CMD_WRITE_DATA_LBA_t{
      char ADR,CMD;
      unsigned short pklen_16bit;
      char ID;
      unsigned short pageNum_16bit,writeLen_16bit;
    };
		
#define         CMD_WRITE_BITS_LBA          0x21        /* ������ �� ������ ��������� ������   */
    //Q:ADR CMD pklen_16bit ID offsetBit_16bit lenBit_16bit datablock CRC_16bit
    //A:ADR CMD pklen_16bit ID offsetBit_16bit lenBit_16bit CRC_16bit
    struct __attribute__ ((packed)) CMD_WRITE_BITS_LBA_t{
      char ADR,CMD;
      unsigned short pklen_16bit;
      char ID;
      unsigned short offsetBit_16bit,lenBit_16bit;
    };

#define         CMD_READ_TABLE_LBA          0x26    /* ������       			                      */
    //Q:ADR CMD pklen_16bit ID pageNum_16bit readLen_16bit CRC_16bit
    //A:ADR CMD pklen_16bit ID pageNum_16bit readLen_16bit datablock CRC_CRC_32_Bit CRC_16bit
    //  reads interpretation table with ID. If ID==0 reads main table
    struct __attribute__ ((packed)) CMD_READ_TABLE_LBA_t{
      char ADR,CMD;
      unsigned short pklen_16bit;
      char ID;
      unsigned short pageNum_16bit,readLen_16bit;
    };

#define         CMD_READ_TABLE_HASH         0x27    /* ������       			                      */
#define         CMD_READ_DATA_HASH          0x28    /* ������       			                      */
    //Q:ADR CMD pklen_16bit ID CRC_16bit
    //A:ADR CMD pklen_16bit ID readLen_16bit datablock CRC_CRC_32_Bit CRC_16bit
                                   //\-- note that readLen_16bit=20
    struct __attribute__ ((packed)) CMD_READ_TABLE_HASH_t{
      char ADR,CMD;
      unsigned short pklen_16bit;
      char ID;
    };

    
// �������� SIDA
// sida command components
#define         scccMask                    (3<<6)
#define         sdcc_Read                   (1<<6) // SIDA Command Command
#define         sdcc_Write                  (2<<6)
#define         sdcc_Answer                 (3<<6)
    
#define         sccdMask                   (15<<2)

#define         sdcd_Data                   (0<<2) // SIDA Command data
#define         sdcd_DataHash               (1<<2)
#define         sdcd_DataSize               (2<<2)
#define         sdcd_Interp                 (3<<2)
#define         sdcd_InterpHash             (4<<2)
#define         sdcd_InterpSize             (5<<2)
#define         sdcd_BitSeries              (6<<2)
#define         sdcd_RESERV                 (7<<2)
    
#define         scctMask                    (3<<0)
#define         sdct_None                   (0<<0) // SIDA Command tail
#define         sdct_EmptyDD                (1<<0)
#define         sdct_FullDD                 (2<<0)
#define         sdct_ErrorCode              (3<<0)
    
// SiDa commands
#define         sdcA_ERROR                            (sdcc_Answer | sdct_ErrorCode)
#define         sdcA_OK                               (sdcc_Answer )
                 
#define         sdcQ_READ_DATA                        (sdcc_Read   | sdcd_Data | sdct_EmptyDD)    /* ������ ������ �� ����������              */
#define         sdcA_READ_DATA                        (sdcc_Answer | sdcd_Data | sdct_FullDD)
    //Q:  CMD ID pageNum_16bit readLen_16bit 
    //A: ACMD ID pageNum_16bit readLen_16bit datablock 
    struct __attribute__ ((packed)) SCC_READ_DATA_t{
      char CMD;
      char ID;
      unsigned short pageNum_16bit,readLen_16bit;
    };
#define         sdcQ_QUERY_DATA_SIZE                  (sdcc_Read   | sdcd_DataSize   | sdct_EmptyDD)    /* ������ ������ �� ����������              */
#define         sdcA_QUERY_DATA_SIZE                  (sdcc_Answer | sdcd_DataSize   | sdct_FullDD)
#define         sdcQ_QUERY_INTERP_SIZE                (sdcc_Read   | sdcd_InterpSize | sdct_EmptyDD)    /* ������ ������ �� ����������              */
#define         sdcA_QUERY_INTERP_SIZE                (sdcc_Answer | sdcd_InterpSize | sdct_FullDD)
    //Q:  CMD ID pageNum_16bit readLen_16bit 
    //A: ACMD ID pageNum_16bit readLen_16bit datablock 

#define         sdcQ_WRITE_DATA                       ( sdcc_Write | sdcd_Data  | sdct_FullDD)           /* ������ ������ � ����������               */
//#define         sdcA_WRITE_DATA                       (sdcc_Answer )                         /* ������ ������ � ����������               */
    //Q:  CMD ID pageNum_16bit writeLen_16bit datablock
    //A: ACMD ID pageNum_16bit writeLen_16bit
    struct __attribute__ ((packed)) SCC_WRITE_DATA_t{
      char CMD;
      char ID;
      unsigned short pageNum_16bit,writeLen_16bit;
      char datablock[2048];
    };

#define         sdcQ_READ_TABLE_HASH                  (  sdcc_Read | sdcd_InterpHash | sdct_EmptyDD )    /* ������       			                      */
#define         sdcA_READ_TABLE_HASH                  (sdcc_Answer | sdcd_InterpHash | sdct_FullDD  )    /* ������       			                      */
#define         sdcQ_READ_DATA_HASH                   (  sdcc_Read | sdcd_DataHash   | sdct_EmptyDD )    /* ������       			                      */
#define         sdcA_READ_DATA_HASH                   (sdcc_Answer | sdcd_DataHash   | sdct_FullDD  )    /* ������       			                      */
    //Q:  CMD ID pageNum_16bit readLen_16bit CRC_16bit
    //A: ACMD ID pageNum_16bit readLen_16bit datablock
                                   //\-- note that readLen_16bit=20
    struct __attribute__ ((packed)) SCC_READ_TABLE_HASH_t{
      char CMD;
      char ID;
      unsigned short pageNum_16bit,readLen_16bit;
    };
    
#define         sdcQ_WRITE_BITS                       ( sdcc_Write | sdcd_BitSeries  | sdct_FullDD)    /* ������ ������ � ����������               */
//#define         sdcA_WRITE_BITS                       (sdcc_Answer )    /* ������ ������ � ����������               */
    //Q:  CMD ID offsetBit_16bit lenBit_16bit datablock 
    //A: ACMD ID offsetBit_16bit lenBit_16bit 
    struct __attribute__ ((packed)) SCC_WRITE_BITS_t{
      char CMD;
      char ID;
      unsigned short offsetBit_16bit,lenBit_16bit;
      char datablock[2048];
    };

#define         sdcQ_READ_TABLE                       (  sdcc_Read | sdcd_Interp     | sdct_EmptyDD)   /* ������       			                      */
#define         sdcA_READ_TABLE                       (sdcc_Answer | sdcd_Interp     | sdct_FullDD )   /* ������       			                      */
    //Q:  CMD ID pageNum_16bit readLen_16bit CRC_16bit
    //A: ACMD ID pageNum_16bit readLen_16bit datablock
    //  reads interpretation table with ID. If ID==0 reads main table
    struct __attribute__ ((packed)) SCC_READ_TABLE_t{
      char CMD;
      char ID;
      unsigned short pageNum_16bit,readLen_16bit;
    };

    
    // Control command
    
    // Frame - transport shell for data and commands:   ADR 0x20 pklen_16bit DATABLOCK CRC32_32bit
    struct __attribute__ ((packed)) PC_FRAME_t{
      char ADR,PID;
      unsigned short pklen_16bit;
    };
   

#define         CMD_LIMIT_FOR_LAYERS        0x30        /* ����� �������, ������� � ������� �� ���������� ������� ���� ���������       */
#define         LAYER_SIDA                  0x30    

#define         ADDR_ADDRESS_POLLING        0x40        /* ������ �� �������� ���������        */


//==========================================================================
// �������� ����� ������ ��������� ������ �� RS-485

#define         RSMD_INVALID_CMD                0x01
#define         RSMD_INVALID_CMD_SUBFUNCTION    0x02
#define         RSMD_INVALID_CMD_DATA           0x03

#define         RSMD_UNSUPPORTED_CMD            0x10
#define         RSMD_RESTRICTED_CMD             0x11
#define         RSMD_UNSUPPORTED_ID             0x12
#define         RSMD_READ_ONLY_WRITE            0x13
#define         RSMD_UNSUPPORTED_PROC_ID        0x14
#define         RSMD_RESTRICTED_WRITE           0x15
#define         RSMD_RESTRICTED_READ            0x16
#define         RSMD_PAGE_ADDR_LBA              0x17
#define         RSMD_DOUBLE_FORMAL_ANSWER       0x18

#define         RSMD_PROGRAMM_ERROR             0x20
#define         RSMD_COMPARTIBLITY_ERROR        0x21

#define         RSMD_HARDWARE_ERROR             0x30

//==========================================================================
// ��������� ���������� ������
#define MIO_PAGE_SIZE                   128
#define MIO_PACKET_SPACE                240

#define LBA_PACKET_SPACE                2048
#define SIDA_PACKET_SPACE               2048
#define SIDA_MAX_PACKET_SIZE            SIDA_PACKET_SPACE+32

#endif
