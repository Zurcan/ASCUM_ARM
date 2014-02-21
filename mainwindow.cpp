#include "mainwindow.h"
#include "ui_mainwindow.h"
/*
PowON
PowOFF
PowOnTime
DateChg
*/
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
//                QPalette red;
//                red.setColor(QPalette::Background,Qt::red);
                ui->widget->setParent(ui->qwtPlot_2);
                ui->widget->setMouseTracking(true);
                QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
                opacityEffect->setOpacity(0.5);
                ui->widget->setGraphicsEffect(opacityEffect);
                ui->widget->setVisible(true);

//                ui->widget->setPalette(red);
//                ui->widget->show();
//                ui->pushButton_5->setParent(ui->widget);
//                ui->pushButton_6->setParent(ui->widget);
//                QPalette transparency;
//                QColor transColor = transparency.light().color();
//                transColor.setAlpha(150);
//                transparency.setColor(QPalette::Background,transColor);
//                //ui->pushButton_5->setba
//                //.setAlpha(100);
//                qDebug() << transparency.light().color().alpha();
//                ui->widget->setPalette(transparency);
                // ui->widget->setEnabled(false);
               // ui->widget->setVisible(false);
     mapTimer = new QTimer(this);
     connect(mapTimer, SIGNAL(timeout()),this,SLOT(incrementMarkerPosition()));
     invisibleVarCounter = 0;
     //connect(ui, SIGNAL())
     //connect(ui->widget, SIGNAL())
     //connect(ui->qwtPlot_2, SIGNAL())
     tmpIcon = new QIcon(":new/p/print");
     ui->actionPrint->setIcon(*tmpIcon);
     ui->actionPrint->setEnabled(false);
     tmpIcon = new QIcon(":new/p/closeLog");
    ui->actionOpen->setIcon(*tmpIcon);
    QIcon *zoominIcon = new QIcon(":new/p/zoomin");
    QIcon *zoomoutIcon = new QIcon(":new/p/zoomout");

    ui->pushButton_5->setIcon(*zoominIcon);
    ui->pushButton_6->setIcon(*zoomoutIcon);
    delete zoominIcon;
    delete zoomoutIcon;
    delete tmpIcon;
    newLogProc= new logProcessor;// (logProcessor*)malloc(sizeof(logProcessor));
    newTmiInterp = new TMIinterpretator;//(TMIinterpretator*)malloc(sizeof(TMIinterpretator));
//    rtPainter = new QwtPlotDirectPainter(this);
    dateChangedArrExistFlag = false;
    timeFractExistFlag = false;
    powOnTimeArrayExistFlag = false;
    ErrXCoords<<QVector <int>();
//    ErrCode <<QVector <long>();
//    ErrCoords<< QVector <QPointF>();
    invisibleVarsMask<<QVector <bool>();

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
//  openLog();

}
void MainWindow::globalInits(int arrayIndexSize)// here's the place to create vector of points+
{

    X = (double*)malloc((arrayIndexSize+1)*sizeOfArray*sizeof(double));
    Y[0]=X+sizeOfArray;
    for(int i =1; i <arrayIndexSize+1; i++)
    {
        Y[i]=Y[i-1]+sizeOfArray;
    }
    qDebug() << arrayIndexSize << "is arrayIndexSize";
    powOnTimeArray = (time_t*)malloc(sizeOfArray*sizeof(time_t));
    timeFract = (char*)malloc(sizeOfArray*sizeof(char));
    dateChangedArr = (bool*)malloc((sizeOfArray*sizeof(bool)));
    ErrCoords = (int*)malloc(sizeOfArray*sizeof(int));
    ErrCode = (long*)malloc(sizeOfArray*sizeof(long));
    for(int i = 0; i < sizeOfArray; i++)
    {
        dateChangedArr[i] = false;
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

//    for(int i = 0; i < varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {

        qDebug() << parLabel[i];
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

bool MainWindow::checkFileHeaderCRC()
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
        long tmpID = newLogProc->setTmpID();
        newLogProc->selectSegment(tmpID);
//        qDebug() << tmpID;
        newLogProc->logDataPointer+=newLogProc->segmentHeader.size;
        CRCtmpFH = CRCtmpFH^newLogProc->segmentHeader.CRC32;
//        qDebug()<< newLogProc->segmentHeader.CRC32;
    }
    if(CRCtmpFH!=newLogProc->fileHeader.CRC32)
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
        newMessage.exec();
//        qDebug() << "error here!";
//        qDebug() << CRCtmpFH;
//        qDebug() << newLogProc->fileHeader.CRC32;
       return true;
    }
//    qDebug() << CRCtmpFH;
//    qDebug() << newLogProc->fileHeader.CRC32;
    return false;
   // else //qDebug()<<CRCtmpFH;
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
                        //qDebug() << newLogProc->logDataPointer;
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
                else
                {
//                    newLogProc->tmpFile.close();
                    isOpened=false;
                    openNewMainWindow();
                    this->close();
                }

      }
    else
    {
//        newLogProc->tmpFile.close();
        isOpened=false;
        openNewMainWindow();
        this->close();
    }
}

bool MainWindow::readDataFromLog()//and now we're reading all the data from our log
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
    int dateTimeChangedIndex=0;
//    for(int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)

//    for(int i = 0; i < sizeOfArray; i++)
//        if(newTmiInterp->TInterpItemArray[dateTimeChangedIndex].)
    newLogProc->logDataPointer = tmpLogDataPointer;
    if(checkSegmentCRC(tmpID))/* if segment is chosen then lets parse it and don't forget that firstly we get it header
                                        also segment with ID begins from 0x8 - is only data interpreter */
     {

      /*
       *At this point we have calculated CRC of head table segment interpretator, and datapointer
       *pointed to the interpreter, but not to its header, so we can get it from interpreter names of head
       */

            newTmiInterp->interpreterRecordsCount=newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
            newTmiInterp->setInterpretationTable(buffArr,newTmiInterp->interpreterRecordsCount);
//            sizeOfArray = newTmiInterp->interpreterRecordsCount;
//            //qDebug()<< sizeOfArray;
           // tmpStr = new QString;
            for (int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)
            {
                qDebug() << newTmiInterp->TInterpItemArray[i].name;
                qDebug() << newTmiInterp->TInterpItemArray[i].typ;
//                invisibleVarsMask.resize(i+1);
                invisibleVarsMask.append(false);
//                invisibleVarsMask.squeeze();

                if((newTmiInterp->TInterpItemArray[i].typ>40)|(newTmiInterp->TInterpItemArray[i].typ==4)|(newTmiInterp->TInterpItemArray[i].typ==27))
                {


                    invisibleVarsMask[i]=true;
                    invisibleVarCounter++;
                }
//                    if(newTmiInterp->TInterpItemArray[i].name=="PowOnTime")
//                {
//                    invisibleVarsMask[i] = true;
//                    invisibleVarCounter++;
//                }

//                if(newTmiInterp->TInterpItemArray[i].name=="TimeFract")
//                {
//                    invisibleVarsMask[i] = true;
//                    invisibleVarCounter++;
//                }


            }
            qDebug() << "vector invisibleVarsMask size is " <<invisibleVarsMask.size();
            varCounter = newTmiInterp->interpreterRecordsCount-2-invisibleVarCounter;
            //qDebug() << varCounter;
//            initGloabalArrays(varCounter);
            for(int i = 0 ; i < invisibleVarsMask.size(); i++)
                qDebug() << invisibleVarsMask[i];
            for(int i =0; i < newTmiInterp->interpreterRecordsCount; i++)
            {

                if((newTmiInterp->TInterpItemArray[i].level!=0)&&(!invisibleVarsMask.at(i)))
                {

                    tmpStr = QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name);
                    if(newTmiInterp->TInterpItemArray[i].typ==8)flagCounter++;
                    //ui->tableWidget->verticalHeaderItem(i-1)->setText(verticalHeaderName);
                    //qDebug() << tmpStr;
                    //varCounter++;
                }

            }

            qDebug() << varCounter<< "is varCounter";
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

                        time_t recTime;
                        time_t lastTime;
                        int tmpRecordCount = newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
                        sizeOfArray = tmpRecordCount;
                        //varCounter-=invisibleVarCounter;
