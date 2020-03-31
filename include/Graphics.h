#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "AGL.h"
#include "Input.h"
#include "Camera.h"
#include "ShaderManager.h"

namespace agl {
  class Graphics {
    GLFWwindow* window;
    
    Camera camera;
    
    ShaderManager* shader_manager;
    
    /**
     * Pointer to user-defined function to be called in loop
     * A user-defined draw function should contain draw calls.
     * Buffer swapping and clearing is done by the loop automatically.
     */
    void (*user_defined)();
    
    public:
    Graphics();
    
    /**
     * Initializes glfw, glad and a window.
     * @param[in] window_name Name of the window to be created
     * @param[in] user_defind User-defined draw function. All of the user's 
     * bufferes should be drawn here
     * @retval <true> The intialization was successful
     * @retval <false> Couldn't initialize 
     */
    bool init(std::string window_name, void (*user_defined)());
    
    /**
     * Handles drawing, inputs and calls a user-defined 
     * function in a loop until quit is set to true
     */
    void on_loop();
    
    /**
     * Called automatically when the main loop is quit.
     * Frees memory.
     */
    void terminate();
    
    /**
     * Returns the multiplication of the view and projection matrices
     */
    Matrix4f* get_vp_matrix();
    
    GLFWwindow* get_window();
    
    ShaderManager* get_shader_manager();
    
    Camera* get_camera();
  };
}

#endif
