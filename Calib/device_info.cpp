#include "device_info.h"
#include "ui_device_info.h"

Device_info::Device_info(UART_Handler * s,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Device_info)
{
    ui->setupUi(this);
    Serial = s;
}

Device_info::~Device_info()
{
    delete ui;
}





void Device_info::on_pushButton_3_clicked()
{
    this->close();
}

void Device_info::on_Read_clicked()
{
    Serial->PP_send("RSN");
    Serial->msleep(1000);
    Serial->PP_send("RMD");
    Serial->msleep(1000);
    Serial->PP_send("RCD");
    Serial->msleep(1000);
    Serial->PP_send("RED");
    Serial->msleep(1000);
    Serial->PP_send("RSV");
    Serial->msleep(1000);
    Serial->PP_send("RPC");
    Serial->msleep(1000);
    emit Refresh_Device_Data();
}

void Device_info::Set_SN(QString SN){
    ui->SN_value->setText(SN);
}

void Device_info::Set_Manufacturing_Date(QString Date){

    ui->Man_Date_value->setText(Date);

}
void Device_info::Set_Calib_Date(QString Date){

    ui->Calib_Date_value->setText(Date);

}
void Device_info::Set_Check_Date(QString Date){

    ui->Check_Date_value->setText(Date);

}

void Device_info::Set_PCB_Ver(QString ver){

    ui->PCB_ver_value->setText(ver);

}
void Device_info::Set_SW_Ver(QString ver){

    ui->SW_ver_value->setText(ver);

}
