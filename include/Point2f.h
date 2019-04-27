#ifndef POINT2F_H
#define POINT2F_H

namespace agl {
  class Point2f {
    public:
    float x, y;
    
    Point2f();
    
    Point2f(float x, float y);
    
    bool operator==(const Point2f &p) const;
  };
}

#endif
