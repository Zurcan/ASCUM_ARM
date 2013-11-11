#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//       WelcomeDialog wd;
//        wd.exec();
    // initiateVideoScreens();
     ui->setupUi(this); 

    // upPlot = this->ui->qwtPlot_2;
     //this->layout()->addWidget(upPlot);
     pf = new PrintForm(this);
    ui->qwtPlot->enableAxis(QwtPlot::yLeft,false);
     ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
            ui->pushButton_3->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
                ui->pushButton_4->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
     mapTimer = new QTimer(this);
     connect(mapTimer, SIGNAL(timeout()),this,SLOT(incrementMarkerPosition()));
     //connect(ui->qwtPlot_2, SIGNAL())
     tmpIcon = new QIcon(":new/p/print");
     ui->actionPrint->setIcon(*tmpIcon);
     ui->actionPrint->setEnabled(false);
     tmpIcon = new QIcon(":new/p/closeLog");
    ui->actionOpen->setIcon(*tmpIcon);

   newLogProc= new logProcessor;// (logProcessor*)malloc(sizeof(logProcessor));
   newTmiInterp = new TMIinterpretator;//(TMIinterpretator*)malloc(sizeof(TMIinterpretator));
//   ui->qwtPlot->installEventFilter(this);
//   ui->qwtPlot_2->installEventFilter(this);
   //ui->qwtPlot_2->setObjectName("upPlot");
//   if(reOpenWindow)
//       openLog();
//    reOpenWindow = false;
}





//mainWindow::mainWindow() : QMainWindow()
//{
//  setupUi(this);
//  connect(buttonObjectName, SIGNAL(clicked()), this, SLOT(openNewMainWindow()));
//}
void MainWindow::openNewMainWindow()
{

  newWin = new MainWindow();
  newWin->show();
  //openLog();

}
void MainWindow::globalInits(int arrayIndexSize)
{

    X = (double*)malloc((arrayIndexSize+1)*sizeOfArray*sizeof(double));
    Y[0]=X+sizeOfArray;
    for(int i =1; i <arrayIndexSize+1; i++)
    {
        Y[i]=Y[i-1]+sizeOfArray;
    }


 //   QPushButton *myButton = new QPushButton;
    ui->qwtPlot_2->setContentsMargins(0,0,-1,0);
    ui->qwtPlot_2->replot();
}

void MainWindow::initiatePlotMarkers()
{
    ui->qwtPlot->enableAxis(0, false);
    verticalMapMarker = new QwtPlotMarker;
    currentTimeMarker = new QwtPlotMarker;
    currentTimeMarker->setLineStyle(QwtPlotMarker::VLine);
    verticalMapMarker->setLineStyle(QwtPlotMarker::VLine);
    currentTimeMarker->setLinePen(QPen(Qt::red,4,Qt::SolidLine));
    verticalMapMarker->setLinePen(QPen(Qt::red,2,Qt::SolidLine));
    currentTimeMarker->setValue(0,0);
    verticalMapMarker->setValue(0,0);
//    double tmpOffset=5;
     //int tmpCounter=0;

    for(int i = 0; i < varCounter; i++)
    {

        flagMarker[i] = new QwtPlotMarker;
        if(flagArray[i])
        {
            flagMarker[i]->setLabel(parLabel[i]);
            flagMarker[i]->setLineStyle(QwtPlotMarker::NoLine);
//            flagMarker[i]->setLinePen(QPen(colors[i]));
          //  flagMarker[i]->attach(ui->qwtPlot_2);

            flagMarker[i]->setValue(80,getOffsetValue(i));
      //      flagMarker[i]->show();
//            tmpCounter++;
        }

    }
    currentTimeMarker->attach(ui->qwtPlot_2);
    verticalMapMarker->attach(ui->qwtPlot);

//    currentTimeMarker->setLabel(firstDateTime.toString());
//    currentTimeMarker->label().setColor(Qt::black);
//    currentTimeMarker->setLabelAlignment(Qt::AlignTop);
//    currentTimeMarker->setSpacing(360);



}

void MainWindow::checkFileHeaderCRC()
{

    newLogProc->selectLogFile(filename);
    newLogProc->readFileHeader();
    unsigned long CRCtmpFH = 0;
    newLogProc->tmpFile.seek(0);
    newLogProc->tmpFile.read(tmpFHPtr,40);
    tmpFHPtr[32]=40;
    tmpFHPtr[33]=0;
    tmpFHPtr[34]=0;
    tmpFHPtr[35]=0;
    tmpFHPtr[36]=0;
    tmpFHPtr[37]=0;
    tmpFHPtr[38]=0;
    tmpFHPtr[39]=0;
    CRCtmpFH = newLogProc->CRC32updater(tmpFHPtr,40,0xffffffff);
    CRCtmpFH = CRCtmpFH^0xffffffff;
    for(int segCount = 0; segCount < 4; segCount++)
    {
        newLogProc->selectSegment(newLogProc->setTmpID());
        newLogProc->logDataPointer+=newLogProc->segmentHeader.size;
        CRCtmpFH = CRCtmpFH^newLogProc->segmentHeader.CRC32;
    }
    if(CRCtmpFH!=newLogProc->fileHeader.CRC32)
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
        newMessage.exec();
       // globalFileErrorFlag = true;
    }
   // else qDebug()<<CRCtmpFH;
}

