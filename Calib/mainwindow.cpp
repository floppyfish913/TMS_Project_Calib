#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "uart_handler.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>
#include "curve_analyzer.h"
#include "device_info.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    I = 0;

    QList<QSerialPortInfo> myports ;

    int i = myports.size();

    ui->setupUi(this);



    Serial = new UART_Handler();
    analyze = new curve_analyzer();
    dev_info = new Device_info(Serial);

    // initialize Graphs

    curve = new QCPCurve(ui->customplot->xAxis,ui->customplot->yAxis);
    limits = new QCPCurve(ui->customplot->xAxis2,ui->customplot->yAxis2);
    ui->customplot->addPlottable(curve);
    ui->customplot->addPlottable(limits);

    limits->setPen(QPen(Qt::red,3));
    curve->setPen(QPen(Qt::green,3));
    ui->customplot->setBackground(QBrush(Qt::black));
    ui->customplot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setTickLabelColor(Qt::white);
    ui->customplot->yAxis->setTickLabelColor(Qt::white);
    ui->customplot->xAxis2->setVisible(true);
    ui->customplot->yAxis2->setVisible(true);


    //serial port info

    myports = QSerialPortInfo().availablePorts();
    for(i=0;i<myports.size();i++)
           ui->PortNamesBox->addItem(myports[i].portName());

    //signal - slots connections
    //UART handler && Mainwindow connection
    connect(Serial,SIGNAL(NotEmpty()),this,SLOT(listen()));
    //Device info connections
    connect(dev_info,SIGNAL(Refresh_Device_Data()),this,SLOT(device_info_refresher()));


    //init variables
    loop = 0;
    shr_1 = 0;
    shr_2 = 0;
    start_flag = 0;
}

MainWindow::~MainWindow()
{
    Serial->close();
    delete ui;
}

void MainWindow::on_ToFile_clicked()
{
    QFile file(ui->export_filename->text());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&file);
    int i;
    for(i=0;i<y.size();i++)
        out << y[i] <<endl;
    file.close();
}

void MainWindow::on_Connect_clicked()
{

   Serial->Init(ui->PortNamesBox->currentText(),QSerialPort().Baud115200,QSerialPort().NoParity,QSerialPort().OneStop);

    if (Serial->isOpen())
    {
        ui->Connect->setText("Connect");
        Serial->close();
     }
    else
    {
        ui->Connect->setText("Disconnect");
        Serial->open();
    }

}



void MainWindow::listen(){
    double sign;
    static QVector<double> x_limit,y_limit;
    static QCPRange range;
    static QMessageBox popup;
    popup.setText("Calibration finished!");
    int i;
    static int discard = 0;
    QList<double> data;
    data =Serial->GetMsg();
    if(y.isEmpty()) {
        discard = 0;
        shr_1 = 0;
        shr_2 = 0;
        start_flag = 0;
        loop = 0;
    }
    y.append(data);
    if (!data.isEmpty() && !discard){
        for(i=0;i<data.length();i+=20){
            sign = data[i];

            yp += sign;
            if(xp.isEmpty())
                xp += sign;
            else
                xp += xp.last()+sign;

            if(yp.count()>1000) {
                yp.removeAt(0);
                xp.removeAt(0);
            }
        }
    }
    else
        return;

    if(yp.length()>3){
        shr_1 = yp.last();
        if ( shr_1-shr_2 > 0 && start_flag == 0)
            start_flag = 1;
        else if ( shr_1-shr_2 < 0 && start_flag == 0)
            start_flag = -1;

        if ((start_flag == -1) && (shr_1 < 0) && (shr_2 > 0))
            loop++;

        if ((start_flag == 1) && (shr_1 > 0) && (shr_2 < 0))
            loop++;

        shr_2=yp.last();

    }

    //creating limits
    range = ui->customplot->xAxis->range();
    x_limit.clear();
    y_limit.clear();
    x_limit << -1000000 << 1000000 << 1000000 << -1000000;
    y_limit << 50*(1+loop/ui->average->value()) <<50*(1+loop/ui->average->value())<<-50*(1+loop/ui->average->value())<<-50*(1+loop/ui->average->value());


    curve->setData(xp.toVector(),yp.toVector());
    limits->setData(x_limit,y_limit);
    ui->customplot->xAxis->rescale();
    ui->customplot->yAxis->setRange(-50*1.5*(1+loop/ui->average->value()),50*1.5*(1+loop/ui->average->value()));
    ui->customplot->yAxis2->setRange(-50*1.5*(1+loop/ui->average->value()),50*1.5*(1+loop/ui->average->value()));


    ui->customplot->replot();
    ui->loop_vis->setText(QString::number(loop % ui->average->value() + 1) + "/" + QString::number(ui->average->value()));
    ui->progressBar->setValue(loop*100/(6*ui->average->value()));

    if(loop == 6*ui->average->value()){
        popup.show();
        discard = 1;
    }

}

void MainWindow::on_ClearBTN_clicked()
{
    y.clear();
    yp.clear();
    xp.clear();
    curve->clearData();
    ui->customplot->replot();
    ui->progressBar->setValue(0);
    loop = 0;
}

void MainWindow::on_CalibBTN_clicked()
{
   analyze->clear();
   QList<double> * an;
   QStandardItemModel * model;
   an = new QList<double>(y);
   analyze->analyze(*an);
   analyze->set_calib_average(ui->average->value());
   if(ui->PumpChanger->currentIndex()==0)
       analyze->set_calib_pump_volume(1000);
   else
       analyze->set_calib_pump_volume(3000);

   model = new QStandardItemModel(10,2,this);
   QList<calib_table_row> Calib_Table = analyze->table.get_table();
   for(int i=0;i<Calib_Table.count();i++){
       QModelIndex index = model->index(i,0,QModelIndex());
       model->setData(index,Calib_Table[i].freq);
       index = model->index(i,1,QModelIndex());
       model->setData(index,Calib_Table[i].factor);
   }
   model->setHeaderData(0,Qt::Horizontal,"Freq (Hz)");
   model->setHeaderData(1,Qt::Horizontal,"Factor (ml)");
    ui->tableView->setModel(model);



}


void MainWindow::on_Dev_info_btn_clicked()
{
    dev_info->show();
}

void MainWindow::device_info_refresher(){
    dev_info->Set_SN(Serial->dev.Serial_Number);
    dev_info->Set_Manufacturing_Date(Serial->dev.Manufacturing_Date);
    dev_info->Set_Calib_Date(Serial->dev.Calib_Date);
    dev_info->Set_Check_Date(Serial->dev.Check_Date);
    dev_info->Set_SW_Ver(Serial->dev.SW_ver);
    dev_info->Set_PCB_Ver(Serial->dev.PCB_ver);
    return;
}
