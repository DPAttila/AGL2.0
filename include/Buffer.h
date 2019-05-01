#ifndef BUFFER_H
#define BUFFER_H

#include <vector> 

#include "glad/glad.h"

#include "AGL.h"
#include "Point.h"
#include "Vertex.h"
#include "Texture.h"
#include "Graphics.h"
#include "Transformation.h"

using namespace std;

namespace agl {
  class Buffer {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    
    Texture texture;
    
    /**
     * Handle to the handles, describes our vertex format
     */
    GLuint vertexarray_id;
    
    /**
     * Handle to the vertex buffer
     */
    GLuint vertexbuffer;
    
    /**
     * Handle to the index buffer
     */
    GLuint indexbuffer;
    
    /**
     * Draw mode (GL_TRIANGLES, GL_LINES, etc.)
     */
    GLenum primitive;
    
    /**
     * Stores the translation, rotation and scaling of the object
     */
    Transformation transformation;
    
    /**
     * Pointer to the graphics context
     * This is needed to get the address of the glsl matrix
     */
    Graphics* graphics;
    
    /**
     * Loads the vertex and index data into the coresponding buffers
     */
    void rebuffer();
    
    public:
    Buffer();
    
    Buffer(GLenum primitive);
    
    void init(AGL* agl);
    
    ~Buffer();
    
    void draw();
    
    /**
     * Adds the set of vertices and indices to the buffer
     * If a vertex already exists, its old index will be used
     */
    void add(vector<Vertex> vertices, vector<unsigned int> indices);
    
    /**
     * Loads the image specified into the texture 
     * object of the texture of the buffer
     */
    void set_texture(std::string file_name);
    
    void clear();
    
    void translate(Point p);
    
    void scale(Point p);
    
    void scale(float f);
    
    void rotate(Point p);
  };  
}

#endif
