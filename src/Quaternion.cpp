#ifndef QUATERNION_CPP
#define QUATERNION_CPP

#include "Quaternion.h"

namespace agl {
  Quaternion::Quaternion() {}
  
  Quaternion::Quaternion(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
  
  void Quaternion::conjugate() {
    y *= -1;
    z *= -1;
    w *= -1;
  }
  
  Quaternion Quaternion::operator*(const Quaternion& q) {
    return Quaternion(
        x*q.x - y*q.y - z*q.z - w*q.w,
        x*q.y + y*q.x + z*q.w - w*q.z,
        x*q.z - y*q.w + z*q.x + w*q.y,
        x*q.w + y*q.z - z*q.y + w*q.x
    );
  }
}

#endif
