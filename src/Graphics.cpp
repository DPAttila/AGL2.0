#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP

#include "Graphics.h"

#include <string>
#include <iostream>

#include "util.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "shader.h"

namespace agl {
  Graphics::Graphics() {}
  
  bool Graphics::init(std::string window_name, void (*user_defined)()) {  
    this->user_defined = user_defined;  
    if (!glfwInit()) {
      alert("Failed to initialize GLFW!");
      return false;
    }
    
    int glfw_version_maj, glfw_version_min, glfw_version_rev;
    glfwGetVersion(&glfw_version_maj, &glfw_version_min, &glfw_version_rev);
    std::cout << "GLFW version " << glfw_version_maj << "." 
              << glfw_version_min << "." << glfw_version_rev << '\n';
    
    glfwWindowHint(GLFW_SAMPLES, 4);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    log(std::to_string(count) + " monitors identified:");
    for (int i = 0; i < count; i++) {
      const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);
      log(std::to_string(mode->width) + " * " + std::to_string(mode->height));
    }
    
    
    window = glfwCreateWindow(
                 glfwGetVideoMode(monitors[0])->width, 
                 glfwGetVideoMode(monitors[0])->height, 
                 window_name.c_str(), 
                 monitors[0], 
                 NULL
             );
    
    /*
    window = glfwCreateWindow(
      1000, 1000, window_name.c_str(),
       NULL, NULL
    );
    */
    
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
    
    camera.init(
        glfwGetVideoMode(monitors[0])->width, 
        glfwGetVideoMode(monitors[0])->height
    );
    
    // Creates and compiles a GLSL program from the shaders
    shader_program_id = load_shaders("src/shader.vs", "src/shader.fs");
    
    sampler_id = glGetUniformLocation(shader_program_id, "sampler");
    
    glsl_matrix_location = glGetUniformLocation(shader_program_id, "world");
    
    glUniform1i(sampler_id, 0);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    return true;
  }
  
  void Graphics::on_loop() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glClearColor(0.1f, 0.5f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Uses the shaders
    glUseProgram(shader_program_id);
    
    user_defined();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    glfwSwapBuffers(window);
  }
  
  void Graphics::terminate() {
    glDeleteProgram(shader_program_id);
    glfwTerminate();
  }
  
  void Graphics::move_camera(Point p) {
    camera.move(p);
  }
  
  void Graphics::move_camera_forward() {
    camera.move_forward();  
  }
  
  void Graphics::move_camera_left() {
    camera.move_left();
  }
  
  void Graphics::move_camera_backwards() {
    camera.move_backwards();
  }
  
  void Graphics::move_camera_right() {
    camera.move_right();
  }
  
  void Graphics::set_camera_pos(Point p) {
    camera.set_pos(p);
  }
  
  void Graphics::orient_camera(float h, float v) {
    camera.orient(h, v);
  }
  
  void Graphics::turn_camera(float h, float v) {
    camera.turn(h, v);
  }
  
  Matrix4f* Graphics::get_vp_matrix() {
    return camera.get_vp_matrix();
  }
  
  GLuint Graphics::get_glsl_matrix_location() {
    return glsl_matrix_location;
  }
  
  GLFWwindow* Graphics::get_window() {
    return window;
  }
}

#endif
