#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include "glad/glad.h"
#include "Camera.h"

#include <GLFW/glfw3.h>

namespace agl {
  class Graphics {
    GLFWwindow* window;
    
    Camera camera;
    
    /**
     * Id of the GLSL program
     */
    GLuint shader_program_id;
    
    /**
     * Handle to the sampler (used for textures)
     * See ogldev tutorial 16
     */
    GLuint sampler_id;
    
    /**
     * If set to true, the main loop stops
     */
    bool quit;
    
    /**
     * Handle to the world matrix uniform variable in the shader
     */
    GLuint glsl_matrix_location;
    
    /**
     * Pointer to user-defined function to be called in loop
     * A user-defined draw function should contain draw calls, 
     * input handling calls and simulation-logic calls.
     * Buffer swapping and clearing is done by the loop automatically.
     */
    void (*user_defined)();
    
    /**
     * Called automatically when the main loop is quit.
     * Frees memory.
     */
    void terminate();
    
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
    
    /**
     * Returns the multiplication of the view and projection matrices
     */
    Matrix4f* get_vp_matrix();
    
    GLuint get_glsl_matrix_location();
  };
}

#endif
