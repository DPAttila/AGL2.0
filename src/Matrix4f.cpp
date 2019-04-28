#ifndef MATRIX4F_CPP
#define MATRIX4F_CPP

#include "Matrix4f.h"

#include <iostream>

namespace agl {
  Matrix4f::Matrix4f() {}
  
  void Matrix4f::set_to_identity() {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        m[i][j] = 0.0;
      }
    }
    
    for (int i = 0; i < 4; i++) 
      m[i][i] = 1.0;
  }
  
  void Matrix4f::print() {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        std::cout << m[i][j] << '\t';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
  
  float* Matrix4f::operator[](int index) {
    return m[index];
  }
  
  Matrix4f Matrix4f::operator*(Matrix4f& right) {
    Matrix4f ret;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        ret[i][j] = 
            m[i][0] * right.m[0][j] +
            m[i][1] * right.m[1][j] +
            m[i][2] * right.m[2][j] +
            m[i][3] * right.m[3][j];
      }
    }
    return ret;
  }
}

#endif
