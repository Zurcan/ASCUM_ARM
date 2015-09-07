#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "QtXmlPatterns/"
/*
PowON
PowOFF
PowOnTime
DateChg
 */
//
QRect tmpRect;
int errorPicker::getClosestToPosIndex(int pos) const
{
    int incval = 0;
    for (int i = 0;  i < sizeOfArr; i++) //pointsQuantity - is a variable that discribes how many points should be on plot
    {
        if(i!=0)
        {
            if(errDesc[i].time==errDesc[i-1].time)
                incval++; //incval is quantity of multipoints at same time
        }
        if((int)errDesc[i].time - (int)errDesc[0].time > pos-incval)
        {
            if(i>1)
            {
                for(int j = i; j > 0; j--)
                {
                    if(errDesc[j].time- (int)errDesc[0].time  <= pos-incval)
                    {
                        return j;
                    }
                    if(errDesc[j].time==errDesc[j-1].time)
                        incval--;
                }
            }
            else return i-1;
        }
    }
    return -1;
}

void errorPicker::initArrs(int arrsize)
{

}

void errorPicker::cleanBeforeClose()
{
    errDesc.clear();
}

QString errorPicker::errorDecoder(int errorCode) const
{
    unsigned short aggregate;
    unsigned char detailer;
    unsigned char occurenceCount;
    QString text=" ";
    aggregate = (unsigned short)((errorCode>>16)&(0x0000ffff));
    switch (aggregate)
    {
        case 0x00000001:
                        {
                            text.append("hReverseCyl_Unlock ");
                            break;
                        }
        case 0x00000002:
                        {
                            text.append("hReverseCyl_Forward ");
                            break;
                        }
        case 0x00000003:
                        {
                            text.append("hReverseCyl_Backward ");
                            break;
                        }
        case 0x00000004:
                        {
                            text.append("hReverseCyl_Neuthral ");
                            break;
                        }
        case 0x00000005:
                        {
                            text.append("hSlowMoveCyl_Motor ");
                            break;
                        }
        case 0x00000006:
                        {
                            text.append("hSlowMoveCyl_Unlock ");
                            break;
                        }
        case 0x00000007:
                        {
                            text.append("hSlowMoveCtrl_DriveFwd ");
                            break;
                        }
        case 0x00000008:
                        {
                            text.append("hSlowMoveCtrl_DriveBwd ");
                            break;
                        }
        case 0x00000009:
                        {
                            text.append("hAir_TankPressure ");
                            break;
                        }
        case 0x0000000A:
                        {
                            text.append("hAirBrake_BrakeCyl ");
                            break;
                        }
        case 0x0000000B:
                        {
                            text.append("hAirBrake_BrakeWay ");
                            break;
                        }
        case 0x0000000C:
                        {
                            text.append("hAirBrake_PressuredWay ");
                            break;
                        }
        case 0x0000000D:
                        {
                            text.append("hBoardVoltageMeasure ");
                            break;
                        }
        case 0x0000000E:
                        {
                            text.append("hDirrection ");
                            break;
                        }
        case 0x0000000F:
                        {
                            text.append("hCAN ");
                            break;
                        }
        case 0x00000010:
                        {
                            text.append("hCtrlPnl1_SelectCtrlPnl ");
                            break;
                        }
        case 0x00000011:
                        {
                            text.append("hFuelPump ");
                            break;
                        }
        case 0x00000012:
                        {
                            text.append("hAltivarRotControl ");
                            break;
                        }
        case 0x00000013:
                        {
                            text.append("hGenerator_SwMech ");
                            break;
                        }
        case 0x00000014:
                        {
                            text.append("hHydraPump_SwMech ");
                            break;
                        }
        case 0x00000015:
                        {
                            text.append("hSlowPump_SwMech ");
                            break;
                        }
        case 0x00000016:
                        {
                            text.append("hSlowDrive_SwMech ");
                            break;
                        }
        case 0x00000017:
                        {
                            text.append("hEngine_RPMctrl ");
                            break;
                        }
        case 0x00000018:
                        {
                            text.append("hTransmission_Control ");
                            break;
                        }
        case 0x00000019:
                        {
                            text.append("hWorkModeSpeed ");
                            break;
                        }
        case 0x0000001A:
                        {
                            text.append("hMainTnk1_FuelLevel ");
                            break;
                        }
        case 0x0000001B:
                        {
                            text.append("hMainTnk2_FuelLevel ");
                            break;
                        }
        case 0x0000001C:
                        {
                            text.append("hHydraPumpCtrl_Neuthral ");
                            break;
                        }
        case 0x0000001D:
                        {
                            text.append("hHydraPumpCtrl_KMU ");
                            break;
                        }
        case 0x0000007F:
                        {
                            text.append("hSELF ");
                            break;
                        }
        case 0x00000102:
                        {
                            text.append("aForwardSet ");
                            break;
                        }
        case 0x00000103:
                        {
                            text.append("aBackwardSet ");
                            break;
                        }
        case 0x00000104:
                        {
                            text.append("aNeutralSet ");
                            break;
                        }
        case 0x00000105:
                        {
                            text.append("aSlowMotorOn ");
                            break;
                        }
        case 0x00000106:
                        {
                            text.append("aSlowMotorOff ");
                            break;
                        }
        case 0x00008000:
                        {
                            text.append("MRK_CONDITION_END ");
                            break;
                        }
        case 0x00000200:
                        {
                            text.append("cNoCanPeripheral ");
                            break;
                        }
        case 0x00000201:
                        {
                            text.append("cNoPeripheral ");
                            break;
                        }
        case 0x00000202:
                        {
                            text.append("cNoPeripheralBlink ");
                            break;
                        }

    }
    detailer = (unsigned char)((errorCode>>8)&(0x000000ff));
    switch (detailer)
    {
        case 0x01:
                    {
                        text.append(" dFBSNoSignal ");
                        break;
                    }
        case 0x02:
                    {
                        text.append(" dFBSShortedToMinus ");
                        break;
                    }
        case 0x03:
                    {
                        text.append(" dFBSShortedToPlus ");
                        break;
                    }
        case 0x04:
                    {
                        text.append(" dFBSDisconnected ");
                        break;
                    }
        case 0x05:
                    {
                        text.append(" dFBSLowerMin ");
                        break;
                    }
        case 0x06:
                    {
                        text.append(" dFBSHigherMax ");
                        break;
                    }
        case 0x41:
                    {
                        text.append(" dFBSOnNoSignal ");
                        break;
                    }
        case 0x42:
                    {
                        text.append(" dFBSOnShortedToMinus ");
                        break;
                    }
        case 0x43:
                    {
                        text.append(" dFBSOnShortedToPlus ");
                        break;
                    }
        case 0x44:
                    {
                        text.append(" dFBSOnDisconnected ");
                        break;
                    }
        case 0x4E:
                    {
                        text.append(" dFBSOnOffUndefined ");
                        break;
                    }
        case 0x4F:
                    {
                        text.append(" dFBSOnOffSimultaneousError ");
                        break;
                    }
        case 0x51:
                    {
                        text.append(" dFBSOffNoSignal ");
                        break;
                    }
        case 0x52:
                    {
                        text.append(" dFBSOffShortedToMinus ");
                        break;
                    }
        case 0x53:
                    {
                        text.append(" dFBSOffShortedToPlus ");
                        break;
                    }
        case 0x54:
                    {
                        text.append(" dFBSOffDisconnected ");
                        break;
                    }
        case 0x55:
                    {
                        text.append(" dFBSNoExpectedReaction ");
                        break;
                    }
        case 0x80:
                    {
                        text.append(" dactFailure ");
                        break;
                    }
        case 0x90:
                    {
                        text.append(" dCANNoEngineMain ");
                        break;
                    }
        case 0x91:
                    {
                        text.append(" dCANNoEngineService1 ");
                        break;
                    }
        case 0x98:
                    {
                        text.append(" dCANNoTransmissionMain ");
                        break;
                    }
        case 0x99:
                    {
                        text.append(" dCANNoTransmissionService1 ");
                        break;
                    }
        case 0xC0:
                    {
                        text.append(" shEEPROM_Read ");
                        break;
                    }
        case 0xC1:
                    {
                        text.append(" shEEPROM_Write ");
                        break;
                    }
        case 0xC2:
                    {
                        text.append(" shEEPROM_Integrity ");
                        break;
                    }
        case 0xC3:
                    {
                        text.append(" shSETUP_Integrity ");
                        break;
                    }
        case 0xC4:
                    {
                        text.append(" shCONFIG_Integrity ");
                        break;
                    }
        case 0xC5:
                    {
                        text.append(" shNVRAM_Read ");
                        break;
                    }
        case 0xC6:
                    {
                        text.append(" shNVRAM_Write ");
                        break;
                    }
        case 0xC7:
                    {
                        text.append(" shNVRAM_Integrity ");
                        break;
                    }
        case 0xC8:
                    {
                        text.append(" shNVRxM_DataLoss ");
                        break;
                    }
        case 0xC9:
                    {
                        text.append(" shNVRAM_Read ");
                        break;
                    }
        case 0xCA:
                    {
                        text.append(" shNVRAM_Write ");
                        break;
                    }
        case 0xCB:
                    {
                        text.append(" shNVRAM_Integrity ");
                        break;
                    }
        case 0xCC:
                    {
                        text.append(" shNVRxM_DataLoss ");
                        break;
                    }
        case 0xCD:
                    {
                        text.append(" shUSB_BKS ");
                        break;
                    }
        case 0xCE:
                    {
                        text.append(" shFLASH_Stg_WR ");
                        break;
                    }
        case 0xCF:
                    {
                        text.append(" shFLASH_Stg_DataLoss ");
                        break;
                    }
        case 0xD0:
                    {
                        text.append(" shEEPROM_StatisticRead ");
                        break;
                    }
        case 0xD1:
                    {
                        text.append(" shEEPROM_StatisticOld ");
                        break;
                    }
        case 0xFE:
                    {
                        text.append(" shOtherFailure ");
                        break;
                    }

    }
    occurenceCount = (unsigned char)((errorCode)&(0x000000ff));
    text.append(QString::number(occurenceCount,10));
    return text;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    OldLog = false;
    globalMagnifyFactor=100;
    mapTimerDelay = 1000;
    firstFlagIndex = 0;
    globalMoveFlag=false;
    globalMagVal=100;
    globalSavedCursorMove=0;
    globalMagnifyBaseVal = 148;
    isOpened=false;
    leftButtonPressed=false;
    mapPlotUsed = false;
    rightButtonPressed = false;
    ui->setupUi(this);//
    ui->tableWidget->hide();
    pf = new PrintForm(this);
    ui->qwtPlot->enableAxis(QwtPlot::yLeft,false);
    ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
            ui->pushButton_3->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
                ui->pushButton_4->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
                ui->widget->setParent(ui->qwtPlot_2);
                ui->widget->setMouseTracking(true);
                QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
                opacityEffect->setOpacity(0.5);
                ui->widget->setGraphicsEffect(opacityEffect);
                ui->widget->setVisible(true);
     canvas = ui->qwtPlot_2->canvas();
     mapTimer = new QTimer(this);
     connect(mapTimer, SIGNAL(timeout()),this,SLOT(incrementMarkerPosition()));
     invisibleVarCounter = 0;
     tmpIcon = new QIcon(":new/p/print");
     ui->actionPrint->setIcon(*tmpIcon);
     ui->actionPrint->setEnabled(false);
     tmpIcon = new QIcon(":new/p/closeLog");
    ui->actionOpen->setIcon(*tmpIcon);
    tmpIcon = new QIcon(":new/p/hp");
    ui->actionHideLeftPanel->setIcon(*tmpIcon);
    ui->actionHideLeftPanel->setEnabled(false);
    QIcon *zoominIcon = new QIcon(":new/p/zoomin");
    QIcon *zoomoutIcon = new QIcon(":new/p/zoomout");
    ui->pushButton_5->setIcon(*zoominIcon);
    ui->pushButton_6->setIcon(*zoomoutIcon);
        ErrCurve = new QwtPlotCurve;
    delete zoominIcon;
    delete zoomoutIcon;
    delete tmpIcon;
    HideLeftArea = true;
    NoFileWasOpened = true;
    lastOpenedFileName = "";
    powOffIndex=-1;
    errCodeIndex = -1;
    errAddIndex = -1;
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
}