void MainWindow::readHeadTableData()//here we read head table - its header and its data
{
    int tmpID= 0;
    int cycleID = 0;
    int tmpLogDataPointer =0;
    newLogProc->tmpFile.seek(0);
    if(newLogProc->fileHeader.fileSize != newLogProc->tmpFile.bytesAvailable())//check file size
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Файл журнала регистратора поврежден.");
        newMessage.exec();
    }
    newLogProc->logDataPointer = 40; // jump through file header
    newLogProc->tmpFile.seek(40);
    buffArr = (char*)malloc(newLogProc->segmentHeader.size);
    for(int segCount = 0; segCount < 4; segCount++)
            {
                cycleID = newLogProc->setTmpID();
                if(cycleID==smallTableID)
                {
                    tmpID = cycleID;
                    tmpLogDataPointer =newLogProc->logDataPointer;
                }
                newLogProc->selectSegment(cycleID);
                newLogProc->logDataPointer+=newLogProc->segmentHeader.size;
            }
    newLogProc->logDataPointer = tmpLogDataPointer;
    if(checkSegmentCRC(tmpID))/* if segment is chosen then lets parse it and don't forget that firstly we get it header
                                        also segment with ID begins from 0x8 - is only data interpreter */
     {

      /*
       *At this point we have calculated CRC of head table segment interpretator, and datapointer
       *pointed to the interpreter, but not to its header, so we can get from interpreter names of head
       */
            newTmiInterp->interpreterRecordsCount=newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
            newTmiInterp->setInterpretationTable(buffArr,newTmiInterp->interpreterRecordsCount);
            for(int i =0; i < newTmiInterp->interpreterRecordsCount; i++)
            {
                if(newTmiInterp->TInterpItemArray[i].level!=0)
                {
                    verticalHeaderName =QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name);
                    ui->tableWidget->verticalHeaderItem(i-1)->setText(verticalHeaderName);
                }

            }
           /*
            *from here we start to processing data from small table
            */
            newLogProc->logDataPointer = 40;
            tmpID = 0;
            tmpLogDataPointer = 40;
            for(int segCount = 0; segCount < 4; segCount++)
                    {
                        cycleID = newLogProc->setTmpID();
                        if(cycleID==(int)(smallTableID&0x7fffffff))
                        {
                            tmpID = cycleID;
                            tmpLogDataPointer =newLogProc->logDataPointer;
                        }
                        newLogProc->selectSegment(cycleID);
                        newLogProc->logDataPointer+=newLogProc->segmentHeader.size;
                    }

              newLogProc->logDataPointer = tmpLogDataPointer;
                if(checkSegmentCRC(tmpID))
                    {
                        qDebug() << newLogProc->logDataPointer;
                        QString tmpField = " ";
                        int tmpRecI = 0;
                        QVariant recFloat;
                        newLogProc->readRecord(newLogProc->segmentHeader.recordSize, newLogProc->segmentHeader.size, newLogProc->logDataPointer);
                        for (int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)
                        {
                            tmpRecI=newTmiInterp->TInterpItemArray[i].offset;
                            if(newTmiInterp->TInterpItemArray[i].level)
                            {
                                switch(newTmiInterp->TInterpItemArray[i].typ)
                                {

                                        case 7 :
                                        {
                                            float tmpFloat, tmpMinFloat, tmpMaxFloat;
                                            int tmpIntFloat;
                                            tmpFloat = newTmiInterp->fieldFloat(&newLogProc->record[tmpRecI]);
                                            qDebug() << tmpFloat;
                                            if(tmpFloat==tmpFloat)
                                            {
                                            tmpMinFloat = newTmiInterp->TInterpItemArray[i].min/pow(10,newTmiInterp->TInterpItemArray[i].mask_);
                                            tmpMaxFloat = newTmiInterp->TInterpItemArray[i].max/pow(10,newTmiInterp->TInterpItemArray[i].mask_);
                                            if((tmpMinFloat==0)&&(tmpMaxFloat==0));
                                            else
                                            {
                                                if(tmpFloat!=tmpMinFloat)
                                                {
                                                if(tmpFloat<tmpMinFloat)tmpFloat = tmpMinFloat;
                                                if(tmpFloat>=tmpMaxFloat)tmpFloat = tmpMaxFloat;
                                                }
                                            }
                                            tmpFloat = tmpFloat*pow(10,newTmiInterp->TInterpItemArray[i].mask_);
                                            tmpIntFloat =(int)tmpFloat;
                                            if(tmpFloat>0)
                                            {
                                                if(tmpIntFloat!=0)
                                                {
                                                    if((tmpFloat-tmpIntFloat)!=0)
                                                    {
                                                    if((tmpFloat-tmpIntFloat)>0.5)tmpIntFloat++;
                                                    }
                                                }
                                            }
                                            if(tmpFloat<0)
                                            {
                                                if(tmpIntFloat!=0)
                                                {
                                                    if((tmpFloat-tmpIntFloat)!=0)
                                                    {
                                                    if(abs(tmpFloat-tmpIntFloat)>0.5)tmpIntFloat--;
                                                    }
                                                }
                                            }
                                            tmpFloat = (float)(tmpIntFloat/pow(10,newTmiInterp->TInterpItemArray[i].mask_));

                                            recFloat = tmpFloat;
                                            tmpField = recFloat.toByteArray();
                                            }
                                            else
                                                tmpField = "Неиспр.";
                                            break;
                                        }

                                           default:
                                        {
                                            tmpField.append("Недоступно");
                                            break;
                                        }
                                }
                                QTableWidgetItem *tmpItem;
                                tmpItem = new QTableWidgetItem;
                                tmpItem->setText(QString::fromStdString(tmpField.toStdString()));
                                ui->tableWidget->setItem(i-2, 1, tmpItem );
                            }
                            //else; //if we
                        }
                    }

      }
}

void MainWindow::readDataFromLog()//and now we're reading all the data from our log
{
    int tmpID= 0;
     double flagOffset=0;
    int cycleID = 0;
    int tmpLogDataPointer =0;
    newLogProc->logDataPointer = 40; // jump through file header
    newLogProc->tmpFile.seek(40);
    //buffArr = (char*)malloc(newLogProc->segmentHeader.size);
    for(int segCount = 0; segCount < 4; segCount++)
            {
                cycleID = newLogProc->setTmpID();
                if(cycleID==bigTableID)
                {
                    tmpID = cycleID;
                    tmpLogDataPointer =newLogProc->logDataPointer;
                }
                newLogProc->selectSegment(cycleID);
                newLogProc->logDataPointer+=newLogProc->segmentHeader.size;
            }
    newLogProc->logDataPointer = tmpLogDataPointer;
    if(checkSegmentCRC(tmpID))/* if segment is chosen then lets parse it and don't forget that firstly we get it header
                                        also segment with ID begins from 0x8 - is only data interpreter */
     {

      /*
       *At this point we have calculated CRC of head table segment interpretator, and datapointer
       *pointed to the interpreter, but not to its header, so we can get from interpreter names of head
       */
            newTmiInterp->interpreterRecordsCount=newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
            newTmiInterp->setInterpretationTable(buffArr,newTmiInterp->interpreterRecordsCount);
//            sizeOfArray = newTmiInterp->interpreterRecordsCount;
//            qDebug()<< sizeOfArray;
           // tmpStr = new QString;
            varCounter = newTmiInterp->interpreterRecordsCount-2;
            qDebug() << varCounter;
            initGloabalArrays(varCounter);
            for(int i =0; i < newTmiInterp->interpreterRecordsCount; i++)
            {

                if(newTmiInterp->TInterpItemArray[i].level!=0)
                {
                    tmpStr = QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name);
                    //ui->tableWidget->verticalHeaderItem(i-1)->setText(verticalHeaderName);
                    qDebug() << tmpStr;
                    //varCounter++;
                }

            }

            //qDebug() << varCounter;
           /*
            *from here we start to processing data from small table
            */
            newLogProc->logDataPointer = 40;
            tmpID = 0;
            tmpLogDataPointer = 40;
            for(int segCount = 0; segCount < 4; segCount++)
                    {
                        cycleID = newLogProc->setTmpID();
                        if(cycleID==(int)(bigTableID&0x7fffffff))
                        {
                            tmpID = cycleID;
                            tmpLogDataPointer =newLogProc->logDataPointer;
                        }
                        newLogProc->selectSegment(cycleID);
                        newLogProc->logDataPointer+=newLogProc->segmentHeader.size;
                    }

              newLogProc->logDataPointer = tmpLogDataPointer;
                if(checkSegmentCRC(tmpID))
                    {
                        char buff[20];

                        time_t recTime;
                        time_t firstPointDateTime;
                        int firstPointInt;
//                        qDebug() << newLogProc->segmentHeader.size;
//                        qDebug() << newLogProc->segmentHeader.recordSize;
                        int tmpRecordCount = newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
                        sizeOfArray = tmpRecordCount;
                        globalInits(varCounter);
                        timeArray = (time_t*)malloc((tmpRecordCount)*sizeof(time_t));
                        int recCounter=0;
                        int recPosition=newLogProc->logDataPointer;
                        int recPositionCompareVal = recPosition;

//                        qDebug() << newLogProc->logDataPointer;
//                        qDebug() <<recPositionCompareVal;
//                        qDebug() << tmpRecordCount;
//                        //newLogProc->selectLogFile(filename);
//                        qDebug() << newLogProc->tmpFile.bytesAvailable();
                        QString tmpField = " ";
                        int tmpRecI = 0;
                        QVariant recFloat;
                        int backIndex=tmpRecordCount-1;
                        for (int index = 0; index < tmpRecordCount; index++)
                        {
                            backIndex = tmpRecordCount-1-index;//but there is a little shaming moment, we have to reverse data arrays because first time indeed is last one
                            X[index]= index;
                            flagOffset=0;
                            newLogProc->readRecord(tmpRecordCount,newLogProc->segmentHeader.recordSize, recPositionCompareVal);
                                 tmpRecI =0;
                                    for (int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)//0 - it's some text, 1 - it's time, others are data
                                    {
                                        tmpRecI=newTmiInterp->TInterpItemArray[i].offset;
                                        if(newTmiInterp->TInterpItemArray[i].level)
                                        {

                                            switch(newTmiInterp->TInterpItemArray[i].typ)
                                            {

                                            case 7 :
                                            {
                                                float tmpFloat, tmpMinFloat, tmpMaxFloat;
                                                int tmpIntFloat;
                                                tmpFloat = newTmiInterp->fieldFloat(&newLogProc->record[tmpRecI]);
                                                //qDebug() << tmpFloat;
                                                if(tmpFloat==tmpFloat)
                                                {
                                                tmpMinFloat = newTmiInterp->TInterpItemArray[i].min/pow(10,newTmiInterp->TInterpItemArray[i].mask_);
                                                tmpMaxFloat = newTmiInterp->TInterpItemArray[i].max/pow(10,newTmiInterp->TInterpItemArray[i].mask_);
                                                if((tmpMinFloat==0)&&(tmpMaxFloat==0));
                                                else
                                                {
                                                    if(tmpFloat!=tmpMinFloat)
                                                    {
                                                    if(tmpFloat<tmpMinFloat)tmpFloat = tmpMinFloat;
                                                    if(tmpFloat>=tmpMaxFloat)tmpFloat = tmpMaxFloat;
                                                    }
                                                }
                                                tmpFloat = tmpFloat*pow(10,newTmiInterp->TInterpItemArray[i].mask_);
                                                tmpIntFloat =lround((double)tmpFloat);
//                                                if(tmpFloat>0)
//                                                {
//                                                    if(tmpIntFloat!=0)
//                                                    {
//                                                        if((tmpFloat-tmpIntFloat)!=0)
//                                                        {
//                                                        if((tmpFloat-tmpIntFloat)>0.5)tmpIntFloat++;
//                                                        }
//                                                    }
//                                                }
//                                                if(tmpFloat<0)
//                                                {
//                                                    if(tmpIntFloat!=0)
//                                                    {
//                                                        if((tmpFloat-tmpIntFloat)!=0)
//                                                        {
//                                                        if(abs(tmpFloat-tmpIntFloat)>0.5)tmpIntFloat--;
//                                                        }
//                                                    }
//                                                }
                                                tmpFloat = (float)(tmpIntFloat/pow(10,newTmiInterp->TInterpItemArray[i].mask_));

                                                Y[i-2][backIndex] =  tmpFloat; //round((double)tmpFloat);

                                                }
                                                else
                                                {
                                                    Y[i-2][backIndex] =0;
                                                    tmpFloat=0;
                                                }
                                              //  thermoPlotMaxs[i-2]=tmpMaxFloat;
                                                if(!index)
                                                    thermoPlotMaxs[i-2]=(double)tmpFloat;
                                                else
                                                if((double)tmpFloat>thermoPlotMaxs[i-2])thermoPlotMaxs[i-2]=(double)tmpFloat;
                                                break;
                                            }
                                            case 10 :
                                            {
                                                recTime = (time_t)newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                recTime = mktime(gmtime(&recTime));
                                                if(index==tmpRecordCount-1)
                                                         firstDateTime = QDateTime::fromTime_t(recTime);
                                                timeArray[backIndex] =recTime;//(int)((uint)recTime-(uint)firstPointDateTime);

                                              //  qDebug() << QDateTime::fromTime_t(recTime);
                                                break;
                                            }
                                            case 8 :
                                            {
                                                //tmpRecI=newTmiInterp.TInterpItemArray[l].offset;

                                                if(newTmiInterp->fieldFlag(&newLogProc->record[tmpRecI], &newTmiInterp->TInterpItemArray[i].mask_))
                                                {
                                                    Y[i-2][backIndex]= 1+flagOffset;
                                                }
                                                else
                                                {
                                                    Y[i-2][backIndex]= 0+flagOffset;
                                                }
                                                thermoPlotMaxs[i-2]=1;
                                                flagOffset+=2;
                                                break;
                                            }


                                                       default:
                                                    {
                                                       // tmpField.append("Недоступно");
                                                        qDebug() << "warning! something goes wrong!";
                                                        break;
                                                    }
                                            }


                                        }

                                        //else; //if we
                                    }
                                    recCounter++;
                                     recPosition+=newLogProc->segmentHeader.recordSize;
                                   //  newLogProc->logDataPointer +=newLogProc->segmentHeader.recordSize;
                         //   }

                         //   qDebug() << recPosition;
                        }
                       qDebug() << "firstValue of TimeArray is:";
                       qDebug() << QDateTime::fromTime_t(timeArray[0]);
  //                      sizeOfArray = newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
                       // sizeOfArray = tmpRecordCount;


                        initiateTimeAxis(firstDateTime,timeArray,tmpRecordCount);

                      //  qDebug() << sizeOfArray;
                }

      }
}

