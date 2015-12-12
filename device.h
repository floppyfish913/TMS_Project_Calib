#ifndef DEVICE_H
#define DEVICE_H
#include <QQueue>
#include <QString>
#include <QtCore>
#include <QVector>

class Device
{
public:
    Device();
    QList<double> get_all();
    void MSG_Handler(QString msg);
    void addData(double data);
    int QChar_to_int(QChar in);
    QQueue<int> data_buffer;

    QString Name;
    QString SW_ver;
    QString Serial_Number;
    QString PCB_ver;
    QString Manufacturing_Date;
    QString Calib_Date;
    QString Check_Date;

private:
signals:

public slots:
};

#endif // DEVICE_H