void MainWindow::reinit()
{
    newLogProc= new logProcessor;// (logProcessor*)malloc(sizeof(logProcessor));
    newTmiInterp = new TMIinterpretator;//(TMIinterpretator*)malloc(sizeof(TMIinterpretator));
    myMsgSys = new msgSys;
    dateChangedArrExistFlag = false;
    timeFractExistFlag = false;
    subTimeExistFlag = false;
    powOnTimeArrayExistFlag = false;
    ErrXCoords<<QVector <double>();
    ErrCoordVector<<QVector<errCoordStruct>();
    invisIntItems<<QVector <invisibleInterpItems>();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if((ui->qwtPlot_2->geometry().x()>18)&(ui->qwtPlot_2->geometry().x()<312))
    {
            QRect tmpRect = ui->qwtPlot_2->geometry();
            if(HideLeftArea)
            {
                tmpRect.setX(312);
                ui->qwtPlot_2->setGeometry(tmpRect);
                ui->scrollArea->resize(295,ui->scrollArea->size().height());
                HideLeftArea = true;
            }
            else
            {
                tmpRect.setX(18);
                ui->qwtPlot_2->setGeometry(tmpRect);
                ui->scrollArea->resize(1,ui->scrollArea->size().height());
                HideLeftArea = false;
            }
    }
    if(ui->qwtPlot_2->geometry().x()==18)
    {
        HideLeftArea = false;
        tmpIcon = new QIcon(":new/p/sp");
        ui->actionHideLeftPanel->setIcon(*tmpIcon);
    }
    if(ui->qwtPlot_2->geometry().x()==312)
    {
        HideLeftArea = true;
        tmpIcon = new QIcon(":new/p/hp");
        ui->actionHideLeftPanel->setIcon(*tmpIcon);
    }
}


int MainWindow::checkLogToBeClosed(QString nameOfOpenedFile)
{
    if(!NoFileWasOpened)
    {
        if((lastOpenedFileName == nameOfOpenedFile)&&(nameOfOpenedFile!=""))
            return 1;
        else
            if((nameOfOpenedFile==""))
                return 2;
            else
                return 0;
    }
    else
    {
        if(nameOfOpenedFile!="")
            return 0;
        else
            return 3;
    }
}

void MainWindow::openNewMainWindow()
{
  closeLog();
}

void MainWindow::globalInits(int arrayIndexSize)// here's the place to create vector of points+
{
    X = (double*)malloc((arrayIndexSize+1)*sizeOfArray*sizeof(double));
    Y[0]=X+sizeOfArray;
    for(int i =1; i <arrayIndexSize+1; i++)
    {
        Y[i]=Y[i-1]+sizeOfArray;
    }
    powOnTimeArray = (time_t*)malloc(sizeOfArray*sizeof(time_t));
    timeFract = new unsigned char[sizeOfArray];
    subTime = new unsigned int[sizeOfArray];
    dateChangedArr = (bool*)malloc((sizeOfArray*sizeof(bool)));
    for(int i = 0; i < sizeOfArray; i++)
    {
        dateChangedArr[i] = false;
    }
    ui->qwtPlot_2->setContentsMargins(0,0,-1,0);
    ui->qwtPlot_2->replot();
}

void MainWindow::initiatePlotMarkers()//we have to init all usable markers in this func
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
    currentTimeMarker->attach(ui->qwtPlot_2);
    verticalMapMarker->attach(ui->qwtPlot);
}

bool MainWindow::checkFileHeaderCRC()
{
    newLogProc->selectLogFile(filename);
    int tmpSegCount = newLogProc->getSegmentsCount();
    newLogProc->checkSegmentsExistance();
    newLogProc->readFileHeader();
    unsigned long CRCtmpFH = 0;
    newLogProc->tmpFile.seek(0);
    newLogProc->tmpFile.read(tmpFHPtr,SIZE_OF_FILEHEADER);
    tmpFHPtr[32]=SIZE_OF_FILEHEADER;
    tmpFHPtr[33]=0;
    tmpFHPtr[34]=0;
    tmpFHPtr[35]=0;
    tmpFHPtr[36]=0;
    tmpFHPtr[37]=0;
    tmpFHPtr[38]=0;
    tmpFHPtr[39]=0;
    CRCtmpFH = newLogProc->CRC32updater(tmpFHPtr,SIZE_OF_FILEHEADER,0xffffffff);
    CRCtmpFH = CRCtmpFH^0xffffffff;
    if(tmpSegCount==4)
        OldLog = true;
    for(int segCount = 0; segCount < tmpSegCount; segCount++)
    {
        long tmpID = newLogProc->setTmpID();
        newLogProc->selectSegment(tmpID);
        newLogProc->logDataPointer+=newLogProc->segmentHeader.size;
        CRCtmpFH = CRCtmpFH^newLogProc->segmentHeader.CRC32;
    }
    if(CRCtmpFH!=newLogProc->fileHeader.selfCRC32)
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
        newMessage.exec();
        return false;
    }
    return true;
}

