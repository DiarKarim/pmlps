#include <cstdio>
#include "pmlps.h"
#include "space/vsr_cga3D_op.h"

using namespace vsr;
using namespace vsr::cga;

// 2-D reconstruction from Fish-eye image and hight info.
// Input: (x, y) normalized position on image sensor
// Input: h the vertical distance from sensor
// Output: pos[0], pos[1], pos[2] estimated position (X, Y, -h)

bool unfish(float x, float y, float h, float& hx, float& hy)
{
#if 0
  // v = -(u-e3) e3 / (u-e3) i.e. the stereographic projection from
  // x-y plane to unit sphere.
  auto v = - Vec(x,y,-1) * Vec(0,0,1) / Vec(x,y,-1);
#else
  float u2 = x*x + y*y;
  auto v = Vec(2*x/(u2+1), 2*y/(u2+1), (u2-1)/(u2+1));
#endif
  auto pointO = Construct::point(0,0,0);
  auto pointP = Construct::point(0,0,-h);
  auto line = pointO ^ v ^ Inf(1);
  auto dlp = (pointP <= Drv(0,0,1));
  auto pos = (dlp <= line);
  hx = pos[0]/pos[3];
  hy = pos[1]/pos[3];
  return true;
}
  
#if 0
int main(){
  ImageSensorPoint ip(165, 65); // (4.627011, 50.897129)
  //ImageSensorPoint ip(174, 66); // (12.963069, 50.000408)
  //ImageSensorPoint ip(175, 74); // (13.790552, 42.291027)
  //ImageSensorPoint ip(164, 74); // (3.670428, 42.209923)
  
  Point3D p;
  ip.normalize(p);
  float x = p.ex();
  float y = p.ey();
  float h = 220.0-70.0;
  float hx, hy;
  printf("(%f, %f) on %f -> ", x, y, h);
  unfish(x, y, h, hx, hy);
  printf("(%.1f, %.1f)\n", hx, hy);
  return 0;
}
#endif
