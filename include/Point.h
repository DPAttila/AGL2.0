#ifndef POINT_H
#define POINT_H

#include <string>

using namespace std;

namespace agl {
  class Point {
    public:
    float x, y, z;
    
    Point();
    
    Point(float x, float y, float z);
    
    /**
     * Returns the length of the vector from (0, 0, 0) to Point
     * Using Pythagoras' theorem
     */
    float pyth();

    void normalize();
    
    Point cross_product(const Point& p);
    
    /**
     * Rotates by angle around vector using quaternions
     * See https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
     */
    void rotate(float angle, Point vector);
    
    bool operator==(const Point& p) const;
    
    Point operator+(const Point& p);
    
    Point operator-(const Point& p);
    
    Point operator*(const float f);
    
    Point operator/(const float f);
    
    Point& operator+=(const Point& p);
    
    Point& operator*=(const float f);
    
    Point& operator/=(const float f);
    
    string to_string();
  };
}

#endif
