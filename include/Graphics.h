#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include "glad/glad.h"

#include <GLFW/glfw3.h>

namespace agl {
  class Graphics {
    GLFWwindow* window;
    
    /**
     * Id of the GLSL program
     */
    GLuint shader_program_id;
    
    /**
     * If set to true, the main loop stops
     */
    bool quit;
    
    /**
     * Called automatically when the main loop is quit.
     * Frees memory.
     */
    void terminate();
    
    /**
     * Pointer to user-defined function to be called in loop
     * A user-defined draw function should contain draw calls, 
     * input handling calls and simulation-logic calls.
     * Buffer swapping and clearing is done by the loop automatically.
     */
    void (*user_defined)();
    
    public:
    Graphics(void (*user_defined)());
    
    /**
     * Initializes glfw, glad and a window
     * @param[in] window_name Name of the window to be created
     * @retval <true> The intialization was successful
     * @retval <false> Couldn't initialize 
     */
    bool init(std::string window_name);
    
    /**
     * Handles drawing, inputs and calls a user-defined 
     * function in a loop until quit is set to true
     * @todo Handle user-defined function 
     */
    void loop();
    
  };
}

#endif
