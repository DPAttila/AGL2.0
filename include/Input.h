#ifndef INPUT_H
#define INPUT_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "imgui.h"

#include "AGL.h"
#include "Point2f.h"

namespace agl {
  class AGL;
  
  class Input {
    GLFWwindow* window;
    
    /**
     * Pointer to the owner AGL instance, 
     * since we have to call it's input handler function
     */
    AGL* agl;

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
    
    double scroll_x, scroll_y;
    
    bool cursor_disabled;
    
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
    
    static void mouse_scroll_callback(GLFWwindow* window, double x, double y);
    
    public:
    
    Input(AGL* agl);

    void key_event(int key, int scancode, int action, int mods);
    
    void cursor_move_event(double x, double y);
    
    void mouse_scroll_event(double x, double y);
    
    /**
     * Should be called every frame by the AGL loop function
     * It increases the time values of the keys that are pressed
     * Calls the input handler function defined by the owner AGL instance
     */
    void on_loop();
    
    /**
     * Sets the cursor mode to GLFW_CURSOSR_DISABLED.
     * This makes the cursor invisible and
     * centered, allowing infinite movement, which is perfect for our camera.
     * See https://www.glfw.org/docs/latest/input_guide.html#cursor_mode
     */
    void disable_cursor();
    
    /**
     * Sets the cursor mode to GLFW_CURSOR_NORMAL.
     * This allows normal cursor movement, ideal for GUIs.
     * See https://www.glfw.org/docs/latest/input_guide.html#cursor_mode
     */
    void enable_cursor();
    
    int get_key(int key);
    
    Point2f get_cursor_pos();
    
    Point2f get_cursor_delta();
    
    Point2f get_scroll();
    
    bool is_cursor_disabled();
  };
}

#endif