void MainWindow::readHeadTableData()//here we read head table - its header and its data
{
    int tmpErr = 0;
    for(int i = 0; i < newLogProc->segIDs.size(); i++)
    {

    }
    if(newLogProc->fileHeader.fileSize != newLogProc->tmpFile.size())//check file size
    {
        newMessage.setWindowTitle("Ошибка!");
        newMessage.setText("Файл журнала регистратора поврежден.");
        newMessage.exec();
    }
    if(!OldLog)
    {
        tmpErr = newLogProc->selectSegment(localizationTableID);
        char tmpBuff[newLogProc->segmentHeader.size];
        newLogProc->readSegment(tmpBuff, sizeof(tmpBuff));
        myMsgSys->parseMessages(tmpBuff);
        if(tmpErr!=0)
        {
//            QVariant tmp2=tmpErr;
//            newMessage.setWindowTitle("Ошибка!");
//            newMessage.setText("Файл журнала регистратора поврежден."+tmp2.toString());
//            newMessage.exec();
        }
    }
    tmpErr = newLogProc->selectSegment(smallTableID);
    if(tmpErr==0)
    {
        ui->tableWidget->show();
          /*
           *At this point we have calculated CRC of head table segment interpretator, and datapointer
           *pointed to the interpreter, but not to its header, so we can get from interpreter names of head
           */
        char buffArr1[newLogProc->segmentHeader.size];
                newLogProc->readSegment(buffArr1, newLogProc->segmentHeader.size );
                newTmiInterp->interpreterRecordsCount=newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
                newTmiInterp->setInterpretationTable(buffArr1,newTmiInterp->interpreterRecordsCount);
                for(int i =0; i <newTmiInterp->interpreterRecordsCount; i++)//naming  summary table headers
                {
                    if((newTmiInterp->TInterpItemArray[i].level!=0)&(ui->tableWidget->rowCount()>i))
                    {
                            verticalHeaderName = QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name);
                            ui->tableWidget->verticalHeaderItem(i-1)->setText(verticalHeaderName);
                    }
                }
               /*
                *from here we start to processing data from small table, filling small table
                */
                  if(newLogProc->selectSegment(smallTableID&0x7fffffff))
                  {
                      QVariant tmpVal = tmpErr;
                      newMessage.setWindowTitle("Ошибка!");
                      newMessage.setText("Файл журнала регистратора поврежден. " + tmpVal.toString());
                      newMessage.exec();
                  }
                            QString tmpField = " ";
                            int tmpRecI = 0;
                            QVariant recFloat;
                            newLogProc->readRecord(newLogProc->segmentHeader.recordSize, newLogProc->segmentHeader.size, newLogProc->logDataPointer);
                            for (int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)
                            {
                                tmpRecI=newTmiInterp->TInterpItemArray[i].offset;
                                if((newTmiInterp->TInterpItemArray[i].level)&(ui->tableWidget->rowCount()>i))
                                {
                                    switch(newTmiInterp->TInterpItemArray[i].typ)
                                    {
                                            case 34 :
                                            {
                                                double tmpDbl;
                                                tmpDbl = newTmiInterp->fieldDouble(&newLogProc->record[tmpRecI]);
                                                QVariant tmpVal = tmpDbl;
                                                tmpField = tmpVal.toByteArray();
                                                break;
                                            }

                                            case 7:
                                            {
                                                float tmpFloat, tmpMinFloat, tmpMaxFloat;
                                                int tmpIntFloat;
                                                tmpFloat = newTmiInterp->fieldFloat(&newLogProc->record[tmpRecI]);
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
                                    if(i>0)
                                        ui->tableWidget->setItem(i-2, 1, tmpItem );
                                }
                            }
    }
    else
    {
//        newMessage.setWindowTitle("Ошибка!");
//        const QChar tmpec = smallTableID&0x7fffffff;
//        newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден. Ошибка сегмента"+QString::fromRawData(&tmpec,8));
//        newMessage.exec();
//        isOpened=false;
//        openNewMainWindow();
        ui->tableWidget->hide();
    }

    tmpErr = newLogProc->selectSegment(camOffsetID);//now entering camoffset segment
    if(tmpErr==0)
    {
        char buffArr1[newLogProc->segmentHeader.size];
                newLogProc->readSegment(buffArr1, newLogProc->segmentHeader.size );
                newTmiInterp->interpreterRecordsCount=newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
                newTmiInterp->setInterpretationTable(buffArr1,newTmiInterp->interpreterRecordsCount);
               /*
                *from here we start to processing data from camOffsets
                */
                  if(newLogProc->selectSegment(camOffsetID&0x7fffffff))
                  {
                      QVariant tmpVal = tmpErr;
                      newMessage.setWindowTitle("Ошибка!");
                      newMessage.setText("Файл журнала регистратора поврежден. " + tmpVal.toString());
                      newMessage.exec();
                  }
                  int tmpRecI = 0;
                  newLogProc->readRecord(newLogProc->segmentHeader.recordSize, newLogProc->segmentHeader.size, newLogProc->logDataPointer);
                  for (int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)
                  {
                      tmpRecI=newTmiInterp->TInterpItemArray[i].offset;
                  }
    }

}



bool MainWindow::readDataFromLog()//and now we're reading all the data from our log
{

    double flagOffset=0;
//    int tmpLogDataPointer =0;
    long tmpErr = newLogProc->selectSegment(bigTableID);//at first we have to read interpreter of bigTable
    QString tmpMsgText;
    QString tmpMsgHint;
    QVector <int> zeros;
    int zeroiterator = 0;
    char *tmpType;
    if(myMsgSys->findMessage(0x88)==0x88)
        if(myMsgSys->findMessage(0x88,tmpType,&tmpMsgText, &tmpMsgHint))
        {

        }
    if(tmpErr==0)/* if segment is chosen then lets parse it and don't forget that firstly we get it header also segment with ID begins from 0x8 - is only data interpreter */
      {
       /*
       *At this point we have calculated CRC of head table segment interpretator, and datapointer
       *pointed to the interpreter, but not to its header, so we can get it from interpreter names of head
       *this part is used to get names of records with certain names, that should be shown on small plot
       *also we're filling here an invisibleVarsMask vector
       *       static const char vUInt8            =0;                             //byte unsigned
       static const char vInt8             =1;                             //byte signed
       static const char vInt16            =2;                             //word signed
       static const char vUInt16           =3;                             //word unsigned
       static const char vInt32            =4;                             //double word signed
       static const char vFract8           =5;                             //numeric similiar as 25.5. Precision assigned by mask.
       static const char vFract16          =6;                             //numeric similiar as 6553.5. Precision assigned by mask.
       static const char vFloat            =7;                             //numeric float
       static const char vFlag             =8;                             //flag.1bit. Setting by mask
       static const char vList             =9;                             //optional element
       static const char vTime             =10;                            //time.32bit.Variable of time
       static const char vProc             =11;                            //subprogram
       static const char vAdjustProc       =12;                            //subprogram, executing with data, has a preamble as submenu
       static const char vSub              =13;                            //submenu
       static const char vString           =14;                            //string up to 255 symbols
       static const char vHString          =15;                            //hidden string
       static const char vText             =16;                            //multi-string text
       static const char vFlag8            =17;                            //flag
       static const char vFlag16           =18;                            //flag
       static const char mUnit             =19;                            //measurement units
       static const char vSettingsProc     =20;                            //procedure of settings adjust processing
       */
        char* buffArr = (char*)malloc(newLogProc->segmentHeader.size);
        newLogProc->readSegment(buffArr, newLogProc->segmentHeader.size );
            newTmiInterp->interpreterRecordsCount=newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
            newTmiInterp->setInterpretationTable(buffArr,newTmiInterp->interpreterRecordsCount);
            invisibleInterpItems invii;
            pointerToSpd = 0;
            pointerToEng1Spd=0;
            for (int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)// creating invisibleVarsMask vector here
            {
                invii.invisibility = true;
                invii.interpIndex = i;
                if((newTmiInterp->TInterpItemArray[i].level==1)||(newTmiInterp->TInterpItemArray[i].level==2))
                {
                    if((char)(newTmiInterp->TInterpItemArray[i].typ)==4)
                    {
                        if(pointerToSpd==0)
                            pointerToSpd = i;
                        invii.invisibility = false;
                    }
                    else if((char)(newTmiInterp->TInterpItemArray[i].typ&0xffff)==3)//
                    {
                        if(pointerToSpd==0)
                            pointerToSpd = i;
                        invii.invisibility = false;
                    }
                    else if((char)(newTmiInterp->TInterpItemArray[i].typ)==0)
                    {
                        if(pointerToSpd==0)
                            pointerToSpd = i;
                        invii.invisibility = false;
                    }
                    else if((char)(newTmiInterp->TInterpItemArray[i].typ&0xffff)==10)
                    {
                        int zeroCounter=0;//this code needs to understand which of times has corresponding name length
                        for(int a = 0; a < sizeof(newTmiInterp->TInterpItemArray[i].name); a++)
                        {
                            if(newTmiInterp->TInterpItemArray[i].name[a]==0)
                                zeroCounter++;
                        }
                        zeros.append(zeroCounter);
                        invii.invisibility = true;
                    }
                    else if(((char)(newTmiInterp->TInterpItemArray[i].typ&0xffff)==7))
                    {
//                        if(QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name) == "Скорость [км/ч]")
//                        {
                        if((pointerToEng1Spd==0)&(pointerToSpd!=0))
                           pointerToEng1Spd = i;
                         if(pointerToSpd==0)
                            pointerToSpd = i;

//                        }
//                        else if(QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name) == "Двигатель.обороты [об/мин]")
//                        {
//                            pointerToEng1Spd = i;
//                        }
                        invii.invisibility = false;
                    }
                    else if((char)(newTmiInterp->TInterpItemArray[i].typ&0xffff)==34)
                    {
                        if((pointerToEng1Spd==0)&(pointerToSpd!=0))
                           pointerToEng1Spd = i;
                        if(pointerToSpd==0)
                            pointerToSpd = i;//
                         if(QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name) == "Скорость [км/ч]")
                         {
                             pointerToSpd = i;
                         }
                         if(QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name) == "Двигатель.обороты [об/мин]")
                         {
                             pointerToEng1Spd = i;
                         }
                         invii.invisibility = false;
                    }
                    else if(/*((char)(newTmiInterp->TInterpItemArray[i].typ)==34)|*/((char)(newTmiInterp->TInterpItemArray[i].typ)==8))
                    {
                        QString tmpString,cuttenStr;
                        QVariant tmp = newTmiInterp->TInterpItemArray[i].name;
                        if(firstFlagIndex==0)
                            firstFlagIndex = i;
                        tmpString = tmp.toString();
                        for(int a = 0; a < tmpString.size(); a++)
                            if((QChar)(tmpString.at(a))!=32)// searching for gaps in tmpString, if symbol isn't gap appending it to cuttenStr
                            {
                                QVariant tmp = tmpString.at(a);
                                cuttenStr.append(tmp.toString());
                            }
                            if((cuttenStr == "LAR_Speed"))
                            {
                                pointerToSpd = i;// this is pointer to Speed, we need it to show in down plot
                            }
                            if(cuttenStr=="LAR_Engine1Speed")
                                pointerToEng1Spd = i;
                            if(cuttenStr=="LAR_Engine2Speed")
                                pointerToEng2Spd = i;
                            invii.invisibility = false;
                    }
                    else
                        invii.invisibility = true;
                }
                else
                {
                    invii.invisibility = true;
                }
                invisIntItems.append(invii);
            }

            for(int i =0; i < newTmiInterp->interpreterRecordsCount; i++)
            {
                    if((char)newTmiInterp->TInterpItemArray[i].typ==8)
                        if(newTmiInterp->TInterpItemArray[i].name!="ErrAdd")
                            flagCounter++;
            }
           /*
            *from here we start to processing data from small table
            */
            newLogProc->setValueLDPtr(SIZE_OF_FILEHEADER);
            long tmpErr1 = newLogProc->selectSegment(bigTableID&0x7fffffff);
            long tmpFlags = newLogProc->getSegmentFlags();
            if(tmpFlags&&0x00000001)//very important flag
                invertedTime = false;//first element in log is erliest
                if(!tmpErr1)
                    {
                        time_t recTime;
                        time_t lastTime;
                        int tmpRecordCount = newLogProc->segmentHeader.size/newLogProc->segmentHeader.recordSize;
                        sizeOfArray = tmpRecordCount;
                        globalInits(/*invisibleVarsMask.size()*/newTmiInterp->interpreterRecordsCount);
                        timeArray = (time_t*)malloc((tmpRecordCount)*sizeof(time_t));
                        ErrCode = (int *)malloc((tmpRecordCount)*sizeof(int));
                        ErrCoords = (double *)malloc((tmpRecordCount)*sizeof(double));
                        int recCounter=0;
                        int recPosition=newLogProc->logDataPointer;
                        int recPositionCompareVal = recPosition;
                        int tmpRecI = 0;
                        int tmpErrVal = 0;
                        int tmpErrLastVal = 0;
                        errCodeIndex = -1;
                        int CoordErrVal = 0;
                        int backIndex=tmpRecordCount-1;
                        for (int index = 0; index < tmpRecordCount; index++)
                        {
                            if(invertedTime)
                                backIndex = tmpRecordCount-1-index;//but there is a little shaming moment, we have to reverse data arrays because first time indeed is last one
                            else
                                backIndex = index;
                            flagOffset=0;
                            newLogProc->readRecord(tmpRecordCount,newLogProc->segmentHeader.recordSize, recPositionCompareVal);
                                 tmpRecI =0;
                                 zeroiterator = 0;
                                    for (int i = 0; i < newTmiInterp->interpreterRecordsCount; i++)
                                    {
                                        tmpRecI=newTmiInterp->TInterpItemArray[i].offset;
                                        if(newTmiInterp->TInterpItemArray[i].level==1)
                                        {
                                            switch(newTmiInterp->TInterpItemArray[i].typ&0xffff)
                                            {
                                                case 0:
                                                {
                                                    if(newTmiInterp->TInterpItemArray[i].name == "TimeFract")
                                                    {
                                                        timeFractExistFlag = true;
                                                        timeFract[backIndex] = newTmiInterp->fieldChar(&newLogProc->record[tmpRecI]);
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        Y[i/*-tmpInvisibleVarDecrease*/][backIndex] =  newTmiInterp->fieldChar(&newLogProc->record[tmpRecI]);
                                                        break;
                                                    }
                                                }
                                                case 34 ://it's double
                                                {
                                                    double tmpDbl;
                                                    tmpDbl = newTmiInterp->fieldDouble(&newLogProc->record[tmpRecI]);
                                                            Y[i/*-tmpInvisibleVarDecrease*/][backIndex] = (double)tmpDbl;
                                                            if(!index)
                                                                thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/]=(double)tmpDbl;
                                                            else if((double)tmpDbl>thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/])
                                                                thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/]=(double)tmpDbl;
                                                    break;
                                                }
                                                case 7:
                                                {
                                                    float tmpFloat, tmpMinFloat, tmpMaxFloat;
                                                    int tmpIntFloat;
                                                    tmpFloat = newTmiInterp->fieldFloat(&newLogProc->record[tmpRecI]);
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
                                                    tmpFloat = tmpIntFloat/pow(10,tmpMask);
                                                    Y[i/*-tmpInvisibleVarDecrease*/][backIndex] =  tmpFloat; //round((double)tmpFloat);
                                                    }
                                                    else
                                                    {
                                                        Y[i/*-tmpInvisibleVarDecrease*/][backIndex] =0;
                                                        tmpFloat=0;
                                                    }
                                                    if(!index)
                                                        thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/]=(double)tmpFloat;
                                                    else
                                                    if((double)tmpFloat>thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/])thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/]=(double)tmpFloat;
                                                    break;
                                                }
                                                case 10 :
                                                {
                                                    recTime = (time_t)newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                    if((newTmiInterp->TInterpItemArray[i].name!="PowOnTime"))
                                                    {
                                                        if(zeros.at(zeroiterator)!=11)
                                                        {
                                                            QString tmpname;
                                                            tmpname = newTmiInterp->TInterpItemArray[i].name;
                                                                if(index==0)
                                                                {

                                                                    lastTime = (int)recTime;
                                                                    endOfLogTime = lastTime;
                                                                }
                                                                if(invertedTime)
                                                                {
                                                                    if(index==tmpRecordCount-1)
                                                                         firstDateTime = QDateTime::fromTime_t(recTime);
                                                                }
                                                                else
                                                                {
                                                                    if(index==1)
                                                                         firstDateTime = QDateTime::fromTime_t(recTime);
                                                                }
                                                        }
                                                        else
                                                            zeroiterator++;
                                                        if(zeroiterator>zeros.size())
                                                            zeroiterator=0;
                                                        timeArray[backIndex] =recTime;//(int)((uint)recTime-(uint)firstPointDateTime);

                                                     }
                                                    else
                                                    {
                                                            timeArray[backIndex] =recTime; //qDebug << newTmiInterp->TInterpItemArray[i].name;

                                                    }
                                                            break;
                                                }
                                                case 4:
                                                {
                                                    QString tmpname;
                                                    tmpname = newTmiInterp->TInterpItemArray[i].name;
                                                    if(tmpname.remove(9,26)=="PowOnTime")
                                                    {
                                                        powOnTimeArrayExistFlag = true;
                                                        recTime = (time_t)newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                        recTime = mktime(gmtime(&recTime));
                                                        powOnTimeArray[backIndex] = recTime;//(int)((uint)recTime-(uint)firstPointDateTime);
                                                    }
                                                    else if(tmpname.remove(4,28)=="Code")
                                                    {
                                                        tmpErrVal = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                        ErrCode[backIndex] = tmpErrVal;
                                                        errCodeIndex = tmpRecI;
                                                   }
                                                    else
                                                    {
                                                        Y[i/*-tmpInvisibleVarDecrease*/][backIndex] = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                    }
                                                    break;
                                                }
                                                case 3:
                                                {
                                                    QString tmpname;
                                                    tmpname = newTmiInterp->TInterpItemArray[i].name;
                                                    if(QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name,8)=="Субвремя")
                                                    {
                                                        subTimeExistFlag = true;
                                                        subTime[backIndex] = newTmiInterp->fieldInt16(&newLogProc->record[tmpRecI]);
                                                    }
//                                                    else
                                                        Y[i/*-tmpInvisibleVarDecrease*/][backIndex] = newTmiInterp->fieldInt16(&newLogProc->record[tmpRecI]);
                                                     break;
                                                }
                                                case 8 :
                                                {

                                                    if(pointerToDateChg==i)
                                                       {
                                                                dateChangedArrExistFlag = true;
                                                                if(newTmiInterp->fieldFlag(&newLogProc->record[tmpRecI], &newTmiInterp->TInterpItemArray[i].mask_))
                                                                {
                                                                    dateChangedArr[backIndex]= 1+flagOffset; //here we forming the Y-array of flags

                                                                    Y[i/*-tmpInvisibleVarDecrease*/][backIndex]= 1+flagOffset; //here we forming the Y-array of flags
                                                                }
                                                                else
                                                                {
                                                                    dateChangedArr[backIndex]= 0+flagOffset;
                                                                    Y[i/*-tmpInvisibleVarDecrease*/][backIndex]= 0+flagOffset;
                                                                }
                                                                thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/]=1;
                                                                flagOffset+=2;
                                                        }
                                                    else
                                                        {
                                                        QString tmpname;
                                                        tmpname = newTmiInterp->TInterpItemArray[i].name;
                                                        if(newTmiInterp->fieldFlag(&newLogProc->record[tmpRecI], &newTmiInterp->TInterpItemArray[i].mask_))
                                                        {
                                                                    if(tmpname.remove(6,26)=="ErrAdd")
                                                                    {
                                                                        errAddIndex = i;
                                                                        Y[i][backIndex] = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                                    }
                                                                    else
                                                                    {
                                                                        Y[i/*-tmpInvisibleVarDecrease*/][backIndex]= 1+flagOffset; //here we forming the Y-array of flags
                                                                        thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/]=1;
                                                                        flagOffset+=2;
                                                                    }
                                                        }
                                                        else
                                                        {
                                                                    if(tmpname.remove(6,26)=="ErrAdd")
                                                                    {
                                                                        errAddIndex = i;
                                                                        Y[i][backIndex] = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                                    }
                                                                    else
                                                                    {
                                                                        Y[i/*-tmpInvisibleVarDecrease*/][backIndex]= 0+flagOffset;
                                                                        thermoPlotMaxs[i/*-tmpInvisibleVarDecrease*/]=1;
                                                                        flagOffset+=2;
                                                                    }
                                                                }
                                                         }
                                                    break;
                                                }
                                                case 27:
                                                {
                                                     tmpErrVal = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                     bool successScanFlag=false;
                                                     for(int a = backIndex; a < tmpRecordCount; a++)
                                                     {
                                                         if(!successScanFlag)
                                                         {
                                                             if(ErrCode[a]==tmpErrLastVal)
                                                             {
                                                                 ErrCoords[backIndex]=ErrCoords[a];
                                                                 successScanFlag = true;
                                                             }
                                                         }
                                                     }
                                                     if(!successScanFlag)
                                                         ErrCoords[backIndex] = CoordErrVal++;
                                                     ErrCode[backIndex]= tmpErrVal;
                                                     tmpErrVal = newTmiInterp->fieldInt(&newLogProc->record[tmpRecI]);
                                                     tmpErrLastVal = tmpErrVal;
                                                     break;
                                                 }
                                                 default:
                                                 {
                                                     break;
                                                 }
                                            }
                                        }

                                    }
                                    recCounter++;
                                    recPosition+=newLogProc->segmentHeader.recordSize;
                        }
                        qDebug() << "firstdatetime" << firstDateTime << tmpRecordCount;
                        for(int c=0; c<tmpRecordCount;c++)
                         if(!initiateTimeAxis(/*firstDateTime,*/timeArray/*,tmpRecordCount*/))
                        {
                            free(buffArr);
                            isOpened=false;
                            openNewMainWindow();
                            return false;
                        }

                }
                else
                {
                    free(buffArr);
                    isOpened=false;
                    openNewMainWindow();
                    return false;
                }
      }
    else
    {
        isOpened=false;
        openNewMainWindow();
        return false;
    }
    return true;
}

