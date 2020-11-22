#ifndef AGL_H
#define AGL_H

#include "Point.h"
#include "Input.h"
#include "Graphics.h"

namespace agl {
  class Graphics;
  class Input;

  /**
   * @brief Abstract wrapper class for graphics and input.
   * The user should only interact with agl by extending this class.
   * The following three methods have to be defined by the user:
   * <draw>(), <input>(), <logic>()
   */
  class AGL {
  protected:
    Graphics *graphics;
    
    Input *input;
    
    std::string window_name;

    bool init_successful;

    bool quit;
    
    /**
     * true: The cursor is disabled, ideal for camera movement
     * false: The cursor is enabled, ideal for ui
     */
    bool cursor_disabled;
    
  public:

    /**
     * Draw function automtically called every frame
     * Has to be defined by the extending class
     */
    virtual void draw_func() = 0;

    /**
     * Input handling function automatically called every frame
     * Has to be defined by the extending class
     */
    virtual void input_func() = 0;

    /**
     * Game / simulation logic function automatically called every frame
     * Has to be defined by the extending class
     */
    virtual void logic_func() = 0;

    AGL(std::string window_name);

    ~AGL();

    void loop();
    
    void finish();
    
    Graphics* get_graphics();
    
    Input* get_input();

    std::string get_window_name();
  };
}

#endif
