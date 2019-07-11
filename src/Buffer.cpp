#ifndef BUFFER_CPP
#define BUFFER_CPP

#include "Buffer.h"

#include <map>
#include <stdio.h>
#include <fstream>
#include <iostream>

#include "util.h"

namespace agl {
  void Buffer::rebuffer() {
    glBindVertexArray(vertexarray_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(
        GL_ARRAY_BUFFER, 
        vertices.size() * sizeof(Vertex),
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
  
  void Buffer::init(AGL* agl) {
    this->graphics = agl->get_graphics();
    
    shader = graphics->get_default_shader();
    shader->subscribe();
    
    glGenVertexArrays(1, &vertexarray_id);
    glBindVertexArray(vertexarray_id);
        
    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &indexbuffer);
    
    transformation.init();
  }
  
  void Buffer::add(vector<Vertex> vertices, vector<unsigned int> indices) {
    int index_size = this->indices.size();
    int vertex_size = this->vertices.size();
    
    if (index_size != 0) {
      // Change the offset of the new indices, since they only describe
      // the new set of vertices and not the already existing ones
      for (int i = 0; i < indices.size(); i++)
        indices[i] += index_size;
    }
    
    if (this->vertices.size() == 0) 
      this->vertices = vertices;
    else {
      // If a new vertex is the same as an old one, it won't get added to the
      // vertex list, the referring new indices get replaced by the old index
      // instead
      bool already_exists;
      bool has_been_redirected[indices.size()];
      for (int i = 0; i < indices.size(); i++)
        has_been_redirected[i] = false;
      
      for (int i = 0; i < vertices.size(); i++) { // for all the new vertices
        already_exists = false;
        for (int j = 0; j < vertex_size; j++) { // for all the old vertices
          // if old vertex == new vertex
          if (vertices[i] == this->vertices[j]) {
            already_exists = true;
            // replaces indices reffering to the new vertex 
            // with indices reffering to the old vertex
            for (int k = 0; k < indices.size(); k++) {
              if (indices[k] == i + index_size && !has_been_redirected[k]) {
                indices[k] = j;
                has_been_redirected[k] = true;
              }
            }
          } 
        }
        if (!already_exists) {
          this->vertices.push_back(vertices[i]);
        }
      }
    }
    
    if (index_size == 0)
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
    shader->use();
    transformation.calculate_wvp_matrix(graphics->get_vp_matrix());
    glUniformMatrix4fv(
        shader->get_wvp_matrix_location(),
        1,
        GL_TRUE,
        &transformation.wvp_matrix[0][0]
    );
    
    glBindVertexArray(vertexarray_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)0
    );
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (const GLvoid*) 12
    );
    glVertexAttribPointer(
      2,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (const GLvoid*) 20
    );
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    
    texture.bind(GL_TEXTURE0);
    
    glDrawElements(
      primitive,
      indices.size(),
      GL_UNSIGNED_INT,
      (void*)0
    );
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
  }
  
