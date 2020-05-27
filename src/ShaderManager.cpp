#ifndef SHADER_MANAGER_CPP
#define SHADER_MANAGER_CPP

#include <iostream>

#include "ShaderManager.h"

namespace agl {
  ShaderManager::ShaderManager() {
    shaders["default"] = new Shader(
      "../shaders/default.vs", 
      "../shaders/default.fs"
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
