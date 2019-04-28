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
    
    calculate_vp_matrix();
  }
  
  void Camera::calculate_translation() {
    translation.set_to_identity();
    translation[0][3] = -pos.x;
    translation[1][3] = -pos.y;
    translation[2][3] = -pos.z;
    
    calculate_vp_matrix();
  }
  
  void Camera::calculate_vp_matrix() {
    vp_matrix = perspective_projection * translation;
  }
  
  Camera::Camera() {}
  
  bool Camera::init(int width, int height) {
    fov = 0.8;
    z_near = 0.1;
    z_far = 10.0;
    pos = Point(0, 0, 0);
    
    this->width = width;
    this->height = height;
    
    calculate_perspective_projection();
    calculate_translation();
    
    return true;
  }
  
  void Camera::set_pos(Point p) {
    this->pos = p;
    calculate_translation();
  }
  
  void Camera::move(Point p) {
    this->pos += p;
    calculate_translation();
  }
  
  Matrix4f* Camera::get_vp_matrix() {
    return &vp_matrix;
  }
}

#endif
