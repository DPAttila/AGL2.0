#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glad/glad.h"

namespace agl {
  /**
   * Loads, compiles and links the shaders
   * @param[in] vertex_file_path The path to the vertex shader source
   * @param[in] fragment_file_path The path to the fragment shader source
   * @returns The id of the linked shader program 
   */
  GLuint load_shaders(std::string vertex_file_path, std::string fragment_file_path);
  
  /**
   * Loads, compiles and links a basic vertex and fragment shader
   */
  GLuint load_basic_shaders();
}
#endif
