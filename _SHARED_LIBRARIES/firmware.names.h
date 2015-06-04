#ifndef __soft_names
#define __soft_names


//===================================================================
//      СОГЛАШЕНИЕ О ФОРМИРОВАНИИ ИМЕН ПРОГРАММНЫХ ПРОДУКТОВ
//
//   Определения:
//     ПАП - программно-аппаратная платформа.
//     ППО - прикладное программное обеспечение
//     СВИБ - соглашение о внутренней идентификации блоков
//   Имя программы (firmware name) предназначено для однозначной идентификации
// конкретного программного обеспечения. Имя программы совместно с записью о
// версии индицируют устройство назначения с его ревизией и версией ПАП, имя
// ППО как целевую функцию, дату создания, версию, номер регистрации версии (build).
//   Имя программы формально не является сигнатурой устройства (но может быть
// таким же), т.к. несет иную функцию.
//   Основное назначение имени программы - идентификация назначения программы,
// целевого устройства и т.п. Также для устройств допускающих установку нескольких
// пакетов программ таких как монитор служит для разделения программ при инсталляции 
// и деинсталляции пакетов.
//   Имя программы формируется путем объединения ряда признаков программы
// в единое символьное имя.
// DDDDDD_AAAAAAAAAAAAAAAAAAAAAAAAА
// где DDDDDD - сокращенное имя целевого устройства;
//     AAAAA..- дополнительное поле для идентификации функции/назначения конкретной
//              программы;
//   Система идентификации блоков по СВИБ использует поле ААААА.. для идентификации
// совместимости ППО, назначения блока и т.п. Поэтому в соответствии с СВИБ 
// дополнительное поле должно содержать название программы, характеризующее
// ее назначение. При этом для устройств разной ревизии аппаратуры и/или платформы
// сохраняющих совместимость с предыдущей версией/ревизией дополнительное поле 
// должно содержать одно и то же название ППО.
//
// В общем случае имя файла программы формируется автоматически 
// после обработки программой регистрации версий ПО.
//=====================================================================
//                                    DDDDDD_AAAAAAAAAAAAAAAAAAAAAAAAA
//=====================================================================
#define       fwBKS_BootLoad          "BKS____MIO_BOOT_LOADER__________"
#define       fwBKS_TM01              "BKS____APPLICATION_TM01_________"
#define       fwBKS_ADM1_3            "BKS____APPLICATION_ADM1_3_______"
#define       fwBKS_MPT6_7            "BKS____APPLICATION_MPT6_7_______"
#define       fwBKS_NORW              "BKS____APPLICATION_NORWAY_______"
#define       fwBKS_MPT6E_LIBIA       "BKS____APPLICATION_MPT6E_LIBIA__"
#define       fwBKS_MPT6_10           "BKS____APPLICATION_MPT6_10______"
#define       fwBKS_MPT6_10_CR        "BKS____APPLICATION_MPT6_10_CR___"
#define       fwBKS_MPT6_9            "BKS____APPLICATION_MPT6_9_______"
#define       fwBKS_TMe               "BKS____APPLICATION_TMe__________"
#define       fwBKS_TMsr              "BKS____APPLICATION_TMSR_________"
#define       fwBKS_TMsv              "BKS____APPLICATION_TMSV_________"
#define       fwBKS_ADM1_3cmi         "BKS____APPLICATION_ADM1_3cmi____"
#define       fwBKS_TMk               "BKS____APPLICATION_TMK__________"
#define       fwBKS_TMk_woSM          "BKS____APPLICATION_TMK_!SM______"
#define       fwBKS_TMk_woSM_APS      "BKS____APPLICATION_TMK_!SM_APS__"
#define       fwBKS_TMk_woSM_AS_RG    "BKS____APPLICATION_TMK_!SM_AS_RG"
#define       fwBKS_TM                "BKS____APPLICATION_TM___________"
#define       fwBKS_TM230             "BKS____APPLICATION_TM230________"
#define       fwBKS_MPT6L             "BKS____APPLICATION_MPT6L________"
#define       fwBKS_TM270             "BKS____APPLICATION_TM270________"
#define       fwBKS_AGMU              "BKS____APPLICATION_AGMU_________"
#define       fwBKS_SANDBOX           "BKS____SANDBOX__________________"

#define       fwUSBBKS_BootLoad       "USBBKS_SPI_BOOT_LOADER__________"
#define       fwUSBBKS                "USBBKS_APPLICATION______________"

#define       fwBKS_SERVICE_HW_TEST   "BKS____SERVICE_HW_TEST__________"

