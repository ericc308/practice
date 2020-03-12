#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <streambuf>
#include <vector>
#include <complex>
#include <math.h>
#include <vector>

struct OrthogonalDomainPoint{
    double x=0;
    double y=0;
    double z=0;

    OrthogonalDomainPoint operator+(OrthogonalDomainPoint in){
        OrthogonalDomainPoint result;
        result.x = x+in.x;
        result.y = y+in.y;
        result.z = z+in.z;
        return result;
    }

     OrthogonalDomainPoint operator*(double in){
        OrthogonalDomainPoint result;
        result.x = in*x;
        result.y = in*y;
        result.z = in*z;
        return result;
    }

    OrthogonalDomainPoint operator*(int in){
        OrthogonalDomainPoint result;
        result.x = in*x;
        result.y = in*y;
        result.z = in*z;
        return result;
    }

    void view(){
        std::cout<<"{"<<x<<","<<y<<","<<z<<"}\n";
    }
};

struct PolarDomainPoint{
    double range=0;
    double az=0;
    double el=0;

    OrthogonalDomainPoint convert_orthogonal_domain(){
        OrthogonalDomainPoint result;
        result.x = range*cos(el)*sin(az);
        result.z = range*cos(el)*cos(az);
        result.y = range * sin(el);
    }

};

class fake_target_info{

    uint32_t id;
    OrthogonalDomainPoint target_orthogonal_position;
    PolarDomainPoint target_polar_position;
    OrthogonalDomainPoint velocity;

public:
    void set_id(uint32_t iid){
        id =iid;
    }
    void set_origin_pos(OrthogonalDomainPoint in){
        target_orthogonal_position = in;
        double relative_range = sqrt(in.x*in.x+in.y*in.y+in.z*in.z);
        double slope_side_az = sqrt(in.x*in.x + in.z*in.z);
        target_polar_position.range = relative_range;
        target_polar_position.az = asin(in.x/slope_side_az);
        target_polar_position.el = asin(in.y/relative_range);
    }
    
    void set_origin_angle_domain(PolarDomainPoint in){
        target_polar_position.range = in.range;
        target_polar_position.az = in.az;
        target_polar_position.el = in.el;
        target_orthogonal_position.x = in.range*cos(in.el)*sin(in.az);
        target_orthogonal_position.z = in.range*cos(in.el)*cos(in.az);
        target_orthogonal_position.y = in.range * sin(in.el);
    }

    void set_velocity(OrthogonalDomainPoint ivelocity){
        velocity = ivelocity;
    }

    OrthogonalDomainPoint get_pos_now(double sec){
        return(target_orthogonal_position + velocity * sec);
    }

};