bool MainWindow::checkSegmentCRC(long segmentID)
{
   //newLogProc->logDataPointer = 40;
   qDebug()<< newLogProc->logDataPointer;
    newLogProc->selectSegment(segmentID);//selecting head table interpretator segment
    qDebug()<< newLogProc->logDataPointer;
    newLogProc->tmpFile.seek(newLogProc->logDataPointer-208);
    newLogProc->tmpFile.read(tmpHeadArr,208);
    tmpHeadArr[4]=0;
    tmpHeadArr[5]=0;
    tmpHeadArr[6]=0;
    tmpHeadArr[7]=0;
    tmpHeadArr[12]=0;
    tmpHeadArr[13]=0;
    tmpHeadArr[14]=0;
    tmpHeadArr[15]=0;
     //buffArr[newLogProc->segmentHeader.size];
     newLogProc->readSegment(buffArr,newLogProc->segmentHeader.size);
     unsigned long CRCtmp = newLogProc->CRC32updater(tmpHeadArr,208,0xffffffff);
     CRCtmp = newLogProc->CRC32updater(buffArr,newLogProc->segmentHeader.size, CRCtmp);
     CRCtmp = newLogProc->CRC32updater((char*)&newLogProc->segmentHeader.size,4, CRCtmp);
     CRCtmp=CRCtmp^0xffffffff;

     if(CRCtmp!=newLogProc->segmentHeader.CRC32)
     {
         newMessage.setWindowTitle("Ошибка!");
         newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
         newMessage.exec();
         return false;
     }
     return true;
}

void MainWindow::initiateTimeAxis(QDateTime startPoint, time_t *times,int length)
{
    timeScale = new TimeScaleDraw(startPoint);
    timeScale->maxVal=sizeOfArray;
    mapTimeScale = new MapTimeScaleDraw("dd.MM.yyyy hh:mm:ss");
    mapTimeScale->setLabelAlignment(Qt::AlignRight);
  //  SecondsLinearScaleEngine *mapTimeScale = new SecondsLinearScaleEngine;
    qDebug() << length;
    timeScale->timeArr= (time_t*)malloc(length*sizeof(time_t));
//    timeScale->move(QwtScaleDraw::LeftScale);
//     for(int i = 0; i < length; i++)
//         tmp->timeArr[i] = times[i];
    timeScale->timeArr = times;
    mapTimeScale->timeArr = times;
//    for(int i = 0; i < length; i++)
//        qDebug() << timeScale->timeArr[i];
//     for(int i =0; i<sizeOfArray; i++)                               //i need to change this construction with some foo that creates array of ints derives from beggining time in secs
//     {
//         tmp->add[i]=i+(rand()%10000+1);
//     }
     //tmpDraw->label(1000);
    //ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom,timeScale);
     ui->qwtPlot_2->setAxisScaleDraw( QwtPlot::xBottom, timeScale );
     ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom,mapTimeScale);
     ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, sizeOfArray, 0);
    // ui->qwtPlot->axisScaleDraw(QwtPlot::xBottom)->setAlignment(Qt::AlignRight);
//     ui->qwtPlot->setAxisScaleDraw( QwtPlot::xBottom, timeScale );
//     ui->qwtPlot->setAxisScaleEngine(  QwtPlot::xBottom, mapTimeScale );


     QwtScaleDraw *sd = ui->qwtPlot_2->axisScaleDraw(QwtPlot::xBottom);
     sd->enableComponent(QwtScaleDraw::Ticks,false);
     ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,-100,100,100);
     QVariant tmpTimeIndex;
     //tmpTimeIndex = firstDateTime.toTime_t();
    printLeftTimeIndex = 0;
    printRightTimeIndex = printLeftTimeIndex+120;
     //ui->qwtPlot->setAxisScale(
//     myScaleDraw = new QwtScaleDraw;
//     abstractScale = new QwtAbstractScale;

//     ui->qwtPlot->setAxisScaleDraw( QwtPlot::xBottom,
//         timeScale );
     //ui->qwtPlot->setAxisScale(QwtPlot::xBottom,-100,100,100);
}

