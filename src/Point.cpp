#ifndef POINT_CPP
#define POINT_CPP

#include "Point.h"

#include <cmath>

namespace agl {
  Point::Point() {}
  
  Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  
  void Point::normalize() {
    const float length = sqrt(x*x + y*y + z*z);
    
    x /= length;
    y /= length;
    z /= length;
  }
  
  Point Point::cross_product(const Point& p) {
    return Point(
               this->y * p.z - this->z * p.y,
               this->z * p.x - this->x * p.z,
               this->x * p.y - this->y * p.x
           );
  }
  
  bool Point::operator==(const Point& p) const {
    return (this->x == p.x && this->y == p.y && this->z == p.z);
  }
  
  Point& Point::operator+=(const Point& p) {
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;
    return *this;
  }
}

#endif
