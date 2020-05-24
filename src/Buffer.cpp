#ifndef BUFFER_CPP
#define BUFFER_CPP

#include "Buffer.h"

#include <map>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <algorithm>

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
  
  Buffer::Buffer(AGL* agl, GLenum primitive) {
    this->primitive = primitive;
    
    this->graphics = agl->get_graphics();
    
    shader = graphics->get_shader_manager()->get_shader("default");
    
    texture = NULL;
    
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
    
    // the world matrix gets calculated by calculating the wvp matrix
    transformation.calculate_wvp_matrix(graphics->get_vp_matrix());
    
    glUniformMatrix4fv( // supplies wvp matrix to the shader
        shader->get_wvp_matrix_location(),
        1,
        GL_TRUE,
        &transformation.wvp_matrix[0][0]
    );
    
    glUniformMatrix4fv( // supplies world matrix to the shader
        shader->get_world_matrix_location(),
        1,
        GL_TRUE,
        &transformation.world_matrix[0][0]
    );
    
    //TODO: the address of this matrix is always changing, 
    // but I guess it shouldn't
    //cout << &transformation.wvp_matrix[0][0] << '\n';
    
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
        (const GLvoid*) 0
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
    
    texture->bind(GL_TEXTURE0);
    
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
    cout << "Deleting buffer.\n";
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &indexbuffer);
    
    if (texture != NULL) {
      delete texture;
      texture = NULL;
    }
    
    // the shader doesn't have to be deleted, 
    // because the ShaderManager takes care of it
    shader = NULL;
  }
  
  void Buffer::set_texture(string file_name) {
    if (texture != NULL) {
      delete texture;
      texture = NULL;
    }
    texture = new Texture(file_name);
  }
  
  void Buffer::set_texture(Texture* texture) {
    this->texture = texture;
  }
  
  void Buffer::set_shader(string name) {
    shader = graphics->get_shader_manager()->get_shader(name);
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
  
  void Buffer::rotate(float h, float v) {
    rotate(Point(-v, -h + 3.14/2.0, 0));
  }
  
  void Buffer::rotate_around_axis(Point axis, float angle) {
    transformation.rotate_around_axis(axis, angle);
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
  
  bool Buffer::load(string obj_path, bool ignore_mtl) {
    cout << "Loading obj file from " << obj_path << "\n";
    
    // gets the directory path, it will be used if a mtl file is requested
    string path = obj_path.substr(0, obj_path.find_last_of("/")+1);
    ifstream in(obj_path);
    if (!in.good()) {
      cout << "Couldn't read obj file\n";
      return false;
    }

    vector<Point> pos;
    vector<Point2f> tex;
    vector<Point> nor;
    
    // A corresponding Vertex gets generated for every string and put in here
    map<string, Vertex> vertex_map;
    
    // Vertex strings in order of appearing (with duplicates)
    vector<string> vertex_strings;
    
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    
    string face_vertex_strings[20];
    
    bool has_mtl = false;
    
    // A color is mapped to every material string 
    // that is read from the .mtl file
    map<string, Point> materials;
    
    // String identifier of the currently used material
    string current_mtl = "";
    
    Point2f uv_coord;
    
    int pos_index = 0, tex_index = 0, nor_index = 0;
    
    char c;
    string a, b;
    float x, y, z;
    int ind = 0;
    while (!in.eof()) {
      in >> a;
      
      if (a == "mtllib" && !ignore_mtl) { 
        has_mtl = true;
        // if a mtl file is requested, it gets 
        // read before contionuing with the obj file
        cout << "Loading mtl file from ";
        in >> a;
        string mtl_path = path + a;
        cout << mtl_path << '\n';
        
        ifstream mtl_in(mtl_path);
        
        if (!mtl_in.good()) {
          cout << "couldn't read mtl file.\n";
          return false;
        }
        
        while (!mtl_in.eof()) {
          mtl_in >> a;
          if (a == "newmtl") {      // a new material is defined
            getline(mtl_in, a);     // with the name a
            // the following lines are ignored until the diffuse color is found
            b = "";
            while (b != "Kd") mtl_in >> b;      
            
            mtl_in >> x >> y >> z;  // the diffuse color is read
            // the diffuse color gets mapped to the material string
            materials[a] = Point(x, y, z);
          }
        }
        
        // each material color gets 3 bytes in the pixel data array
        unsigned char* pixel_data = new unsigned char[materials.size() * 3];
        
        map<string, Point>::iterator it0 = materials.begin();
        ind = 0;
        for (it0; it0 != materials.end(); it0++) {
          pixel_data[ind  ] = it0->second.x * 255;
          pixel_data[ind+1] = it0->second.y * 255;
          pixel_data[ind+2] = it0->second.z * 255;
          ind += 3;
        }
        
        cout << "Creating texture from mtl data\n";
        texture = new Texture(GL_TEXTURE_2D, pixel_data, materials.size());
        cout << "Texture created\n";
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
        getline(in, a);
        a = a.substr(1) + " ";
        //cout << a << "\n";
        size_t num_spaces = count(a.begin(), a.end(), ' ');
        
        for (int i = 0; i < num_spaces; i++) { // for all vertices of a face
          // a vertex definition usually has the form v/vt/vn, 
          // where v, vt, vn are indices
          //cout << a.find(" ") << ' ';
          b = a.substr(0, (int)a.find(" "));
          //cout << b << '\n';
          a = a.substr(a.find(" ")+1);
          
          // adds b to a temporary set of vertices describing the current face
          face_vertex_strings[i] = b;
          
          // if vertex is not yet in the map
          if (vertex_map.find(b) == vertex_map.end()) {
            // vertex
            ind = 0;
            pos_index = 0;
            while (ind < b.size() && b[ind] != '/') {
              pos_index *= 10;
              pos_index += b[ind] - '0';
              ind++;
            }
            
            // texture
            ind++;
            tex_index = 0;
            while (ind < b.size() && b[ind] != '/') {
              tex_index *= 10;
              tex_index += b[ind] - '0';
              ind++;
            }
            
            // normal
            ind++;
            nor_index = 0;
            while (ind < b.size()) {
              nor_index *= 10;
              nor_index += b[ind] - '0';
              ind++;
            }
            
            // subtract 1 since we are indexing 
            // from 0 and obj is indexing from 1
            pos_index -= 1;
            tex_index -= 1;
            nor_index -= 1;
            
            if (has_mtl) {
              y = 0;
              x = distance(materials.begin(), materials.find(current_mtl)) / (float)materials.size() + 1.0 / (materials.size() + 1);
              uv_coord = Point2f(x, y);
            } else {
              uv_coord = tex[tex_index];
            }
            // adds the new vertex to the vertex map
            vertex_map[b] = Vertex(pos[pos_index], uv_coord, nor[nor_index]);
          }
        }
        
        if (num_spaces == 3) { // if the face is a triangle
          for (int i = 0; i < 3; i++) {
            vertex_strings.push_back(face_vertex_strings[i]);
          }
        } else if (num_spaces == 4) { // if the face is a quad
          for (int i = 0; i < 3; i++) {
            vertex_strings.push_back(face_vertex_strings[i]);
          }
          
          vertex_strings.push_back(face_vertex_strings[0]);
          vertex_strings.push_back(face_vertex_strings[2]);
          vertex_strings.push_back(face_vertex_strings[3]);
        } else {
          
        }
      } else if (a == "usemtl" && !ignore_mtl) {
        getline(in, current_mtl);
      }
    }
    
    map<string, Vertex>::iterator it = vertex_map.begin();
    for (it; it != vertex_map.end(); it++)
      vertices.push_back(it->second);
    
    for (int i = 0; i < vertex_strings.size(); i++)
      indices.push_back(distance(vertex_map.begin(), vertex_map.find(vertex_strings[i])));
    
    add(vertices, indices);
    
    cout << "Obj file loaded.\n";
    return true;
  }
}

#endif
