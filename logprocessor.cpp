#include "logprocessor.h"
#include <QString>
//#include <QTextStream>
#include <QFile>
//#include <stdlib.h>
//#include <stdio.h>
//class logProcessor;
logProcessor::logProcessor()
{


}



int logProcessor::selectLogFile(QString filename)
{

    int bytesToRead=0;
    tmpFile.setFileName(filename);
    tmpFile.open(QIODevice::ReadOnly);
    bytesToRead = tmpFile.bytesAvailable();
    if(!readFileHeader())bytesToRead=0;
    return bytesToRead;
}

bool logProcessor::readSegment(char *buf, int size)
{

    if(tmpFile.seek(logDataPointer))
        if(tmpFile.read(buf,size))
            return true;
    return false;
}

bool logProcessor::moveBackLDPtr()
{
    if(tmpFile.isOpen())
    {
        logDataPointer = 0;
        if(logDataPointer==0)
            return true;
        else
            return false;
    }
    else return false;
}

bool logProcessor::setValueLDPtr(qint64 val)
{
    if(tmpFile.isOpen())
    {
    if(val<=tmpFile.size())
        {
            logDataPointer = val;
            return true;
        }
    return false;
    }
    return false;
}

bool logProcessor::pointFileValAtLDPtr(long ptrVal)
{
    if(setValueLDPtr(ptrVal))
        return tmpFile.seek(ptrVal);
    else
        return false;
}

bool logProcessor::readRecord(int recCount, int Size, int savedDataPointer)   //it seems to me that I shouldn't use bytesAvailable,
{                                                                             //but it should be size of segment... or something like this
    int tmp1,tmp2;
    logRecordPointer = logDataPointer;
    tmpFile.seek(logDataPointer);
    tmp1 = tmpFile.bytesAvailable();
    if(tmp1>=Size)
    {
        tmpFile.seek(logRecordPointer);
        //tmp1 = tmpFile.bytesAvailable();
        if(logDataPointer<=Size*recCount+savedDataPointer)
        {
            tmpFile.read(record,Size);
            logDataPointer+=Size;
        }
        else
        {
            //logDataPointer+=Size;
            return false;
        }
        return true;
    }
    else return false;
    return true;
}

bool logProcessor::readTMIInterpreter(char* buf)
{
    return true;
}

bool logProcessor::readFileHeader(void)
{
   char tmparr[SIZE_OF_FILEHEADER];  // I didn't used sizeof(fileHeader_t) because it returns not "correct" value, including struct size and malloc and calloc size
//   int i=0;
   fileHeaderPointer = &fileHeader;
   tmpFile.seek(0);
   tmpFile.read(tmparr, SIZE_OF_FILEHEADER);
   fileHeaderPointer = (fileHeader_t*)tmparr;
   fileHeader = *fileHeaderPointer;
   logDataPointer = SIZE_OF_FILEHEADER;
   return true;
}

long logProcessor::setTmpID()
{
    char tmpIDarr[4];
    long *tmpID;
    long tmpDataPointer = logDataPointer;
    tmpFile.seek(logDataPointer);
    int tmp1 = tmpFile.bytesAvailable();
    while(tmp1+tmpDataPointer>logDataPointer)
    {
        tmpFile.seek(logDataPointer);
        tmpFile.read(tmpIDarr,sizeof(tmpIDarr));
        tmpID = (long*)&tmpIDarr[0];
        return *tmpID;
    }
    return 0;
}

long logProcessor::readTmpID(long pointer)
{
    char tmpIDarr[4];
    long *tmpID;
    if(tmpFile.seek(pointer))
    {
        tmpFile.read(tmpIDarr,sizeof(tmpIDarr));
        tmpID = (long*)&tmpIDarr[0];
        return *tmpID;
    }
    else return -1;//incorrect seek
}

long logProcessor::readSegmentSize(long pointer)
{
    char tmpArr[4];
    long *tmpSize;
    if(tmpFile.seek(pointer+4))
    {
        tmpFile.read(tmpArr,sizeof(tmpArr));
        tmpSize = (long*)&tmpArr[0];
        return *tmpSize;
    }
    else return -1;//incorrect seek
}