int MainWindow::createErrCoordsArray()
{
    for(int i =0 ; i < sizeOfArray; i++)
    {
        if(i ==0)
        {
            if(ErrCode[i]!=0)
                ErrCoords[0] = 1;
            else
            {
                ErrCoords[0] = 0;
            }
            maxErrCoord = ErrCoords[0]; //maxErrCoord is quantity var,actually it means how many  not zero errCodes were in array ErrCode[]
        }
        else
        {
            bool equalflag = false;
               if(ErrCode[i]==0)
                   ErrCoords[i]=ErrCoords[i-1];
               else
               {
                   for(int ii = 0; ii< i; ii++)
                   {
                       if(ErrCode[i] == ErrCode[ii])
                       {
                           ErrCoords[ii] = ErrCoords[i];
                           equalflag = true;
                           ii = i;
                       }

                   }
                   if(!equalflag)
                   {
                       ErrCoords[i] = maxErrCoord+1;
                       maxErrCoord++;
                   }
               }
        }
    }
    return 0;
}

bool MainWindow::checkSegmentCRC(long segmentID)
{
    newLogProc->selectSegment(segmentID);//selecting head table interpretator segment
    newLogProc->tmpFile.seek(newLogProc->logDataPointer-SIZE_OF_SEGMENTHEADER);
    newLogProc->tmpFile.read(tmpHeadArr,SIZE_OF_SEGMENTHEADER);
    tmpHeadArr[4]=0;
    tmpHeadArr[5]=0;
    tmpHeadArr[6]=0;
    tmpHeadArr[7]=0;
    tmpHeadArr[12]=0;
    tmpHeadArr[13]=0;
    tmpHeadArr[14]=0;
    tmpHeadArr[15]=0;
    char* tmpBuffArr = (char*)malloc(newLogProc->segmentHeader.size);
    if(newLogProc->readSegment(tmpBuffArr,newLogProc->segmentHeader.size))
     {
         unsigned long CRCtmp = newLogProc->CRC32updater(tmpHeadArr,SIZE_OF_SEGMENTHEADER,0xffffffff);
         CRCtmp = newLogProc->CRC32updater(tmpBuffArr,newLogProc->segmentHeader.size, CRCtmp);
         CRCtmp = newLogProc->CRC32updater((char*)&newLogProc->segmentHeader.size,4, CRCtmp);
         CRCtmp=CRCtmp^0xffffffff;
         free(tmpBuffArr);
         if(CRCtmp!=newLogProc->segmentHeader.CRC32)
         {
             newMessage.setWindowTitle("Ошибка!");
             newMessage.setText("Ошибка контрольной суммы. Файл журнала регистратора поврежден.");
             newMessage.exec();
             return false;
         }
         return true;
     }
     else
     {
         newMessage.setWindowTitle("Ошибка!");
         newMessage.setText("Ошибка чего-то. Файл журнала регистратора поврежден.");
         newMessage.exec();
         return false;
     }
}

bool MainWindow::initiateTimeAxis(/*QDateTime startPoint,*/ time_t *times/*,int length*/)
{
    unsigned int pointsAmount=0;
    unsigned int tmpAbs=0;
    bool increasingTimeFlag = false;
    createErrCoordsArray();
    if(!OldLog)
    {
        for(int i = 1; i < sizeOfArray; i++)
        {
            if(dateChangedArrExistFlag)
            {
                if(!dateChangedArr[i])
                {                                                       //if there was an appearence of dateChanged flag, that is being searched in dateChangeArr
                    pointsAmount += (abs)((int)times[i]-(int)times[i-1]);      //we have to increase pointsAmount value only by one, otherwise increase it by subtracted value
                }
                else pointsAmount++;                                    //of times[i]-times[i-1]
            }
            else
            {
                if((int)times[i]==(int)times[i-1])
                {
                    pointsAmount++;
                }
                else if(timeFractExistFlag)
                {
                    tmpAbs = abs((int)times[i]-(int)times[i-1]);
                    if(tmpAbs>=MAX_POINTS)
                    {
                        int tmpUnabs = (int)times[i]-(int)times[i-1];
                        if(tmpUnabs>0)
                        {
                            times[i] = times[i-1];
                            if(timeFract[i]<timeFract[i-1])
                                timeFract[i] = timeFract[i-1]+1;
                        }
                        else
                        {
                            times[i-1] = times[i];
                            if(timeFract[i-1]<timeFract[i])
                                timeFract[i-1] = timeFract[i]+1;
                        }
                        tmpAbs=1;
                    }
                    pointsAmount+=tmpAbs;
                }
                else if(subTimeExistFlag)
                {
                    tmpAbs = abs((int)times[i]-(int)times[i-1]);
                    if(tmpAbs<=MAX_POINTS)
                    {
                        int tmpUnabs = (int)times[i]-(int)times[i-1];
                        if(tmpUnabs<0)
                        {
                            tmpAbs = abs(tmpUnabs);
                        }
                        else if(tmpUnabs>0)
                        {
                            increasingTimeFlag = true;
                            tmpAbs = abs(tmpUnabs);
                        }
                        else
                            tmpAbs=1;
                    }
                    pointsAmount+=tmpAbs;
                }
            }
        }
        if(pointsAmount<=0)
        {
            newMessage.setWindowTitle("Ошибка!");
            newMessage.setText("Проверьте правильность лог-файла. Слишком мало точек для построения!");
            newMessage.exec();
            return false;
        }
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
            timeScale = new TimeScaleDraw(QDateTime::fromTime_t(times[0]));
            timeScale->maxVal=pointsAmount;
            mapTimeScale = new MapTimeScaleDraw("dd.MM.yyyy hh:mm:ss");
            mapTimeScale->setLabelAlignment(Qt::AlignRight);
            allPoints = (time_t*)malloc(pointsAmount*sizeof(time_t));
            if(!increasingTimeFlag)
            {
                allPoints[0] = times[pointsAmount-1];
                allPoints[pointsAmount-1] = times[0];
            }
            else
            {
                allPoints[0] = times[0];
                allPoints[pointsAmount-1] = times[sizeOfArray -1];
            }
            for (int i = 1;  i < pointsAmount; i++)     // we create global array of time points, also adding points that are duplicated
            {
                if(increasingTimeFlag)
                    allPoints[i] = times[i];
                else
                    allPoints[i] = times[pointsAmount-i];
            }
            timeScale->fillTimeVector(pointsQuantity,times);
            timeScale->timeArr = allPoints;
            mapTimeScale->timeArr = allPoints;
             ui->qwtPlot_2->setAxisScaleDraw( QwtPlot::xBottom, timeScale );
             ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom,mapTimeScale);
             ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, pointsAmount, 0);
             QwtScaleDraw *sd = ui->qwtPlot_2->axisScaleDraw(QwtPlot::xBottom);
             sd->enableComponent(QwtScaleDraw::Ticks,false);
             ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom, 0, pointsAmount, 0);
            printLeftTimeIndex = 0;
            printRightTimeIndex = printLeftTimeIndex+120;
            return true;
        }
    }
    else
    {
        pointsAmount =sizeOfArray;
        pointsQuantity = pointsAmount;
        timeScale = new TimeScaleDraw(QDateTime::fromTime_t(times[0]));
        timeScale->maxVal = sizeOfArray-1;//(long)times[sizeOfArray-1];
        mapTimeScale = new MapTimeScaleDraw("dd.MM.yyyy hh:mm:ss");
        mapTimeScale->setLabelAlignment(Qt::AlignRight);
        timeScale->timeArr = times;
        mapTimeScale->timeArr = times;
         ui->qwtPlot_2->setAxisScaleDraw( QwtPlot::xBottom, timeScale );
         ui->qwtPlot->setAxisScaleDraw(QwtPlot::xBottom,mapTimeScale);
         ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0, pointsAmount, 0);
         QwtScaleDraw *sd = ui->qwtPlot_2->axisScaleDraw(QwtPlot::xBottom);
         sd->enableComponent(QwtScaleDraw::Ticks,false);
         ui->qwtPlot_2->setAxisScale(QwtPlot::xBottom, 0, pointsAmount, 0);
        printLeftTimeIndex = 0;
        printRightTimeIndex = printLeftTimeIndex+120;
        return true;
    }
}

int MainWindow::generateLinearTimeArr( double *linearizedTA)
{
    /***********************************************************************************************
     * This part is used to create linear time scale, i.e. set to X1 number of time
     * vals corresponding to each log record situated from first record's time by proportional value.
     * If between 2 members of time array it is more than 1 second, we have to add same amount
     * of X1 members as seconds between that 2 members of timeArr.
     * Returns in argument(2) linearized time array from unlinearized time array timeArray.
     ***************************************************************************/
    int incval = 0;
    if(!OldLog)
    {
        for(int i = 0; i < sizeOfArray; i++)
        {
            if(i>0)
            {
                if((int)timeArray[i]==(int)timeArray[i-1])
                {

                    incval++;

                }

                linearizedTA[i] = (int)timeArray[i]-(int)timeArray[0]+incval;

            }
            else
                 linearizedTA[i] = (int)timeArray[i]-(int)timeArray[0];

        }
    }
    else
    {
        for(int i = 0; i < sizeOfArray; i++)
        {
            linearizedTA[i]=i;
        }
    }
    return 0;
}

