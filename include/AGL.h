#ifndef AGL_H
#define AGL_H

#include "Point.h"
#include "Input.h"
#include "Graphics.h"

namespace agl {
  class Graphics;
  /**
   * @brief Wrapper class for graphics and input.
   * The user should only interact with agl through this class
   */
  class AGL {
    Graphics *graphics;
    
    Input input;
    
    bool quit;
    
    /**
     * true: The cursor is disabled, ideal for camera movement
     * false: The cursor is enabled, ideal for ui
     */
    bool cursor_disabled;
    
    /**
     * Pointer to user-defined function to be called in loop.
     * A user-defined function should contain game logic calls.
     */
    void (*user_defined)();
    
    void terminate();
    
    public:
    bool init(
        std::string window_name, 
        void (*user_defined_draw)(),
        void (*user_defined_input)(),
        void (*user_defined_logic)()
    );
    
    void loop();
    
    void finish();
    
    Graphics* get_graphics();
    
    /**
     * Just calls the corresponding Keyboard function
     */
    int get_key(int key);
    
    Point2f get_cursor_delta();
    
    Point2f get_cursor_pos();
    
    /**
     * Just calls the corresponding Graphics function
     */
    void move_camera(Point p);
    
    /**
     * Just calls the corresponding Graphics function
     */
    void move_camera_forward();
    
    /**
     * Just calls the corresponding Graphics function
     */
    void move_camera_left();
    
    /**
     * Just calls the corresponding Graphics function
     */
    void move_camera_backwards();
    
    /**
     * Just calls the corresponding Graphics function
     */
    void move_camera_right();
    
    /**
     * Just calls the corresponding Graphics function
     */
    void set_camera_pos(Point p);
    
    /**
     * Just calls the corresponding Graphics function
     */
    void orient_camera(float h, float v);
    
    /**
     * Just calls the corresponding Camera function
     */
    void turn_camera(float h, float v);
    
    void disable_cursor();
    
    void enable_cursor();
    
    bool is_cursor_disabled();
  };
}

#endif
