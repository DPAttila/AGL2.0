#ifndef MATRIX4F_H
#define MATRIX4F_H

namespace agl {
  class Matrix4f {
    public:
    float m[4][4];
    
    Matrix4f();
    
    /**
     * Makes the matrix an identity matrix \n
     * 1 0 0 0 \n
     * 0 1 0 0 \n
     * 0 0 1 0 \n
     * 0 0 0 1 \n
     */
    void set_to_identity();
    
    void print();

    /**
     * @param[in] index The index of the row to be returned
     * @returns A pointer to a row of the matrix
     */
    float* operator[](int index);
    
    /**
     * Matrix multiplication
     */
    Matrix4f operator*(Matrix4f& right);
  };
}

#endif
