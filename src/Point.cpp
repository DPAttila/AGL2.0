#ifndef POINT_CPP
#define POINT_CPP

#include "Point.h"

namespace agl {
  Point::Point() {}
  
  Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
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