void MainWindow::initiateCurves()
{
    verticalFlagScale = new VerticalFlagScaleDraw(24);
   // ui->qwtPlot->enableAxis(QwtPlot::xTop,true);
    ui->qwtPlot->enableAxis(QwtPlot::xBottom,true);
    AxisLabelDate = firstDateTime;
     //srand(double(NULL));
    for (int i =0; i<varCounter; i++)
           {
            curve1[i] = new QwtPlotCurve;
            curve1[i]->setPen(QPen(colors[i]));
            curve1[i]->setSamples(X,Y[i],sizeOfArray);
            if(i<2)
            {

                curve1[i]->attach(ui->qwtPlot);
                curve1[i]->setAxes(QwtPlot::xBottom,i);
                ui->qwtPlot->enableAxis(i,false);
                ui->qwtPlot->setContentsMargins(-50,0,0,0);
                ui->qwtPlot->replot();
            }
            if(!flagArray[i])
            {
                curve2[i] = new QwtPlotCurve;
                curve2[i]->setPen(QPen(colors[i]));
                curve2[i]->setSamples(X,Y[i],sizeOfArray);
                 curve2[i]->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
                 curve2[i]->setAxes(QwtPlot::xBottom,i);//this one
                 ui->qwtPlot_2->enableAxis(i,true);//and enable it
                 QPalette myPalette;
                 myPalette.setColor(QPalette::Foreground,colors[i]);
                 myPalette.setColor(QPalette::Text,colors[i]);
 //                curve2[i]->setTitle(parLabel[i]);
                 ui->qwtPlot_2->axisWidget(i)->setPalette(myPalette);
                 ui->qwtPlot_2->replot();
            }
            else
            {
                curve2[i] = new QwtPlotCurve;
                curve2[i]->setPen(QPen(colors[i]));
//                QwtLegend curveLegend;
                // qDebug()<< curve2[i]->offset;
                curve2[i]->setSamples(X,Y[i],sizeOfArray);
                if((int)Y[i][0]%2)curve2[i]->setBaseline(Y[i][0]-1);
                else curve2[i]->setBaseline(Y[i][0]);
                curve2[i]->setBrush(QBrush(colors[i],Qt::Dense6Pattern));
//                curve2[i]->setTitle(parLabel[i]);

//                QwtSeriesData<QPointF> *myData;// = curve2[i]->data();
//                curve2[i]->setData(myData);
//                QPolygonF myPoints;
//                for(int j =0; j < sizeOfArray; j++)
//                {
//                    myPoints << QPointF(X[j], Y[i][j]);
//                }
//                curve2[i]->setSamples(new ShiftData (myPoints));
                curve2[i]->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
                curve2[i]->setAxes(QwtPlot::xBottom,11);//this one
                ui->qwtPlot_2->enableAxis(11,false);//and enable it
                QPalette myPalette;
                myPalette.setColor(QPalette::Foreground,Qt::black);
                myPalette.setColor(QPalette::Text,Qt::black);
                ui->qwtPlot_2->setAxisScaleDraw(11,verticalFlagScale);
                ui->qwtPlot_2->setAxisScale(11, 0, 23, 1);
                //ui->qwtPlot_2->setAxisLabelAlignment(QwtPlot::xBottom,Qt::AlignLeft);
                ui->qwtPlot_2->setAxisTitle(QwtPlot::xBottom, firstDateTime.date().toString());
 //               plotPointer = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
 //                                               QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
 //                                               ui->qwtPlot_2->canvas());
//                connect(plotPointer, SIGNAL(moved(QPoint)),
//                        this, SLOT(cursorMoved(QPoint)));
                ui->qwtPlot_2->axisWidget(i)->setPalette(myPalette);
                ui->qwtPlot_2->replot();
               // offset+=2;
            }
//             }
            // ui->qwtPlot_2->setAxisScale(i,thermoPlotMins[i],thermoPlotMaxs[i],0.25);


            }

}

void MainWindow::initiateVideoScreens()
{
    videoScreen1 = new QWidget (this);
    videoScreen2 = new QWidget(this);
    NcFramelessHelper fh;
    fh1 = new NcFramelessHelper;
    fh2 = new NcFramelessHelper;
    videoLayout1 = new QHBoxLayout;
    videoLayout2 = new QHBoxLayout;
    videoScreen1->setLayout(videoLayout1);
    videoScreen2->setLayout(videoLayout2);
    fh1->activateOn(videoScreen1);
    fh2->activateOn(videoScreen2);
    videoScreen1->setGeometry(330,490,250,180);
    videoScreen2->setGeometry(330,490,250,180);
    QPalette tmpPalette;
    tmpPalette.setColor(QPalette::Background,Qt::darkGray);
    videoScreen1->setPalette(tmpPalette);
    videoScreen2->setPalette(tmpPalette);
    videoScreen1->setWindowFlags( Qt::Tool |Qt::FramelessWindowHint);
    videoScreen2->setWindowFlags(  Qt::Tool |Qt::FramelessWindowHint);//add Qt::WindowStaysOnTopHint  if need on top of everything
    videoScreen2->show();
    videoScreen1->show();

}

//void MainWindow::mouseMoveEvent(QMouseEvent * event)
//{

//    if(isCursorPositionOnUpPlot()||isCursorPositionOnDownPlot())
//    {
//        QWidget *widget = qApp->widgetAt(QCursor::pos());
//        QString widget_name = widget->objectName();
//        QString parent_name = widget->parent()->objectName();
//        if(isCursorPositionOnUpPlot())
//        {

// }



/* If leftButtonPressed (if mouse been moved, leftButtonPressed = false), we have to move marker to this position
 *if pressed right button (leftButtonPressed = false too), we do nothing,
 */
//void MainWindow::mouseReleaseEvent(QMouseEvent *event)
//{

//    if(isCursorPositionOnUpPlot()||isCursorPositionOnDownPlot())
//    {
//        QWidget *widget = qApp->widgetAt(QCursor::pos());
//        QString widget_name = widget->objectName();
//        QString parent_name = widget->parent()->objectName();
//        if(isCursorPositionOnUpPlot())
//        {
//            if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot_2")&(ui->qwtPlot_2->isEnabled()))
//                if(leftButtonPressed)
//                {
//                    if(globalMoveFlag)
//                    {
//                        globalMoveFlag = false;
//                        leftButtonPressed = false;
//                    }
//                    else
//                        if(globalCursorPos==QCursor::pos().x())
//                        {
//                            int cursorPositionOnPlot = ui->qwtPlot_2->mapFromGlobal(QCursor::pos()).x();
//                            int cursorOffset= calculateCursorPlotOffset();
//                            int moveVal = (int)ui->qwtPlot_2->invTransform(QwtPlot::xBottom,(cursorPositionOnPlot + cursorOffset ));
////                            qDebug() << moveVal;
//                            moveMapMarker(moveVal);
//                            leftButtonPressed=false;
//                        }
//                }

//        }
//     else
//      {
//           if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot")&(ui->qwtPlot->isEnabled()))
//           {
//               if(leftButtonPressed)
//               {
//                    if(globalCursorPos==QCursor::pos().x())
//                    {
//                       // int downCursorPos = (int)ui->qwtPlot->transform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x())+ui->qwtPlot->transform(QwtPlot::xBottom, 0);
//                        //qDebug() << downCursorPos;
//                      //  moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()) + ui->qwtPlot->transform(QwtPlot::xBottom, 0));//100 - is offset
//                        leftButtonPressed = false;
//                    }
//               }
//           }
//      }
//    }
//}
bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
   // if(target==Ui::MainWindow)
    //qDebug() << target->parent();
   // if(target->parent())
