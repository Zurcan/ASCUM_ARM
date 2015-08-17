#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_curve_fitter.h>
#include <qwt_color_map.h>
#include <qwt_scale_widget.h>
#include <qwt_painter.h>
#include <qwt_text.h>
#include <qwt_abstract_scale_draw.h>
#include <qwt_scale_draw.h>
#include <qwt_abstract_scale.h>
#include <qwt_scale_engine.h>
#include <qwt_global.h>
#include <qwt_interval.h>
#include <qwt_text_label.h>
#include <qwt_plot_picker.h>
#include <qwt_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_directpainter.h>
#include <qwt_symbol.h>
#include <qwt_scale_div.h>
#include <qwt_thermo.h>

#include <QLayout>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <QPalette>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia>
#include <QtMultimedia/QVideoFrame>
#include <QtMultimedia/QMediaPlayer>
#include <QMovie>
#include <qvideosurfaceformat.h>
#include <QMediaPlaylist>
#include <QFileDialog>
#include "WWidget.h"
#include "NcFramelessHelper.h"
#include "rotatedlabel.h"
#include <QString>
#include <LOG_PROCESSOR/logprocessor.h>
#include <TMIinterpretator.h>
#include <QMessageBox>
#include <welcomedialog.h>
#include <qtimer.h>
#include <QCheckBox>
#include <printform.h>
#include <qtrpt.h>
#include <QMouseEvent>
#include <QCursor>
#include <QSpacerItem>
#include <QVector>
#include <msgSys.h>
#include <QTableWidgetItem>
#include <QXmlStreamReader>
namespace Ui {
class MainWindow;
}

    class errorPicker: public QwtPlotPicker
    {
    public:
        errorPicker(QwtPlotCanvas *canvas):QwtPlotPicker(canvas){}
        ~errorPicker(){errDesc.clear();}
        int sizeOfArr;
        int ErrBaseVal;
        int getClosestToPosIndex(int pos) const;
        QString errorDecoder(int errorCode)const;
        typedef struct
        {
            time_t time;
            int errors;
            double errAddress;
            double errCoord;
        }errDescriptor;
        QVector <errDescriptor> errDesc;
        void setDisplayMode(DisplayMode trackerMode);
        void initArrs(int arrsize);
        virtual QwtText trackerTextF(const QPointF & pos) const
        {
            int currentpos = 0;
            int currentErr = 0;
            QString hex;
            QwtText text;
            text.setText("");
            int intpos = (int)pos.x();
            int ypos = (int)pos.y();
            currentpos = getClosestToPosIndex(intpos);
            if(currentpos<0)
            {
                currentpos = 0;
                currentErr = errDesc[currentpos].errors;//errorsArr[currentpos];
            }
            else
                currentErr = errDesc[currentpos].errors;//errorsArr[currentpos];
            hex.setNum(currentErr,16);
            if((errDesc[currentpos].errors!=0)&(/*(errDesc[currentpos].errCoord==ypos-1)||(errDesc[currentpos].errCoord==ypos+1)||*/(errDesc[currentpos].errCoord==ypos)))
                text.setText(/*"( установлена ошибка: "+*/errorDecoder(currentErr)/*hex*//*+")"*/);
            qDebug() << currentpos<<errDesc[currentpos].errCoord<<errDesc[currentpos].errors<<ypos;
            return text;
        }
        void cleanBeforeClose();

    private:


    };

class MainWindow : public QMainWindow
{
    Q_OBJECT




public:
    class TimeScaleDraw: public QwtScaleDraw
    {
    public:
        TimeScaleDraw( const QDateTime &base ):
            baseTime( base )
        {
        }
        time_t *timeArr;
        long maxVal;
        long currentIndex;
        virtual QwtText label( double v ) const
        {
            QDateTime upTime;
            QString tmp="";
            if((long)v < 0) return tmp;// аналогично переделать для всех значений V, кроме текущего индекса
            if((long)v > maxVal) return tmp;
                if((long)v==currentIndex)
                {
                    if(!(long)v)
                        upTime = baseTime;
                    else
                        upTime = QDateTime::fromTime_t(timeArr[(long)v]);
                }
                else return tmp;
            return upTime.time().toString();
        }


    private:
        QDateTime baseTime;

    };


    class MapTimeScaleDraw: public QwtScaleDraw
    {
    public:
    MapTimeScaleDraw(QString fmt) : format(fmt) { }
    time_t *timeArr;
    virtual QwtText label(double v) const
    {
       QwtText retVal;
       QDateTime upTime = QDateTime::fromTime_t(timeArr[(int)v]);
       if(v==0)
       {
           retVal = upTime.toString("dd.MM.yyyy hh:mm:ss");
           return retVal;
       }
       else return upTime.toString(format);
    }
    private:
    const QString format;
    };

