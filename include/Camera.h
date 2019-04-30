#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include "Matrix4f.h"

namespace agl {
  class Camera {
    /**
     * Field of view
     */
    float fov;
    
    /**
     * Clipping values; nothing will be seen
     * closer than z_near or farther than z_far
     */
    float z_near, z_far;
    
    float vertical_angle, horizontal_angle;
    
    /**
     * Window width and height
     */
    int width, height;
    
    /**
     * Camera position
     */
    Point pos;
    
    /**
     * Target of the camera
     */
    Point look_at;
    
    /**
     * Y axis of the camera space
     */
    Point up;
    
    float move_speed;
    
    Matrix4f perspective_projection;
    
    /**
     * Camera position matrix
     * Note that the coordinates are negated in this matrix
     * See http://ogldev.atspace.co.uk/www/tutorial13/tutorial13.html
     */
    Matrix4f translation;
    
    /**
     * This is a UVN matrix
     * See http://ogldev.atspace.co.uk/www/tutorial13/tutorial13.html
     */
    Matrix4f rotation;
    
    /**
     * View-Projection matrix
     */
    Matrix4f vp_matrix;
    
    void limit_vertical_angle();
    
    /**
     * See http://ogldev.atspace.co.uk/www/tutorial12/tutorial12.html
     */
    void calculate_perspective_projection();
    
    /**
     * Almost the same as an object translation
     * matrix, but the coordinates are negated.
     * See http://ogldev.atspace.co.uk/www/tutorial13/tutorial13.html
     */
    void calculate_translation();
    
    /**
     * See http://ogldev.atspace.co.uk/www/tutorial13/tutorial13.html
     *     http://ogldev.atspace.co.uk/www/tutorial15/tutorial15.html
     *     https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
     */
    void calculate_rotation();
    
    /**
     * the View-Projection matrix is the multiplication of the perspective 
     * projection, camera translation and camera rotation matrices.
     */
    void calculate_vp_matrix();
    
    public:
    Camera();
    
    /**
     * Camera is moved TO p (the actual position is set to p)
     */
    void set_pos(Point p);
    
    /**
     * Camera is moved BY p (p is added to the actual position)
     */
    void move(Point p);
    
    void move_forward();
    
    void move_left();
    
    void move_backwards();
    
    void move_right();
    
    /**
     * Camera orientation is set TO these angles
     * @param[in] h Horizontal orientation angle
     * @param[in] v Vertical orientation angle
     */
    void orient(float h, float v);
    
    /**
     * Camera is rotated BY these angles
     * @param[in] h Horizontal rotation angle
     * @param[in] v Vertical rotation angle
     */
    void turn(float h, float v);
    
    bool init(int width, int height);
    
    /**
     * Returns the view and projection matrices multiplied
     */
    Matrix4f* get_vp_matrix();
  };
}

#endif
