#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

// 24.805693, 120.991103
const static double pi = M_PI; 

struct GPSPosition{
    double latitude=0;
    double longtitude=0;
    double altitude=0;
    void view(){std::cout<<"latitude : "<<latitude<<" longtitude : "<<longtitude<<" altitude : "<<altitude<<std::endl;}
};

GPSPosition ned2geodetic_tron(double xNorth, double yEast, double zDown, GPSPosition reference) {
    GPSPosition result;
  // //// 1. NED2ECEF (enu2ecefFormula.m)

  // //// 1.1 enu2ecef - target (enu2ecefvFormula.m)

  double cosPhi = cos(reference.latitude*pi/180);

  double sinPhi = sin(reference.latitude*pi/180);

  double cosLambda = cos(reference.longtitude*pi/180);

  double sinLambda = sin(reference.longtitude*pi/180);

 double t = cosPhi*-zDown - sinPhi*xNorth;

  double dz = sinPhi*-zDown + cosPhi*xNorth;

  double dx = cosLambda*t - sinLambda*yEast;

  double dy = sinLambda*t + cosLambda*yEast;

  //// 1.2 geodetic2ecef - radar   (gedetic2ecef.m)

//   double wgs84 = wgs84Ellipsoid('kilometer');

  // Ellipsoid has the form: [semimajor_axis, eccentricity].

  double a =  6.3781e+03;

  double e2 =  pow(0.0818,2);

  double f = e2 / (1 + sqrt(1 - e2));

  double sinphi = sin(reference.latitude * pi/180);

  double cosphi = cos(reference.latitude * pi/180);

  e2 = f * (2 - f);

  double N = a / sqrt(1 - e2 * sinphi * sinphi);

  double rho = (N + reference.altitude)*cosphi;

  double z0 = (N * (1 - e2) + reference.altitude)*sinphi;

//   [ x0, y0 ] = pol2cart(deg2rad(reference.longtitude), rho);
  double x0 = rho * cos(reference.longtitude*pi/180);
  double y0 = rho * sin(reference.longtitude*pi/180);
  // 1.3.  Origin + offset from origin equals position in ECEF.

  double x = x0 + dx;

  double y = y0 + dy;

  double z = z0 + dz;

  //// 2. ECEF to geodetic (ecef2geodetic.m)

  // function [lat, lon, h] = ecef2geodetic(x, y, z, ellipsoid)

  // Return phi and lambda in radians.

  // [ lon_rad, rho ] = cart2pol(x, y);

  double lon_rad = atan2(y , x);
 rho = sqrt(x * x + y * y);

  // sinfun = @sin;

  // cosfun = @cos;

  // atan2fun = @atan2;

  // Spheroid properties

  double b = (1 - f) * a; // Semiminor axis

  e2 = f * (2 - f); // Square of (first) eccentricity

  double ep2 = e2 / (1 - e2); // Square of second eccentricity

  // Bowring's formula for initial parametric (beta) and geodetic

  // (phi) latitudes

  double beta = atan2(z, (1 - f) * rho);

  double phi = atan2(z + b * ep2 * pow(sin(beta),3), rho - a * e2 * pow(cos(beta),3));

  // Fixed-point iteration with Bowring's formula

  // (typically converges within two or three iterations)

  double betaNew = atan2((1 - f) * sin(phi), cos(phi));

  int count = 0;

  while(beta!=betaNew && count < 5){

        beta = betaNew;

        phi = atan2(z + b * ep2 * pow(sin(beta), 3), rho - a * e2 * pow(cos(beta),3));

  betaNew = atan2((1 - f) * sin(phi), cos(phi));

  count = count + 1;

}

      // Ellipsoidal height from final value for latitude

      sinphi = sin(phi);

  N = a / sqrt(1 - e2 * pow(sinphi,2));

  result.altitude = rho*cos(phi) + (z + e2 * N*sinphi)*sinphi - N;

  double lat_rad = phi;

  result.longtitude =lon_rad * 180 / pi ;

  result.latitude = lat_rad* 180 / pi ;
  return result;
}

int main(){
  GPSPosition origin{24.805693,120.991103,0};
  GPSPosition result = ned2geodetic_tron(1,1,1,origin);
  result.view();

  return 0;
}