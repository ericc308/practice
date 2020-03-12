#include "operator.h"

int main(){
    OrthogonalDomainPoint p1{1,1,1}, p2{2,2,2};

    fake_target_info fa_tar1;
    fa_tar1.set_origin_pos(p1);
    fa_tar1.set_velocity(p2);
    OrthogonalDomainPoint pf = fa_tar1.get_pos_now(10);
    pf.view();
    return 0;
}