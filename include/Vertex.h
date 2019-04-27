#ifndef VERTEX_H
#define VERTEX_H

#include "Point.h"
#include "Point2f.h"

namespace agl {
  class Vertex {
    public:
    /**
     * Position in 3D space
     */
    Point pos;
    
    /**
     * Texture coordinates (in the range ([0, 1], [0, 1])
     * See ogldev tutorial 16:
     * http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html
     */
    Point2f tex;
    
    Vertex();
    
    Vertex(Point pos, Point2f tex);
    
    bool operator==(const Vertex& v) const;
  };
}

#endif
