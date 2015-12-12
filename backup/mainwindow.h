#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uart_handler.h"
#include "qcustomplot.h"
#include "curve_analyzer.h"
#include "device_info.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void new_data();
    QList<double> x,y,xp,yp;

private slots:

    void on_Connect_clicked();

    void on_ClearBTN_clicked();

    void on_ToFile_clicked();

    void on_CalibBTN_clicked();

    void on_Dev_info_btn_clicked();

public slots:
    void listen();
 //   void Write_data(Device _out);
  //  void Read_Data(Device * _in);

private:
    UART_Handler * Serial;
    Ui::MainWindow *ui;
    Device_info * dev_info;
    double shr_1,shr_2;
    int start_flag,loop;
    QCPCurve * curve;
    QCPCurve * limits;
    curve_analyzer * analyze;
    int I;
};

#endif // MAINWINDOW_H
