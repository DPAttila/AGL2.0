#ifndef AGL_CPP
#define AGL_CPP

#include "AGL.h"

namespace agl {
  bool AGL::init(
      std::string window_name, 
      void (*user_defined_draw)(),
      void (*user_defined_input)(),
      void (*user_defined_logic)()
  ) {
    graphics = new Graphics();
    
    if (!graphics->init(window_name, user_defined_draw))
      return false;
    if (!input.init(graphics->get_window(), user_defined_input))
      return false;
    
    this->user_defined = user_defined_logic;
    input.set_camera_cursor_mode();
    
    quit = false;
    cursor_disabled = true;
    
    return true;
  }
  
  void AGL::loop() {
    while (!quit) {
      graphics->on_loop();
      input.on_loop();
      user_defined();
    }
    
    terminate();
  }
  
  void AGL::terminate() {
    graphics->terminate();
    delete graphics;
  }
  
  void AGL::finish() {
    quit = true;
  }
  
  Graphics* AGL::get_graphics() {
    return graphics;
  }
  
  /**
   * Just calls the corresponding Keyboard function
   */
  int AGL::get_key(int key) {
    return input.get_key(key);
  }
 
  Point2f AGL::get_cursor_delta() {
    return input.get_cursor_delta();
  }
  
  Point2f AGL::get_cursor_pos() {
    return input.get_cursor_pos();
  }
  
  /**
   * Just calls the corresponding Graphics function
   */
  void AGL::move_camera(Point p) {
    graphics->move_camera(p);
  }
  
  /**
   * Just calls the corresponding Graphics function
   */
  void AGL::move_camera_forward() {
    graphics->move_camera_forward();
  }
  
  /**
   * Just calls the corresponding Graphics function
   */
  void AGL::move_camera_left() {
    graphics->move_camera_left();
  }
  
  /**
   * Just calls the corresponding Graphics function
   */
  void AGL::move_camera_backwards() {
    graphics->move_camera_backwards();
  }
  
  /**
   * Just calls the corresponding Graphics function
   */
  void AGL::move_camera_right() {
    graphics->move_camera_right();
  }
  
  /**
   * Just calls the corresponding Graphics function
   */
  void AGL::set_camera_pos(Point p) {
    graphics->set_camera_pos(p);
  }
  
  /**
   * Just calls the corresponding Graphics function
   */
  void AGL::orient_camera(float h, float v) {
    graphics->orient_camera(h, v);
  }
  
  /**
   * Just calls the corresponding Camera function
   */
  void AGL::turn_camera(float h, float v) {
    graphics->turn_camera(h, v);
  }
  
  void AGL::disable_cursor() {
    cursor_disabled = true;
    input.set_camera_cursor_mode();
  }
  
  void AGL::enable_cursor() {
    cursor_disabled = false;
    input.set_ui_cursor_mode();
  }
  
  bool AGL::is_cursor_disabled() {
    return cursor_disabled; 
  }
}

#endif
