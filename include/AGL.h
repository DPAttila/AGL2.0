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
    
    Input* get_input();
  };
}

#endif
