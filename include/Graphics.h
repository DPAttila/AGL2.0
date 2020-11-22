#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "AGL.h"
#include "Camera.h"
#include "ShaderManager.h"

namespace agl {
  class AGL;

  class Graphics {
    GLFWwindow* window;
    
    Camera camera;
    
    ShaderManager* shader_manager;
    
    /**
     * Pointer to the owner AGL instance, 
     * since we have to call it's draw function
     */
    AGL* agl;
    
    bool init_successful;

    public:

    Graphics(AGL* agl);
    
    ~Graphics();

    /**
     * Calls the draw function defined by the owner AGL instance
     */
    void on_loop();
    
    /**
     * Returns the multiplication of the view and projection matrices
     */
    Matrix4f* get_vp_matrix();
    
    GLFWwindow* get_window();
    
    ShaderManager* get_shader_manager();
    
    Camera* get_camera();

    bool is_init_successful();
  };
}

#endif
