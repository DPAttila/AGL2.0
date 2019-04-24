#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP

#include "Graphics.h"

#include "util.h"
#include "shader.h"

namespace agl {
  Graphics::Graphics(void (*user_defined)()) {
    this->user_defined = user_defined;
  }
  
  bool Graphics::init(std::string window_name) {    
    if (!glfwInit()) {
      alert("Failed to initialize GLFW!");
      return false;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
    window = glfwCreateWindow(
                 800, 
                 640, 
                 window_name.c_str(), 
                 glfwGetPrimaryMonitor(), 
                 NULL
             );
    
    if (window == NULL) {
      alert("Failed to open GLFW window.");
      glfwTerminate();
      return false;
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      alert("Failed to initialize GLAD.");
      return false;
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Creates and compiles a GLSL program from the shaders
    shader_program_id = load_shaders("src/shader.vs", "src/shader.fs");
    
    glsl_matrix_location = glGetUniformLocation(shader_program_id, "world");
    
    return true;
  }
  
  void Graphics::loop() {
    quit = false;
    while (!quit) {
      glClearColor(0.1f, 0.5f, 0.2f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      
      // Uses the shaders
      glUseProgram(shader_program_id);
      
      user_defined();
      
      glfwSwapBuffers(window);
      glfwPollEvents();
      
      if (
        glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwWindowShouldClose(window) != 0
      ) {
        quit = true;
      }
    }
    
    terminate();
  }
  
  void Graphics::terminate() {
    glDeleteProgram(shader_program_id);
    glfwTerminate();
  }
  
  GLuint Graphics::get_glsl_matrix_location() {
    return glsl_matrix_location;
  }
}

#endif
