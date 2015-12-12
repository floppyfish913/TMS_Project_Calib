#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <QFrame>
#include "uart_handler.h"

namespace Ui {
class Device_info;
}

class Device_info : public QFrame
{
    Q_OBJECT

public:
    explicit Device_info(UART_Handler * s,QWidget *parent = 0);
    ~Device_info();
    void Set_SN(QString SN);
    void Set_Manufacturing_Date(QString Date);
    void Set_Calib_Date(QString Date);
    void Set_Check_Date(QString Date);
    void Set_PCB_Ver(QString ver);
    void Set_SW_Ver(QString ver);
signals:
    void Refresh_Device_Data();
private slots:
    void on_pushButton_3_clicked();
    void on_Read_clicked();

private:
    Ui::Device_info *ui;
    UART_Handler * Serial;
};

#endif // DEVICE_INFO_H
