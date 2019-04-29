#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Input.h"

namespace agl {
  /**
   * @todo: possibly create a new class that controls Graphics and Input 
   */
  class Graphics {
    GLFWwindow* window;
    
    Camera camera;
    
    Input input;
    
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
    
    /**
     * Sets the cursor mode to GLFW_CURSOSR_DISABLED
     * and enables raw mouse motion. This makes the cursor invisible and
     * centered, allowing infinite movement, which is perfect for our camera.
     * See https://www.glfw.org/docs/latest/input_guide.html#cursor_mode
     */
    void set_camera_cursor_mode();
    
    public:
    Graphics();
    
    /**
     * Initializes glfw, glad and a window.
     * Sets the glfw user pointer to the object initialized, 
     * so it can be accessed from anywhere
     * @param[in] window_name Name of the window to be created
     * @retval <true> The intialization was successful
     * @retval <false> Couldn't initialize 
     */
    bool init(std::string window_name, void (*user_defined)());
    
    /**
     * Handles drawing, inputs and calls a user-defined 
     * function in a loop until quit is set to true
     * @todo Handle user-defined function 
     */
    void loop();
    
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
    void orient_camera(Point p);
    
    /**
     * Just calls the corresponding Camera function
     */
    void turn_camera(Point p);
    
    /**
     * Just calls the corresponding Keyboard function
     */
    void key_event(int key, int scancode, int action, int mods);
    
    void cursor_move_event(double x, double y);
    
    /**
     * Just calls the corresponding Keyboard function
     */
    int get_key(int key);
    
    Point2f get_cursor_delta();
    
    Point2f get_cursor_pos();
     
    /**
     * Returns the multiplication of the view and projection matrices
     */
    Matrix4f* get_vp_matrix();
    
    GLuint get_glsl_matrix_location();
  };
}

#endif
