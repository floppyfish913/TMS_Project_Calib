#include "curve.h"

Curve::Curve()
{

}

double Curve::abs_avg(){

    return max_volume()/this->curve.length();

}

double Curve::max_volume(){
    int i;
    double sum=0;
    for(i=0;i<this->curve.length();i++){
          if(curve[i] > 0)
             sum += this->curve[i];
           else
             sum -=this->curve[i];
    }
    return sum;
}

double Curve::factor(){
    return (pump*2*avg)/max_volume(); //6 fujasnyira van tervezve  3 fujasra van beallitva
}

void Curve::append(double add){
    curve+=add;
}

void Curve::clear(){

    curve.clear();
}

void Curve::set_pump(int vol){
    pump=vol;
}
void Curve::set_avg(int _avg){
    avg=_avg;
}