  Buffer::~Buffer() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &indexbuffer);
    shader->unsubscribe();
    shader = NULL;
  }
  
  void Buffer::set_texture(std::string file_name) {
    texture.init(GL_TEXTURE_2D, file_name);
  }
  
  void Buffer::clear() {
    vertices.clear();
    indices.clear();
  }
  
  void Buffer::translate(Point p) {
    transformation.translate(p);
  }
  
  void Buffer::scale(Point p) {
    transformation.scale(p);
  }
  
  void Buffer::scale(float f) {
    transformation.scale(f);
  }
  
  void Buffer::rotate(Point p) {
    transformation.rotate(p);
  }
  
  vector<Vertex> Buffer::get_vertices() {
    return vertices;
  }
  
  Vertex Buffer::get_vertex(unsigned int i) {
    return vertices[i];
  }
  
  vector<unsigned int> Buffer::get_indices() {
    return indices;
  }
  
  void Buffer::set_vertex(unsigned int index, Vertex vertex) {
    if (index >= 0 && index < indices.size()) {
      vertices[index] = vertex;
      rebuffer();
    }
  }
  
  void Buffer::set_vertices(vector<Vertex> vertices) {
    this->vertices.clear();
    this->vertices = vertices;
    rebuffer();
  }
  
  void Buffer::save(string filename) {
    ofstream out(filename);
    
    for (int i = 0; i < vertices.size(); i++)
      out << "v " 
          << vertices[i].pos.x << " " 
          << vertices[i].pos.y << " "
          << vertices[i].pos.z << "\n";
    out << "\n";
    
    for (int i = 0; i < vertices.size(); i++)
      out << "vn "
          << vertices[i].nor.x << " "
          << vertices[i].nor.y << " "
          << vertices[i].nor.z << "\n";
    out << "\n";
    
    for (int i = 0; i < vertices.size(); i++)
      out << "vt "
          << vertices[i].tex.x << " "
          << vertices[i].tex.y << "\n";
    
    if (primitive == GL_TRIANGLES) {
      for (int i = 0; i < indices.size(); i++) {
        if (i%3 == 0) 
          out << "\nf ";
        out << indices[i]+1 << "/" << indices[i]+1 << "/" << indices[i]+1 << " ";
      }
    } else {
      printf(ANSI_COLOR_RED "Saving of this kind of primitive is not implemented." ANSI_END_COLOR);
    }
  }
  
  bool Buffer::load(string filename) {
    cout << "Loading obj from " << filename << '\n';
        
    ifstream in(filename);
    if (!in.good()) return false;

    vector<Point> pos;
    vector<Point2f> tex;
    vector<Point> nor;
    
    // A corresponding Vertex gets generated for every string and put in here
    map<string, Vertex> vertex_map;
    
    // Vertex strings in order of appearing (with duplicates)
    vector<string> vertex_strings;
    
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    
    char c;
    string a;
    float x, y, z;
    int pos_index, tex_index, nor_index;
    int ind = 0;
    while (!in.eof()) {
      in >> a;

      if (a == "mtllib") {
        cout << "mtl file requested: ";
        in >> a;
        cout << a << '\n';
      } else if (a == "v") { // vertex
        in >> x >> y >> z; // note that w is not read, it is skipped.
        pos.push_back(Point(x, y, z));
      } else if (a == "vt") { // texture
        in >> x >> y; // note that z is not read, it is skipped.
        tex.push_back(Point2f(x, y));
      } else if (a == "vn") { // normal
        in >> x >> y >> z;
        nor.push_back(Point(x, y, z));
      } else if (a == "f") {
        for (int i = 0; i < 3; i++) { // three vertices of a triangle
          // a vertex definition usually has the form v/vt/vn, 
          // where v, vt, vn are indices
          in >> a;
          vertex_strings.push_back(a);
          
          // if vertex is not yet in the map
          if (vertex_map.find(a) == vertex_map.end()) {
            // vertex
            ind = 0;
            pos_index = 0;
            while (ind < a.size() && a[ind] != '/') {
              pos_index *= 10;
              pos_index += a[ind] - '0';
              ind++;
            }
            
            // texture
            ind++;
            tex_index = 0;
            while (ind < a.size() && a[ind] != '/') {
              tex_index *= 10;
              tex_index += a[ind] - '0';
              ind++;
            }
            
            // normal
            ind++;
            nor_index = 0;
            while (ind < a.size()) {
              nor_index *= 10;
              nor_index += a[ind] - '0';
              ind++;
            }
            
            // subtract 1 since we are indexing 
            // from 0 and obj is indexing from 1
            pos_index -= 1;
            tex_index -= 1;
            nor_index -= 1;
            
            // adds the new vertex to the vertex map
            vertex_map[a] = Vertex(pos[pos_index], tex[tex_index], nor[nor_index]);
          }
        }
      }
    }
    
    map<string, Vertex>::iterator it = vertex_map.begin();
    for (it; it != vertex_map.end(); it++)
      vertices.push_back(it->second);
    
    for (int i = 0; i < vertex_strings.size(); i++)
      indices.push_back(distance(vertex_map.begin(), vertex_map.find(vertex_strings[i])));
    
    add(vertices, indices);
    
    return true;
  }
}

#endif
