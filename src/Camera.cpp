#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "Camera.h"

#include <cmath>

namespace agl {
  void Camera::limit_vertical_angle() {
    if (vertical_angle > M_PI/2.0) vertical_angle = M_PI/2.0;
    else if (vertical_angle < -M_PI/2.0) vertical_angle = -M_PI/2.0; 
  }
  
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
    Point vertical(0.0, 1.0, 0.0);
    
    // n is the target vector, or look at vector
    Point n(1.0, 0.0, 0.0);
    
    // This is a quaternion rotation around the world vertical axis by
    // the horizontal angle
    // See https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
    n.rotate(horizontal_angle, vertical);
    n.normalize();
    
    // The horizontal axis is perpendicular to the plane defined by 
    // the horizontal component of look_at and the world vertical axis
    Point horizontal = vertical.cross_product(n);     
    horizontal.normalize();
    
    // Another quaternion rotation, around the horizontal axis by
    // the vertical angle
    // The calculation of the target vector is finished.
    n.rotate(vertical_angle, horizontal);
    n.normalize();
    
    // this is the "old" up vector
    Point u = n.cross_product(horizontal);
    
    u = u.cross_product(n); // the right vector is calculated here
    u.normalize();
    
    // this is the new up vector
    Point v = n.cross_product(u);
    
    look_at = n;
    up = v;
    
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
    fov = 1.5;
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
  
  void Camera::orient(float h, float v) {
    horizontal_angle = h;
    vertical_angle = v;
    
    limit_vertical_angle();
    
    calculate_rotation();
  }
  
  void Camera::turn(float h, float v) {
    horizontal_angle += h;
    vertical_angle += v;
    
    limit_vertical_angle();
    
    calculate_rotation();
  }
  
  Matrix4f* Camera::get_vp_matrix() {
    return &vp_matrix;
  }
}

#endif
