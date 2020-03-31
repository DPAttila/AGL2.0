#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <map>
#include <string>

#include "Shader.h"

using namespace std;

namespace agl {
  /**
  * This class takes cares of the shaders
  */
  class ShaderManager{
    
    /**
    * Maps the shaders to names (strings)
    */
    map<string, Shader*> shaders;
    
  public:
    ShaderManager();
    
    Shader* get_shader(string name);
    
    /**
    * @param[in] name Name of the shader
    * @param[in] vs_path Path to the vertex shader
    * @param[in] fs_path Path to the fragment shader
    * If a shader already exists with this name, it is overwritten
    * @returns True if the shader was created
    * @returns False if the shader could not be created
    */
    bool add_shader(string name, string vs_path, string fs_path);
  };
}
#endif
