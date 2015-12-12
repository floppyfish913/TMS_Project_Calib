#ifndef UART_HANDLER_H
#define UART_HANDLER_H
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCore>
#include <QQueue>
#include <QVector>
#include "device.h"
class UART_Handler : public QThread
{
    Q_OBJECT

public:
    UART_Handler();
    void open();
    void close();
    bool isOpen();
    void Init(QString portname, QSerialPort::BaudRate baud,QSerialPort::Parity parity,QSerialPort::StopBits stopbits);
    int bufferCount();
    void run();
    QList<double> GetMsg();
    Device dev;
    QQueue<char> buffer;
private:
    QString MSG;
    QSerialPort port;


signals:
    void NotEmpty();

public slots:
};



#endif // UART_HANDLER_H
