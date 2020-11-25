#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP

#include "Graphics.h"

#include <string>
#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "util.h"
#include "ShaderManager.h"

namespace agl {
  Graphics::Graphics(AGL* agl) {
    printf("\n");
    this->agl = agl;

    if (!glfwInit()) {
      printf(ANSI_COLOR_RED "Failed to initialize GLFW!" ANSI_END_COLOR);
      init_successful = false;
      return;
    }
    
    int glfw_version_maj, glfw_version_min, glfw_version_rev;
    glfwGetVersion(&glfw_version_maj, &glfw_version_min, &glfw_version_rev);
    printf(
        "GLFW version %i.%i.%i\n", 
        glfw_version_maj, 
        glfw_version_min, 
        glfw_version_rev
    );
    
    glfwWindowHint(GLFW_SAMPLES, 4);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    printf("%i monitors identified:\n", count);

    for (int i = 0; i < count; i++) {
      const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);
      printf("%i * %i\n", mode->width, mode->height);
    }
    
    window = glfwCreateWindow(
                 glfwGetVideoMode(monitors[count-1])->width, 
                 glfwGetVideoMode(monitors[count-1])->height, 
                 agl->get_window_name().c_str(), 
                 monitors[count-1], 
                 NULL
             );
    
    if (window == NULL) {
      printf(ANSI_COLOR_RED "Failed to open GLFW window." ANSI_END_COLOR);
      glfwTerminate();
      init_successful = false;
      return;
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      printf(ANSI_COLOR_RED "Failed to initialize GLAD." ANSI_END_COLOR);
      init_successful = false;
      return;
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    camera.init(
        glfwGetVideoMode(monitors[0])->width, 
        glfwGetVideoMode(monitors[0])->height
    );
    
    shader_manager = new ShaderManager();
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    
    printf("\n");
    init_successful = true;
  }
  
  void Graphics::on_loop() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    agl->draw_func();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    glfwSwapBuffers(window);
  }
  
  Graphics::~Graphics() {
    delete shader_manager;
    glfwTerminate();
  }
  
  Matrix4f* Graphics::get_vp_matrix() {
    return camera.get_vp_matrix();
  }

  void Graphics::draw_buffer(Buffer* buffer) {
    buffer->draw(camera.get_vp_matrix());
  }
  
  GLFWwindow* Graphics::get_window() {
    return window;
  }
  
  ShaderManager* Graphics::get_shader_manager() {
    return shader_manager;
  }
  
  Camera* Graphics::get_camera() {
    return &camera;    
  }

  bool Graphics::is_init_successful() {
    return init_successful;
  }
}

#endif
