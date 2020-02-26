#ifndef POINT_CPP
#define POINT_CPP

#include "Point.h"

#include <cmath>
#include <cstdlib>

#include "Quaternion.h"

using namespace std;

namespace agl {
  Point::Point() {}
  
  Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  
  float Point::pyth() {
    return sqrt(x*x + y*y + z*z);
  }
  
  void Point::normalize() {
    const float length = pyth();
    
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
  
  void Point::rotate(float angle, Point vector) {
    Quaternion p(0, this->x, this->y, this->z);
    
    Quaternion q(
        cos(angle/2), 
        vector.x * sin(angle/2),
        vector.y * sin(angle/2),
        vector.z * sin(angle/2)
    );
    
    Quaternion q_conjugate = q;
    q_conjugate.conjugate();
    
    Quaternion a = q * p * q_conjugate;
    
    this->x = a.y;
    this->y = a.z;
    this->z = a.w;
  }
  
  bool Point::operator==(const Point& p) const {
    return (this->x == p.x && this->y == p.y && this->z == p.z);
  }
  
  Point Point::operator+(const Point& p) {
    return Point(this->x + p.x, this->y + p.y, this->z + p.z);
  }
  
  Point Point::operator*(const float f) {
    return Point(this->x * f, this->y * f, this->z * f);
  }
  
  Point Point::operator/(const float f) {
    return Point(this->x / f, this->y / f, this->z / f);
  }
  
  Point& Point::operator+=(const Point& p) {
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;
    return *this;
  }
  
  string Point::to_string() {
    return std::to_string(x) + "\t" + std::to_string(y) + "\t" + std::to_string(z);    
  }
}

#endif
