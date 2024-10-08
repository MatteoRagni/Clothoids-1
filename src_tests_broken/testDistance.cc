//#define _USE_MATH_DEFINES
#include "Clothoids.hh"

using G2lib::real_type;
using G2lib::int_type;
using namespace std;

int
main() {

  G2lib::ClothoidCurve C;
  real_type x0     = 0;
  real_type y0     = 2;
  real_type theta0 = 0;
  real_type kappa0 = 10;
  real_type dk     = -1;// 0;
  real_type L      = 10;
  C.build( x0, y0, theta0, kappa0, dk, L );

  //real_type x = -2.75;
  //real_type y = -3.2000000000000001776;
  real_type x = 10;
  real_type y = 15;
  real_type X, Y, S;

  real_type T, d;
  int_type info = C.closest_point_ISO( x, y, X, Y, S, T, d );

  cout << "\nd = " << d
       << "\nX = " << X
       << "\nY = " << Y
       << "\nS = " << S
       << "\nT = " << T
       << "\ninfo = " << info
       << "\n";

  cout << "\n\nALL DONE FOLKS!!!\n";

  return 0;
}