//                        globalInits(varCounter);
                        globalInits(invisibleVarsMask.size());
                      //  newTmiInterp->TInterpItemArray[0].
                        timeArray = (time_t*)malloc((tmpRecordCount)*sizeof(time_t));
                        int recCounter=0;
                        int recPosition=newLogProc->logDataPointer;
                        int recPositionCompareVal = recPosition;
                        QString tmpField = " ";
                        int tmpRecI = 0;
                        QVariant recFloat;
                        int tmpErrVal = 0;
                        int tmpErrLastVal = 0;
                        int errCounter=0;
                        int CoordErrVal = 0;
                        int backIndex=tmpRecordCount-1;
                        for (int index = 0; index < tmpRecordCount; index++)
                        {
                       //     qDebug() << "error?";

                            backIndex = tmpRecordCount-1-index;//but there is a little shaming moment, we have to reverse data arrays because first time indeed is last one
                           // X[index]= index+10;
                            flagOffset=0;
                            newLogProc->readRecord(tmpRecordCount,newLogProc->segmentHeader.recordSize, recPositionCompareVal);
                                 tmpRecI =0;
                                 int tmpInvisibleVarDecrease=0;
                                 qDebug() << "recCount is " << newTmiInterp->interpreterRecordsCount;
                                    for (int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)//0 - it's some text, 1 - it's time, others are data
                                    {
                                        if(index<3)
                                        {
                                      //   qDebug() << newTmiInterp->TInterpItemArray[i].typ;
//                                            qDebug() << QString::fromStdString(newTmiInterp->TInterpItemArray[i].name);
                                           // qDebug() << sizeof(int);
                                        }
                                        if(invisibleVarsMask.at(i))tmpInvisibleVarDecrease++;
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
                                                ////qDebug() << tmpFloat;
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
                                                int tmpMask = newTmiInterp->TInterpItemArray[i].mask_;
                                                tmpFloat = tmpFloat*pow(10,tmpMask);
                                                tmpIntFloat = tmpFloat;
                                               // tmpFloat = round(tmpDblFloat);
                                            /*    if(newTmiInterp->TInterpItemArray[i].mask_)
                                                {
                                                    int drop = tmpIntFloat%(int)pow(10,newTmiInterp->TInterpItemArray[i].mask_);
                                                    if(drop!=0)tmpIntFloat = tmpIntFloat - drop;
                                                }*/
                                                //tmpIntFloat =(short int)(round((double)tmpFloat));
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
                                                tmpFloat = tmpIntFloat/pow(10,tmpMask);
                                               // if(tmpMask)//qDebug()<<(double)tmpFloat;
                                                //if(i-2)
                                                //int tmpInt = (int)(tmpFloat*pow(10,newTmiInterp->TInterpItemArray[i].mask_));
                                               // tmpFloat = tmpInt;
                                               // tmpInt = ceil(tmpInt);
                                                //tmpFloat=(float)(tmpInt/pow(10,newTmiInterp->TInterpItemArray[i].mask_));
                                                Y[i-2-tmpInvisibleVarDecrease][backIndex] =  tmpFloat; //round((double)tmpFloat);

                                                }
                                                else
                                                {
                                                    Y[i-2-tmpInvisibleVarDecrease][backIndex] =0;
                                                    tmpFloat=0;
                                                }
                                              //  thermoPlotMaxs[i-2]=tmpMaxFloat;
                                                if(!index)
                                                    thermoPlotMaxs[i-2-tmpInvisibleVarDecrease]=(double)tmpFloat;
                                                else
                                                if((double)tmpFloat>thermoPlotMaxs[i-2-tmpInvisibleVarDecrease])thermoPlotMaxs[i-2-tmpInvisibleVarDecrease]=(double)tmpFloat;
                                                break;
                                            }
                                            case 10 :
                                            {

                                                recTime = (time_t)newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                recTime = mktime(gmtime(&recTime));
                                                if(newTmiInterp->TInterpItemArray[i].name!="PowOnTime")
                                                {
                                                        if(index==0)
                                                        {

                                                            lastTime = (int)recTime;
                                                            endOfLogTime = lastTime;
                                                        }
                                                        if(index==tmpRecordCount-1)
                                                                 firstDateTime = QDateTime::fromTime_t(recTime);
                                                        X[index] = (int)lastTime - (int)recTime;
                                                      //  qDebug() << X[index];
                                                        timeArray[backIndex] =recTime;//(int)((uint)recTime-(uint)firstPointDateTime);
                                                 }
                                                else
                                                {

                                                    //Y[i-2][backIndex] = (int)recTime;//c
                                                    //qDebug() << newTmiInterp->TInterpItemArray[i].level;
                                                    qDebug() << newTmiInterp->TInterpItemArray[i].name;
                                                }
                                                      //  //qDebug() << QDateTime::fromTime_t(recTime);
                                                        break;
                                            }
                                            case 8 :
                                            {
                                                //tmpRecI=newTmiInterp.TInterpItemArray[l].offset;
                                               // if(i==1)
                                                //{
                                                 //   flagCounter++;
                                                //    qDebug()<<flagCounter;
                                                //}

                                                if(newTmiInterp->fieldFlag(&newLogProc->record[tmpRecI], &newTmiInterp->TInterpItemArray[i].mask_))
                                                {
                                                    Y[i-2-tmpInvisibleVarDecrease][backIndex]= 1+flagOffset; //here we forming the Y-array of flags
                                                }
                                                else
                                                {
                                                    Y[i-2-tmpInvisibleVarDecrease][backIndex]= 0+flagOffset;
                                                }
                                                thermoPlotMaxs[i-2-tmpInvisibleVarDecrease]=1;
                                                flagOffset+=2;
                                                break;
                                            }
                                            case 27:
                                            {
                                                 tmpErrVal = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                 bool successScanFlag=false;
//                                                if(tmpErrVal!=tmpErrLastVal)
                                                 for(int a = backIndex; a < tmpRecordCount; a++)
                                                     if(!successScanFlag)
                                                     {
                                                         if(ErrCode[a]==tmpErrLastVal)
                                                         {
                                                             ErrCoords[backIndex]=ErrCoords[a];
                                                             successScanFlag = true;
                                                         }
                                                     }
                                                 if(!successScanFlag)
                                                     ErrCoords[backIndex] = CoordErrVal++;
                                                 ErrCode[backIndex]= tmpErrVal;
//                                                        {
//                                                            if(tmpErrVal!=0)
//                                                            {
//                                                                errCounter++;
//                                                                ErrXCoords.insert(errCounter-1, backIndex);
//                                                                qDebug() << ErrXCoords.indexOf(backIndex, errCounter ) << " these are X coords of error";
//                                                                ErrXCoords.iterator++;
                                                                tmpErrVal = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
//                                                                ErrCode.insert(errCounter-1, tmpErrVal);
//                                                                ErrCode.iterator++;
                                                                tmpErrLastVal = tmpErrVal;
//                                                            }
//                                                        }

                                                 qDebug() << tmpErrVal<<" these are tmpErrVals of error";


                                            }

                                                       default:
                                                    {
                                                            if(newTmiInterp->TInterpItemArray[i].name=="PowOnTime")
                                                            {
                                                                powOnTimeArrayExistFlag = true;
                                                                recTime = (time_t)newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                                recTime = mktime(gmtime(&recTime));


                                                                powOnTimeArray[backIndex] = recTime;//(int)((uint)recTime-(uint)firstPointDateTime);
                                                                qDebug() << powOnTimeArray[backIndex];
            //                                                    qDebug()  << "powOnTimeArray";

                                                            }
//                                                            if()
                                                            if(newTmiInterp->TInterpItemArray[i].name == "TimeFract")
                                                            {

                                                                timeFractExistFlag = true;
                                                                timeFract[backIndex] = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                            }
                                                            if(newTmiInterp->TInterpItemArray[i].name=="DateChg")
                                                               {
                                                                        dateChangedArrExistFlag = true;

                                                                        //dateTimeChangeIndex = i;

                                                                        if(newTmiInterp->fieldFlag(&newLogProc->record[tmpRecI], &newTmiInterp->TInterpItemArray[i].mask_))
                                                                        {
                                                                            dateChangedArr[backIndex]= 1+flagOffset; //here we forming the Y-array of flags
                                                                        }
                                                                        else
                                                                        {
                                                                            dateChangedArr[backIndex]= 0+flagOffset;
                                                                        }
                                                                        thermoPlotMaxs[i-2-tmpInvisibleVarDecrease]=1;
                                                                        flagOffset+=2;
                                                                }
                                                       // tmpField.append("Недоступно");
                                                        //qDebug() << "warning! something goes wrong!";
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

                         //   //qDebug() << recPosition;
                        }
                       //qDebug() << "firstValue of TimeArray is:";
                       //qDebug() << QDateTime::fromTime_t(timeArray[0]);
  //                      sizeOfArray = newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
                       // sizeOfArray = tmpRecordCount;

                         qDebug() << "error??";
                        if(!initiateTimeAxis(firstDateTime,timeArray,tmpRecordCount))
                        {

//                            newLogProc->tmpFile.close();
//                            closeLog();
                            isOpened=false;
                            openNewMainWindow();
                            this->close();
                            return false;
                        }

                      //  //qDebug() << sizeOfArray;
                }
                else
                {

//                    newLogProc->tmpFile.close();
                    isOpened=false;
                    openNewMainWindow();
                    this->close();
                    return false;
                }

      }
    else
    {

//        newLogProc->tmpFile.close();
        isOpened=false;
        openNewMainWindow();
        this->close();
        return false;
    }
    return true;
}

