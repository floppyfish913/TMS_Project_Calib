#include "device_info.h"
#include "ui_device_info.h"

Device_info::Device_info(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Device_info)
{
    ui->setupUi(this);
}

Device_info::~Device_info()
{
    delete ui;
}





void Device_info::on_pushButton_3_clicked()
{
    this->close();
}
