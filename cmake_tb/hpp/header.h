#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <iostream>

struct  RadarInfo{
double x=0;
double y=0;
double z=0;
void view(){std::cout<<"(x,y,z) = "<<"("<<x<<","<<y<<","<<z<<")\n";}
};

class Simulator{
RadarInfo radar;
public:
Simulator();
void get_pos_now();
};