//    qDebug() << target;
//    qDebug() << event;
//    if(target==ui->qwtPlot || target == ui->qwtPlot_2)// || target->parent()->objectName()=="qwtPlot_2" ||target->parent()->objectName()=="qwtPlot")
//    {

        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = (QMouseEvent *) event;
            QWidget *widget = qApp->widgetAt(QCursor::pos());
            QString widget_name = widget->objectName();
            QString parent_name = widget->parent()->objectName();
            if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot_2")&(ui->qwtPlot_2->isEnabled()))
            {
                if(mouseEvent->buttons()==Qt::LeftButton)
                {
                 //   moveMapMarker((int)ui->qwtPlot_2->invTransform(QwtPlot::xBottom,QCursor::pos().x() - plotPosOffset));
                    globalCursorPos = QCursor::pos().x();
                    globalCursorPoint = QCursor::pos();
                    leftButtonPressed = true;
                }
                if(mouseEvent->buttons()==Qt::RightButton)
                {
                    globalMagnifierPreviosPos=QCursor::pos().x();
                    rightButtonPressed = true;
                }
            }
            if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot")&(ui->qwtPlot->isEnabled()))
            {
                if(mouseEvent->button()==Qt::LeftButton)moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()) + ui->qwtPlot->transform(QwtPlot::xBottom, 0));//100 - is offset
                globalCursorPos = QCursor::pos().x();
                mapPlotUsed = true;
            }
           return true;
        }
        if(event->type()==QEvent::MouseButtonRelease)
        {
            //QMouseEvent *mouseEvent = (QMouseEvent *) event;
//            QWidget *widget = qApp->widgetAt(QCursor::pos());
//            QString widget_name = widget->objectName();
 //           QString parent_name = target->parent()->objectName();//widget->parent()->objectName();
          //  if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot_2")&(ui->qwtPlot_2->isEnabled()))
//            if(parent_name=="qwtPlot_2")
//            {
                if(leftButtonPressed)
                {
                    if(globalMoveFlag)
                    {
                        globalMoveFlag = false;
                        leftButtonPressed = false;
                    }
                    else
                        if(globalCursorPos==QCursor::pos().x())
                        {
                            int cursorPositionOnPlot = ui->qwtPlot_2->mapFromGlobal(QCursor::pos()).x();
                            int cursorOffset= calculateCursorPlotOffset();
                            int moveVal = (int)ui->qwtPlot_2->invTransform(QwtPlot::xBottom,(cursorPositionOnPlot + cursorOffset ));
//                            qDebug() << moveVal;
                            moveMapMarker(moveVal);
                            leftButtonPressed=false;
                        }
                }
                else rightButtonPressed = false;
//            }
           // if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot")&(ui->qwtPlot->isEnabled()))
//            if(parent_name=="qwtPlot")
//            {
                if(mapPlotUsed)
                {
                     if(globalCursorPos==QCursor::pos().x())
                     {
                        // int downCursorPos = (int)ui->qwtPlot->transform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x())+ui->qwtPlot->transform(QwtPlot::xBottom, 0);
                         //qDebug() << downCursorPos;
                       //  moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()) + ui->qwtPlot->transform(QwtPlot::xBottom, 0));//100 - is offset
                         mapPlotUsed = false;
                     }
                }
//            }
            return true;
        }
       if(event->type()==QEvent::MouseMove)
       {
           QMouseEvent *mouseEvent = (QMouseEvent *) event;
           if(mouseEvent->buttons()==Qt::LeftButton)
           {
               if(leftButtonPressed)
               {
                   globalMoveFlag = true;
                   //int globalPos = ui->qwtPlot_2->invTransform(QwtPlot::xBottom, globalCursorPoint.x());
                   int globalPos =  globalCursorPoint.x();
                   //int currentPos = ui->qwtPlot_2->invTransform(QwtPlot::xBottom, QCursor::pos().x());
                   int currentPos = QCursor::pos().x();
                   int cursorPositionMoved =globalPos - currentPos;//ui->qwtPlot_2->mapFromGlobal(globalPos).x() - ui->qwtPlot_2->mapFromGlobal(currentPos).x();
                   cursorPositionMoved = cursorPositionMoved*(globalMagVal*4/ui->qwtPlot_2->canvas()->width());
                   int moveVal = currentTimeMarker->value().x() + cursorPositionMoved;// (int)ui->qwtPlot_2->invTransform(QwtPlot::xBottom,(cursorPositionOnPlot + cursorPositionMoved)) ;//+cursorPositionMoved;
                 //  qDebug() << moveVal;

                   moveMapMarker(moveVal);

                   //return;
                  // moveMapMarker((int)ui->qwtPlot_2->invTransform(QwtPlot::xBottom,QCursor::pos().x()+(globalCursorPos-QCursor::pos().x())));
                   globalCursorPos=QCursor::pos().x();
                   globalCursorPoint = QCursor::pos();
               }
               else
               if(mapPlotUsed)
               {
                  // if(mouseEvent>buttons()==Qt::LeftButton)
                       moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()) + ui->qwtPlot->transform(QwtPlot::xBottom, 0));//100 - is offset
                  // mapPlotUsed = false;
               }
           }
           if(mouseEvent->buttons()==Qt::RightButton)
           {
               if(rightButtonPressed)
               {
               if(globalMagnifierPreviosPos>QCursor::pos().x())
                   globalMagnifyFactor++;
               if(globalMagnifierPreviosPos<QCursor::pos().x())
                   globalMagnifyFactor--;
               globalMagnifierPreviosPos = QCursor::pos().x();
               upPlotMagnifier(globalMagnifyFactor);
               //rightButtonPressed=false;
               }
           }
       return true;
       }
        //return true;
 //       }

  // return false;
    return QMainWindow::eventFilter(target, event);
}

//void MainWindow::mousePressEvent(QMouseEvent  *event)
//{
//    QWidget *widget = qApp->widgetAt(QCursor::pos());
//    QString widget_name = widget->objectName();
//    QString parent_name = widget->parent()->objectName();
//    if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot_2")&(ui->qwtPlot_2->isEnabled()))
//    {
//        if(event->buttons()==Qt::LeftButton)
//        {
//         //   moveMapMarker((int)ui->qwtPlot_2->invTransform(QwtPlot::xBottom,QCursor::pos().x() - plotPosOffset));
//            globalCursorPos = QCursor::pos().x();
//            globalCursorPoint = QCursor::pos();
//            leftButtonPressed = true;
//        }
//        if(event->buttons()==Qt::RightButton)
//            globalMagnifierPreviosPos=QCursor::pos().x();
//    }
//    if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot")&(ui->qwtPlot->isEnabled()))
//    {
//        if(event->buttons()==Qt::LeftButton)moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()) + ui->qwtPlot->transform(QwtPlot::xBottom, 0));//100 - is offset
//        globalCursorPos = QCursor::pos().x();
//        leftButtonPressed = true;
//    }
//}

void MainWindow::moveMapMarker(long int position)
{
    if(position>=sizeOfArray)position=sizeOfArray-1;
    if(position < 0)position = 0;
   // qDebug()<< "position is" << position;
    timeScale->currentIndex = position;
    ui->actionPrint->setEnabled(true);
    verticalMapMarker->setValue(position,0);
    currentTimeMarker->setValue(position,0);
    QDateTime tmpDate=QDateTime::fromTime_t(timeArray[position]);

    if(tmpDate.date()!=AxisLabelDate.date())
    {
        ui->qwtPlot_2->setAxisTitle(QwtPlot::xBottom,tmpDate.date().toString());
        AxisLabelDate = tmpDate;
    }

    double magnifiedVal = upPlotMagnifier(globalMagnifyFactor);

    int tmpCounter=0;
    for(int i =0; i <varCounter; i++ )
    {
        if(!flagArray[i])
        {
            thermo[i]->setValue(Y[i][position]);
        }
        else
        {
            checkBox[i]->setChecked((int)Y[i][position]%2);
            flagMarker[i]->setValue(0.8*magnifiedVal +position,flagMarkerOffsetBase+tmpCounter*flagMarkerIncStep);
            tmpCounter++;
        }

    }

    pf->SetMapMarkerPosition(timeArray[position]);

    for(int i = 0; i<varCounter; i++)
    {
        QVariant tmp;
        if(!flagArray[i])
        {
            //thermo[i]->
//            QwtScaleDraw scldrw;
//            scldrw.label(thermo[i]->value());
//            thermo[i]->setScaleDraw(&scldrw);
//            thermo[i]->setShortcutEnabled(1,true);

            tmp = thermo[i]->value();
            thermo[i]->setToolTip(tmp.toString());
            valueLabel[i]->setText(tmp.toString());
        }
    }

    ui->qwtPlot->replot();
    ui->qwtPlot_2->replot();
}



