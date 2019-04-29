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
    
    bool operator==(const Point& p) const;
    
    Point& operator+=(const Point& p);
  };
}

#endif
