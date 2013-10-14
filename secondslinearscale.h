#ifndef SECONDSLINEARSCALE_H
#define SECONDSLINEARSCALE_H
#include "qwt_scale_engine.h"
class SecondsLinearScaleEngine : public QwtLinearScaleEngine
{
public:
    virtual void autoScale( int maxSteps,
        double &x1, double &x2, double &stepSize ) const;

protected:
    double divideInterval( double interval, int numSteps ) const;
    double ceil60 ( double v ) const;

};

#endif // SECONDSLINEARSCALE_H
