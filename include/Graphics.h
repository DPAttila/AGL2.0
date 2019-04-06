#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include "glad/glad.h"

#include <GLFW/glfw3.h>

namespace agl {
  class Graphics {
    GLFWwindow* window;
   
    /**
     * If set to true, the main loop stops
     */
    bool quit;
    
    /**
     * Called automatically when the main loop is quit.
     * Frees allocated memory.
     */
    void terminate();
    
    public:
    
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
     * //TODO: Handle user-defined function
     */
    void loop();
    
  };
}

#endif
