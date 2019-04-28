#ifndef MATRIX4F_H
#define MATRIX4F_H

namespace agl {
  class Matrix4f {
    public:
    float m[4][4];
    
    Matrix4f();
    
    /**
     * Makes our matrix an identity matrix
     * 1 0 0 0
     * 0 1 0 0
     * 0 0 1 0
     * 0 0 0 1
     */
    void set_to_identity();
    
    void print();
    
    /**
     * @todo: possibly make inline
     */
    float* operator[](int index);
    
    /**
     * Matrix multiplication
     */
    Matrix4f operator*(Matrix4f& right);
  };
}

#endif