bool MainWindow::checkSegmentCRC(long segmentID)
{
   //newLogProc->logDataPointer = 40;
   //qDebug()<< newLogProc->logDataPointer;
    newLogProc->selectSegment(segmentID);//selecting head table interpretator segment
    //qDebug()<< newLogProc->logDataPointer;
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

bool MainWindow::initiateTimeAxis(QDateTime startPoint, time_t *times,int length)
{

    int pointsAmount=0;
//    if(dateChangedArrExistFlag)
//    {
        for(int i = 1; i < sizeOfArray; i++)
        {
            if(!dateChangedArr[i])
            {                                                       //if there was an appearence of dateChanged flag, that is being searched in dateChangeArr
                pointsAmount += (int)times[i]-(int)times[i-1];      //we have to increase pointsAmount value only by one, otherwise increase it by subtracted value
                qDebug() << dateChangedArr[i] << " date Changed";

            }
            else pointsAmount++;                                    //of times[i]-times[i-1]
        }
//    }
    if(times[sizeOfArray-1]<times[0])
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Проверьте правильность лог-файла. Ось времени развернута в обратную сторону!");
        newMessage.exec();
        return false;
    }
    qDebug() << QDateTime::fromTime_t(times[sizeOfArray-1]) << "begin time" << QDateTime::fromTime_t(times[0])<< "end time";
    if(pointsAmount > MAX_POINTS)
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Проверьте правильность лог-файла. Слишком много точек для построения!");
        newMessage.exec();
        return false;
    }
    else
    {
            pointsQuantity = pointsAmount;
            timeScale = new TimeScaleDraw(startPoint);


            timeScale->maxVal=pointsAmount;
            mapTimeScale = new MapTimeScaleDraw("dd.MM.yyyy hh:mm:ss");
            mapTimeScale->setLabelAlignment(Qt::AlignRight);
            //qDebug() << length;
            timeScale->timeArr= (time_t*)malloc(sizeOfArray*sizeof(time_t));
            time_t *allPoints = (time_t*)malloc(pointsAmount*sizeof(time_t));
            allPoints[0] = times[0];

            allPoints[pointsAmount-1] = times[sizeOfArray -1];
            for (int i = 1; i < pointsAmount-1; i++)
            {
                allPoints[i] = allPoints[i-1]+1;
            }

        //    timeScale->timeArr = times;
        //    mapTimeScale->timeArr =times;
            timeScale->timeArr = allPoints;
            mapTimeScale->timeArr = allPoints;
            qDebug() << "pointsAmount";
            qDebug() << pointsAmount;
            qDebug() << sizeOfArray;
            for(int i = 0; i < sizeOfArray; i++)
                qDebug() << Y[0][i];
             ui->qwtPlot_2->setAxisScaleDraw( QwtPlot::xBottom, timeScale );
             ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom,mapTimeScale);
             ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, pointsAmount, 0);
             QwtScaleDraw *sd = ui->qwtPlot_2->axisScaleDraw(QwtPlot::xBottom);
             sd->enableComponent(QwtScaleDraw::Ticks,false);
             ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom, 0, pointsAmount, 0);
            // ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,-100,100,100);
             QVariant tmpTimeIndex;
            printLeftTimeIndex = 0;
            printRightTimeIndex = printLeftTimeIndex+120;