    class VerticalFlagScaleDraw: public QwtScaleDraw
    {
    public:
        VerticalFlagScaleDraw(int count) :  countSet(count) { }

    virtual QwtText label(double v) const
    {
         if(countSet < (int)v)
             v=countSet;
         QString labelText = "0";
         if((int)v%2)labelText = "1";

        return labelText;
    }
    private:
    const int countSet;
    };


class MyPlotCurve: public QwtPlotCurve
{
public:
    MyPlotCurve(double offset) : setOffset(offset){}
private:
    void shiftDown( QRect &rect, int offset ) const
    {
        MyPlotCurve::boundingRect().translate( 0, 2);
    }

private:
    const double setOffset;
};
    QwtPlotDirectPainter *rtPainter;
    QwtSymbol errorSym;
    QVector <double> ErrXCoords;
    typedef struct
    {
        int code;
        int coord;
    }errCoordStruct;
    QVector <errCoordStruct> ErrCoordVector;
    typedef enum
    {
        data=0,
        flag=1,
        error = 2,
        fill = 3 ,
        notavailable = -1

    }curvetypes;

    typedef struct
    {
        QwtPlotCurve *curve;              //qwt class for curve
        int axis;                         //axis scale number
        QColor cColor;                    //same as name
        curvetypes cType;                 //what kind curve it is
        QVector <double> cData;           //vasts of data
        bool cAttachable;                 //is this curve used on plot or not
        bool isCurveHidden;
        QwtPlotMarker *flagMarker;
        QString cName;
    }curves;                              //each struct means a curve
    typedef struct
    {
        QPushButton *axisButton;
        QCheckBox   *checkBox;
        QwtThermo   *thermo;
        QHBoxLayout *thermoLayout;
        QHBoxLayout *labelLayout;
        QLabel      *valueLabel;
        QString     parLabel;
        int widgetType; // same as curvetypes

    }curveWidgets;
    typedef struct
    {
        bool invisibility;
        int interpIndex;
    }invisibleInterpItems; //this struct is middle layer between interitems and curves themselves
    QVector <invisibleInterpItems> invisIntItems;
    QVector <curves> cArrayDetailedPlot;
    QVector <curves> cArrayGlobalMapPlot;
    QVector <curveWidgets> cArrayCurveWidgets;
    curves errorCurve;
    int powOffIndex;
    QwtThermo *thermo[24];
    QCheckBox *checkBox[24];
    double *ErrCoords;
    int *ErrCode;
    int maxErrCoord;
    int globalAddErrFlagBaseLine;
    int errCodeIndex;
    int errAddIndex;
    int globalCursorMove;
    int globalCursorFirstPressPos;
    int plotRectBasicWidth;
    bool mapPlotUsed = false;
    bool rightButtonPressed = false;
    QString lastOpenedFileName;
    QVector <QString> errorCodes ;
#define MAX_POINTS 1000000
    bool dateChangedArrExistFlag;
    bool timeFractExistFlag;
    bool powOnTimeArrayExistFlag;
    bool isOpened=false;
    bool leftButtonPressed=false;
    bool leftButtonReleased=false;
    bool reOpenWindow = false;
    bool OldLog;
    double globalMagVal=100;
    double globalSavedCursorMove=0;
    int globalMagnifyBaseVal = 148;
    TimeScaleDraw *timeScale;
    MapTimeScaleDraw *mapTimeScale;
    VerticalFlagScaleDraw *verticalFlagScale;
    QTimer *mapTimer;
    int lastFlag;
    int mapTimerDelay = 1000;
    int globalMagnifyFactor=100;
    bool rectsInc=false;
    int rectQty = 2;
    int globalMagnifierPreviosPos;
    int globalCursorPos;
    int beforeMovePosition;
    int globalMoveFlag=false;
    QPoint globalCursorPoint;
    QIcon *tmpIcon;
    QDateTime AxisLabelDate;
   int axisCount = 2;
   int varCounter;
   int invisibleVarCounter;
   QVector <bool> invisibleVarsMask;
   unsigned char *timeFract;
   time_t *powOnTimeArray;
   QString tmpStr;
   PrintForm *pf;
    QwtPlotMarker *verticalMapMarker;
    QwtPlotMarker *currentTimeMarker;
    errorPicker *errpicker;
    unsigned int sizeOfArray=1000;
    QString filename;
    QString openedFileName;
    char tmpHeadArr[208];
    char tmpFHPtr[40];
    QString verticalHeaderName;
    TMIinterpretator *newTmiInterp;
    #define smallTableID 0x80000012
    #define bigTableID 0x80000011
    #define localizationTableID 0x00000001
    #define camOffsetID 0x80000081
    MainWindow *newWin = 0;
    QtRPT *report;
    double *X;
    double *Y[24];
    bool *dateChangedArr;
    QwtText markerLbl;
    time_t *timeArray;
    time_t *allPoints;
    time_t endOfLogTime;
    int flagPowOffCount;
    int pointsQuantity;
    int lastTimeVal;
    int flagArray[24];
    int pointerToEng1Spd=0;
    int pointerToEng2Spd=0;
    int pointerToSpd=0;
    int pointerToDateChg=0;
    double thermoPlotMins[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0,0};
    double thermoPlotMaxs[24];// = {10, 100, 80, 90, 200, 210, 1500, 130, 1, 1, 1, 1,1}; //
    bool isAxisHidden[24];//QVector <bool> isAxisHidden;// ={false, false, false, false, false, false, false, false, false, false, false, false, false};

