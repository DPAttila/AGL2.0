#ifndef QUATERNION_H
#define QUATERNION_H

namespace agl {
  class Quaternion {
    public:
    float x, y, z, w;
    
    Quaternion();
    
    Quaternion(float x, float y, float z, float w);
  
    void conjugate();
    
    Quaternion operator*(const Quaternion& q);
  };
}

#endif
