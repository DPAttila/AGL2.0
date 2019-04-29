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
  
  void Camera::calculate_rotation() {
    Point n = look_at;
    n.normalize();
    
    Point u = up;
    u = u.cross_product(look_at);
    u.normalize();
    
    Point v = n.cross_product(u);
    
    rotation.set_to_identity();
    
    rotation[0][0] = u.x;
    rotation[0][1] = u.y;
    rotation[0][2] = u.z;
    rotation[1][0] = v.x;
    rotation[1][1] = v.y;
    rotation[1][2] = v.z;
    rotation[2][0] = n.x;
    rotation[2][1] = n.y;
    rotation[2][2] = n.z;
    
    calculate_vp_matrix();
  }
  
  void Camera::calculate_vp_matrix() {
    vp_matrix = perspective_projection * rotation * translation;
  }
  
  Camera::Camera() {}
  
  bool Camera::init(int width, int height) {
    fov = 0.8;
    z_near = 0.1;
    z_far = 10.0;
    pos = Point(0, 0, 0);
    
    look_at = Point(0, 0, 1);
    up = Point(0, 1, 0);
    
    this->width = width;
    this->height = height;
    
    move_speed = 0.1;
    
    perspective_projection.set_to_identity();
    rotation.set_to_identity();
    translation.set_to_identity();
    
    calculate_perspective_projection();
    calculate_rotation();
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
  
  void Camera::move_forward() {
    move(look_at * move_speed);
  }
  
  void Camera::move_backwards() {
    move(look_at * (-move_speed));
  }
  
  void Camera::move_left() {
    Point left = look_at.cross_product(up); 
    left.normalize();
    move(left * move_speed);
  }
  
  void Camera::move_right() {
    Point right = up.cross_product(look_at);
    right.normalize(); 
    move(right * move_speed);
  }
  
  void Camera::orient(Point p) {
    this->look_at = p;
    calculate_rotation();
  }
  
  void Camera::turn(Point p) {
    this->look_at += p;
    calculate_rotation();
  }
  
  Matrix4f* Camera::get_vp_matrix() {
    return &vp_matrix;
  }
}

#endif