#define       fwBRK_BootLoad          "BRK____MIO_BOOT_LOADER__________"
#define       fwBRK                   "BRK____APPLICATION______________"

#define       fwTP2_BootLoad          "TP2____MIO_BOOT_LOADER__________"
#define       fwTP2                   "TP2____APPLICATION_LIBIA________"

#define       fwTP2MM_BootLoad        "TP2_250MM_MIO_BOOT_LOADER_______"
#define       fwTP2MM                 "TP2_250MM_APPLICATION___________"

#define       fwBCS_BootLoad          "BCS____MIO_BOOT_LOADER__________"
#define       fwBCS                   "BCS____APPLICATION______________"
#define       fwBCS_Temperature       "BCS____TEMPERATURE______________"

#define       fwBAS_BootLoad          "BAS____MIO_BOOT_LOADER__________"
#define       fwBAS                   "BAS____APPLICATION______________"

#define       fwKBCS_BootLoad         "KBCS___MIO_BOOT_LOADER__________"
#define       fwKBCS                  "KBCS___APPLICATION______________"

#define       fwDISPLAY_ASOP_BootLoad "MON7'__MIO_BOOT_LOADER__________"
#define       fwDISPLAY_ASOP          "MON7'__ASOP_CONTROL_____ADM13M__"

#define       fwDISPLAY_BootLoad      "MON10'_MIO_BOOT_LOADER__________"
#define       fwDISPLAY               "MON10'_ASKUM2_APPLICATION_______"
#define       fwDISPLAY_LIBIA         "MON10'_ASKUM2_APPLICATION_LIBIA_"
#define       fwDISPLAY_MPT6_10       "MON10'_ASKUM2_APP_MPT6_10_______"
#define       fwDISPLAY_MPT6_10_CR    "MON10'_ASKUM2_APP_MPT6_10_CR____"
#define       fwDISPLAY_MPT6_9        "MON10'_ASKUM2_APP_MPT6_9________"
#define       fwDISPLAY_TMe           "MON10'_ASKUM2_APP_TMe___________"
#define       fwDISPLAY_TM01          "MON7'__ASOP_APP_TM01____________"
#define       fwDISPLAY_TMsr          "MON7'__ASOP_APP_TMSR____________"
#define       fwDISPLAY_TMsv          "MON7'__ASOP_APP_TMSV____________"
#define       fwDISPLAY_ADM1_3cmi     "MON10'_ASKUM2_APP_ADM1_3cmi_____"
#define       fwDISPLAY_TMk           "MON10'_ASKUM2_APP_TMK___________"
#define       fwDISPLAY_TMk_woSM      "MON10'_ASKUM2_APP_TMK_!SM_______"
#define       fwDISPLAY_TMk_woSM_RG   "MON10'_ASKUM2_APP_TMK_!SM_RG____"
#define       fwDISPLAY_TM            "MON10'_ASKUM2_APP_TM____________"
#define       fwDISPLAY_TM230         "MON10'_ASKUM2_APP_TM230_________"
#define       fwDISPLAY_TM270         "MON10'_ASKUM2_APP_TM270_________"
#define       fwDISPLAY_MPT6L         "MON10'_ASKUM2_APP_MPT6L_________"
#define       fwDISPLAY_AGMU          "MON10'_ASKUM2_APP_AGMU__________"

#define       fwBARS_BootLoad         "BARS___MIO_BOOT_LOADER__________"
#define       fwBARS                  "BARS___APPLICATION______________"

#define       fwBUN_BootLoad          "BUN____MIO_BOOT_LOADER__________"
#define       fwBUN                   "BUN____APPLICATION______________"

#define       fwPDU_P_BootLoad        "PDU_P__MIO_BOOT_LOADER__________"
#define       fwPDU_PP                "PDU_PP__APPLICATION_____________"
#define       fwRPDU_PP               "RPDU_PP_APPLICATION_____________"
#define       fwRPDU_PK               "RPDU_PK_APPLICATION_____________"
#define       fwRPDU_U                "RPDU_U__APPLICATION_____________"
#define       fwRPDU_UA               "RPDU_UA_APPLICATION_____________"

#define       fwUSBCNV_BootLoad       "USBCNV_MIO_BOOT_LOADER__________"
#define       fwUSBCNV_Generator      "USBCNV_GENERATOR________________"
#define       fwUSBCNV_NetSimulator   "USBCNV_NETWORK_SIMULATOR________"

#define       fwDIM_App               "DIM____APPLICATION______________"

#endif