//            free(allPoints);
//            delete(timeScale);
            return true;
    }
}

void MainWindow::initiateCurves()
{
    double *X1 = (double*)malloc(sizeOfArray*sizeof(double));
    for(int i = 0; i < sizeOfArray; i++)
    {
        X1[i] = (int)timeArray[i]-(int)timeArray[0];
        qDebug() << X1[i];
        qDebug() << Y[1][i];
    }
    verticalFlagScale = new VerticalFlagScaleDraw(24);
   // ui->qwtPlot->enableAxis(QwtPlot::xTop,true);
    ui->qwtPlot->enableAxis(QwtPlot::xBottom,true);
//    QwtCurveFitter *fitter = new QwtCurveFitter;

    AxisLabelDate = firstDateTime;

     //srand(double(NULL));
//    for (int i =0; i<varCounter; i++)
//        if(!invisibleVarsMask[i])
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
           {
            curve1[i] = new QwtPlotCurve;
//            this->chi
            curve1[i]->setPen(QPen(colors[i]));
            curve1[i]->setStyle(QwtPlotCurve::Steps);
            curve1[i]->setCurveAttribute(QwtPlotCurve::Inverted);

            curve1[i]->setSamples(X1,Y[i],sizeOfArray);
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
                        curve2[i]->setStyle(QwtPlotCurve::Steps);
                        curve2[i]->setCurveAttribute(QwtPlotCurve::Inverted);
                        //curve2[i]->set
                        curve2[i]->setSamples(X1,Y[i],sizeOfArray);
                         curve2[i]->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
                         curve2[i]->setAxes(QwtPlot::xBottom,i);//this one
                         ui->qwtPlot_2->enableAxis(i,true);//and enable it
                         QPalette myPalette;
                         myPalette.setColor(QPalette::Foreground,colors[i]);
                         myPalette.setColor(QPalette::Text,colors[i]);
         //                curve2[i]->setTitle(parLabel[i]);
                         //qDebug() << newTmiInterp->TInterpItemArray[i].mask_;
                         ui->qwtPlot_2->axisWidget(i)->setPalette(myPalette);
                         ui->qwtPlot_2->replot();
                    }
                    else
                    {
                        curve2[i] = new QwtPlotCurve;
                        curve2[i]->setPen(QPen(colors[i]));
        //                QwtLegend curveLegend;
                        // //qDebug()<< curve2[i]->offset;
                        curve2[i]->setSamples(X1,Y[i],sizeOfArray);
                        if((int)Y[i][0]%2)curve2[i]->setBaseline(Y[i][0]-1);
                        else curve2[i]->setBaseline(Y[i][0]);
                        curve2[i]->setBrush(QBrush(colors[i],Qt::Dense6Pattern));
                        curve2[i]->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
                        curve2[i]->setAxes(QwtPlot::xBottom,12);//this one
                        ui->qwtPlot_2->enableAxis(12,false);//and enable it
                        QPalette myPalette;
                        myPalette.setColor(QPalette::Foreground,Qt::black);
                        myPalette.setColor(QPalette::Text,Qt::black);
                        ui->qwtPlot_2->setAxisScaleDraw(12,verticalFlagScale);
                        ui->qwtPlot_2->setAxisScale(12, 0, flagCounter*2-1, 1);
                        QwtText tmpTitle = firstDateTime.date().toString("dd.MM.yyyy");
                        QFont tmpFont;
                        tmpFont.setBold(false);
                        tmpTitle.setFont(tmpFont);
                        ui->qwtPlot_2->setAxisTitle(QwtPlot::xBottom, tmpTitle);
                        ui->qwtPlot_2->axisWidget(i)->setPalette(myPalette);
                        ui->qwtPlot_2->replot();
                       // offset+=2;
                    }
//            QFont axisTitleFont;
//            axisTitleFont.setBold(true);
//            axisTitleFont.setWordSpacing(100);
//             }
            // ui->qwtPlot_2->setAxisScale(i,thermoPlotMins[i],thermoPlotMaxs[i],0.25);

            }
     errorCurve = new QwtPlotCurve;
     QVector <QPointF> tmpSamples;
     tmpSamples.begin();
     tmpSamples.append(QPointF(10,10));
     tmpSamples.insert(tmpSamples.begin(),QPointF(20,10));
     errorCurve->setSamples(tmpSamples);
     errorSym.setColor(Qt::black);
     errorSym.setStyle(QwtSymbol::Diamond);
     errorSym.setPen(QColor(Qt::black));
     errorSym.setSize(4);
     QwtText tmpTxt;
     errorMarker = new QwtPlotMarker;
     tmpTxt.setText("0x001234");
     errorMarker->setLabel(tmpTxt);
     errorMarker->setValue(QPointF(15,12));
     errorMarker->setLineStyle(QwtPlotMarker::NoLine);
     errorMarker->setLinePen(QPen(Qt::red,1,Qt::SolidLine));
     errorMarker->attach(ui->qwtPlot_2);
     errorMarker->show();
     errorCurve->setSymbol(&errorSym);
     errorCurve->attach(ui->qwtPlot_2);
     for(int i = 0; i < ErrXCoords.count(); i++)
     {
         qDebug() << ErrXCoords[i];
     }

    free(X1);


}

