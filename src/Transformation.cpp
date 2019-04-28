#ifndef TRANSFORMATION_CPP
#define TRANSFORMATION_CPP

#include "Transformation.h"

#include <cmath>

namespace agl {
  Transformation::Transformation() {}
  
  bool Transformation::init() {
    translation_matrix.set_to_identity();
    scale_matrix.set_to_identity();
    rotation_matrix.set_to_identity();
    
    return true;
  }
  
  void Transformation::translate(Point p) {
    translation_matrix[0][3] = p.x;
    translation_matrix[1][3] = p.y;
    translation_matrix[2][3] = p.z;
  }
  
  void Transformation::scale(Point p) {
    scale_matrix[0][0] = p.x;
    scale_matrix[1][1] = p.y;
    scale_matrix[2][2] = p.z;
  }
  
  void Transformation::scale(float f) {
    scale_matrix[0][0] = f;
    scale_matrix[1][1] = f;
    scale_matrix[2][2] = f;
  }
  
  void Transformation::rotate(Point p) {
    Matrix4f rx, ry, rz;
        
    rx[0][0] = 1.0; rx[0][1] = 0.0;      rx[0][2] = 0.0;       rx[0][3] = 0.0;
    rx[1][0] = 0.0; rx[1][1] = cos(p.x); rx[1][2] = -sin(p.x); rx[1][3] = 0.0;
    rx[2][0] = 0.0; rx[2][1] = sin(p.x); rx[2][2] = cos(p.x);  rx[2][3] = 0.0;
    rx[3][0] = 0.0; rx[3][1] = 0.0;      rx[3][2] = 0.0;       rx[3][3] = 1.0;
    
    ry[0][0] = cos(p.y); ry[0][1] = 0.0; ry[0][2] = -sin(p.y); ry[0][3] = 0.0;
    ry[1][0] = 0.0;      ry[1][1] = 1.0; ry[1][2] = 0.0;       ry[1][3] = 0.0;
    ry[2][0] = sin(p.y); ry[2][1] = 0.0; ry[2][2] = cos(p.y);  ry[2][3] = 0.0;
    ry[3][0] = 0.0;      ry[3][1] = 0.0; ry[3][2] = 0.0;       ry[3][3] = 1.0;

    rz[0][0] = cos(p.z); rz[0][1] = -sin(p.z); rz[0][2] = 0.0; rz[0][3] = 0.0;
    rz[1][0] = sin(p.z); rz[1][1] = cos(p.z);  rz[1][2] = 0.0; rz[1][3] = 0.0;
    rz[2][0] = 0.0;      rz[2][1] = 0.0;       rz[2][2] = 0.0; rz[2][3] = 0.0;
    rz[3][0] = 0.0;      rz[3][1] = 0.0;       rz[3][2] = 0.0; rz[3][3] = 1.0;
    
    rotation_matrix = rz * ry * rx;
  }
  
  void Transformation::calculate_wvp_matrix(Matrix4f* vp_matrix) {    
    wvp_matrix = *vp_matrix * 
                 translation_matrix * 
                 rotation_matrix * 
                 scale_matrix;
  }
}

#endif
