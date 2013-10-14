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
     pf = new PrintForm(this);
    ui->qwtPlot->enableAxis(QwtPlot::yLeft,false);
     ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
            ui->pushButton_3->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
                ui->pushButton_4->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
     mapTimer = new QTimer(this);
     connect(mapTimer, SIGNAL(timeout()),this,SLOT(incrementMarkerPosition()));
     tmpIcon = new QIcon(":new/p/print");
     ui->actionPrint->setIcon(*tmpIcon);
     ui->actionPrint->setEnabled(false);
     tmpIcon = new QIcon(":new/p/openLog");
    ui->actionOpen->setIcon(*tmpIcon);

     newLogProc= new logProcessor;// (logProcessor*)malloc(sizeof(logProcessor));
     newTmiInterp = new TMIinterpretator;//(TMIinterpretator*)malloc(sizeof(TMIinterpretator));


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
            flagMarker[i]->setValue(90,getOffsetValue(i));
      //      flagMarker[i]->show();
//            tmpCounter++;
        }

    }
    currentTimeMarker->attach(ui->qwtPlot_2);
    verticalMapMarker->attach(ui->qwtPlot);


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
                        for (int index = 0; index < tmpRecordCount; index++)
                        {
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
                                                Y[i-2][index] =(double)tmpFloat;

                                                }
                                                else
                                                {
                                                    Y[i-2][index] =0;
                                                    tmpFloat=0;
                                                }

                                                if(!index)
                                                    thermoPlotMaxs[i-2]=(double)tmpFloat;
                                                else
                                                    if((double)tmpFloat>Y[i-2][index-1])thermoPlotMaxs[i-2]=(double)tmpFloat;
                                                break;
                                            }
                                            case 10 :
                                            {
                                                recTime = (time_t)newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                if(index==0)
                                                         firstDateTime = QDateTime::fromTime_t(recTime);
                                                timeArray[index] =recTime;//(int)((uint)recTime-(uint)firstPointDateTime);

                                              //  qDebug() << QDateTime::fromTime_t(recTime);
                                                break;
                                            }
                                            case 8 :
                                            {
                                                //tmpRecI=newTmiInterp.TInterpItemArray[l].offset;

                                                if(newTmiInterp->fieldFlag(&newLogProc->record[tmpRecI], &newTmiInterp->TInterpItemArray[i].mask_))
                                                {
                                                    Y[i-2][index]= 1+flagOffset;
                                                }
                                                else
                                                {
                                                    Y[i-2][index]= 0+flagOffset;
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
                       // qDebug() << "we're here";
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
    mapTimeScale = new MapTimeScaleDraw("dd.MM.yyyy hh:mm:ss");
  //  SecondsLinearScaleEngine *mapTimeScale = new SecondsLinearScaleEngine;
    qDebug() << length;
    timeScale->timeArr= (time_t*)malloc(length*sizeof(time_t));

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
//     ui->qwtPlot->setAxisScaleDraw( QwtPlot::xBottom, timeScale );
//     ui->qwtPlot->setAxisScaleEngine(  QwtPlot::xBottom, mapTimeScale );

     ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,-100,100,100);

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
                ui->qwtPlot_2->enableAxis(11,true);//and enable it
                QPalette myPalette;
                myPalette.setColor(QPalette::Foreground,Qt::black);
                myPalette.setColor(QPalette::Text,Qt::black);
                ui->qwtPlot_2->setAxisScaleDraw(11,verticalFlagScale);
                ui->qwtPlot_2->setAxisScale(11, 0, 23, 1);
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



void MainWindow::mousePressEvent(QMouseEvent  *event)
{
   // qDebug() << ui->qwtPlot->invTransform(QwtPlot::xBottom,event->pos().x());
    //qDebug() << cursor().pos().y();
   // qDebug() << ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->cursor().pos().x());
//    qDebug() << ui->qwtPlot->size();
    QWidget *widget = qApp->widgetAt(QCursor::pos());
    QString widget_name = widget->objectName();
    QString parent_name = widget->parent()->objectName();
   // qDebug() << widget->parent()->objectName();
    if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot"))
    moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->cursor().pos().x()));
}

void MainWindow::moveMapMarker(long int position)
{
    if(position>sizeOfArray)position=sizeOfArray;
    if(position < 0)position = 0;
    ui->actionPrint->setEnabled(true);
    verticalMapMarker->setValue(position,0);
    currentTimeMarker->setValue(position,0);

   // markerLbl.setText("123");
    //currentTimeMarker->setLabel(markerLbl);
 //   timeScale->updateBaseTime(QDateTime::fromTime_t(timeScale->timeArr[]));
    ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,-100+position,100+position,100);// -100 and 100 are some constants indeed
    //ui->qwtPlot->setAxisAutoScale(0,true);
    int tmpCounter=0;
    //qDebug() << "new cycle";
    for(int i =0; i <varCounter; i++ )
    {
        if(!flagArray[i])
            thermo[i]->setValue(Y[i][position]);
        else
        {
//            radio[i]->setChecked((int)Y[i][position]%2);

            checkBox[i]->setChecked((int)Y[i][position]%2);

//            radio[i]->setEnabled(true);
//            radio[i]->setCheckable(true);
//            qDebug() << i;
//            qDebug() << ((int)Y[i][position])%2;
//            if(((int)Y[i][position])%2==1)radio[i]->setChecked(true);
//            else radio[i]->setChecked(false);
           // radio[i]->setDisabled(true);
            flagMarker[i]->setValue(90+position,flagMarkerOffsetBase+tmpCounter*flagMarkerIncStep);
            tmpCounter++;
            //flagMarker[i]->setValue(position, curve2[i]->maxYValue());
        }

    }