void MainWindow::initiateVideoScreens()
{
    videoScreen1 = new QWidget(this);
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


/* If leftButtonPressed (if mouse been moved, leftButtonPressed = false), we have to move marker to this position
 *if pressed right button (leftButtonPressed = false too), we do nothing,
 */

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
   // if(target==Ui::MainWindow)
    //if()
//    qDebug() << target;
   // if(target->parent())
//    //qDebug() << target;
//    //qDebug() << event;
//    if(target==ui->qwtPlot || target == ui->qwtPlot_2)// || target->parent()->objectName()=="qwtPlot_2" ||target->parent()->objectName()=="qwtPlot")
//    {

        if(event->type() == QEvent::MouseButtonPress & target!=0x0)
        {
            QMouseEvent *mouseEvent = (QMouseEvent *) event;
           // QWidget *widget = qApp->widgetAt(QCursor::pos());
           // QString widget_name = widget->objectName();
            QString parent_name = target->objectName();
           // if((widget_name == "QwtPlotCanvas")&(parent_name=="qwtPlot_2")&(ui->qwtPlot_2->isEnabled()))
            if(parent_name=="qwtPlot_2")
            {
                if(mouseEvent->buttons()==Qt::LeftButton)
                {
                 //   moveMapMarker((int)ui->qwtPlot_2->invTransform(QwtPlot::xBottom,QCursor::pos().x() - plotPosOffset));
                    globalCursorPos = QCursor::pos().x();
                    globalCursorPoint = QCursor::pos();
                    leftButtonPressed = true;
                    globalCursorFirstPressPos = QCursor::pos().x();
                    globalCursorMove = 0;
                }
                if(mouseEvent->buttons()==Qt::RightButton)
                {
                    globalMagnifierPreviosPos=QCursor::pos().x();
                    rightButtonPressed = true;
                }
            }
            if(parent_name=="qwtPlot")
            {
//                double widthGain = sizeOfArray/ui->qwtPlot->axisWidget(QwtPlot::xBottom)->width();
                if(mouseEvent->button()==Qt::LeftButton)moveMapMarker(ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()));//moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()) + ui->qwtPlot->transform(QwtPlot::xBottom,0));//100 - is offset
//                qDebug()<< ui->qwtPlot->axisWidget(QwtPlot::xBottom)->width();
//                qDebug()<< ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left());
//                qDebug()<< sizeOfArray;
//                qDebug()<< ui->qwtPlot->mapFromGlobal(QCursor::pos()).x();
//                qDebug()<< ui->qwtPlot->transform(QwtPlot::xBottom,0);
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
            globalSavedCursorMove=0;
                if(leftButtonPressed)
                {
                    if(globalMoveFlag)
                    {
                        globalCursorMove = 0;
                        globalMoveFlag = false;
                        leftButtonPressed = false;
                    }
                    else
                        if(globalCursorPos==QCursor::pos().x())
                        {
                            int cursorPositionOnPlot = ui->qwtPlot_2->mapFromGlobal(QCursor::pos()).x();
                            int cursorOffset= calculateCursorPlotOffset();
                            int moveVal = (int)ui->qwtPlot_2->invTransform(QwtPlot::xBottom,(cursorPositionOnPlot + cursorOffset ));
//                            //qDebug() << moveVal;
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
                         ////qDebug() << downCursorPos;
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
                   double globalPos =  globalCursorPos;
                   //qDebug() << globalPos;
                   //int currentPos = ui->qwtPlot_2->invTransform(QwtPlot::xBottom, QCursor::pos().x());
                   double currentPos = QCursor::pos().x();
                   int visWidth =  ui->qwtPlot_2->axisWidget(QwtPlot::xBottom)->width();
                  // if(ui->qwtPlot_2->visibleRegion().rectCount()>2)visWidth = ui->qwtPlot_2->visibleRegion().rects()[2].width();
                   //else visWidth =  ui->qwtPlot_2->axisWidget(QwtPlot::xBottom)->width();
                   double cursorPositionMoved =globalPos - currentPos;//ui->qwtPlot_2->mapFromGlobal(globalPos).x() - ui->qwtPlot_2->mapFromGlobal(currentPos).x();
                   globalCursorMove +=cursorPositionMoved;
                   int cursorGlobalError = (globalCursorFirstPressPos-currentPos) - globalCursorMove;//some errors of scroll navigation appears if we just make int from double, truncated value is became lost
                   cursorPositionMoved = (cursorPositionMoved+cursorGlobalError)*(globalMagVal*2/visWidth);//making conversion from pixels to units of upPlot
                   globalSavedCursorMove+=cursorPositionMoved; // save all double shifts into global counter
                   int moveVal = currentTimeMarker->value().x() + (int)globalSavedCursorMove;// get only integer part of double
                   globalCursorMove = globalCursorFirstPressPos - currentPos; //this string is needed to calculate global error value
                   globalSavedCursorMove-=(int)globalSavedCursorMove; // subtract integer part from the double, same as delphi trunc() operation
                   moveMapMarker(moveVal);
                   globalCursorPos=QCursor::pos().x();
                   globalCursorPoint = QCursor::pos();
               }
               else
               if(mapPlotUsed)
               {
                  // if(mouseEvent>buttons()==Qt::LeftButton)
                       moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x() - ui->qwtPlot->contentsMargins().left()) );//100 - is offset
                  // mapPlotUsed = false;
               }
           }
           else if(mouseEvent->buttons()==Qt::RightButton)
           {
               if(rightButtonPressed)
               {
               if(globalMagnifierPreviosPos>QCursor::pos().x())
               {
                   double tmpInc = 10*globalMagVal/ui->qwtPlot_2->canvas()->width();
                   if(tmpInc<1)tmpInc = 1;
                   globalMagnifyFactor+=tmpInc;
               }
           //    qDebug() << globalMagVal*2/ui->qwtPlot_2->canvas()->width();
               if(globalMagnifierPreviosPos<QCursor::pos().x())
               {
                   double tmpInc = 10*globalMagVal/ui->qwtPlot_2->canvas()->width();
                   if(tmpInc<1)tmpInc = 1;
                   globalMagnifyFactor-=tmpInc;
               }

               globalMagnifierPreviosPos = QCursor::pos().x();
               upPlotMagnifier(globalMagnifyFactor);
               //rightButtonPressed=false;
               }
           }
           //else if(target->) qDebug

       return true;
       }
//           qDebug()<< ui->qwtPlot_2->visibleRegion().rects()[1].width();
//           qDebug()<< ui->qwtPlot_2->visibleRegion().rectCount();
//       if(ui->qwtPlot_2->visibleRegion().rectCount()-rectQty!=0)
//       {
//           if(rectQty==2)plotRectBasicWidth =ui->qwtPlot_2->visibleRegion().rects()[2].width() - ui->qwtPlot_2->visibleRegion().rects()[1].width();
//           else plotRectBasicWidth =  ui->qwtPlot_2->visibleRegion().rects()[1].width();

//       }
       if(plotRectBasicWidth==0)
       {
           plotRectBasicWidth = ui->widget->pos().x()+ui->widget->width();
       }
           //if(ui->qwtPlot_2->visibleRegion().rectCount()<3) Ktulhu is here!!!
            if((ui->qwtPlot_2->visibleRegion().rectCount()<3)&&(ui->qwtPlot_2->visibleRegion().rectCount()>1))
           {
//               qDebug() << ui->qwtPlot_2->visibleRegion().rects()[0].width();
//               qDebug() << ui->qwtPlot_2->visibleRegion().rects()[1].width();
//               qDebug() << ui->qwtPlot_2->visibleRegion().rects()[0].x();
//               qDebug() << ui->qwtPlot_2->visibleRegion().rects()[1].x();
               if(ui->qwtPlot_2->visibleRegion().rects()[1].x()>=ui->qwtPlot_2->visibleRegion().rects()[0].x())
               {
                ui->widget->move(ui->widget->pos().x()+(ui->qwtPlot_2->visibleRegion().rects()[1].width()-plotRectBasicWidth), ui->widget->pos().y());
                plotRectBasicWidth = ui->qwtPlot_2->visibleRegion().rects()[1].width();
               }
               else
               {
//                qDebug() << "here we are";
                ui->widget->move(ui->widget->pos().x()+(ui->qwtPlot_2->visibleRegion().rects()[1].width()-plotRectBasicWidth) - ui->qwtPlot_2->visibleRegion().rects()[0].width(), ui->widget->pos().y());
                plotRectBasicWidth = ui->qwtPlot_2->visibleRegion().rects()[1].width()- ui->qwtPlot_2->visibleRegion().rects()[0].width();
//                qDebug() << ui->widget->pos().x();

               }
               // rectQty = ui->qwtPlot_2->visibleRegion().rectCount();
           }
           else if(ui->qwtPlot_2->visibleRegion().rectCount()==3)//and here Ktulhu too
           {

               ui->widget->move(ui->widget->pos().x()+(ui->qwtPlot_2->visibleRegion().rects()[2].width()-ui->qwtPlot_2->visibleRegion().rects()[1].width()-plotRectBasicWidth), ui->widget->pos().y());
               plotRectBasicWidth = ui->qwtPlot_2->visibleRegion().rects()[2].width() - ui->qwtPlot_2->visibleRegion().rects()[1].width();
               //rectQty = ui->qwtPlot_2->visibleRegion().rectCount();
           }
