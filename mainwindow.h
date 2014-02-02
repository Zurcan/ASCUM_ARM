#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_curve_fitter.h>

#include <qwt_scale_widget.h>
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
#include <qwt_thermo.h>
#include <QString>
#include <logprocessor.h>
#include <TMIinterpretator.h>
#include <QMessageBox>
#include <qwt_text.h>
#include <qwt_abstract_scale_draw.h>
#include <qwt_scale_draw.h>
#include <qwt_abstract_scale.h>
#include <qwt_scale_engine.h>
#include <qwt_global.h>
#include <qwt_interval.h>
#include <welcomedialog.h>
#include <qtimer.h>
#include <QCheckBox>
#include <printform.h>
#include <qtrpt.h>
#include <qwt_scale_div.h>
#include <QMouseEvent>
#include <QCursor>
#include <qwt_plot_picker.h>
#include <QSpacerItem>
#include <qwt_plot_directpainter.h>
#include <qwt_symbol.h>
//#include "secondslinearscale.h"
//#include <qwt_a
namespace Ui {
class MainWindow;
}
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
        int maxVal;
        int currentIndex;
        virtual QwtText label( double v ) const
        {
            QDateTime upTime;
            QString tmp="";
            if((int)v < 0)return tmp;// аналогично переделать для всех значений V, кроме текущего индекса
            if((int)v>maxVal) return tmp;
//            if((int)v==0)
//                upTime = baseTime;
           // else
                if((int)v==currentIndex)
                {
                    if(!(int)v)
                        upTime = baseTime;
                    else
                        upTime = QDateTime::fromTime_t(timeArr[(int)v]);
                }
                else return tmp;
            return upTime.time().toString();
        }
