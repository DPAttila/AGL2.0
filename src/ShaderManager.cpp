#ifndef SHADER_MANAGER_CPP
#define SHADER_MANAGER_CPP

#include <iostream>

#include "ShaderManager.h"

namespace agl {
  ShaderManager::ShaderManager() {
    shaders["default"] = new Shader(
      "#version 330 core\n"
      "layout(location = 0) in vec3 position;\n"
      "layout(location = 1) in vec2 texcoord;\n"
      "uniform mat4 wvp;\n"
      "out vec2 texcoord_fs;\n"
      "out vec3 pos_in;\n"
      "void main() {\n"
      "  gl_Position = wvp * vec4(position, 1.0);\n"
      "  texcoord_fs = texcoord;\n"
      "  pos_in = position;\n"
      "}"
      , 
      "#version 330 core\n"
      "in vec2 texcoord_fs;\n"
      "in vec3 pos_in;\n"
      "out vec4 color;\n"
      "uniform sampler2D sampler;\n"
      "void main() {\n"
      "  color = texture2D(sampler, texcoord_fs.st);\n"
      "}\n"
    );
  }

  Shader* ShaderManager::get_shader(string name) {
    if (shaders[name] != nullptr)
      return shaders[name];
    
    cout << "Shader " + name + " not found!\n";
    cout << "Returning default shader.\n";
    
    return shaders["default"];
  }


  bool ShaderManager::add_shader(string name, string vs_path, string fs_path) {
    if (shaders[name] != nullptr) {
      cout << "Shader " << name << " already exists.\n";
      cout << "Deleting old shader.\n";
      delete shaders[name];
    }
    
    Shader* shader = new Shader(vs_path, fs_path); 
    
    if (shader->is_compile_successful()) {
      shaders[name] = shader;
      return true;
    } else {
      cout << "Couldn't create shader " << name << "\n";
      return false;
    }
  }
}

#endif
