#ifndef CURVE_ANALYZER_H
#define CURVE_ANALYZER_H
#include <QObject>
#include "calib_table.h"
#include "curve.h"
class curve_analyzer
{
public:
    curve_analyzer();
    void clear();
    void analyze(QList<double> collected_data);
    calib_table table;
    void set_calib_average(int _avg);
    void set_calib_pump_volume(int vol);
private:
    QList<Curve> datas;
    int pump;
    int avg;
signals:

public slots:
};

#endif // CURVE_ANALYZER_H