//           qDebug() << ui->widget->pos().x()+ui->widget->width();
//           qDebug() << plotRectBasicWidth;
//           qDebug() << ui->qwtPlot_2->visibleRegion().rectCount();
//           qDebug() << ui->widget->pos();
       //}
  // return false;
    return QMainWindow::eventFilter(target, event);
}


void MainWindow::moveMapMarker(long int globalPosition)
{
   // qDebug()<< position;
    if(globalPosition>=pointsQuantity)globalPosition=pointsQuantity-1;
    if(globalPosition < 0)globalPosition = 0;
    int position = getClosestToPositionIndex(globalPosition);
    qDebug() << position;
   // //qDebug()<< "position is" << position;
    timeScale->currentIndex = globalPosition;
    ui->actionPrint->setEnabled(true);
   // verticalMapMarker->hide();

    verticalMapMarker->setValue(globalPosition,0);
    currentTimeMarker->setValue(globalPosition,0);
    QDateTime tmpDate=QDateTime::fromTime_t(timeArray[position]);
    QwtText tmpTitle;

    if(tmpDate.date()!=AxisLabelDate.date())
    {
        tmpTitle = tmpDate.date().toString("dd.MM.yyyy");
        QFont tmpFont;
        tmpFont.setBold(false);
        tmpTitle.setFont(tmpFont);
        ui->qwtPlot_2->setAxisTitle(QwtPlot::xBottom,tmpTitle);

        AxisLabelDate = tmpDate;
    }

    double magnifiedVal = upPlotMagnifier(globalMagnifyFactor);

    int tmpCounter=0;
//    for(int i =0; i <varCounter; i++ )
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
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

//    for(int i = 0; i<varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
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

            if(newTmiInterp->TInterpItemArray[i+2].mask_)
            {
                char tmpArr[10];
                //QString tmpString = tmp.toString();
                sprintf(tmpArr,"%.1f",thermo[i]->value());
                thermo[i]->setToolTip(tmpArr);
                valueLabel[i]->setText(tmpArr);
            }

            //tmpString.sprintf("%f");

           //thermo[i]->value();
            else
            {
                thermo[i]->setToolTip(tmp.toString());
                valueLabel[i]->setText(tmp.toString());
            }
        }
    }

 // verticalMapMarker->show();
//    ui->qwtPlot_2->canvas()->setPaintAttribute(QwtPlotCanvas::BackingStore,true);
//    ui->qwtPlot->canvas()->setPaintAttribute(QwtPlotCanvas::BackingStore,true);
//    ui->qwtPlot_2->canvas()->setPaintAttribute(QwtPlotCanvas::Opaque,false);
//    ui->qwtPlot->canvas()->setPaintAttribute(QwtPlotCanvas::Opaque,false);
    ui->qwtPlot->replot();
    ui->qwtPlot_2->replot();

}



void MainWindow::initiateThermos()
{
    QPalette thermoPalette;

//    for(int i = 0; i<varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {
//        if(!i)
//        {
//            QPushButton *collapseAllButton = new QPushButton(this);
//            QLabel *collapseAllLabel = new QLabel (this);
       // ui->checkBox->
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
                ////qDebug() << i;
                buttonIndex = i;
                connect(axisButton[buttonIndex],SIGNAL(clicked()),this,SLOT(indexChanged()));
                connect(axisButton[buttonIndex],SIGNAL(released()),this, SLOT(hideAxis()));
                thermoPalette.setColor(QPalette::ButtonText, colors[i] );
                //qDebug() << thermoPlotMaxs[i];
                //qDebug() << thermoPlotMins[i];
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
   // //qDebug() << QObject::sender();

    QObject * tmp = sender();
//    for(int i = 0; i<varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {
        if(tmp==axisButton[i])index=i;
    }
    ////qDebug() << index ;
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
            //qDebug()<< getOffsetValue(index);
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

//    delete ui;
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
//    for(int i = 0; i<varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {
        if(isAxisHidden[i])hiddenCounter++;
        if(hiddenCounter>=notHiddenIndex)isAxisHidden[i]=true;
    }
//    for( index =0; index< varCounter;index++)
    for(int index = 0 ; index < invisibleVarsMask.size(); index++)
        if(!invisibleVarsMask[index])
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
//    for(int i = 0; i < varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {
        thermoPlotMins[i] = 0;
       //float  tmpMinFloat = newTmiInterp->TInterpItemArray[i+1].min/pow(10,newTmiInterp->TInterpItemArray[i+1].mask_);
       // thermoPlotMins[i] = (int)tmpMinFloat;
      //  //qDebug() << thermoPlotMins[i];
    }
//    for(int i = 0; i < varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {
//        float tmpMaxFloat = newTmiInterp->TInterpItemArray[i+2].max/pow(10,newTmiInterp->TInterpItemArray[i+2].mask_);
//        thermoPlotMaxs[i] = (int)tmpMaxFloat;
        if(thermoPlotMaxs[i]<1)thermoPlotMaxs[i]=1;
      //  //qDebug() << thermoPlotMaxs[i];
    }
//    for(int i = 0; i < varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {
        if(i<axisCount)
            isAxisHidden[i] = false;
        else
            isAxisHidden[i] = true;
    }

//    for(int i = 0; i < varCounter;i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {
      //  parLabel[i] = new QString;
        if(newTmiInterp->TInterpItemArray[i+2].typ==8)
        {
            flagArray[i]=1;
          //  flagCounter++;
        }
        else flagArray[i] = 0;
        parLabel[i] = QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i+2].name);// = QString::fromLocal8Bit();
        parLabel[i].replace("[","(");
        parLabel[i].replace("]",")");
      //  //qDebug()<< parLabel[i];
    }
//    //qDebug() << "flag count:";
//qDebug() << flagCounter;
}

//void MainWindow::closeEvent(QCloseEvent *event)
//{
////    event->ignore();
//////    closeLog();
//////    closeLog();
//////    this->deleteLater();
////    //QCoreApplication::quit();
////    if(isOpened)
////    {


////        this->closeLog();
////    }
////    QApplication::quit();
////    openNewMainWindow();
////    this->deleteLater();
////    event->ignore();
//}

