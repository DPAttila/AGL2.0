#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include "Matrix4f.h"

namespace agl {
  class Camera {
    Point pos;
    
    /**
     * Field of view
     */
    float fov;
    
    float z_near, z_far;
    
    int width, height;
    
    Matrix4f perspective_projection;
    
    Matrix4f vp_matrix;
    
    /**
     * See http://ogldev.atspace.co.uk/www/tutorial12/tutorial12.html
     */
    void calculate_perspective_projection();
    
    public:
    Camera();
    
    void set_pos(Point p);
    
    void move(Point p);
    
    bool init(int width, int height);
    
    /**
     * Returns the view and projection matrices multiplied
     */
    Matrix4f* get_vp_matrix();
  };
}

#endif
