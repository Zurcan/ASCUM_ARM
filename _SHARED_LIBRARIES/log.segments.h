#ifndef logsegments
#define logsegments

// Storage data logs IDs
#define stgid_Language                  0x00000001
#define stgid_ShortLog                  0x00000011
#define stgid_StatLog                   0x00000012

enum LCRtype_t {
  lcrt__TapedData,
  lcrt__Data,
  lcrt__ConstData
};
/* sizeof(LCRtype_t) should be equal to one byte
 * for GNU GCC it is achieved by compiler option -fshort-enums
 */

struct __attribute__ ((packed)) LogConfigRec_t{          //
  unsigned long LID;                                     // Log segment ID
  unsigned int  itemSize;                                // Size in bytes of singular record
  unsigned int  segmentSize;                             // Segment size in bytes
  LCRtype_t type;                                        // Log segment type
  unsigned long reserv1;                                 //
  unsigned long reserv2;                                 //
};

struct __attribute__ ((packed)) segmentHeader_t{
    unsigned long LID;
      #define idf_InterpretationData		0x80000000
    long size;
    long recordSize;
    long CRC32;
    long flags;
    LCRtype_t type;
    char pad[3];
      #define shf__IncrementalTime      0x00000001       ///< Флаг определяет направление хода времени в сегменте
                                                         /// журнала. Если  флаг установлен, то первый элемент - самый
                                                         /// ранний, если флаг сброшен, то первый элемент - самый поздний и наиболее актуальный
    long reserved[46];
};

struct __attribute__ ((packed)) fileHeader_t{
    char magic[8];                                    // "ASKUMLOG"
    char formatVersion;                                  // =0
    char pad[3];                                         // =0
    long reserved[5];                                    // =0
    //long segmentsCount;                                //
    long fileSize;                                       //
    long selfCRC32;                                      //
};



#define LOG_CONFIG_MAX_RECS             32

#endif
