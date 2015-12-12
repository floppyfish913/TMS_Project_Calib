#ifndef CALIB_TABLE_H
#define CALIB_TABLE_H
#include <QList>
#include <QObject>

typedef struct {
    double freq;
    double factor;

}calib_table_row;


class calib_table
{
public:
    calib_table();
    void add(double freq,double factor);
    QList<calib_table_row> get_table();
    void clear();
private:
    QList<calib_table_row> table;

signals:

public slots:
};

#endif // CALIB_TABLE_H
