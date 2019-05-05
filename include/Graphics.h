#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "AGL.h"
#include "Input.h"
#include "Camera.h"
#include "Shader.h"

namespace agl {
  class Graphics {
    GLFWwindow* window;
    
    Camera camera;
    
    /**
     * Basic shader, buffers are initialized with it
     */
    Shader* basic_shader;
    
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
     * Just calls the corresponding Camera function
     */
    void move_camera(Point p);
    
    void move_camera_forward();
    
    void move_camera_left();
    
    void move_camera_backwards();
    
    void move_camera_right();
    
    /**
     * Just calls the corresponding Camera function
     */
    void set_camera_pos(Point p);
    
    /**
     * Just calls the corresponding Camera function
     */
    void orient_camera(float h, float v);
    
    /**
     * Just calls the corresponding Camera function
     */
    void turn_camera(float h, float v);
    
    /**
     * Returns the multiplication of the view and projection matrices
     */
    Matrix4f* get_vp_matrix();
    
    GLFWwindow* get_window();
    
    Shader* get_default_shader();
  };
}

#endif
