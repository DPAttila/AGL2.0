#ifndef POINT2F_CPP
#define POINT2F_CPP

#include "Point2f.h"

namespace agl {
  Point2f::Point2f() {}
  
  Point2f::Point2f(float x, float y) {
    this->x = x;
    this->y = y;
  }
  
  bool Point2f::operator==(const Point2f &p) const {
    return (this->x == p.x && this->y == p.y);
  }
}

#endif
