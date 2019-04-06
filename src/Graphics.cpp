#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP

#include "Graphics.h"

#include "Util.h"

namespace agl {
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
                 640, 
                 480, 
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
  }
  
  void Graphics::loop() {
    quit = false;
    while (!quit) {
      glClearColor(0.1f, 0.5f, 0.2f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      
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
    glfwTerminate();
  }
}

#endif
