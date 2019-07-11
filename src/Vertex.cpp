#ifndef VERTEX_CPP
#define VERTEX_CPP

#include "Vertex.h"

namespace agl {
  Vertex::Vertex() {}
  
  Vertex::Vertex(Point pos, Point2f tex) {
    this->pos = pos;
    this->tex = tex;
  }
  
  Vertex::Vertex(Point pos, Point2f tex, Point nor) {
    this->pos = pos;
    this->tex = tex;
    this->nor = nor;
  }
  
  bool Vertex::operator==(const Vertex &v) const {
    return (this->pos == v.pos && this->tex == v.tex && this->nor == v.nor);
  }
}

#endif
