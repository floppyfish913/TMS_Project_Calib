#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <QFrame>

namespace Ui {
class Device_info;
}

class Device_info : public QFrame
{
    Q_OBJECT

public:
    explicit Device_info(QWidget *parent = 0);
    ~Device_info();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::Device_info *ui;
};

#endif // DEVICE_INFO_H