//        void updateBaseTime(const QDateTime &updatedInitialTime)
//        {
//            baseTime=updatedInitialTime;
//            invalidateCache();
//        }

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


    //QDateTime t = QDateTime::fromTime_t((int)v);
    //return t.toString(format);
       if(v==0)
       {
           //label.setColor(Qt::yellow);
          // label(QwtText::setRenderFlags(Qt::AlignRight));
           retVal = upTime.toString("dd.MM.yyyy hh:mm:ss");
           //retVal.setRenderFlags(Qt::AlignRight);
          // retVal.setRenderFlags(Qt::AlignTrailing);
           return retVal;
       }
       else return upTime.toString(format);
    }


    private:
    const QString format;
    //const QString firstFormat="dd MM hh:mm:ss yy";
    };

    class VerticalFlagScaleDraw: public QwtScaleDraw
    {
    public:
        VerticalFlagScaleDraw(int count) :  countSet(count) { }
    //time_t *timeArr;
    // int count;
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

//    class ShiftData: public QwtPointSeriesData
//    {
//    public:
//        ShiftData( const QVector<QPointF> &samples ):
//            //QwtPointSeriesData( samples ):
//            m_offset( 10.0 )
//        {
//        }
//        void setOffset( double off )
//        {
//            m_offset = off;
//        }

//        virtual QPointF sample( size_t index ) const
//        {
//            QPointF point = QwtPointSeriesData::sample( index );
//            return QPointF( point.x(), point.y() + m_offset );
//        }

//        virtual QRectF boundingRect() const
//        {
//            return QwtPointSeriesData::boundingRect().translated( 0.0, m_offset );
//        }
//    private:
//        double m_offset;
//    };

class MyPlotCurve: public QwtPlotCurve
{
public:
    MyPlotCurve(double offset) : setOffset(offset){}
private:
    void shiftDown( QRect &rect, int offset ) const
    {
//        QwtPlotCurve.boundingRect()
        MyPlotCurve::boundingRect().translate( 0, 2);
    }
//   virtual void QwtPlotCurve::applyOffset(const double *xData, const double *yData, int size )
//        {
//            delete d_series;
//            d_series = new QwtPointArrayData( xData, yData, size );
//            itemChanged();
//        }
private:
    const double setOffset;
};
   // QwtPlot
    QwtPlotDirectPainter *rtPainter;
    QwtPlotPicker *plotPointer;
    QwtSymbol errorSym;
    QVector <int> ErrXCoords;
    QVector <long> ErrCode;
    QVector <QPointF> ErrCoords;
    int globalCursorMove;
    int globalCursorFirstPressPos;
    int plotRectBasicWidth;
    bool mapPlotUsed = false;
    bool rightButtonPressed = false;
//    QwtPlot upPlot;// = new QwtPlot()
    bool isOpened=false;
    bool leftButtonPressed=false;
    bool leftButtonReleased=false;
    bool reOpenWindow = false;
    double globalMagVal=100;
    double globalSavedCursorMove=0;
    int globalMagnifyBaseVal = 148;
    TimeScaleDraw *timeScale;
    MapTimeScaleDraw *mapTimeScale;
    VerticalFlagScaleDraw *verticalFlagScale;
    QTimer *mapTimer;
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
    QwtAbstractScale *abstractScale;
    QwtAbstractScaleDraw *abstractScDraw;
    QwtScaleDraw *myScaleDraw;
    QDateTime AxisLabelDate;
   int axisCount = 2;
   int varCounter;
   QString tmpStr;
   PrintForm *pf;
    QwtPlotMarker *verticalMapMarker;
    QwtPlotMarker *currentTimeMarker;
    int sizeOfArray=1000;
    QString filename;
    QString openedFileName;
    char tmpHeadArr[208];
    char tmpFHPtr[40];
    char *buffArr;
    QString verticalHeaderName;
    TMIinterpretator *newTmiInterp;
    #define smallTableID 0x80000012
    #define bigTableID 0x80000011
    MainWindow *newWin = 0;
    QtRPT *report;
    double *X;
    double *Y[24];
    QwtText markerLbl;
    time_t *timeArray;
    time_t endOfLogTime;
    int pointsQuantity;
    int lastTimeVal;
    int flagArray[24];
    double thermoPlotMins[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0,0};
    double thermoPlotMaxs[24];// = {10, 100, 80, 90, 200, 210, 1500, 130, 1, 1, 1, 1,1}; //
    bool isAxisHidden[24];// ={false, false, false, false, false, false, false, false, false, false, false, false, false};
    QString parLabel[24];// = {"Скорость, км/ч", "Скорость двиг. 1, км/ч", "Скорость двиг. 2, км/ч", "Давление торм. маг. бар", "Давление торм. цил. бар", "highWayPres","Потребление топлива, л", "Флаг вперед", "Флаг назад", "ErrorHide", "ErrorRaise","parampampam","parampampampam"};
    //QString parLabelNew[];
    QMovie *movie;
    QPrinter *printer;
    logProcessor *newLogProc;
 //   QVideoWidget *myVideo;
//    QRadioButton *radio[24];
    QwtThermo *thermo[24];
    QCheckBox *checkBox[24];
    QPushButton *axisButton[24];
   // QwtThermo *Thermo1,*Thermo2,*Thermo3,*Thermo4,*Thermo5,*Thermo6,*Thermo7,*Thermo8,*Thermo9,*Thermo10,*Thermo11,*Thermo12,*Thermo13;
    QMediaPlayer *videoPlayer1,*videoPlayer2;
    QHBoxLayout *videoLayout1, *videoLayout2;
    QMediaPlaylist *playlist;
    QHBoxLayout *thermoLayout[24] ;
    QHBoxLayout *labelLayout[24];//we have to add this layout to print value of the thermo near to the label1
    QLabel *valueLabel[24];// here we will print value of the thermo
    QWidget  *videoScreen1;
    QWidget *videoScreen2;
    QMessageBox newMessage;
    NcFramelessHelper *fh1,*fh2;
    QColor colors[23] = {Qt::darkGreen, Qt::blue, Qt::lightGray, Qt::darkGray, Qt::green, Qt::darkCyan, Qt::magenta, QColor(204,255,102,255), Qt::darkRed, Qt::darkMagenta, QColor(255,0,0,127), QColor(255,204,255,255), QColor(0,102,255,127), QColor(255,204,255,255),QColor(160,102,0,255), QColor(255,160,255,255), QColor(202,255,0,255), QColor(255,0,0,127), Qt::darkYellow, Qt::cyan, QColor(202,202,255,255), QColor(102,0,160,255), QColor(255,160,50,255)};
    QDateTime firstDateTime;
    int printLeftTimeIndex=0, printRightTimeIndex=0;
    QwtPlotCurve *errorCurve;
    QwtPlotCurve *curve1[24];
    QwtPlotCurve *curve2[24];
    QwtPlotMarker *flagMarker[24];
    QwtPlotMarker *errorMarker;
    double flagMarkerOffsetBase = 1.25;
    double flagMarkerIncStep = 0;
    int flagCounter = 0;
   /*here are the stats of the machine*/

    explicit MainWindow(QWidget *parent = 0);
    void moveMapMarker(long int globalPosition);
    void convertTimeToPosition(QDateTime firstTime, QDateTime secondTime);
    void preparePlotData();
    void initiateThermos();
    void initiateVideoScreens();
    void initiateCurves();
    bool checkFileHeaderCRC();
    void initiatePlotMarkers();
    void readHeadTableData();
    void readDataFromLog();
    void globalInits(int arrayIndexSize);
    void initiateTimeAxis(QDateTime startPoint, time_t *times, int length);
    void initGloabalArrays(int values);
    void setGlobalArrays();
    void hideWasteAxes(int notHiddenIndex);
    bool checkSegmentCRC(long segmentID);
    void openAndPlayVideo();
    void initiateRadios();
    double getOffsetValue(int flagIndex);
    double upPlotMagnifier(int);
    //void upPlotMoveCursor(int);
    void openLog();
    void closeLog();

    int getClosestToPositionIndex(int);
    void openNewMainWindow();
    bool isCursorPositionOnUpPlot();
    bool isCursorPositionOnDownPlot();
    int calculateCursorPlotOffset();
    void getPointsQuantity(time_t firstTime,time_t lastTime);
    ~MainWindow();
public slots:
    bool eventFilter(QObject *, QEvent *);
   // void ::mouseMoveEvent(QMouseEvent *);
private slots:

    void hideAxis();
//    void mousePressEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *);
    void moveMagnifyWidget();
    void increaseMagnifyFactor();
    void decreaseMagnifyFactor();
    void cursorMoved(QPoint);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void indexChanged();
    //void collapseAllCurves();
    void showAllCurves();
    void on_actionOpen_triggered();
    void incrementMarkerPosition();
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_actionPrint_triggered();
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
    void on_qwtPlot_2_destroyed();

private:
    int buttonIndex;
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
