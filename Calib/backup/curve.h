#ifndef CURVE_H
#define CURVE_H

#include <QObject>
#include <QList>
class Curve
{
public:
    Curve();
    double abs_avg();
    double max_volume();
    double factor();
    void append(double add);
    void clear();
    void set_pump(int vol);
    void set_avg(int _avg);
private:
    QList<double> curve;
    int pump;
    int avg;
signals:

public slots:
};

#endif // CURVE_H
