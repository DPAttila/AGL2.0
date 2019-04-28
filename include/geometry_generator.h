#ifndef GEOMETRY_GENERATOR_H
#define GEOMETRY_GENERATOR_H

#include <vector>

#include "Point.h"
#include "Vertex.h"

namespace agl {
  /**
   * See https://en.wikipedia.org/wiki/Regular_icosahedron
   * Generates icosahedron using spherical coordinates
   */
  void generate_icosahedron(std::vector<Point> &points);
  
  /**
   * See https://en.wikipedia.org/wiki/Regular_icosahedron
   * Generates icosahedron using spherical coordinates
   * Sets the indices required for drawing the icosahedron by triangles
   */
  void generate_icosahedron(
      std::vector<Point> &points, 
      std::vector<unsigned int> &indices
  );
  
  /**
   * See https://en.wikipedia.org/wiki/Regular_icosahedron
   * Generates icosahedron using spherical coordinates
   * Sets the indices required for drawing the icosahedron as triangles
   * Sets the texture coordinates to [0,0] temporally
   */
  void generate_icosahedron(
      std::vector<Vertex> &vertices,
      std::vector<unsigned int> &indices
  );
}

#endif
