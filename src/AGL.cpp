#ifndef AGL_CPP
#define AGL_CPP

#include "AGL.h"
#include <iostream>

namespace agl {
  AGL::AGL(std::string window_name) {
    graphics = new Graphics(this);
    
    if (!graphics->is_init_successful()) {
      init_successful = false;
      return;
    }

    input = new Input(this);
    
    input->disable_cursor();
    
    quit = false;
    cursor_disabled = true;

    init_successful = true;
  }

  AGL::~AGL() {
    delete graphics;
    delete input;
  }

  void AGL::loop() {
    while (!quit) {
      graphics->on_loop();
      input->on_loop();
      logic_func();
    }
  }

  void AGL::finish() {
    quit = true;
  }
  
  Graphics* AGL::get_graphics() {
    return graphics;
  }
  
  Input* AGL::get_input() {
    return input;
  }

  std::string AGL::get_window_name() {
    return window_name;
  }
}

#endif
