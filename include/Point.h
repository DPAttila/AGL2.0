#ifndef POINT_H
#define POINT_H

namespace agl {
  class Point {
    public:
    float x, y, z;
    
    Point();
    
    Point(float x, float y, float z);
    
    void normalize();
    
    Point cross_product(const Point& p);
    
    /**
     * Rotates by angle around vector using quaternions
     * See https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
     */
    void rotate(float angle, Point vector);
    
    bool operator==(const Point& p) const;
    
    Point operator*(const float f);
    
    Point& operator+=(const Point& p);
  };
}

#endif