    QMovie *movie;
    QPrinter *printer;
    logProcessor *newLogProc;
    msgSys *myMsgSys;

    QMediaPlayer *videoPlayer1,*videoPlayer2;
    QHBoxLayout *videoLayout1, *videoLayout2;
    QMediaPlaylist *playlist;
    QwtPlotCanvas *canvas;

    QWidget  *videoScreen1;
    QWidget *videoScreen2;
    QMessageBox newMessage;
    NcFramelessHelper *fh1,*fh2;
    QColor colors[23] = { QColor(0,102,255,127), QColor(255,204,255,255), Qt::lightGray, Qt::darkGray, Qt::green, Qt::darkCyan,  QColor(204,255,102,255), Qt::darkRed, Qt::darkMagenta, QColor(255,0,0,127), QColor(255,204,255,255),Qt::darkGreen, Qt::magenta, Qt::blue, QColor(160,102,0,255), QColor(255,160,255,255), QColor(202,255,0,255), QColor(255,0,0,127), Qt::darkYellow, Qt::cyan, QColor(202,202,255,255), QColor(102,0,160,255), QColor(255,160,50,255)};
    QDateTime firstDateTime;
    int printLeftTimeIndex=0, printRightTimeIndex=0;
    QwtPlotCurve *curve1[24];
    QwtPlotCurve *curve2[24];

    QwtPlotMarker *errorMarker;
    QwtPlotCurve *ErrCurve;
    double flagMarkerOffsetBase = 1.25;
    double flagMarkerIncStep = 0;
    int flagCounter = 0;
    bool invertedTime = true;
    bool HideLeftArea;
    bool NoFileWasOpened;
   /*here are the stats of the machine*/

    explicit MainWindow(QWidget *parent = 0);
    void moveMapMarker(long int globalPosition);
    void reinit();
    void convertTimeToPosition(QDateTime firstTime, QDateTime secondTime);
    void preparePlotData();
    void initiateThermos();
    void initiateVideoScreens();
    void initiateCurves();
    void initCurves();              //for new curves
    int generateLinearTimeArr(double *linearizedTA);
    bool checkFileHeaderCRC();
    void initiatePlotMarkers();
    void readHeadTableData();
    bool readDataFromLog();
    int initPicker();
    void globalInits(int arrayIndexSize);
    bool initiateTimeAxis(QDateTime startPoint, time_t *times, int length);
    void initGloabalArrays(int values);
    void setGlobalArrays();
    void hideWasteAxes(int notHiddenIndex);
    bool checkSegmentCRC(long segmentID);
    void openAndPlayVideo();
    void initiateRadios();
    double getOffsetValue(int flagIndex);
    double upPlotMagnifier(int);
    int setFilledPowerOffTime(double *X);
    int createErrCoordsCurve(double *X);

    int createErrCoordsArray();
    int openLog();
    int createErrCodeFromErrAddArray(double *X);
    int closeLog();\
    int checkLogToBeClosed(QString nameOfOpenedFile); //check if new opening file is really new, if file is duplicated with old, just do nothing, if file is not exist show an error
    void resizeEvent(QResizeEvent *);
    int getClosestToPositionIndex(int);
    void openNewMainWindow();
    bool isCursorPositionOnUpPlot();
    bool isCursorPositionOnDownPlot();
    int calculateCursorPlotOffset();
    void initFlagScale();
    void getPointsQuantity(time_t firstTime,time_t lastTime);
    ~MainWindow();
public slots:
    bool eventFilter(QObject *, QEvent *);
private slots:

    void hideAxis();
    void moveMagnifyWidget();
    void increaseMagnifyFactor();
    void decreaseMagnifyFactor();
    void cursorMoved(QPoint);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void indexChanged();
    void showAllCurves();
    void on_actionOpen_triggered();
    void incrementMarkerPosition();
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_actionPrint_triggered();
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
    void on_qwtPlot_2_destroyed();

    void on_checkBox_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_toggled(bool checked);

    void on_checkBox_pressed();

    void on_actionHideLeftPanel_triggered();

    void on_actionHideLeftPanel_triggered(bool checked);

    void on_actionHideLeftPanel_toggled(bool arg1);

private:
    int buttonIndex;
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