void MainWindow::initiateThermos()
{
    QPalette thermoPalette;

    for(int i = 0; i<varCounter; i++)
    {
        if(!flagArray[i])
        {
                thermoLayout[i] = new QHBoxLayout(this);
                labelLayout[i] = new QHBoxLayout(this);
                ui->scrollArea->setLayout(ui->verticalLayout_7);
                //ui->verticalScrollBar->setLayout(ui->verticalLayout_7);
                //ui->verticalScrollBar->setParent(ui->scrollArea);
                //ui->verticalLayout_7->addWidget(ui->verticalScrollBar,);
                thermo[i] = new QwtThermo(this);
                axisButton[i] = new QPushButton(this);
                //qDebug() << i;
                buttonIndex = i;
                connect(axisButton[buttonIndex],SIGNAL(clicked()),this,SLOT(indexChanged()));
                connect(axisButton[buttonIndex],SIGNAL(released()),this, SLOT(hideAxis()));
                thermoPalette.setColor(QPalette::ButtonText, colors[i] );
                qDebug() << thermoPlotMaxs[i];
                qDebug() << thermoPlotMins[i];
                thermo[i]->setMaxValue(thermoPlotMaxs[i]);
                thermo[i]->setMinValue(thermoPlotMins[i]);
                thermo[i]->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
                thermo[i]->setValue(Y[i][0]);
                thermo[i]->setMaximumHeight(70);
                QVariant tmp;
                tmp = thermo[i]->value();
                thermo[i]->setToolTip(tmp.toString());

 //               thermo[i]->setScalePosition(QwtThermo::RightScale);
 //               thermo[i]->setScalePosition(QwtThermo::NoScale);
                thermo[i]->setAlarmEnabled(false);
                thermo[i]->setPalette(thermoPalette);
                //QString *tmpStr = parLabel[i];
                RotatedLabel *label1 = new RotatedLabel(parLabel[i]);
                valueLabel[i] = new QLabel(tmp.toString());
                label1->setAngle(0);
                axisButton[i]->setFixedSize(20,20);
                if(isAxisHidden[i])
                    axisButton[i]->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
                else
                    axisButton[i]->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
                labelLayout[i]->addWidget(label1);
                //QSpacerItem *tmpSpace = new QSpacerItem(10,5,QSizePolic);
                //labelLayout[i]->addSpacerItem();
                labelLayout[i]->addStretch();
                labelLayout[i]->addWidget(valueLabel[i]);

                ui->verticalLayout_7->addLayout(labelLayout[i]);
               // ui->verticalLayout_7->addWidget(label1);

               // thermoLayout[i]->addWidget(label1);

                thermoLayout[i]->addWidget(thermo[i]);
                 thermoLayout[i]->addWidget(axisButton[i]);
                thermoLayout[i]->setMargin(0);
                thermoLayout[i]->setSpacing(0);
            //    ui->scrollArea->setLayout(thermoLayout[i]);
                ui->verticalLayout_7->addLayout(thermoLayout[i]);
        }
    }

}

void MainWindow::indexChanged()
{

}
void MainWindow::hideAxis()
{
    int index;
   // qDebug() << QObject::sender();

    QObject * tmp = sender();
    for(int i = 0; i<varCounter; i++)
    {
        if(tmp==axisButton[i])index=i;
    }
    //qDebug() << index ;
    isAxisHidden[index] = !isAxisHidden[index];
    double tmpMagVal = upPlotMagnifier(globalMagnifyFactor);
   // int tmpCounter = 0;
    if(isAxisHidden[index])
    {
        curve2[index]->detach();//by default we have 1st axis with this curve on the plot, also it is enabled by default
        int tmpIndex = 11;
        if(!flagArray[index])
        {
            tmpIndex = index;
            curve2[index]->setAxes(1,tmpIndex);//this one
            ui->qwtPlot_2->enableAxis(tmpIndex,false);//and enable it

          // flagMarker[index]->setValue(0.8*tmpMagVal,flagMarkerOffsetBase+tmpCounter*flagMarkerIncStep);
        }
        else
            flagMarker[index]->detach();

        ui->qwtPlot_2->replot();
        axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
     }
    else
    {
        curve2[index]->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
        int tmpIndex = 11;
        if(!flagArray[index])
        {
            tmpIndex = index;
            curve2[index]->setAxes(1,tmpIndex);//this one

            flagMarker[index]->show();
            ui->qwtPlot_2->enableAxis(tmpIndex,true);//and enable it
        }
        else
        {
            flagMarker[index]->attach(ui->qwtPlot_2);
            flagMarker[index]->setValue(tmpMagVal*0.8+verticalMapMarker->value().x(),getOffsetValue(index));
            qDebug()<< getOffsetValue(index);
        }
        ui->qwtPlot_2->replot();
        axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    }
}

void MainWindow::preparePlotData()
{
    //srand(double(NULL));
//    for(int j = 0; j < varCounter; j++)
//    for(int i = 0; i < sizeOfArray; i++ )
//       {
//        if(j==0)
//        {
//            X[i]  =i;
//        }
//        Y[j][i] = 5;
//       }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    mark[i]=new QwtPlotMarker;
//    mark[i]->setSymbol(your_symbol);
//    mark[i]->setValue(pt.x(),pt.y());
//    mark[i]->attach(your_plot);
//    i++;
//}

void MainWindow::on_pushButton_clicked()
{

    mapTimer->start(mapTimerDelay);
    //moveMapMarker(verticalMapMarker->value().x()+1);
}

void MainWindow::incrementMarkerPosition()
{
    moveMapMarker(verticalMapMarker->value().x()+1);
}

void MainWindow::on_pushButton_2_clicked()
{

    moveMapMarker(sizeOfArray);
}

void MainWindow::openAndPlayVideo()
{
    videoPlayer1 = new QMediaPlayer;
    videoPlayer2 = new QMediaPlayer;
    QVideoWidget *wVideo1 = new QVideoWidget(videoScreen1);
    videoLayout1->addWidget(wVideo1);
    QVideoWidget *wVideo2 = new QVideoWidget(videoScreen2);
    videoLayout2->addWidget(wVideo2);
    videoPlayer1->setVideoOutput(wVideo1);
    wVideo1->setGeometry(videoLayout1->geometry());
    wVideo1->show();
    videoPlayer2->setVideoOutput(wVideo2);
    wVideo2->setGeometry(videoLayout2->geometry());
    wVideo2->show();
     QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
     videoPlayer1->setMedia(QUrl::fromLocalFile(fileName));
     videoPlayer2->setMedia(QUrl::fromLocalFile(fileName));
     videoPlayer1->play();
     videoPlayer2->play();
}

void MainWindow::initGloabalArrays(int valuesCount)
{

}
void MainWindow::hideWasteAxes(int notHiddenIndex)
{
    int index;
    int hiddenCounter=0;
    for(int i = 0; i<varCounter; i++)
    {
        if(isAxisHidden[i])hiddenCounter++;
        if(hiddenCounter>=notHiddenIndex)isAxisHidden[i]=true;
    }
    for( index =0; index< varCounter;index++)
    {
        if(isAxisHidden[index])
        {
            curve2[index]->detach();//by default we have 1st axis with this curve on the plot, also it is enabled by default
            int tmpIndex = 11;
            if(!flagArray[index])
            {
                tmpIndex = index;
                curve2[index]->setAxes(1,tmpIndex);//this one
                ui->qwtPlot_2->enableAxis(tmpIndex,false);//and enable it
            }
            ui->qwtPlot_2->replot();
            axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
         }
        else
        {
            curve2[index]->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
            int tmpIndex = 11;
            if(!flagArray[index])
            {
                tmpIndex = index;
                curve2[index]->setAxes(1,tmpIndex);//this one
                ui->qwtPlot_2->enableAxis(tmpIndex,true);//and enable it
            }
            ui->qwtPlot_2->replot();
            axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
        }
    }
}


void MainWindow::setGlobalArrays()
{
//    tmpMinFloat = newTmiInterp->TInterpItemArray[i].min/pow(10,newTmiInterp->TInterpItemArray[i].mask_);
//    tmpMaxFloat = newTmiInterp->TInterpItemArray[i].max/pow(10,newTmiInterp->TInterpItemArray[i].mask_);
//    newTmiInterp->TInterpItemArray[i]
    for(int i = 0; i < varCounter; i++)
    {
        thermoPlotMins[i] = 0;
       //float  tmpMinFloat = newTmiInterp->TInterpItemArray[i+1].min/pow(10,newTmiInterp->TInterpItemArray[i+1].mask_);
       // thermoPlotMins[i] = (int)tmpMinFloat;
      //  qDebug() << thermoPlotMins[i];
    }
    for(int i = 0; i < varCounter; i++)
    {
//        float tmpMaxFloat = newTmiInterp->TInterpItemArray[i+2].max/pow(10,newTmiInterp->TInterpItemArray[i+2].mask_);
//        thermoPlotMaxs[i] = (int)tmpMaxFloat;
        if(thermoPlotMaxs[i]<1)thermoPlotMaxs[i]=1;
      //  qDebug() << thermoPlotMaxs[i];
    }
    for(int i = 0; i < varCounter; i++)
    {
        if(i<axisCount)
            isAxisHidden[i] = false;
        else
            isAxisHidden[i] = true;
    }

    for(int i = 0; i < varCounter;i++)
    {
      //  parLabel[i] = new QString;
        if(newTmiInterp->TInterpItemArray[i+2].typ==8)flagArray[i]=1;
        else flagArray[i] = 0;
        parLabel[i] = QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i+2].name);// = QString::fromLocal8Bit();
        parLabel[i].replace("[","(");
        parLabel[i].replace("]",")");
      //  qDebug()<< parLabel[i];
    }
