#include "calib_table.h"

calib_table::calib_table()
{

}

void calib_table::add(double freq,double factor){

    calib_table_row new_row;
    new_row.factor = factor;
    new_row.freq = freq;
    table+=new_row;

}

QList<calib_table_row> calib_table::get_table(){

    return table;

}

void calib_table::clear(){
    table.clear();

}