void MainWindow::on_actionOpen_triggered()
{
    if(!isOpened)
    {
            openLog();
    }
    else
   {

        isOpened=false;
//        delete X;
//        for(int i =0; i < varCounter; i++)delete Y[i];
//        this->closeLog();
//        for(int i = 0; i < varCounter; i++)
//            if(!flagArray[i])
//            {
//                buttonIndex = i;
//                disconnect(axisButton[buttonIndex],SIGNAL(clicked()),this,SLOT(indexChanged()));
//                disconnect(axisButton[buttonIndex],SIGNAL(released()),this, SLOT(hideAxis()));
//            }
//        disconnect(ui->checkBox,SIGNAL(toggled(bool)),this,SLOT(showAllCurves()));
//        disconnect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(increaseMagnifyFactor()));
//        disconnect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(decreaseMagnifyFactor()));
////        QObject::disconnect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
////                         this, SLOT(setValue(int&, QString&, QVariant&, int)));
//        disconnect(mapTimer, SIGNAL(timeout()),this,SLOT(incrementMarkerPosition()));
//        qApp->closeAllWindows();
//        qApp->quit();



//        closeLog();
        openNewMainWindow();
         this->close();
//        this->close();

//        this->deleteLater();

//        this->hide();
//        QApplication::quit();
//        qDebug() << this->children();



//        this->hide();
//       delete ui;

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
//    //qDebug() << tmpList;
//    qDeleteAll(tmpList.begin(), tmpList.end());
//    tmpList.clear();
//    ////qDebug() << tmpList;
    //qDeleteAll
//    QIt tmp = tmpList.begin();
//    while (tmp!=tmpList.end())
//    {
//        QObject *item = *tmpList;
//        delete item;
//    }
    delete parLabel;
    free(timeScale->timeArr);
    delete checkBox;
            for(int i = 0; i < varCounter; i++)
                if(!flagArray[i])
                {
                    buttonIndex = i;
                    disconnect(axisButton[buttonIndex],SIGNAL(clicked()),this,SLOT(indexChanged()));
                    disconnect(axisButton[buttonIndex],SIGNAL(released()),this, SLOT(hideAxis()));
                }
            disconnect(ui->checkBox,SIGNAL(toggled(bool)),this,SLOT(showAllCurves()));
            disconnect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(increaseMagnifyFactor()));
            disconnect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(decreaseMagnifyFactor()));
    //        QObject::disconnect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
    //                         this, SLOT(setValue(int&, QString&, QVariant&, int)));
            disconnect(mapTimer, SIGNAL(timeout()),this,SLOT(incrementMarkerPosition()));
    free(X);// X;
//    for(int i =0; i < varCounter; i++)
    free(Y);
    free(powOnTimeArray);
    free(timeFract);
    free(dateChangedArr);
    newLogProc->tmpFile.close();
//    this->deleteLater();
    delete newLogProc;
    delete timeScale;
