#ifndef BUFFER_CPP
#define BUFFER_CPP

#include "Buffer.h"

#include "util.h"

namespace agl {
  void Buffer::rebuffer() {
    glBindVertexArray(vertexarray_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(
        GL_ARRAY_BUFFER, 
        vertices.size() * sizeof(Point),
        &vertices[0],
        GL_STATIC_DRAW
    );
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        &indices[0],
        GL_STATIC_DRAW
    );
  }
  
  Buffer::Buffer() {
    this->primitive = GL_TRIANGLES;
  }
  
  Buffer::Buffer(GLenum primitive) {
    this->primitive = primitive;
  }
  
  void Buffer::init() {
    glGenVertexArrays(1, &vertexarray_id);
    glBindVertexArray(vertexarray_id);
        
    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &indexbuffer);
  }
  
  void Buffer::add(vector<Point> vertices, vector<unsigned int> indices) {
    if (this->vertices.size() == 0) 
      this->vertices = vertices;
    else
      this->vertices.insert(
          this->vertices.end(), 
          vertices.begin(), 
          vertices.end()
      );
    
    if (this->indices.size() == 0)
      this->indices = indices;
    else
      this->indices.insert(
          this->indices.end(),
          indices.begin(),
          indices.end()
      );
    
    rebuffer();
  }
  
  void Buffer::draw() {
    glBindVertexArray(vertexarray_id);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    
    glDrawElements(
      primitive,
      indices.size(),
      GL_UNSIGNED_INT,
      (void*)0
    );
    
    glDisableVertexAttribArray(0);
  }
  
  Buffer::~Buffer() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &indexbuffer);
  }
}

#endif