int logProcessor::selectSegment(long ID)//first of all we need to find segment, we're searching for by it's ID;
                                                         //the next step is to get selected segment's Header and set pointer to it's first record;
{
    char tmparr[SIZE_OF_SEGMENTHEADER]; // need to make select,check CRC, move logDataPointer, return smth
    long tmpDataPointer;
    if(ID==0)return -1;//wrong ID
    segmentHeaderPointer = &segmentHeader;
    tmpFile.seek(logDataPointer);
    tmpDataPointer = logDataPointer;
    int tmp1 = tmpFile.bytesAvailable();
    while(tmp1+tmpDataPointer>logDataPointer) //untill logDataPointer is lesser than file size
        {
        //    qDebug() << logDataPointer;
        tmpFile.seek(logDataPointer);
        tmpFile.read(tmparr,sizeof(tmparr));
        segmentHeaderPointer = (segmentHeader_t*)&tmparr;
        segmentHeader = *segmentHeaderPointer;
        logDataPointer+=sizeof(tmparr);
        if(ID==segmentHeader.ID)
            return 0;
        else
            logDataPointer+=segmentHeader.size;
        }
    return -2;//something wrong with segment size
}

int logProcessor::checkSegmentsExistance()
{
//    char tmparr[SIZE_OF_SEGMENTHEADER];
    setValueLDPtr(SIZE_OF_FILEHEADER);
    segIDs<<QVector <long>();
//    char tmpIDarr[4];
    if(tmpFile.size()>SIZE_OF_FILEHEADER)
    {
        int i =0;
        pointFileValAtLDPtr(SIZE_OF_FILEHEADER);
        int tmpPointer = SIZE_OF_FILEHEADER;
        while(tmpFile.size() > logDataPointer)
        {
            if(!segIDs.size())
                segIDs.append(0);
            segIDs[i]= readTmpID(tmpPointer);
            long tmpLength = readSegmentSize(tmpPointer);
            if(tmpLength!=-1)
            tmpPointer+=tmpLength;
            tmpPointer+=SIZE_OF_SEGMENTHEADER;
            i++;
        }
        return 0; // file is finished
    }
    return -1;// file is too small
}


char* logProcessor::generateFileHeader()
{
    char retBuf[sizeof(fileHeader_t)];
    char *tmpBuf;
    char i;
    for (i = 0;i<sizeof(fileHeader_t);i++)
        retBuf[i]=i+0x30;
   // long tmpCrc32 = CRC32updater(retBuf,sizeof(fileHeader_t)-4,);
    fileHeaderPointer = &fileHeader;
    fileHeaderPointer = (fileHeader_t * )retBuf;
    fileHeader = *fileHeaderPointer;
   // fileHeader.CRC32 = tmpCrc32;
    tmpBuf = &fileHeader.askumLog[0];

    return tmpBuf;
}

char* logProcessor::generateSegmentHeader(char *buf)
{

    char retArr[sizeof(segmentHeader_t)];
    char *retBuf;
    for(int i = 0; i < sizeof(segmentHeader_t); i++)
        retArr[i]=i+0x30;
    segmentHeaderPointer=&segmentHeader;
    segmentHeaderPointer = (segmentHeader_t*)retArr;
    segmentHeader = *segmentHeaderPointer;
    retBuf= (char*)&segmentHeader.ID;
    return retBuf;
}

bool logProcessor::CRC32checker(char *buf, int CRC, int length)// здесь *buf - указывает на массив данных в сегменте, исключая CRC, которое записывается отдельно
{
    bool retVal=false;
    int tmpCRC = CRC32calculator(buf,length);
    if(tmpCRC==CRC)retVal=true;
    return retVal;
}

int logProcessor::CRC32calculator(char *buf, long length)
{
    unsigned long crcTable[256];
    unsigned long crc=0xffffffff; int i,j;
    for (i = 0; i < 256; i++)
    {
        crc = i;
        for (j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320 : crc >> 1;
        crcTable[i] = crc;
    };
    crc=0xffffffff;
    while(length--)
        crc = crcTable[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

    return crc;//^0xffffffff;
}

unsigned long logProcessor::CRC32updater(char *buf, int length, unsigned long crc)//this function will be commonly used to calculate crc32
{
    unsigned long crcTable[256];
    unsigned long tmpCrc=0xffffffff;
    int i,j;
    for (i = 0; i < 256; i++)
    {
        tmpCrc = i;
        for (j = 0; j < 8; j++)
            tmpCrc = tmpCrc & 1 ? (tmpCrc >> 1) ^ 0xEDB88320 : tmpCrc >> 1;
        crcTable[i] = tmpCrc;
    };
    //crc=0xffffffff;
    while(length--)
        crc = crcTable[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

    return crc;//^0xffffffff;
}

logProcessor::~logProcessor()
{
//    delete logProcessor::logProcessor();
    tmpFile.close();
}
