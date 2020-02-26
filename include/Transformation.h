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
    
    void rotate(Point p);
    
    /**
     * Rotates around axis by angle
     */
    void rotate_around_axis(Point axis, float angle);
    
    void calculate_world_matrix();
    
    void calculate_wvp_matrix(Matrix4f* vp_matrix);
  };
}

#endif