//    qDebug() << "flag count:";
//    qDebug() << flagCounter;
}

void MainWindow::on_actionOpen_triggered()
{
    if(!isOpened)
    {
            openLog();
    }
    else
   {
        isOpened=false;

        openNewMainWindow();
        this->close();

   }
}
void MainWindow::closeLog()
{
//    ui->qwtPlot->setEnabled(false);
//    ui->qwtPlot_2->setEnabled(false);

//  // delete timeScale;
//   ui->qwtPlot->detachItems(QwtPlotItem::Rtti_PlotItem,true);
//   ui->qwtPlot->detachItems(QwtPlotItem::Rtti_PlotUserItem,true);
//   //ui->qwtPlot->detachItems(QwtPlotItem::Rtti_PlotScale,true);
//   ui->qwtPlot->replot();
//   ui->qwtPlot_2->detachItems(QwtPlotItem::Rtti_PlotItem,true);
//   ui->qwtPlot_2->replot();
//   ui->tableWidget->clear();
//   ui->tableWidget->setEnabled(false);
//   ui->pushButton->setEnabled(false);
//   ui->pushButton_2->setEnabled(false);
//   ui->pushButton_3->setEnabled(false);
//   ui->pushButton_4->setEnabled(false);
//    QObjectList tmpList= ui->scrollArea->children();
//    qDebug() << tmpList;
//    qDeleteAll(tmpList.begin(), tmpList.end());
//    tmpList.clear();
//    //qDebug() << tmpList;
    //qDeleteAll
//    QIt tmp = tmpList.begin();
//    while (tmp!=tmpList.end())
//    {
//        QObject *item = *tmpList;
//        delete item;
//    }
    //    delete parLabel;
  //  delete checkBox;

//    free(X);// X;
//    free(Y);
//    newLogProc->tmpFile.close();
//    //delete newLogProc;

//    delete curve2;
//    delete curve1;
//    delete timeArray;
//    delete thermoPlotMaxs;
//    //delete newLogProc;
//    //delete newTmiInterp;
//    delete flagMarker;
//    for (int i =0; i < 24; i++)
//        flagArray[i]=0;

}

