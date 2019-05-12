#ifndef INPUT_H
#define INPUT_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "imgui.h"

#include "Point2f.h"

namespace agl {
  /**
   * TODO: make the user-defined glfw pointer point to the Input class instance
   */
  class Input {
    GLFWwindow* window;
    
    static const int key_count = 350;
    
    /**
     * Base value is 0
     * If a key is pressed, it's value will be increased 
     * until it's released, then it's set back to 0.
     * (If a value is not 0, it shows us for how long 
     * has the key been pressed)
     * For the keycodes see https://www.glfw.org/docs/latest/group__keys.html
     */
    int keys[key_count];
    
    double cursor_x, cursor_y;
    
    double cursor_delta_x, cursor_delta_y;
    
    /**
     * Pointer to user-defined function to be called in loop.
     * A user-defined input function should contain input handling calls.
     */
    void (*user_defined)();
    
    /**
     * This function is made static so it can be set as a callback for GLFW
     * It calls the key handling method of the actual input object 
     * which is retrieved through the GLFW window's user-defined pointer 
     * which points to the Graphics object.
     */
    static void key_callback(
        GLFWwindow* window, 
        int key, 
        int scancode, 
        int action, 
        int mods
    );
    
    /**
     * This function is made static so it can be set as a callback for GLFW
     * It calls the cursor movement method of the actual input object 
     * which is retrieved through the GLFW window's user-defined pointer 
     * which points to the Graphics object.
     */
    static void cursor_pos_callback(GLFWwindow* window, double x, double y);
    
    public:
    bool init(GLFWwindow* window, void (*user_defined)());
    
    void key_event(int key, int scancode, int action, int mods);
    
    void cursor_move_event(double x, double y);
    
    /**
     * Should be called every frame by the Graphics loop function
     * It increases the values of the keys that are pressed
     */
    void on_loop();
    
    /**
     * Sets the cursor mode to GLFW_CURSOSR_DISABLED.
     * This makes the cursor invisible and
     * centered, allowing infinite movement, which is perfect for our camera.
     * See https://www.glfw.org/docs/latest/input_guide.html#cursor_mode
     */
    void set_camera_cursor_mode();
    
    /**
     * Sets the cursor mode to GLFW_CURSOR_NORMAL.
     * This allows normal cursor movement, ideal for GUIs.
     * See https://www.glfw.org/docs/latest/input_guide.html#cursor_mode
     */
    void set_ui_cursor_mode();
    
    int get_key(int key);
    
    Point2f get_cursor_pos();
    
    Point2f get_cursor_delta();
  };
}

#endif
