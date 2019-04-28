#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "Camera.h"

#include <cmath>

namespace agl {
  void Camera::calculate_perspective_projection() {
    for (int i = 0; i < 4; i++) 
      for (int j = 0; j < 4; j++)
        perspective_projection[i][j] = 0;
    
    const float ar = width / (float)height; // aspect ratio
    const float z_range = z_near - z_far;
    const float tan_half_fov = tan(fov / 2.0);
    
    perspective_projection[0][0] = 1.0 / (tan_half_fov * ar);
    perspective_projection[1][1] = 1.0 / tan_half_fov;
    perspective_projection[2][2] = (-z_near - z_far) / z_range;
    perspective_projection[2][3] = 2.0 * z_far * z_near / z_range;
    perspective_projection[3][2] = 1.0;
  }
  
  Camera::Camera() {}
  
  bool Camera::init(int width, int height) {
    fov = 0.8;
    z_near = 0.1;
    z_far = 10.0;
    this->width = width;
    this->height = height;
    
    calculate_perspective_projection();
    
    vp_matrix = perspective_projection;
  }
  
  Matrix4f* Camera::get_vp_matrix() {
    return &vp_matrix;
  }
}

#endif
