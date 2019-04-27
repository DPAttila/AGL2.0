#ifndef VERTEX_CPP
#define VERTEX_CPP

#include "Vertex.h"

namespace agl {
  Vertex::Vertex() {}
  
  Vertex::Vertex(Point pos, Point2f tex) {
    this->pos = pos;
    this->tex = tex;
  }
  
  bool Vertex::operator==(const Vertex &v) const {
    return (this->pos == v.pos && this->tex == v.tex);
  }
}

#endif
