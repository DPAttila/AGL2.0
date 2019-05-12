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
    
    Shader* shader;
    
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
    
    /**
     * Returns the list of vertices
     */
    vector<Vertex> get_vertices();
    
    /**
     * Returns the vertex at the specified index
     * @param[in] i The index of the vertex to be returned
     */
    Vertex get_vertex(unsigned int i);
    
    /**
     * Returns the list of indices
     */
    vector<unsigned int> get_indices();
    
    /**
     * Sets the vertex at index to the vertex specified
     * @param[in] index Index of the vertex to be changed
     * @param[in] vertex The new value of the vertex
     */
    void set_vertex(unsigned int index, Vertex vertex);
    
    /**
     * Sets the vertices to the new vertices specified
     * @param[in] vertices The new vertex list
     */
    void set_vertices(vector<Vertex> vertices);
    
    /**
     * Saves the buffer to a file in obj format
     * See https://en.wikipedia.org/wiki/Wavefront_.obj_file
     * @param[in] filename Name of the output file
     */
    void save(string filename);
  };  
}

#endif