//    if(pf->isVisible())
//    {
//        pf->close();
//        pf->show();
//    }

    pf->SetMapMarkerPosition(timeArray[position]);
    //qDebug() << tmpCounter;
    //qDebug() << verticalMapMarker->xValue();
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
                QVBoxLayout *thermoLayout = new QVBoxLayout(this);
                ui->groupBox->setLayout(ui->horizontalLayout_2);
                thermo[i] = new QwtThermo(this);
                axisButton[i] = new QPushButton(this);
                //qDebug() << i;
                buttonIndex = i;
                connect(axisButton[buttonIndex],SIGNAL(clicked()),this,SLOT(indexChanged()));
                connect(axisButton[buttonIndex],SIGNAL(released()),this, SLOT(hideAxis()));
                thermoPalette.setColor(QPalette::ButtonText, colors[i] );
                qDebug() << thermoPlotMaxs[i];
                qDebug() << thermoPlotMins[i];
                thermo[i]->setMaxValue((double)thermoPlotMaxs[i]);
                thermo[i]->setMinValue((double)thermoPlotMins[i]);
                thermo[i]->setValue(Y[i][0]);
                thermo[i]->setMaximumHeight(100);
                thermo[i]->setScalePosition(QwtThermo::RightScale);
                thermo[i]->setScalePosition(QwtThermo::NoScale);
                thermo[i]->setAlarmEnabled(false);
                thermo[i]->setPalette(thermoPalette);
                //QString *tmpStr = parLabel[i];
                RotatedLabel *label1 = new RotatedLabel(parLabel[i]);
                label1->setAngle(270);
                axisButton[i]->setFixedSize(20,20);
                if(isAxisHidden[i])
                    axisButton[i]->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
                else
                    axisButton[i]->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
                ui->horizontalLayout_2->addWidget(label1);
                thermoLayout->addWidget(axisButton[i]);
                thermoLayout->addWidget(thermo[i]);
                thermoLayout->setMargin(0);
                thermoLayout->setSpacing(0);
                ui->horizontalLayout_2->addLayout(thermoLayout);
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

    if(isAxisHidden[index])
    {
        curve2[index]->detach();//by default we have 1st axis with this curve on the plot, also it is enabled by default
        int tmpIndex = 11;
        if(!flagArray[index])
        {
            tmpIndex = index;
            curve2[index]->setAxes(1,tmpIndex);//this one
            ui->qwtPlot_2->enableAxis(tmpIndex,false);//and enable it

          //  flagMarker[i]->setValue(90,flagMarkerOffsetBase+tmpCounter*flagMarkerIncStep);
        }
        else
            flagMarker[index]->detach();

        ui->qwtPlot_2->replot();
        axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
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
            flagMarker[index]->setValue(90+verticalMapMarker->value().x(),getOffsetValue(index));
            qDebug()<< getOffsetValue(index);
        }
        ui->qwtPlot_2->replot();
        axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
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
            axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
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
            axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
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
      //  qDebug()<< parLabel[i];
    }
//    qDebug() << "flag count:";
//    qDebug() << flagCounter;
}

void MainWindow::on_actionOpen_triggered()
{

     filename = QFileDialog::getOpenFileName(this,"Открыть файл лога регистратора", "c:","Выберите файл лога регистратора(*.alg)");
     //qDebug()<< filename;
     if(filename!="")
     {
         ui->qwtPlot->setEnabled(true);
            ui->qwtPlot_2->setEnabled(true);
                ui->tableWidget->setEnabled(true);
                    ui->actionPrint->setEnabled(true);
                        ui->actionOpen->setEnabled(true);
                            ui->groupBox->setEnabled(true);
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
    }
}
void MainWindow::initiateRadios()
{
    for(int i = 0; i<varCounter; i++)
    {
        if(flagArray[i])
        {
                QVBoxLayout *thermoLayout = new QVBoxLayout(this);
                ui->groupBox->setLayout(ui->horizontalLayout_2);
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
                label1->setAngle(270);
                axisButton[i]->setFixedSize(20,20);
                axisButton[i]->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
                ui->horizontalLayout_2->addWidget(label1);
                thermoLayout->addWidget(axisButton[i]);
//                thermoLayout->addWidget(radio[i]);
                thermoLayout->addWidget(checkBox[i]);
                thermoLayout->setMargin(0);
                thermoLayout->setSpacing(0);
                ui->horizontalLayout_2->addLayout(thermoLayout);
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

void MainWindow::on_actionPrint_triggered()
{

   pf->show();
   pf->SetMapMarkerPosition(timeArray[(int)verticalMapMarker->value().x()]);
   //connect(verticalMapMarker,SIGNAL(moveMapMarker),this,)
   // connect(, SIGNAL(timeout()),this,SLOT(incrementMarkerPosition()));
}
