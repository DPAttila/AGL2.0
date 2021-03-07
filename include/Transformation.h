#ifndef TRASNFORMATION_H
#define TRANSFORMATION_H

#include "Point.h"
#include "Matrix4f.h"

namespace agl {
  class Transformation {
    public:
    /**
     * Position in 3D space
     */
    Matrix4f translation_matrix;
    
    /**
     * Size
     */
    Matrix4f scale_matrix;
    
    /**
     * Rotation
     */
    Matrix4f rotation_matrix;

    Matrix4f world_matrix;
    
    Matrix4f wvp_matrix;
    
    Transformation();
    
    bool init();
    
    void translate(Point p);
    
    void scale(Point p);
    
    void scale(float f);
    
    /**
     * Applies rotation around the center point (0, 0, 0),
     * meaning the rotation will happen "in place" 
     */
    void rotate(Point p);
    
    /**
     * Rotates around axis by angle
     * 
     * One point of the axis is the center (0, 0, 0),
     * meaning the rotation will happen "in place" 
     * https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
     */
    void rotate_around_axis(Point axis, float angle);
    
    /**
     * Rotates around a given point by angle
     * 
     * The rotation will not happen "in place", the position of the object
     * will also change
     */
    void rotate_around_point(Point rot_center, Point angles);

    void calculate_world_matrix();
    
    void calculate_wvp_matrix(Matrix4f* vp_matrix);
  };
}

#endif
