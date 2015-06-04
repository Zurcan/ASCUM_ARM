#ifndef __CMDIDS
#define __CMDIDS

#define CID__STORE_USB                             0xBDE8
#define CID__STORE_USB_BREAK                       0xC5EE
#define CID__SET_DATETIME                          0x8B4C
#define CID__RESETBLOCKSTAT                        0x7C96
#define CID__SELECTBLOCK                           0x156D
#define CID__DIAGDATA_EN                           0x56FE
#define CID__DIAGDATA_DIS                          0x0002
#define CID__ALL_CANCEL                            0x9C03
#define CID__CONNECT_NEW_REMOTE                    0x4510
#define CID__DISCONNECT_REMOTES                    0xFC45

/*
#define CID__CLUTCH_OFF             0x0001
#define CID__CLUTCH_ON              0x0002
#define CID__ZHALUSI_ON             0x0003
#define CID__ZHALUSI_OFF            0x0004  
#define CID__SET50HZ                0x0005
#define CID__CLUTCH_SWITCH          0x000A
#define CID__ZHALUSI_SWITCH         0x000B

                                    
#define CID__MODE_MANEVR            0x0010
#define CID__MODE_POEZDN            0x0011
#define CID__MODE_STOP              0x0012
     
//     {MPT6}
#define CID__TURN_1ST               0x0013
#define CID__TURN_2ND               0x0014
#define CID__TURN_3RD               0x0015
#define CID__TURN_NEUTRAL           0x0016
#define CID__AUTOCONTROL            0x0017
#define CID__MANUALCONTROL          0x0018
#define CID__TURN_4TH               0x0019
#define CID__TURN_5TH               0x001A
#define CID__TURN_REV               0x001B
#define CID__TURN_D                 0x001C
//     {Glob}                                 
#define CID__DIR_NEUTHRAL           0x001F
#define CID__DIR_FORWARD            0x0020
#define CID__DIR_BACKWARD           0x0021
#define CID__GENERATOR_ON           0x0022
#define CID__GENERATOR_OFF          0x0023
#define CID__HYDRAPUMP_ON           0x0024
#define CID__HYDRAPUMP_OFF          0x0025
      
//     {MPT6}
#define CID__SLOWPUMP_ON            0x0026
#define CID__SLOWPUMP_OFF           0x0027

#define CID__SLOWDRIVE_ON           0x0028
#define CID__SLOWDRIVE_OFF          0x0029
#define CID__SLOWDRIVE_WHYNOT       0x002F

#define CID__ALLTOOLOFF             0x002A
#define CID__HYDRAPUMP_SWITCH       0x002B
#define CID__SLOWDRIVE_SWITCH       0x002C
#define CID__SLOWPUMP_SWITCH        0x002D
#define CID__GENERATOR_SWITCH       0x002E

#define CID__SOFTCRANE_SWITCH       0x0050
//     {Glob}                                 

#define CID__SET_OSN_PULT_LIGHT     0x0030
#define CID__SET_ADD_PULT_LIGHT     0x0031
#define CID__SET_OSN_INDIC_LIGHT    0x0032
#define CID__SET_ADD_INDIC_LIGHT    0x0033

#define CID__INCREASE_PULT_LIGHT    0x0034
#define CID__DECREASE_PULT_LIGHT    0x0035
#define CID__INCREASE_INDIC_LIGHT   0x0036
#define CID__DECREASE_INDIC_LIGHT   0x0037

#define CID__WORK_MODE              0x0038
#define CID__TRANSPORT_MODE         0x0039
#define CID__WORK_MODE_SWITCH       0x003A
#define CID__DEBLOCK_TALJ           0x0040
#define CID__DEBLOCK_CRANE_UP       0x0041
#define CID__CRANE_REMOTE_SWITCH    0x0042
#define CID__PLATE_REMOTE_SWITCH    0x0043
                                    
#define CID__SYNCRONIZE__CLOCK      0x0100
#define CID__SYNCRONIZE__PWD1       0x0101
#define CID__SYNCRONIZE__PWD2       0x0102
#define CID__SYNCRONIZE__PWD3       0x0103
#define CID__SYNCRONIZE__LOCALS     0x0104
#define CID__SYNCRONIZE__DATA       0x0110

#define CID__SWITCH_SLOW_JOY_CTRL   0x0120
#define CID__SWITCH_DIESEL_JOY_CTRL 0x0121
#define CID__SWITCH_SLOW_REMOTE     0x0122

#define CID__OPT_OTHERCRANE_SWITCH  0x0150
#define CID__OPT_OTHERPLATE_SWITCH  0x0151
#define CID__OPT_RESSORS_ON         0x0152
#define CID__OPT_RESSORS_OFF        0x0153
#define CID__OPT_PANTOGRAF_SWITCH   0x0154
#define CID__OPT_HIAB_SWITCH        0x0155
#define CID__OPT_HIAB_BUR_SWITCH    0x0156
#define CID__OPT_UBM_BUR_ON         0x0157
#define CID__OPT_UBM_BUR_OFF        0x0158
#define CID__OPT_UBM_BUR_SWITCH     0x0159
#define CID__OPT_MIRROR_HEAT        0x0160
#define CID__OPT_RESSORS_SWITCH     0x0161
#define CID__OPT_ZHALUSI_OPEN       0x0162
#define CID__OPT_ZHALUSI_CLOSE      0x0163
#define CID__OPT_ZASLONKA_OPEN      0x0164
#define CID__OPT_ZASLONKA_CLOSE     0x0165
#define CID__OPT_SIFA_SWITCH        0x0166
#define CID__SM__PLATE_SW		        0x0167
#define CID__PWR_SHAFT_ON           0x0168
#define CID__PWR_SHAFT_OFF          0x0169
#define CID__PWR_SHAFT_SWITCH       0x016A
#define CID__ENGINE2_WORK_SWITCH    0x016B
#define CID__ENGINE_SPEED_IDLE      0x016C
#define CID__ENGINE2_WORK_ON        0x016D
#define CID__ENGINE2_WORK_OFF       0x016E


#define CID__GYDRARASPRED_ON        0x0200
#define CID__GYDRARASPRED_OFF       0x0201
#define CID__INT_HIAB_SWITCH        0x0202
#define CID__HYDRARASWITCH_SWITCH   0x0203
#define CID__KMU_ON                 0x0204
#define CID__KMU_OFF                0x0205
#define CID__KMU_SWITCH             0x0206
#define CID__COMPRESSOR_ON          0x0208
#define CID__COMPRESSOR_OFF         0x0209
#define CID__COMPRESSOR_SWITCH      0x020A

#define CIDH__REV_BLOCK_CYL_ON      0xA210
#define CIDH__REV_CYL_FORWARD       0xA211 
#define CIDH__REV_CYL_BACKWARD      0xA212
#define CIDH__REV_CYL_NEUTRAL       0xA213
#define CIDH__REV_BLOCK_CYL_OFF     0xA214
#define CIDH__SM_BLOCK_CYL_ON       0xA215
#define CIDH__SM_BLOCK_CYL_OFF      0xA216
#define CIDH__SM_MOTOR_ON           0xA217
#define CIDH__SM_MOTOR_OFF          0xA218
#define CIDH__SM_SET_NEUTHRAL       0xA219
#define CIDH__SM_FIND_NEUTHRAL      0xA21A
#define CIDH__SM_SET_OPT_KMU        0xA220
#define CIDH__ENGINE_SPEED_IDLE     0xA221
#define CIDH__STRT_SERVICE_ROTATION 0xA238
#define CIDH__STOP_SERVICE_ROTATION 0xA239
#define CIDH__BRAKE_ON              0xA23A
#define CIDH__BRAKE_OFF             0xA23B

#define CID__SM__INCREASE_SPEED     0x0301
#define CID__SM__DECREASE_SPEED     0x0302
#define CID__SM__BRAKE              0x0303

#define CID__UNLOCK_MOVEMENT        0x0400

#define CID__SNOW_ROTOR_SW          0x0401
#define CID__SNOW_TRANSPORTER_SW    0x0402

#define CID__DIAGDATA_EN            0x2010
#define CID__DIAGDATA_DIS           0x2011
#define CID__SELECTBLOCK            0x2012
#define CID__RESETBLOCKSTAT         0x2013
#define CID__SET_DATETIME           0x2020
#define CID__STORE_USB              0x2021
#define CID__STORE_USB_BREAK        0x2022

#define CID__CONNECT_NEW_REMOTE     0xE001
#define CID__DISCONNECT_REMOTES     0xE002

#define CID__TEST1                  0x2000
#define CID__TEST2                  0x2001
#define CID__TEST3                  0x2002
#define CID__TEST4                  0x2003
#define CID__TEST5                  0x2004
#define CID__TEST6                  0x2005
#define CID__ALL_CANCEL             0xFEF0
#define CID__NONE                   0xFEE0
*/
#endif
