#include "device.h"

Device::Device()
{

}

QList<double> Device::get_all(){
    QList<double> temp;
    while(data_buffer.size()>0)
        temp.append(data_buffer.dequeue()/1000);
    return temp;


}
void Device::addData(double data){

    data_buffer.enqueue(data);
}

void Device::MSG_Handler(QString msg){
     QString type;
     QString data;

     int flow =0;
     type = msg.left(2);
     data = msg.remove(0,2);
     if (type == "MD") {
         flow += QChar_to_int(data[4]);
         flow += QChar_to_int(data[3])<<8;
         flow += QChar_to_int(data[2])<<16;
         flow += QChar_to_int(data[1])<<24;
         flow *= data[0].toLatin1();
         data_buffer.enqueue(flow);
     }
}

int Device::QChar_to_int(QChar in){
    int result;
    if (in.toLatin1() >= 0)
        result = (int)in.toLatin1();
    else
        result = 256 + (int)in.toLatin1();
    return result;
}