//    delete curve2;
//    delete curve1;
    delete timeArray;
    delete thermoPlotMaxs;
    delete mapTimeScale;
    delete timeScale;
    delete flagMarker;
    delete newTmiInterp;
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
              // ui->tableWidget->setEnabled(true);
                   ui->actionPrint->setEnabled(true);
                       ui->actionOpen->setEnabled(true);
                           ui->scrollArea->setEnabled(true);
                               ui->pushButton->setEnabled(true);
                                   ui->pushButton_2->setEnabled(true);
                                       ui->pushButton_3->setEnabled(true);
                                           ui->pushButton_4->setEnabled(true);

    if(checkFileHeaderCRC())
    {
        newLogProc->tmpFile.close();
        isOpened=false;
        openNewMainWindow();
        this->close();
     }
    else
    {

    readHeadTableData();

    if(readDataFromLog())
        {
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
    }
}
void MainWindow::initiateRadios()
{
//    for(int i = 0; i<varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
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
                ////qDebug() << i;
                buttonIndex = i;
               // //qDebug() << (int)Y[i][0];
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
    ui->checkBox->setEnabled(true);
//    ui->tableWidget->setEnabled(true);
    connect(ui->checkBox,SIGNAL(toggled(bool)),this,SLOT(showAllCurves()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(increaseMagnifyFactor()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(decreaseMagnifyFactor()));
    plotRectBasicWidth = ui->qwtPlot_2->visibleRegion().rects()[1].width();
   // qDebug() << plotRectBasicWidth;
   // connect(ui->checkBox, SIGNAL(clicked(bool)),this,SLOT(collapseAllCurves()));
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

    double tmpOffset;
    tmpOffset = (thermoPlotMaxs[0]/flagCounter)/4;
    double tmpGain;
     double tmpMax;
     double tmpMin=0;
     if(thermoPlotMaxs[0]<10)
     {
         if(thermoPlotMaxs[0]<=1)
         {
             tmpMax = 0.6;
             tmpMin = -0.6;
         }
       else  tmpMax=10;
     }
     else
     {
          if((int)thermoPlotMaxs[0]%10!=0)
            {
            if(thermoPlotMaxs[0]>1)
                tmpMax = (int)((thermoPlotMaxs[0]*10 +10)/10);
            }
        else tmpMax = thermoPlotMaxs[0];
    }
    tmpGain = (double)(tmpMax-tmpMin)/(flagCounter*2 -1);
    flagMarkerIncStep = tmpGain*2;
    tmpOffset = tmpGain/2 + tmpMin;
    flagMarkerOffsetBase = tmpOffset;
    for(int i = 0; i < flagIndex; i++)
    {
        if(flagArray[i])
        {
            tmpOffset+=flagMarkerIncStep;
        }
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
            ////qDebug() << paramValue.toString();
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
//        for (int i = 0; i < varCounter; i++)
        for(int i = 0 ; i < invisibleVarsMask.size(); i++)
            if(!invisibleVarsMask[i])
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
      // //qDebug() << pf->returnFromTime();
      // //qDebug() << pf->retutnToTime();
       convertTimeToPosition(pf->returnFromTime(),pf->retutnToTime());
      // //qDebug() << ui->tableWidget->verticalHeaderItem(0)->text();
       report = new QtRPT(this);
       QFileDialog dialog(this);
       //QString fileName = dialog.getOpenFileName(this,"Открыть файл лога регистратора", "c:","Выберите файл (*.*)");;
       QString fileName = "ascumarm_05_09_13.xml";
       report->recordCount << printRightTimeIndex - printLeftTimeIndex;
       if (report->loadReport(fileName) == false) {
           //qDebug()<<"Report's file not found";
       }
       else
       {
      //     //qDebug()<<"File found processing";
      //     //qDebug()<<fileName;
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
//    bool error1, error2;
    for(int i = 0; i < sizeOfArray; i++)
    {
        if(firstTime.toTime_t()<=timeArray[i])
        {
            printLeftTimeIndex = i;
            i=sizeOfArray;
        }

    }
  //  //qDebug() << printLeftTimeIndex;
    for(int i = printLeftTimeIndex; i < sizeOfArray; i++)
    {
        if(secondTime.toTime_t()<=timeArray[i])
        {
            printRightTimeIndex = i;
             i=sizeOfArray;
        }

    }
 //   //qDebug()<<printRightTimeIndex;
}

double MainWindow::upPlotMagnifier(int factor)
{
    if(factor>200) factor=200;
    if(factor<0)factor=0;
    double magVal = exp((double)factor/25);
    magVal=round(magVal);
    if(magVal>3000)magVal=3000;
    if(magVal<0)magVal = 0;
    ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom,-magVal+currentTimeMarker->value().x(),magVal+currentTimeMarker->value().x(),1);
    int tmpCounter=0;
//    for(int i =0; i < varCounter; i++)
    for(int i = 0 ; i < invisibleVarsMask.size(); i++)
        if(!invisibleVarsMask[i])
    {
        if(flagArray[i])
        {
            flagMarker[i]->setValue(0.8*magVal +currentTimeMarker->value().x(),flagMarkerOffsetBase+tmpCounter*flagMarkerIncStep);
            tmpCounter++;
        }
    }
    ui->qwtPlot_2->replot();
    globalMagVal = magVal;
    QVariant tmpPercents = (int)((globalMagnifyBaseVal/magVal) *100);

    ui->label->setText(tmpPercents.toString()+"%");
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
//            int tmpOffset = ui->qwtPlot_2->width() - ui->qwtPlot_2->transform(QwtPlot::xBottom, currentTimeMarker->value().x()+upPlotMagnifier(globalMagnifyFactor));
            offset = 0;
//            //qDebug() << ui->qwtPlot_2->visibleRegion().rects()[0].width();
            //offset = tmpOffset + offset - ui->qwtPlot_2->width() ;
        }
        else
            offset = -ui->qwtPlot_2->visibleRegion().rects()[0].width();
    }
//    //qDebug() << offset;
 //   //qDebug() << ui->qwtPlot_2->width();
//    //qDebug() << ui->qwtPlot_2->visibleRegion();
//    //qDebug() << ui->qwtPlot_2->visibleRegion().rects()[0].width();
    return offset;
}

bool MainWindow::isCursorPositionOnDownPlot()
{
    int windowXpos= ui->qwtPlot->mapToGlobal(ui->qwtPlot->pos()).x();
    int cursorXPos =QCursor::pos().x();
//    int windowYpos = ui->qwtPlot->mapToGlobal(ui->qwtPlot->pos()).y();
  //  //qDebug() << windowYpos;
//    int cursorYpos = QCursor::pos().y();
//    //qDebug() << windowYpos;
//    //qDebug() << windowXpos;
//    //qDebug() <<cursorYpos;
//    //qDebug() << cursorXPos;
   // //qDebug() << ui->qwtPlot->visibleRegion();//
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
//    //qDebug() << windowYpos;
//    //qDebug() << windowXpos;
//    //qDebug() <<cursorYpos;
//    //qDebug() << cursorXPos;

    //ui->qwtPlot_2->mapToGlobal(ui->qwtPlot_2->pos()).x();
    if(((cursorXPos<(windowXpos+MainWindow::width()))&(cursorXPos>(windowXpos+ui->scrollArea->width())))&
            ((cursorYpos<(windowYpos+ui->qwtPlot_2->height()))&(cursorYpos>(windowYpos))))
        return true;
    else return false;
}

void MainWindow::cursorMoved(QPoint pos)
{
    //qDebug() << pos;
}

void MainWindow::on_qwtPlot_2_destroyed()
{

}
void MainWindow::showAllCurves()
{
    int index;
//    int hiddenCounter=0;
//    for(int i = 0; i<varCounter; i++)
//    {
//        if(isAxisHidden[i])hiddenCounter++;
//        if(hiddenCounter>=notHiddenIndex)isAxisHidden[i]=true;
//    }
//    for( index =0; index< varCounter;index++)
    for(int index = 0 ; index < invisibleVarsMask.size(); index++)
        if(!invisibleVarsMask[index])
    {
         if(ui->checkBox->checkState())
         {
         if(isAxisHidden[index])
                {
                curve2[index]->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
                 if(!flagArray[index])
                {
                    //tmpIndex = index;
                    curve2[index]->setAxes(1,index);//this one
                    ui->qwtPlot_2->enableAxis(index,true);//and enable it

                }
                 else
                 {
                     flagMarker[index]->attach(ui->qwtPlot_2);
//                     qDebug() << flagMarker[index]->yValue();
//                     qDebug() << thermoPlotMaxs[0];
                 }


                ui->qwtPlot_2->replot();
                axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
                isAxisHidden[index] = false;
            }
         }
            else
            {
             if(!isAxisHidden[index])
             {
                curve2[index]->detach();//by default we have 1st axis with this curve on the plot, also it is enabled by default
                if(!flagArray[index])
                {
                    curve2[index]->setAxes(1,index);//this one
                    ui->qwtPlot_2->enableAxis(index,false);//and enable it
                }
                else flagMarker[index]->detach();

                ui->qwtPlot_2->replot();
                axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
                isAxisHidden[index] =true;
            }
         }
        }
    }
void MainWindow::moveMagnifyWidget()
{

}

//void MainWindow::collapseAllCurves()
//{
//    int index;

//    for( index =0; index< varCounter;index++)
//    {
//        if(!isAxisHidden[index])
//        {
//            curve2[index]->detach();//by default we have 1st axis with this curve on the plot, also it is enabled by default
//            if(!flagArray[index])
//            {
//                curve2[index]->setAxes(1,index);//this one
//                ui->qwtPlot_2->enableAxis(index,false);//and enable it
//            }

//            ui->qwtPlot_2->replot();
//            axisButton[index]->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
//            isAxisHidden[index] =true;
//        }
//    }
//}
void MainWindow::increaseMagnifyFactor()
{

    if(globalMagnifyFactor>200)globalMagnifyFactor = 200;
     if(globalMagnifyFactor<0)globalMagnifyFactor = 0;
     globalMagnifyFactor++;
    upPlotMagnifier(globalMagnifyFactor);
}

void MainWindow::decreaseMagnifyFactor()
{

     if(globalMagnifyFactor>200)globalMagnifyFactor = 200;
     if(globalMagnifyFactor<0)globalMagnifyFactor = 0;
      globalMagnifyFactor--;
   //   qDebug()<<globalMagnifyFactor;
    upPlotMagnifier(globalMagnifyFactor);

}

void MainWindow::getPointsQuantity(time_t firstTime, time_t lastTime)
{
    pointsQuantity = firstTime - lastTime;
    qDebug() << pointsQuantity;
}

int MainWindow::getClosestToPositionIndex(int pos)
{
//    qDebug() << pos;
//    qDebug() << (int)endOfLogTime;
//     qDebug() << (int) timeArray[0];
//      qDebug() << (int)timeArray[sizeOfArray-2];
    for (int i = 0; i < sizeOfArray; i++) //pointsQuantity - is a variable that discribes how many points should be on plot
    {
        qDebug() << (int)((int)endOfLogTime - (int)timeArray[i]);
        if((int)timeArray[i]-(int)timeArray[0] >pos)
        return i-1;


    }
    return -1;
}
