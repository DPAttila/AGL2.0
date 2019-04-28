#ifndef GEOMETRY_GENERATOR_CPP
#define GEOMETRY_GENERATOR_CPP

#include "geometry_generator.h"

#include <cmath>
#include <cstdlib>

namespace agl {
  void generate_icosahedron(std::vector<Point> &points) {
    std::vector<unsigned int> indices;
    generate_icosahedron(points, indices);
  }
  
  void generate_icosahedron(
      std::vector<Point> &points,
      std::vector<unsigned int> &indices
  ) {
    std::vector<Vertex> vertices;
    
    generate_icosahedron(vertices, indices);
    
    for (int i = 0; i < vertices.size(); i++)
      points.push_back(vertices[i].pos);
  }
  
  void generate_icosahedron(
      std::vector<Vertex> &vertices,
      std::vector<unsigned int> &indices
  ) {
    vertices.clear();
    indices.clear();
    
    // north pole
    vertices.push_back(
        Vertex(
            Point(0, 0, 1),
            Point2f(0, 0)
        )
    );
    
    // south pole
    vertices.push_back(
        Vertex(
            Point(0, 0, -1),
            Point2f(0, 0)
        )
    );
    
    // "The other ten vertices are at latitude ±arctan(0.5) ≈ ±26.57°. 
    // These ten vertices are at evenly spaced longitudes (36° apart), 
    // alternating between north and south latitudes."
    // See https://en.wikipedia.org/wiki/Regular_icosahedron
    const double lat1 = M_PI/2.0 + atan(0.5), lat2 = M_PI/2.0 - atan(0.5);
    double lon = 0;
    for (int i = 0; i < 10; i++) {
      if (i % 2)
        vertices.push_back(
            Vertex(
                Point(cos(lon) * sin(lat1), sin(lon) * sin(lat1), cos(lat1)),
                Point2f(rand()%100/100.0, rand()%100/100.0)
            )
        );
      else
        vertices.push_back(
            Vertex(
                Point(cos(lon) * sin(lat2), sin(lon) * sin(lat2), cos(lat2)),
                Point2f(rand()%100/100.0, rand()%100/100.0)
            )
        );
      
      lon += M_PI/5.0;
    }
    
    // 5 vertices are closer to the north pole, while 5 are closer 
    // to the south. First we create the triangles which have either 
    // pole as a vertice.
    // Vertex #2 is closer to the north pole (Vertex #0), so
    // the triangles will go like this:
    // (0, 2, 4) (north), (1, 3, 5) (south), (0, 4, 6) (north), etc.
    for (int i = 2; i < 12; i++) {
      if (i%2) // South pole
        indices.push_back(1);
      else     // North pole
        indices.push_back(0);
    
      indices.push_back(i);
    
    
      if (i < 10)
        indices.push_back(2 + i);
      else 
        indices.push_back(i - 8);
        
    }
    
    // Now we create the triangles which have neither pole as a vertice,
    // this is a bit more straightforward
    for (int i = 2; i < 12; i++) {
      indices.push_back(i);
      if (i < 11)
        indices.push_back(i + 1);
      else
        indices.push_back(2);
      
      if (i < 10)
        indices.push_back(i + 2);
      else
        indices.push_back(i - 8);
    }
    
  }
}

#endif
