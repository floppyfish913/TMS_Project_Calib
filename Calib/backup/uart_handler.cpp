#include "uart_handler.h"
#include <QThread>
#include <QMessageBox>
#include <QDebug>

UART_Handler::UART_Handler()
{
 MSG="";
}
void UART_Handler::Init(QString portname, QSerialPort::BaudRate baud,QSerialPort::Parity parity,QSerialPort::StopBits stopbits){

    this->port.setPortName(portname);
    this->port.setBaudRate(baud);
    this->port.setStopBits(stopbits);
    this->port.setParity(parity);
    this->port.setFlowControl(QSerialPort().NoFlowControl);
    this->port.setDataBits(QSerialPort().Data8);
}


void UART_Handler::open(){
    this->port.open(QIODevice::ReadWrite);
    this->start();
}

bool UART_Handler::isOpen(){
    return (this->port.isOpen() && this->isRunning());

}

void UART_Handler::close(){
    this->quit();
    this->port.close();

}


void UART_Handler::run(){
    static char received = 0;
    static char state = 0;
    while(true){
        if(this->port.bytesAvailable()){
                this->port.read(&received,1);
                switch (received){

                case '[':
                    if (state != 2) {
                        state = 1;
                        MSG="";
                        }
                    else {
                        MSG += received;
                        state = 1;
                    }
                    break;
                case '\\':
                    if (state != 2) state = 2;
                    else {
                        MSG += received;
                        state = 1;
                    }
                    break;
                case ']':
                    if (state != 2) state = 0;
                    else {
                        MSG += received;
                        state = 1;
                    }
                    break;
                default:
                     MSG += received;
                    break;

                }

                if(state == 0) {
                   dev.MSG_Handler(MSG);
                   if(bufferCount() > 30)
                   emit NotEmpty();
                }
        }
    }
}


QList<double> UART_Handler::GetMsg(){


    return dev.get_all();
}


int UART_Handler::bufferCount(){

   return dev.data_buffer.size();

}
