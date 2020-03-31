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
    input.disable_cursor();
    
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
  
  Input* AGL::get_input() {
    return &input;
  }
}

#endif