void MainWindow::initCurves()
{
    double *X1 = (double*)malloc(sizeOfArray*sizeof(double));
    generateLinearTimeArr(X1);
    QVector <double> X1vect;
    for(int i = 0; i < sizeOfArray;i++)
        X1vect.append(X1[i]);
    verticalFlagScale = new VerticalFlagScaleDraw(20);
    ui->qwtPlot->enableAxis(QwtPlot::xBottom,true);
    AxisLabelDate = firstDateTime;
    lastFlag = -1;
    powOffIndex = -1;
    errAddIndex = -1;
    flagPowOffCount = 0;
    int tmpFlagCounter = 0;
    int index = 0;
    for (int i =0; i<invisIntItems.size(); i++)
        if((!invisIntItems[i].invisibility)||(invisIntItems[i].interpIndex==0))
           {
            curves newCurve;
            int lastIndex=0;
            newCurve.curve = new QwtPlotCurve;
            for(int a  = 0; a < sizeOfArray; a++)
                newCurve.cData.append(Y[i][a]);
            newCurve.cColor = colors[i];
            newCurve.curve->setPen(QPen(newCurve.cColor));
            newCurve.curve->setStyle(QwtPlotCurve::Steps);
            newCurve.curve->setCurveAttribute(QwtPlotCurve::Inverted);
            newCurve.curve->setSamples(X1vect,newCurve.cData);
            newCurve.cType = (curvetypes)0 ;
            if(!invisIntItems[i].invisibility)
                newCurve.cAttachable = 1;
            else
                newCurve.cAttachable = 0;
            newCurve.axis = index;
            newCurve.isCurveHidden = true;
            newCurve.cName = QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name);// = QString::fromLocal8Bit();
            if(newCurve.cName=="Ошибка");
            newCurve.cName.replace("[","(");
            newCurve.cName.replace("]",")");
            if((char)newTmiInterp->TInterpItemArray[i].typ==8)
                {
                    if(newCurve.cName=="ErrAdd")
                    {
                        newCurve.cType = (curvetypes)0;
                        newCurve.flagMarker =0;
                    }
                    else
                    {
                        newCurve.cType=(curvetypes)1;
                        newCurve.flagMarker = new QwtPlotMarker;
                        newCurve.flagMarker->setLabel( newCurve.cName);
                        newCurve.flagMarker->setLineStyle(QwtPlotMarker::NoLine);
                        newCurve.flagMarker->setValue(80,1);//getOffsetValue(i));
                        newCurve.flagMarker->setAxes(QwtPlot::xBottom,firstFlagIndex);
                        cArrayDetailedPlot[lastIndex].curve->setAxes(QwtPlot::xBottom,cArrayDetailedPlot[lastIndex].axis);//this one
                    }
                }
                else
                {
                    newCurve.cType = (curvetypes)0;
                    newCurve.flagMarker =0;
                }

                    if(newCurve.cType==MainWindow::data)//adding not flags curves
                    {
                        if((i==pointerToSpd)||(i==pointerToEng1Spd)) // adding curves to global map plot
                        {
                            cArrayGlobalMapPlot.append(newCurve);
                            int cindex = cArrayGlobalMapPlot.size()-1;

                            cArrayGlobalMapPlot[cindex].curve = new QwtPlotCurve;
                            cArrayGlobalMapPlot[cindex].curve->setPen(QPen(newCurve.cColor));
                            cArrayGlobalMapPlot[cindex].curve->setStyle(QwtPlotCurve::Steps);
                            cArrayGlobalMapPlot[cindex].curve->setCurveAttribute(QwtPlotCurve::Inverted);
                            cArrayGlobalMapPlot[cindex].curve->setSamples(X1vect,newCurve.cData);
                            if(newCurve.cAttachable)
                                cArrayGlobalMapPlot[cindex].curve->attach(ui->qwtPlot);
                            cArrayGlobalMapPlot[cindex].curve->setAxes(QwtPlot::xBottom,newCurve.axis);
                            ui->qwtPlot->enableAxis(newCurve.axis,false);
                            ui->qwtPlot->setContentsMargins(-50,0,0,0);
                            ui->qwtPlot->replot();
                        }
                        QPalette myPalette;
                        cArrayDetailedPlot.append(newCurve);
                        lastIndex =cArrayDetailedPlot.size()-1;
                        if(newCurve.cAttachable)
                            cArrayDetailedPlot[lastIndex].curve->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
                            cArrayDetailedPlot[lastIndex].curve->setAxes(QwtPlot::xBottom,cArrayDetailedPlot[lastIndex].axis);//this one
                            if(newCurve.cAttachable)
                               ui->qwtPlot_2->enableAxis(cArrayDetailedPlot[lastIndex].axis,true);//and enable it
                            myPalette.setColor(QPalette::Foreground,cArrayDetailedPlot[lastIndex].cColor);
                            myPalette.setColor(QPalette::Text,cArrayDetailedPlot[lastIndex].cColor);
                            ui->qwtPlot_2->axisWidget(cArrayDetailedPlot[lastIndex].axis)->setPalette(myPalette);
                            ui->qwtPlot_2->replot();
                    }
                    else if(newCurve.cType==1)
                    {
                        lastFlag = i;
                        newCurve.cType = (curvetypes)1;
                        tmpFlagCounter++;
                        cArrayDetailedPlot.append(newCurve);
                        lastIndex =cArrayDetailedPlot.size()-1;
                        if((int)cArrayDetailedPlot[lastIndex].cData.at(0)%2)
                            cArrayDetailedPlot[lastIndex].curve->setBaseline(cArrayDetailedPlot[lastIndex].cData.at(0)-1);
                        else
                            cArrayDetailedPlot[lastIndex].curve->setBaseline(cArrayDetailedPlot[lastIndex].cData.at(0));
                        QString tmpstr;
                        tmpstr = QString::fromLocal8Bit(newTmiInterp->TInterpItemArray[i].name);
                        tmpstr.remove(6,26);
                        cArrayDetailedPlot[lastIndex].curve->setBrush(QBrush(colors[i],Qt::Dense6Pattern));
                        if(newCurve.cAttachable)
                            cArrayDetailedPlot[lastIndex].curve->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
                        cArrayDetailedPlot[lastIndex].curve->setAxes(QwtPlot::xBottom,firstFlagIndex);//this one firstFlagIndex is index of axis where we bound all the flag curves
                        ui->qwtPlot_2->enableAxis(0,false);//and enable it
                        QPalette myPalette;
                        myPalette.setColor(QPalette::Foreground,Qt::black);
                        myPalette.setColor(QPalette::Text,Qt::black);
                        ui->qwtPlot_2->setAxisScaleDraw(firstFlagIndex,verticalFlagScale);
                        ui->qwtPlot_2->setAxisScale(firstFlagIndex, 0, flagCounter*2-1, 1);
                        QwtText tmpTitle = firstDateTime.date().toString("dd.MM.yyyy");
                        QFont tmpFont;
                        tmpFont.setBold(false);
                        tmpTitle.setFont(tmpFont);
                        ui->qwtPlot_2->setAxisTitle(QwtPlot::xBottom, tmpTitle);
                        ui->qwtPlot_2->axisWidget(cArrayDetailedPlot[lastIndex].axis)->setPalette(myPalette);
                        if(tmpstr == "PowOFF")
                        {
                            powOffIndex =i;
                            flagPowOffCount = tmpFlagCounter;
                        }
                        if(tmpstr =="ErrAdd")
                        {
                            errAddIndex = i;
                            globalAddErrFlagBaseLine = flagCounter*2-2;
                        }
                        ui->qwtPlot_2->replot();
                    }
             index++;
            }
    for(int c = 0; c < cArrayDetailedPlot.size(); c++)
    {

    }
    if(!OldLog)
    {
        if(errCodeIndex!=-1)
        {
            errpicker = new errorPicker(ui->qwtPlot_2->canvas());
            createErrCodeFromErrAddArray(X1);
            createErrCoordsCurve(X1);
            initPicker();
        }
        if(powOffIndex!=-1)
            setFilledPowerOffTime(X1);
    }
    free(X1);
}

void MainWindow::initFlagScale()//here we have to make some init of flagscale
{

}

int MainWindow::createErrCodeFromErrAddArray(double *XX)
{
    double maxcoord=0;
    bool equalflag;
    int equalIndex=0;
    for(int i = 0; i< sizeOfArray;i++)
    {
        errCoordStruct coord;
        coord.coord=0;
        coord.code = 0;
        if(ErrCode[i]!=0)
        {
            if(i==0)
            {
                if(ErrCode[0]==0)
                {
                    coord.coord = 0;
                    coord.code = ErrCode[0];

                }
                else
                {
                    coord.coord = 1;
                    coord.code = ErrCode[0];

                }
                ErrCoordVector.append(coord);
                ErrXCoords.append(XX[i]);
                maxcoord++;
            }
            else
            {
                if(ErrCode[i]!=ErrCode[i-1])
                {
                    for(int a = 0; a < i; a++)
                    {
                        if(ErrCode[a]==ErrCode[i])
                        {
                            for(int b = 0; b < ErrCoordVector.size();b++)
                            {
                                if(ErrCoordVector[b].code==ErrCode[a])
                                {
                                    coord.coord = ErrCoordVector[b].coord;
                                    b = ErrCoordVector.size();
                                }
                            }
                            equalflag = true;
                            equalIndex = a;
                            a=i;
                        }
                        else
                        {
                            coord.coord = maxcoord;
                            equalflag = false;
                            equalIndex = 0;
                        }

                    }
                    if(equalflag)
                    {
                        coord.code = ErrCode[i];
                        ErrCoordVector.append(coord);
                        ErrXCoords.append(XX[i]);
                    }
                    else
                    {
                        coord.code = ErrCode[i];
                        ErrCoordVector.append(coord);
                        ErrXCoords.append(XX[i]);
                        maxcoord++;
                    }
                }
            }
        }
    }
    for(int i = 0; i < ErrCoordVector.size();i++)
    return 0;
}

int MainWindow::createErrCoordsCurve(double *X)
{
    QPalette myPalette;
    errorSym.setColor(Qt::blue);
    errorSym.setStyle(QwtSymbol::Diamond);
    errorSym.setPen(QColor(Qt::blue));
    errorSym.setSize(5);
    errorCurve.curve = new QwtPlotCurve;
    errorCurve.cColor = colors[errCodeIndex];
    errorCurve.curve->setPen(QPen(colors[errCodeIndex]));
    errorCurve.curve->setStyle(QwtPlotCurve::Steps);
    errorCurve.curve->setCurveAttribute(QwtPlotCurve::Inverted);
    QVector <double> errcoordv;
    for(int i = 0; i < ErrCoordVector.size(); i++)
    {
        errcoordv.append(ErrCoordVector[i].coord);
    }
    errorCurve.curve->setSamples(ErrXCoords,errcoordv);
    errorCurve.cType = error ;
    errorCurve.cAttachable = 1;
    errorCurve.axis = errCodeIndex;
    errorCurve.isCurveHidden = true;
    errorCurve.cName = "Error Curve";// = QString::fromLocal8Bit();
    errorCurve.flagMarker = 0;
    myPalette.setColor(QPalette::Foreground,colors[errCodeIndex]);
    myPalette.setColor(QPalette::Text,colors[errCodeIndex]);
    ui->qwtPlot_2->axisWidget(errCodeIndex)->setPalette(myPalette);
    errorCurve.curve->setSymbol(&errorSym);
    errorCurve.curve->setAxes(QwtPlot::xBottom,errCodeIndex);
    cArrayDetailedPlot.append(errorCurve);
    if(cArrayDetailedPlot[cArrayDetailedPlot.size()-1].cAttachable)
        cArrayDetailedPlot[cArrayDetailedPlot.size()-1].curve->attach(ui->qwtPlot_2);
    ui->qwtPlot_2->replot();
}

int MainWindow::initPicker()
{
    int iterator=0,coords=0,code=0;
    for(int i = 0; i < sizeOfArray; i++)
    {
        if(iterator ==0)
        {
            coords = ErrCoordVector[iterator].coord;
            code = ErrCoordVector[iterator].code;
            iterator++;
        }
        else
        {
            if(iterator<ErrCoordVector.size())
            {
                if(ErrCode[i]!=ErrCode[i-1])
                {
                    coords = ErrCoordVector[iterator].coord;
                    code = ErrCoordVector[iterator].code;
                    iterator++;
                }
            }
        }
        errpicker->errDesc.append({timeArray[i],code/*ErrCode[i]*/,Y[errAddIndex][i],coords});
    }
    errpicker->sizeOfArr = sizeOfArray;
    errpicker->setStateMachine(new QwtPickerDragPointMachine());
    errpicker->setAxis(QwtPlot::xBottom,errCodeIndex);
    errpicker->ErrBaseVal = globalAddErrFlagBaseLine;
    errpicker->setRubberBandPen(QColor(Qt::green));
    errpicker->setRubberBand(QwtPicker::NoRubberBand);
    errpicker->setTrackerPen(QColor(Qt::black));
    errpicker->setTrackerMode(QwtPlotPicker::AlwaysOn);

}

int MainWindow::setFilledPowerOffTime(double *X)
{
      QwtPlotCurve *curve = new QwtPlotCurve;
      for(int i  = 0; i < sizeof(Y[powOffIndex]); i++)
          Y[powOffIndex][i]-=1;
      curve->setStyle(QwtPlotCurve::Steps);
      curve->setPen(QPen(QColor(Qt::white),0.1));
      curve->setBaseline(0);
      curve->setCurveAttribute(QwtPlotCurve::Inverted);
      curve->setSamples(X,Y[powOffIndex],sizeOfArray);
      QBrush brush(QColor(255, 255, 0, 100), Qt::SolidPattern);//yellow 255;255;0
      curve->setBrush(brush);
      curve->attach(ui->qwtPlot);
      curve->setAxes(QwtPlot::xBottom,powOffIndex);
      ui->qwtPlot->enableAxis(powOffIndex,false);
      ui->qwtPlot->setContentsMargins(-50,0,0,0);
      ui->qwtPlot->setAxisScale(1, 0, flagPowOffCount*2-2, 0.1);
      ui->qwtPlot->replot();
      return 0;
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
    videoScreen1->setWindowFlags(Qt::Tool |Qt::FramelessWindowHint);
    videoScreen2->setWindowFlags(Qt::Tool |Qt::FramelessWindowHint);//add Qt::WindowStaysOnTopHint  if need on top of everything
    videoScreen2->show();
    videoScreen1->show();
}


