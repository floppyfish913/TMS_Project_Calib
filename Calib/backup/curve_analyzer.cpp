#include "curve_analyzer.h"

curve_analyzer::curve_analyzer()
{

}

void curve_analyzer::analyze(QList<double> collected_data){
    Curve t_curve;
    int i=0;
    int start_flag=0;
    int loop=0;
    double shr_1=0,shr_2=0;

    //görbék detektálása
    //6db ki-be adatsoronként
    for(i=0;i<collected_data.length();i++){
        shr_1 = collected_data[i];
        if ( shr_1-shr_2 > 0 && start_flag == 0)
            start_flag = 1;
        else if ( shr_1-shr_2 < 0 && start_flag == 0)
            start_flag = -1;

        if ((start_flag == -1) && (shr_1 < 0) && (shr_2 > 0))
            loop++;

        if ((start_flag == 1) && (shr_1 > 0) && (shr_2 < 0))
            loop++;

        t_curve.append(shr_1);

        if (loop == avg ){
            t_curve.set_avg(avg);
            t_curve.set_pump(pump);
            datas.append(t_curve);
            loop = 0;
            t_curve.clear();
        }

        shr_2 = collected_data[i];
    }

    if(!datas.isEmpty()){
    for(i=0;i<datas.length();i++)
        table.add(datas[i].abs_avg(),datas[i].factor());

    }
}

void curve_analyzer::clear(){
    datas.clear();
    table.clear();
}

void curve_analyzer::set_calib_average(int _avg){
    avg=_avg;
}
void curve_analyzer::set_calib_pump_volume(int vol){
    pump = vol;
}
