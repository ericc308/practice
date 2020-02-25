#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <cstdint>
#include <iostream>

struct target{
    uint32_t id;
    double range;
    double az;
    double el;
    void view(){std::cout<<"{ "<<id<<" , "<<range<<" , "<<az<<" , "<<el<<" }\n";}
};

int main(){

    std::vector<target> targets;

    std::vector<target> target_list;
    for(int itar = 0 ; itar < 5 ; itar++){
        target tar1{static_cast<uint32_t>(itar+1),static_cast<double>(itar*10), static_cast<double>(itar*2), static_cast<double>(itar*6)};
        targets.push_back(tar1);
    }

    target_list.insert(target_list.begin(),targets.begin(),targets.end());

    for(auto it : target_list){
        it.view();
    }

    return 0;
}