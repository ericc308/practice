#include "../hpp/header.h"
Simulator::Simulator(){
    radar.x = 10;
    radar.y = 15;
    radar.z = 20;
}

void Simulator::get_pos_now(){
    radar.view();
}