/*
 *If leftButtonPressed (if mouse been moved, leftButtonPressed = false), we have to move marker to this position
 *if pressed right button (leftButtonPressed = false too), we do nothing,
 */

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
        if(event->type() == QEvent::MouseButtonPress & target!=0x0)
        {
            QMouseEvent *mouseEvent = (QMouseEvent *) event;
            QString parent_name = target->objectName();
            if(parent_name=="qwtPlot_2")
            {
                if(mouseEvent->buttons()==Qt::LeftButton)
                {
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
                if(mouseEvent->button()==Qt::LeftButton)moveMapMarker(ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()));//moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x()-ui->qwtPlot->contentsMargins().left()) + ui->qwtPlot->transform(QwtPlot::xBottom,0));//100 - is offset
                globalCursorPos = QCursor::pos().x();
                mapPlotUsed = true;
            }
           return true;
        }
        if(event->type()==QEvent::MouseButtonRelease)
        {
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
                            moveMapMarker(moveVal);
                            leftButtonPressed=false;
                        }
                }
                else rightButtonPressed = false;
                if(mapPlotUsed)
                {
                     if(globalCursorPos==QCursor::pos().x())
                     {
                         mapPlotUsed = false;
                     }
                }
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
                   double globalPos =  globalCursorPos;
                   double currentPos = QCursor::pos().x();
                   int visWidth =  ui->qwtPlot_2->axisWidget(QwtPlot::xBottom)->width();
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
                       moveMapMarker((int)ui->qwtPlot->invTransform(QwtPlot::xBottom,ui->qwtPlot->mapFromGlobal(QCursor::pos()).x() - ui->qwtPlot->contentsMargins().left()) );//100 - is offset
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
               if(globalMagnifierPreviosPos<QCursor::pos().x())
               {
                   double tmpInc = 10*globalMagVal/ui->qwtPlot_2->canvas()->width();
                   if(tmpInc<1)tmpInc = 1;
                   globalMagnifyFactor-=tmpInc;
               }
               globalMagnifierPreviosPos = QCursor::pos().x();
               upPlotMagnifier(globalMagnifyFactor);
               }
           }
       return true;
       }
       if(plotRectBasicWidth==0)
       {
           plotRectBasicWidth = ui->widget->pos().x()+ui->widget->width();
       }
            if((ui->qwtPlot_2->visibleRegion().rectCount()<3)&&(ui->qwtPlot_2->visibleRegion().rectCount()>1))
           {
               if(ui->qwtPlot_2->visibleRegion().rects()[1].x()>=ui->qwtPlot_2->visibleRegion().rects()[0].x())
               {
                ui->widget->move(ui->widget->pos().x()+(ui->qwtPlot_2->visibleRegion().rects()[1].width()-plotRectBasicWidth), ui->widget->pos().y());
                plotRectBasicWidth = ui->qwtPlot_2->visibleRegion().rects()[1].width();
               }
               else
               {
                ui->widget->move(ui->widget->pos().x()+(ui->qwtPlot_2->visibleRegion().rects()[1].width()-plotRectBasicWidth) - ui->qwtPlot_2->visibleRegion().rects()[0].width(), ui->widget->pos().y());
                plotRectBasicWidth = ui->qwtPlot_2->visibleRegion().rects()[1].width()- ui->qwtPlot_2->visibleRegion().rects()[0].width();
               }
           }
           else if(ui->qwtPlot_2->visibleRegion().rectCount()==3)//and here Ktulhu too
           {
               ui->widget->move(ui->widget->pos().x()+(ui->qwtPlot_2->visibleRegion().rects()[2].width()-ui->qwtPlot_2->visibleRegion().rects()[1].width()-plotRectBasicWidth), ui->widget->pos().y());
               plotRectBasicWidth = ui->qwtPlot_2->visibleRegion().rects()[2].width() - ui->qwtPlot_2->visibleRegion().rects()[1].width();
           }
    return QMainWindow::eventFilter(target, event);
}


void MainWindow::moveMapMarker(long int globalPosition)
{
    if(globalPosition>=pointsQuantity)
    {
        globalPosition=pointsQuantity-1;
    }
    if(globalPosition < 0)globalPosition = 0;
    int position;
    if(OldLog)
        position = globalPosition;
    else
        position = getClosestToPositionIndex(globalPosition);// may be we don't need this +1
    timeScale->currentIndex = globalPosition;
    ui->actionPrint->setEnabled(true);
    verticalMapMarker->setValue(globalPosition,0);
    currentTimeMarker->setValue(globalPosition,0);
    QDateTime tmpDate=QDateTime::fromTime_t(timeArray[position]);
    QwtText tmpTitle;
    if(tmpDate.date()!=AxisLabelDate.date())
    {
        tmpTitle = tmpDate.date().toString("dd.MM.yyyy");
        QFont tmpFont;
        tmpTitle.setFont(tmpFont);
        ui->qwtPlot_2->setAxisTitle(QwtPlot::xBottom,tmpTitle);
        AxisLabelDate = tmpDate;
    }
    double magnifiedVal = upPlotMagnifier(globalMagnifyFactor);
    int tmpCounter=0;\
    int flagmarkercounter=0;
    for(int i =0; i < cArrayDetailedPlot.size();i++)
        if(cArrayDetailedPlot[i].cAttachable)
    {

        if(cArrayDetailedPlot[i].cType==(curvetypes)0)
        {
            cArrayCurveWidgets[i].thermo->setValue(cArrayDetailedPlot[i].cData.at(position));
        }
        else if(cArrayDetailedPlot[i].cType==1)
        {
            cArrayCurveWidgets[i].checkBox->setChecked((int)cArrayDetailedPlot[i].cData.at(position)%2);
            cArrayDetailedPlot[i].flagMarker->setValue(0.8*magnifiedVal +globalPosition,flagMarkerOffsetBase+tmpCounter*flagMarkerIncStep);
            tmpCounter++;
            flagmarkercounter++;
        }
        else if(cArrayDetailedPlot[i].cType==2)
        {
            QString txt = errpicker->errorDecoder(ErrCode[position]);
            cArrayCurveWidgets[i].valueLabel->setText(txt);
        }

    }
    pf->SetMapMarkerPosition(timeArray[position]);
    for(int i = 0; i < cArrayDetailedPlot.size(); i++)
        if(cArrayDetailedPlot[i].cAttachable)
    {
        QVariant tmp;
        if(cArrayDetailedPlot[i].cType==0)
        {
            tmp = cArrayCurveWidgets[i].thermo->value();
            if(newTmiInterp->TInterpItemArray[i+2].mask_)
            {
                char tmpArr[10];
                sprintf(tmpArr,"%.1f",cArrayCurveWidgets[i].thermo->value());
                cArrayCurveWidgets[i].thermo->setToolTip(tmpArr);
                cArrayCurveWidgets[i].valueLabel->setText(tmpArr);
            }
            else
            {
                cArrayCurveWidgets[i].thermo->setToolTip(tmp.toString());
                cArrayCurveWidgets[i].valueLabel->setText(tmp.toString());
            }
        }
    }

    ui->qwtPlot->replot();
    ui->qwtPlot_2->replot();

}



void MainWindow::initiateThermos()
{

}

void MainWindow::indexChanged()
{

}
void MainWindow::hideAxis()
{
    int index=0;
    QObject * tmp = sender();
    for(int i = 0 ; i < cArrayDetailedPlot.size(); i++)
        if(cArrayDetailedPlot[i].cAttachable)
    {
            if(tmp==cArrayCurveWidgets[i].axisButton)
                index=i;
    }
    cArrayDetailedPlot[index].isCurveHidden = !cArrayDetailedPlot[index].isCurveHidden;
    double tmpMagVal = upPlotMagnifier(globalMagnifyFactor);
    if((cArrayDetailedPlot[index].isCurveHidden)&(cArrayDetailedPlot[index].cAttachable))
    {
        cArrayDetailedPlot[index].curve->detach();//by default we have 1st axis with this curve on the plot, also it is enabled by default
        if((cArrayDetailedPlot[index].cType==0)|(cArrayDetailedPlot[index].cType==2))
        {
            if(cArrayDetailedPlot[index].cType==0)
            {
                cArrayDetailedPlot[index].curve->setAxes(1,index);//this one
                ui->qwtPlot_2->enableAxis(index,false);//and enable it
            }
        }
        else
            cArrayDetailedPlot[index].flagMarker->detach();
        ui->qwtPlot_2->replot();
        ui->qwtPlot->replot();
        cArrayCurveWidgets[index].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
     }
    else
    {
        if(cArrayDetailedPlot[index].cAttachable)
            cArrayDetailedPlot[index].curve->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
//        int tmpIndex = 11;
        if(cArrayDetailedPlot[index].cAttachable)
        {
            if((cArrayDetailedPlot[index].cType==0)|(cArrayDetailedPlot[index].cType==2))
            {
                if(cArrayDetailedPlot[index].cType==0)
                {
                    cArrayDetailedPlot[index].curve->setAxes(1,index);//this one
                    ui->qwtPlot_2->enableAxis(index,true);//and enable it
                }
                else
                {

                }
            }
            else
            {
                if(cArrayDetailedPlot[index].cAttachable)
                    cArrayDetailedPlot[index].flagMarker->attach(ui->qwtPlot_2);
                cArrayDetailedPlot[index].flagMarker->setValue(tmpMagVal*0.8+verticalMapMarker->value().x(),getOffsetValue(index));
            }
        }
        ui->qwtPlot_2->replot();
        ui->qwtPlot->replot();
        cArrayCurveWidgets[index].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    }
}