void MainWindow::openLog()
{
//    newLogProc= new logProcessor;// (logProcessor*)malloc(sizeof(logProcessor));
//    newTmiInterp = new TMIinterpretator;//(TMIinterpretator*)malloc(sizeof(TMIinterpretator));
    filename = QFileDialog::getOpenFileName(this,"Открыть файл лога регистратора", "c:","Выберите файл лога регистратора(*.alg)");
    //qDebug()<< filename;
    if(filename!="")
    {
        ui->qwtPlot->setEnabled(true);
           ui->qwtPlot_2->setEnabled(true);
               ui->tableWidget->setEnabled(true);
                   ui->actionPrint->setEnabled(true);
                       ui->actionOpen->setEnabled(true);
                           ui->scrollArea->setEnabled(true);
                               ui->pushButton->setEnabled(true);
                                   ui->pushButton_2->setEnabled(true);
                                       ui->pushButton_3->setEnabled(true);
                                           ui->pushButton_4->setEnabled(true);
    checkFileHeaderCRC();
    readHeadTableData();
    readDataFromLog();
    setGlobalArrays();
    initiatePlotMarkers();
    initiateThermos();
    initiateRadios();
    initiateCurves();
    hideWasteAxes(axisCount);
    isOpened=true;
    tmpIcon = new QIcon(":new/p/openLog");
    ui->actionOpen->setIcon(*tmpIcon);
    ui->actionOpen->setToolTip("Закрыть файл журнала регистратора");
    pf->setBaseTime(timeArray[0],firstDateTime);
//         installEventFilter(this);
//        ui->qwtPlot->setMouseTracking(true);
//        ui->qwtPlot_2->setMouseTracking(true);
//        ui->qwtPlot->canvas()->setMouseTracking(true);
//        ui->qwtPlot_2->canvas()->setMouseTracking(true);
       ui->qwtPlot->installEventFilter(this);
       ui->qwtPlot_2->installEventFilter(this);

    }
}
void MainWindow::initiateRadios()
{
    for(int i = 0; i<varCounter; i++)
    {
        if(flagArray[i])
        {
               thermoLayout[i]= new QHBoxLayout(this);
                ui->scrollArea->setLayout(ui->verticalLayout_7);
//                radio[i] = new QRadioButton(this);
                checkBox[i] = new QCheckBox (this);
//                radio[i]->setEnabled(false);
                checkBox[i]->setEnabled(false);
                axisButton[i] = new QPushButton(this);
                //qDebug() << i;
                buttonIndex = i;
               // qDebug() << (int)Y[i][0];
                connect(axisButton[buttonIndex],SIGNAL(clicked()),this,SLOT(indexChanged()));
                connect(axisButton[buttonIndex],SIGNAL(released()),this, SLOT(hideAxis()));
//                radio[i]->setCheckable(true);
//                radio[i]->setChecked((int)Y[i][0]%2);
                checkBox[i]->setCheckable(true);
                checkBox[i]->setChecked((int)Y[i][0]%2);
                //checkBox[i]->setCheckable(false);
                 RotatedLabel *label1 = new RotatedLabel(parLabel[i]);
                label1->setAngle(0);
                axisButton[i]->setFixedSize(20,20);
                axisButton[i]->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
               // ui->verticalLayout_7->addWidget(label1);

                thermoLayout[i]->addWidget(label1);
                thermoLayout[i]->addStretch();
                thermoLayout[i]->addWidget(checkBox[i]);
               // thermoLayout[i]->addStretch();
                thermoLayout[i]->addWidget(axisButton[i]);
                thermoLayout[i]->setMargin(0);
                thermoLayout[i]->setSpacing(0);
                //thermoLayout[i]->addStretch();
                ui->verticalLayout_7->addLayout(thermoLayout[i]);
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{

    moveMapMarker(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    mapTimer->stop();
}

double MainWindow::getOffsetValue(int flagIndex)
{

    double tmpOffset = flagMarkerOffsetBase;
    for(int i = 0; i < flagIndex; i++)
    {
        if(flagArray[i])tmpOffset+=flagMarkerIncStep;
    }
    return tmpOffset;
}

void MainWindow::setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage)
{
    QString tmpParamValue;
    QVariant tmpval;
    //if(recNo<printLeftTimeIndex)recNo=printLeftTimeIndex;
   // if((recNo>=printLeftTimeIndex)&&(recNo<=printRightTimeIndex))
   //     {
        if (paramName == "Машина")
        {
            paramValue = ui->tableWidget->item(0,0)->text();
            //qDebug() << paramValue.toString();
        }
        if (paramName == "TodayDate")
            paramValue = QDate::currentDate().toString();
        if (paramName == "Наработка системы")
            paramValue = ui->tableWidget->item(0,0)->text();
        if (paramName == "Наработка двигателя 1") {
            paramValue = ui->tableWidget->item(1,0)->text();
        }
        if (paramName == "Наработка двигателя 2") {
            paramValue = ui->tableWidget->item(2,0)->text();
        }
        if (paramName == "Пробег") {
            paramValue = ui->tableWidget->item(3,0)->text();
        }
        if (paramName == "Суточный пробег") {
            paramValue = ui->tableWidget->item(4,0)->text();
        }
    //    if (paramName == "FirstDate")
    //    {
    //        if(recNo==0)tmpParamValue = model->item(0,0)->text();
    //        else tmpParamValue = model->item(recNo,0)->text();
    //        tmpParamValue.chop(9);
    //        paramValue = tmpParamValue;
    //    }
        if (paramName == "Время")
        {
            tmpval= QDateTime::fromTime_t(timeArray[recNo+printLeftTimeIndex]);
            tmpParamValue = tmpval.toString();
            tmpParamValue.remove(0,11);
            paramValue = tmpParamValue;

        }
        for (int i = 0; i < varCounter; i++)
        {

            if(flagArray[i])
            {
                tmpval = (int)(Y[i][recNo+printLeftTimeIndex])%2;
                if(paramName == parLabel[i])paramValue = tmpval.toString();
            }
            else
            {
                tmpval = Y[i][recNo+printLeftTimeIndex];
                tmpval = tmpval.toFloat();
                if(paramName == parLabel[i])paramValue =  tmpval.toString();
            }
         }
   // }

}
void MainWindow::on_actionPrint_triggered()
{
   int result = pf->exec();
   pf->SetMapMarkerPosition(timeArray[(int)verticalMapMarker->value().x()]);
   if(QDialog::Accepted == result)
   {
      // qDebug() << pf->returnFromTime();
      // qDebug() << pf->retutnToTime();
       convertTimeToPosition(pf->returnFromTime(),pf->retutnToTime());
      // qDebug() << ui->tableWidget->verticalHeaderItem(0)->text();
       report = new QtRPT(this);
       QFileDialog dialog(this);
       //QString fileName = dialog.getOpenFileName(this,"Открыть файл лога регистратора", "c:","Выберите файл (*.*)");;
       QString fileName = "ascumarm_05_09_13.xml";
       report->recordCount << printRightTimeIndex - printLeftTimeIndex;
       if (report->loadReport(fileName) == false) {
           qDebug()<<"Report's file not found";
       }
       else
       {
      //     qDebug()<<"File found processing";
      //     qDebug()<<fileName;
           QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                            this, SLOT(setValue(int&, QString&, QVariant&, int)));
       }
       report->printExec();
   }
   //connect(verticalMapMarker,SIGNAL(moveMapMarker),this,)
   // connect(, SIGNAL(timeout()),this,SLOT(incrementMarkerPosition()));
}

void MainWindow::convertTimeToPosition(QDateTime firstTime, QDateTime secondTime)
{
    bool error1, error2;
    for(int i = 0; i < sizeOfArray; i++)
    {
        if(firstTime.toTime_t()<=timeArray[i])
        {
            printLeftTimeIndex = i;
            i=sizeOfArray;
        }

    }
  //  qDebug() << printLeftTimeIndex;
    for(int i = printLeftTimeIndex; i < sizeOfArray; i++)
    {
        if(secondTime.toTime_t()<=timeArray[i])
        {
            printRightTimeIndex = i;
             i=sizeOfArray;
        }

    }
 //   qDebug()<<printRightTimeIndex;
}

double MainWindow::upPlotMagnifier(int factor)
{
    if(factor>200) factor=200;
    if(factor<0)factor=0;
    double magVal = exp((double)factor/20);
    magVal=round(magVal);
    if(magVal>3000)magVal=3000;
    if(magVal<0)magVal = 0;

    ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,-magVal+currentTimeMarker->value().x(),magVal+currentTimeMarker->value().x(),1);

    int tmpCounter=0;
    for(int i =0; i < varCounter; i++)
    {

        if(flagArray[i])
        {
            flagMarker[i]->setValue(0.8*magVal +currentTimeMarker->value().x(),flagMarkerOffsetBase+tmpCounter*flagMarkerIncStep);
            tmpCounter++;
        }
    }

    ui->qwtPlot_2->replot();
    globalMagVal = magVal;
    return magVal;
}

int MainWindow::calculateCursorPlotOffset()
{
    int offset=0;
    if(ui->qwtPlot_2->visibleRegion().rects().count()>1)
    {
        if(ui->qwtPlot_2->visibleRegion().rects()[0].x()>0)
        {
            //offset = ui->qwtPlot_2->visibleRegion().rects()[0].width();
            int tmpOffset = ui->qwtPlot_2->width() - ui->qwtPlot_2->transform(QwtPlot::xBottom, currentTimeMarker->value().x()+upPlotMagnifier(globalMagnifyFactor));
            offset = 0;
//            qDebug() << ui->qwtPlot_2->visibleRegion().rects()[0].width();
            //offset = tmpOffset + offset - ui->qwtPlot_2->width() ;
        }
        else
            offset = -ui->qwtPlot_2->visibleRegion().rects()[0].width();
    }
//    qDebug() << offset;
 //   qDebug() << ui->qwtPlot_2->width();
//    qDebug() << ui->qwtPlot_2->visibleRegion();
//    qDebug() << ui->qwtPlot_2->visibleRegion().rects()[0].width();
    return offset;
}

bool MainWindow::isCursorPositionOnDownPlot()
{
    int windowXpos= ui->qwtPlot->mapToGlobal(ui->qwtPlot->pos()).x();
    int cursorXPos =QCursor::pos().x();
    int windowYpos = ui->qwtPlot->mapToGlobal(ui->qwtPlot->pos()).y();
  //  qDebug() << windowYpos;
    int cursorYpos = QCursor::pos().y();
//    qDebug() << windowYpos;
//    qDebug() << windowXpos;
//    qDebug() <<cursorYpos;
//    qDebug() << cursorXPos;
   // qDebug() << ui->qwtPlot->visibleRegion();//
    //ui->qwtPlot->mapToGlobal(ui->qwtPlot->pos()).x();
    if((cursorXPos<(windowXpos+ui->qwtPlot->width()))&(cursorXPos>(windowXpos)))//&
            //((cursorYpos<(windowYpos+ui->qwtPlot->height()))&(cursorYpos>(windowYpos))))
        return true;
    else return false;
}

bool MainWindow::isCursorPositionOnUpPlot()
{
    int windowXpos= ui->qwtPlot_2->mapToGlobal(ui->qwtPlot_2->pos()).x();
    int cursorXPos =QCursor::pos().x();
    int windowYpos = ui->qwtPlot_2->mapToGlobal(ui->qwtPlot_2->pos()).y();

    int cursorYpos = QCursor::pos().y();
//    qDebug() << windowYpos;
//    qDebug() << windowXpos;
//    qDebug() <<cursorYpos;
//    qDebug() << cursorXPos;

    //ui->qwtPlot_2->mapToGlobal(ui->qwtPlot_2->pos()).x();
    if(((cursorXPos<(windowXpos+MainWindow::width()))&(cursorXPos>(windowXpos+ui->scrollArea->width())))&
            ((cursorYpos<(windowYpos+ui->qwtPlot_2->height()))&(cursorYpos>(windowYpos))))
        return true;
    else return false;
}

void MainWindow::cursorMoved(QPoint pos)
{
    qDebug() << pos;
}

void MainWindow::on_qwtPlot_2_destroyed()
{

}