void MainWindow::preparePlotData()
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::on_pushButton_clicked()
{
    mapTimer->start(mapTimerDelay);
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
void MainWindow::hideWasteAxes(int notHiddenIndex)//hide unused axis (nuber of not hidden axis usually means )
{
    int index;
    int hiddenCounter=0,notHiddenCounter=0;
    for(int i = 0; i < cArrayCurveWidgets.size(); i++)
    {
        if(cArrayCurveWidgets[i].widgetType==0)
        {
            ui->verticalLayout_7->addLayout(cArrayCurveWidgets[i].labelLayout);
            ui->verticalLayout_7->addLayout(cArrayCurveWidgets[i].thermoLayout);
        }
    }
    for(int i = 0; i < cArrayCurveWidgets.size(); i++)
    {
        if(cArrayCurveWidgets[i].widgetType>=1)
        {
            ui->verticalLayout_7->addLayout(cArrayCurveWidgets[i].thermoLayout);
        }
    }
  for(int i =0; i < cArrayCurveWidgets.size();i++)
      if(cArrayCurveWidgets[i].widgetType!=-1)
      {
        cArrayCurveWidgets[1].axisButton->click();
        cArrayCurveWidgets[1].axisButton->click();
        break;
      }

    for(int i =0; i < ui->qwtPlot_2->axisCnt;i++)
    {
        if(i!=QwtPlot::xBottom)
            ui->qwtPlot_2->enableAxis(i,false);
    }

    for(int i =0; i < cArrayDetailedPlot.size(); i++)
        if(cArrayDetailedPlot[i].cAttachable)
    {
        if((cArrayDetailedPlot[i].cType==0)&(cArrayDetailedPlot[i].cAttachable))
        {
            if(notHiddenCounter==0)
            {
                cArrayCurveWidgets[i].axisButton->click();
                notHiddenCounter++;

            }
        }
    }
    for(int i = 0 ; i < cArrayDetailedPlot.size(); i++)
        if(cArrayDetailedPlot[i].cAttachable)
    {
        if(cArrayDetailedPlot[i].isCurveHidden)
        {
            cArrayDetailedPlot[i].curve->detach();//by default we have 1st axis with this curve on the plot, also it is enabled by default
            int tmpIndex = 11;
            if(cArrayDetailedPlot[i].cType==0)
            {
                tmpIndex = i;
                cArrayDetailedPlot[i].curve->setAxes(1,cArrayDetailedPlot[i].axis);//this one
                ui->qwtPlot_2->enableAxis(cArrayDetailedPlot[i].axis,false);//and enable it
            }
            ui->qwtPlot_2->replot();
            cArrayCurveWidgets[i].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
         }
        else
        {
            if(cArrayDetailedPlot[i].cAttachable)
                cArrayDetailedPlot[i].curve->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
            int tmpIndex = 11;
            if((cArrayDetailedPlot[i].cType==0)&(cArrayDetailedPlot[i].cAttachable))
            {
                    cArrayDetailedPlot[i].curve->setAxes(1,cArrayDetailedPlot[i].axis);//this one
                    ui->qwtPlot_2->enableAxis(cArrayDetailedPlot[i].axis,true);//and enable it
            }
            ui->qwtPlot_2->replot();
            cArrayCurveWidgets[i].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
        }
    }
}


void MainWindow::setGlobalArrays()
{
    for (int i =0; i<invisIntItems.size(); i++)
        if(!invisIntItems[i].invisibility)
        {
            thermoPlotMins[i] = 0;
        }
    for (int i =0; i<invisIntItems.size(); i++)
        if(!invisIntItems[i].invisibility)
        {
            if(thermoPlotMaxs[i]<1)
                thermoPlotMaxs[i]=1;
        }
}

void MainWindow::on_actionOpen_triggered()
{
        openLog();
}

int MainWindow::closeLog()
{
    if(isOpened==true)
    {
        currentTimeMarker->detach();
        verticalMapMarker->detach();
        if(errCodeIndex!=-1)
            errorCurve.curve->detach();
        ui->qwtPlot_2->detachItems(QwtPlotItem::Rtti_PlotItem, true);
        ui->qwtPlot->detachItems(QwtPlotItem::Rtti_PlotItem, true);
        for(int i =0; i< ui->qwtPlot_2->axisCnt; i++)
        {
            ui->qwtPlot_2->enableAxis(i,false);
        }
        for(int i =0; i< ui->qwtPlot->axisCnt; i++)
            ui->qwtPlot->enableAxis(i,false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        for(int i = 0; i < cArrayCurveWidgets.size(); i++)
            if(cArrayDetailedPlot[i].cAttachable)
        {
            QLayoutItem* item;
            while ( ( item =cArrayCurveWidgets[i].thermoLayout->takeAt( 0 ) ) != NULL )
                  {
                       delete item->widget();
                       delete item;
                   }
        }
        for(int i = 0; i < cArrayCurveWidgets.size(); i++)
            if(cArrayDetailedPlot[i].cAttachable)
        {
            QLayoutItem* item;
            if(cArrayCurveWidgets[i].widgetType==0)
            while ( ( item =cArrayCurveWidgets[i].labelLayout->takeAt( 0 ) ) != NULL )
                  {
                       delete item->widget();
                       delete item;
                   }
        }
        cArrayCurveWidgets.clear();
        ui->horizontalLayout_3->setEnabled(false);
        ui->checkBox->setEnabled(false);
        ui->qwtPlot->setEnabled(false);
        ui->qwtPlot_2->setEnabled(false);
        newLogProc->tmpFile.close();
        delete newLogProc;
        delete newTmiInterp;
        ErrXCoords.clear();
        ErrCoordVector.clear();
        invisIntItems.clear();
        delete timeArray;
        delete dateChangedArr;
        markerLbl.setText("");
        delete allPoints;
        flagMarkerOffsetBase = 1.25;
        flagMarkerIncStep = 0;
        flagCounter = 0;
        OldLog = false;
        invertedTime = true;
        delete X;
        delete Y;
        delete ErrCoords;
        delete ErrCode;\
        if(errCodeIndex!=-1)
        {
            delete errpicker;
        }
        errCodeIndex =-1;
        cArrayDetailedPlot.clear();
        cArrayGlobalMapPlot.clear();
    }
    return 0;
}


int MainWindow::openLog()
{
    filename = QFileDialog::getOpenFileName(this,"Открыть файл лога регистратора", "c:","Выберите файл лога регистратора(*.alg)");
    if(filename!=lastOpenedFileName)
    {
        if(filename!="")
        {
            if(!NoFileWasOpened)
            {
                closeLog();
            }
            ui->actionHideLeftPanel->setEnabled(true);
            reinit();
            lastOpenedFileName = filename;
            NoFileWasOpened = false;
            ui->qwtPlot->setEnabled(true);
               ui->qwtPlot_2->setEnabled(true);
                   ui->actionPrint->setEnabled(true);
                       ui->actionOpen->setEnabled(true);
                           ui->scrollArea->setEnabled(true);
                               ui->pushButton->setEnabled(true);
                                   ui->pushButton_2->setEnabled(true);
                                       ui->pushButton_3->setEnabled(true);
                                          ui->pushButton_4->setEnabled(true);
            if(!checkFileHeaderCRC())
            {
                newLogProc->tmpFile.close();
            }
            else
            {
            readHeadTableData();
            if(readDataFromLog())
                {
                    setGlobalArrays();
                    initCurves();
                    initiatePlotMarkers();
                    initiateRadios();
                    hideWasteAxes(axisCount);
                    isOpened=true;
                    tmpIcon = new QIcon(":new/p/openLog");
                    ui->actionOpen->setIcon(*tmpIcon);
                    ui->actionOpen->setToolTip("Закрыть файл журнала регистратора");
                    pf->setBaseTime(timeArray[0],firstDateTime);
                    ui->qwtPlot->installEventFilter(this);
                    ui->qwtPlot_2->installEventFilter(this);
                    moveMapMarker(0);
                    newLogProc->tmpFile.close();
                    this->resize(1025,725); //to fix size of scroll area and qwt plots we need to do this
                }
//                for(int i =0; i < cArrayDetailedPlot.size();i++)
//                    if(cArrayDetailedPlot[i].cAttachable)
//                {
//                }
             }
        }
        return 0;
    }
    return 1;
}


void MainWindow::initiateRadios()
{
    QPalette thermoPalette;
    int index=0, index_=0,attachableCount=0;
    curveWidgets cWidgets;
    attachableCount = cArrayDetailedPlot.size();
    for(int i = 0; i <cArrayDetailedPlot.size();i++ )
        if(!cArrayDetailedPlot[i].cAttachable)
            attachableCount--;
    for(int i = 0; i <cArrayDetailedPlot.size();i++ )
        if(cArrayDetailedPlot[i].cAttachable)
    {
        cWidgets.parLabel= cArrayDetailedPlot[i].cName;// = QString::fromLocal8Bit();
        cWidgets.axisButton = new QPushButton(this);
            if(cArrayDetailedPlot[i].cType==0)
            {
                    cWidgets.thermo = new QwtThermo(this);
                    cWidgets.checkBox = 0;
                    cWidgets.widgetType = 0;//means data
                    cWidgets.valueLabel = new QLabel(this);
                    QHBoxLayout *tmpLayout = new QHBoxLayout;
                    QHBoxLayout *tmpLayout_ = new QHBoxLayout;
                    cWidgets.thermoLayout = tmpLayout;
                    cWidgets.labelLayout = tmpLayout_;
                    ui->scrollArea->setLayout(ui->verticalLayout_7);
                    cArrayCurveWidgets.append(cWidgets);
                    buttonIndex = i;
                    connect(cArrayCurveWidgets[i].axisButton,SIGNAL(clicked()),this,SLOT(indexChanged()));
                    connect(cArrayCurveWidgets[i].axisButton,SIGNAL(released()),this, SLOT(hideAxis()));
                    thermoPalette.setColor(QPalette::ButtonText, cArrayDetailedPlot[i].cColor );
                    cArrayCurveWidgets[i].thermo->setMaxValue(cArrayDetailedPlot[i].curve->maxYValue()/*thermoPlotMaxs[i]*/);
                    cArrayCurveWidgets[i].thermo->setMinValue(cArrayDetailedPlot[i].curve->minYValue()/*thermoPlotMins[i]*/);
                    cArrayCurveWidgets[i].thermo->setOrientation(Qt::Horizontal,QwtThermo::NoScale);
                    cArrayCurveWidgets[i].thermo->setValue(Y[i][0]);
                    cArrayCurveWidgets[i].thermo->setMaximumHeight(70);
                    QVariant tmp;
                    tmp = cArrayCurveWidgets[i].thermo->value();
                    cArrayCurveWidgets[i].thermo->setToolTip(tmp.toString());
                    cArrayCurveWidgets[i].thermo->setAlarmEnabled(false);
                    cArrayCurveWidgets[i].thermo->setPalette(thermoPalette);
                    RotatedLabel *label1 = new RotatedLabel(cArrayCurveWidgets[i].parLabel);
                    cArrayCurveWidgets[i].valueLabel->setText(tmp.toString());
                    label1->setAngle(0);
                    cArrayCurveWidgets[i].axisButton->setFixedSize(20,20);
                    if(cArrayDetailedPlot[i].isCurveHidden)
                        cArrayCurveWidgets[i].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
                    else
                        cArrayCurveWidgets[i].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
                    cArrayCurveWidgets[i].labelLayout->addWidget(label1);
                    cArrayCurveWidgets[i].labelLayout->addStretch();
                    cArrayCurveWidgets[i].labelLayout->addWidget(cArrayCurveWidgets[i].valueLabel);
                    cArrayCurveWidgets[i].thermoLayout->addWidget(cArrayCurveWidgets[i].thermo);
                    cArrayCurveWidgets[i].thermoLayout->addWidget(cArrayCurveWidgets[i].axisButton);
                    cArrayCurveWidgets[i].thermoLayout->setMargin(0);
                    cArrayCurveWidgets[i].thermoLayout->setSpacing(0);
            }
        else if(cArrayDetailedPlot[i].cType==1)
        {
                cWidgets.thermo = 0;
                cWidgets.checkBox = new QCheckBox (this);
                cWidgets.widgetType = 1;//means flag
                cWidgets.valueLabel = 0;//no value just flag
                QHBoxLayout *tmplayout = new QHBoxLayout;
                cWidgets.thermoLayout = tmplayout;
                ui->scrollArea->setLayout(ui->verticalLayout_7);
                cWidgets.labelLayout =0;
                cArrayCurveWidgets.append(cWidgets);
                RotatedLabel *label1 = new RotatedLabel(cArrayCurveWidgets[i].parLabel);
                cArrayCurveWidgets[i].checkBox->setEnabled(false);
                cArrayCurveWidgets[i].checkBox->setStyleSheet("QCheckBox::disabled{color:black;}""QCheckBox::indicator:checked:disabled{background: black;}""QCheckBox::indicator:unchecked:disabled{border: 1px solid black;}");
                buttonIndex = i;
                connect(cArrayCurveWidgets[i].axisButton,SIGNAL(clicked()),this,SLOT(indexChanged()));
                connect(cArrayCurveWidgets[i].axisButton,SIGNAL(released()),this, SLOT(hideAxis()));
                cArrayCurveWidgets[i].checkBox->setCheckable(true);
                cArrayCurveWidgets[i].checkBox->setChecked((int)cArrayDetailedPlot[i].cData.at(0)%2);
                label1->setAngle(0);
                cArrayCurveWidgets[i].axisButton->setFixedSize(20,20);
                cArrayCurveWidgets[i].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
                cArrayCurveWidgets[i].thermoLayout->addWidget(label1);
                cArrayCurveWidgets[i].thermoLayout->addStretch();
                cArrayCurveWidgets[i].thermoLayout->addWidget(cArrayCurveWidgets[i].checkBox);
                cArrayCurveWidgets[i].thermoLayout->addWidget(cArrayCurveWidgets[i].axisButton);
                cArrayCurveWidgets[i].thermoLayout->setMargin(0);
                cArrayCurveWidgets[i].thermoLayout->setSpacing(0);
        }
        else if(cArrayDetailedPlot[i].cType==2)
            {
                cWidgets.thermo = 0;
                cWidgets.checkBox = 0;
                cWidgets.widgetType = 2;//means error
                cWidgets.valueLabel = new QLabel(this);//no flag just value
                QHBoxLayout *tmplayout = new QHBoxLayout;
                cWidgets.thermoLayout = tmplayout;
                ui->scrollArea->setLayout(ui->verticalLayout_7);
                cWidgets.labelLayout =0;
                cArrayCurveWidgets.append(cWidgets);
                RotatedLabel *label1 = new RotatedLabel(cArrayCurveWidgets[i].parLabel);
                buttonIndex = i;
                connect(cArrayCurveWidgets[i].axisButton,SIGNAL(clicked()),this,SLOT(indexChanged()));
                connect(cArrayCurveWidgets[i].axisButton,SIGNAL(released()),this, SLOT(hideAxis()));
                label1->setAngle(0);
                cArrayCurveWidgets[i].axisButton->setFixedSize(20,20);
                cArrayCurveWidgets[i].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
                cArrayCurveWidgets[i].thermoLayout->addWidget(label1);
                cArrayCurveWidgets[i].thermoLayout->addStretch();
                cArrayCurveWidgets[i].thermoLayout->addWidget(cArrayCurveWidgets[i].valueLabel);
                cArrayCurveWidgets[i].thermoLayout->addWidget(cArrayCurveWidgets[i].axisButton);
                cArrayCurveWidgets[i].thermoLayout->setMargin(0);
                cArrayCurveWidgets[i].thermoLayout->setSpacing(0);
            }
    }
    else
        {
            cWidgets.axisButton = 0;
            cWidgets.thermo = 0;
            cWidgets.checkBox = 0;
            cWidgets.widgetType = -1;//means flag
            cWidgets.valueLabel = 0;//no value just flag
            cArrayCurveWidgets.append(cWidgets);
        }
    ui->checkBox->setEnabled(true);
    connect(ui->checkBox,SIGNAL(toggled(bool)),this,SLOT(showAllCurves()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(increaseMagnifyFactor()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(decreaseMagnifyFactor()));
    ui->qwtPlot_2->enableAxis(QwtPlot::xBottom,true);
    ui->qwtPlot_2->enableAxis(QwtPlot::yLeft,true);
    ui->qwtPlot->enableAxis(QwtPlot::xBottom,true);
    plotRectBasicWidth = ui->qwtPlot_2->visibleRegion().rects()[1].width();
}


void MainWindow::on_pushButton_4_clicked()
{

    moveMapMarker(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    mapTimer->stop();
}

double MainWindow::getOffsetValue(int flagIndex)//this all is used to make correctly shown texts on flag curves
{

    double tmpOffset;
    int greatestFlagIndex=0;
    int flagOffsetMax=0;
    for(int i =0; i < cArrayDetailedPlot.size(); i++)
        if(cArrayDetailedPlot[i].cAttachable)
                {
                    if(cArrayDetailedPlot[i].cType==1)
                    {
                        flagOffsetMax+=2;
                    }
                }
    tmpOffset = (flagOffsetMax/flagCounter)/4;
    double tmpGain;
    double tmpMax;
    double tmpMin=0;
     if(flagOffsetMax<10)
     {
         if(flagOffsetMax<=1)
         {
             tmpMax = 0.6;
             tmpMin = -0.6;
         }
       else  tmpMax=10;
     }
     else
     {
          if((int)flagOffsetMax%10!=0)
            {
            if(flagOffsetMax>1)
                tmpMax = (int)((flagOffsetMax*10 +10)/10);
            }
        else tmpMax = flagOffsetMax;
     }
     if(tmpMax==10)
         tmpGain = (double)(tmpMax-tmpMin)/(flagCounter*2);
     else
        tmpGain = (double)(tmpMax-tmpMin)/(flagCounter*2+1);
    flagMarkerIncStep = tmpGain*2;
    tmpOffset = tmpGain/2 + tmpMin;
    flagMarkerOffsetBase = tmpOffset;
    for(int i = 0; i < flagIndex; i++)
    {
        if(cArrayDetailedPlot[i].cType==1)
        {
            tmpOffset+=flagMarkerIncStep;
        }
    }
    qDebug() << tmpOffset;
    qDebug() << flagOffsetMax;
    return tmpOffset;
}

void MainWindow::setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage)
{
    QString tmpParamValue;
    QVariant tmpval;
    if ((paramName == "Машина")/*||(paramName=="SAS_Counter                    ")*/)
        {
            paramValue = ui->tableWidget->item(0,0)->text();
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
        for (int i = 0; i < cArrayDetailedPlot.size(); i++)
        if(cArrayDetailedPlot[i].cAttachable)
        {

            if(cArrayDetailedPlot[i].cType==1)
            {
                tmpval = (int)(cArrayDetailedPlot[i].cData.at(recNo+printLeftTimeIndex))%2;
                paramValue = tmpval.toString();
            }
            else
            {
                tmpval = cArrayDetailedPlot[i].cData.at(recNo+printLeftTimeIndex);
                tmpval = tmpval.toFloat();
                paramValue =  tmpval.toString();
            }
         }
}
void MainWindow::on_actionPrint_triggered()
{
   int result = pf->exec();
   pf->SetMapMarkerPosition(timeArray[(int)verticalMapMarker->value().x()]);
   if(QDialog::Accepted == result)
   {
       convertTimeToPosition(pf->returnFromTime(),pf->retutnToTime());
       report = new QtRPT(this);
       QFileDialog dialog(this);
       QString fileName = "ascumarm_05_09_13.xml";
       report->recordCount << printRightTimeIndex - printLeftTimeIndex;
       if (report->loadReport(fileName) == false) {
       }
       else
       {
           QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                            this, SLOT(setValue(int&, QString&, QVariant&, int)));
       }
       report->printExec();
   }
}

void MainWindow::convertTimeToPosition(QDateTime firstTime, QDateTime secondTime)
{
    for(int i = 0; i < sizeOfArray; i++)
    {
        if(firstTime.toTime_t()<=timeArray[i])
        {
            printLeftTimeIndex = i;
            i=sizeOfArray;
        }

    }
    for(int i = printLeftTimeIndex; i < sizeOfArray; i++)
    {
        if(secondTime.toTime_t()<=timeArray[i])
        {
            printRightTimeIndex = i;
             i=sizeOfArray;
        }

    }
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
    for(int i =0; i < cArrayDetailedPlot.size();i++)
        if(cArrayDetailedPlot[i].cAttachable)
    {
        if(cArrayDetailedPlot[i].cType==1)
        {
            cArrayDetailedPlot[i].flagMarker->setValue(0.8*magVal +currentTimeMarker->value().x(),flagMarkerOffsetBase+tmpCounter*flagMarkerIncStep);
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
            offset = 0;
        }
        else
            offset = -ui->qwtPlot_2->visibleRegion().rects()[0].width();
    }
    return offset;
}

bool MainWindow::isCursorPositionOnDownPlot()
{
    int windowXpos= ui->qwtPlot->mapToGlobal(ui->qwtPlot->pos()).x();
    int cursorXPos =QCursor::pos().x();
    if((cursorXPos<(windowXpos+ui->qwtPlot->width()))&(cursorXPos>(windowXpos)))//&
          return true;
    else
        return false;
}

bool MainWindow::isCursorPositionOnUpPlot()
{
    int windowXpos= ui->qwtPlot_2->mapToGlobal(ui->qwtPlot_2->pos()).x();
    int cursorXPos =QCursor::pos().x();
    int windowYpos = ui->qwtPlot_2->mapToGlobal(ui->qwtPlot_2->pos()).y();
    int cursorYpos = QCursor::pos().y();
    if(((cursorXPos<(windowXpos+MainWindow::width()))&(cursorXPos>(windowXpos+ui->scrollArea->width())))&
            ((cursorYpos<(windowYpos+ui->qwtPlot_2->height()))&(cursorYpos>(windowYpos))))
        return true;
    else return false;
}

void MainWindow::cursorMoved(QPoint pos)
{

}

void MainWindow::on_qwtPlot_2_destroyed()
{

}
void MainWindow::showAllCurves()
{
    int index=0;
    double tmpMagVal = upPlotMagnifier(globalMagnifyFactor);
    for(int i = 0 ; i < cArrayDetailedPlot.size(); i++)
        if(cArrayDetailedPlot[i].cAttachable)
    {
        index = cArrayDetailedPlot[i].axis;
             if(ui->checkBox->checkState())
             {
                if(cArrayDetailedPlot[i].isCurveHidden)
                    {
                        if(cArrayDetailedPlot[i].cAttachable)
                            cArrayDetailedPlot[i].curve->attach(ui->qwtPlot_2);//by default we have 1st axis with this curve on the plot, also it is enabled by default
                        if(((cArrayDetailedPlot[i].cType==0)||(cArrayDetailedPlot[index].cType==2))&cArrayDetailedPlot[index].cAttachable)
                        {
                             if(index!=20)
                             {

                                 cArrayDetailedPlot[i].curve->setAxes(1,index);//this one
                                 ui->qwtPlot_2->enableAxis(index,true);//and enable it
                             }
                             else
                             {

                                 cArrayDetailedPlot[i].curve->setAxes(1,index-3);//this one
                                 ui->qwtPlot_2->enableAxis(index-3,true);//and enable it
                             }

                        }
                        else if((cArrayDetailedPlot[i].cType==1))
                         {
                            if(cArrayDetailedPlot[i].cAttachable)
                            {
                                cArrayDetailedPlot[i].flagMarker->setValue(tmpMagVal*0.8+verticalMapMarker->value().x(),getOffsetValue(i));
                                cArrayDetailedPlot[i].flagMarker->attach(ui->qwtPlot_2);                                
                            }
                         }
                    ui->qwtPlot_2->replot();
                    cArrayCurveWidgets[i].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
                    cArrayDetailedPlot[i].isCurveHidden = false;
                }
             }
            else
            {
                 if(!cArrayDetailedPlot[i].isCurveHidden )
                 {
                    cArrayDetailedPlot[i].curve->detach();//by default we have 1st axis with this curve on the plot, also it is enabled by default
                    if((cArrayDetailedPlot[i].cType==0)||(cArrayDetailedPlot[index].cType==2))
                    {
                        if(index!=20)
                        {

                            cArrayDetailedPlot[i].curve->setAxes(1,index);//this one
                            ui->qwtPlot_2->enableAxis(index,false);//and enable it
                        }
                        else
                        {

                            cArrayDetailedPlot[i].curve->setAxes(1,index-3);//this one
                            ui->qwtPlot_2->enableAxis(index-3,false);//and enable it
                        }
                    }
                    else if(cArrayDetailedPlot[i].cType==1)
                            cArrayDetailedPlot[i].flagMarker->detach();

                    ui->qwtPlot_2->replot();
                    cArrayCurveWidgets[i].axisButton->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
                    cArrayDetailedPlot[i].isCurveHidden  =true;
                }
         }
        }
    }

void MainWindow::moveMagnifyWidget()
{

}

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
    upPlotMagnifier(globalMagnifyFactor);
}

void MainWindow::getPointsQuantity(time_t firstTime, time_t lastTime)
{
    pointsQuantity = firstTime - lastTime;
}


int MainWindow::getClosestToPositionIndex(int pos)
{
    int incval = 0;
    for (int i = 1;  i < sizeOfArray; i++) //pointsQuantity - is a variable that discribes how many points should be on plot
    {
        if(timeArray[i]==timeArray[i-1])
            incval++; //incval is quantity of multipoints at same time
        if((int)timeArray[i] - (int)timeArray[0] > pos-incval)
        {
            if(i>1)
            {
                int j = i;
                while(j>=0)
                {
                    if((int)timeArray[j]- (int)timeArray[0]  <= pos-incval)
                    {
                        return j;
                    }
                    if(timeArray[j]==timeArray[j-1])
                        incval--;
                    j--;
                }
            }
            else
            {
                return i-1;
            }
        }
    }
    return 0;
}

void MainWindow::on_checkBox_clicked()
{

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{

}

void MainWindow::on_checkBox_toggled(bool checked)
{

}

void MainWindow::on_checkBox_pressed()
{

}

void MainWindow::on_actionHideLeftPanel_triggered()
{
        tmpRect = ui->qwtPlot_2->geometry();
        if(HideLeftArea)
        {
            HideLeftArea = false;
            tmpRect.setX(18);
            tmpRect.setY(tmpRect.y());
            ui->scrollArea->resize(1,ui->scrollArea->size().height());
            ui->qwtPlot_2->setGeometry(tmpRect);
            tmpIcon = new QIcon(":new/p/sp");
            ui->actionHideLeftPanel->setIcon(*tmpIcon);

        }
        else
        {
            HideLeftArea = true;
            tmpRect.setX(312);
            tmpRect.setY(tmpRect.y());
            ui->scrollArea->resize(295,ui->scrollArea->size().height());
            ui->qwtPlot_2->setGeometry(tmpRect);
            tmpIcon = new QIcon(":new/p/hp");
            ui->actionHideLeftPanel->setIcon(*tmpIcon);
        }
}

void MainWindow::on_actionHideLeftPanel_triggered(bool checked)
{

}

void MainWindow::on_actionHideLeftPanel_toggled(bool arg1)
{

}

void MainWindow::on_pushButton_5_clicked()
{

}
