#ifndef KEYBOARD_CPP
#define KEYBOARD_CPP

#include "Input.h"

#include "Graphics.h"

#include <iostream>

namespace agl {

  void Input::init(GLFWwindow* window) {
    this->window = window;
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
  }
  
  void Input::key_callback(
      GLFWwindow* window, 
      int key, 
      int scancode, 
      int action, 
      int mods
  ) {
    ((Graphics*)glfwGetWindowUserPointer(window))->
        key_event(key, scancode, action, mods);
  }
  
  void Input::key_event(int key, int scancode, int action, int mods) {
    if (key > -1 && key < key_count) {
      if (action == GLFW_PRESS) keys[key] = 1;
      else if (action == GLFW_RELEASE) keys[key] = 0;
    }
  }
  
  void Input::cursor_pos_callback(GLFWwindow* window, double x, double y) {
    ((Graphics*)glfwGetWindowUserPointer(window))->
      cursor_move_event(x, y);
  }
  
  void Input::cursor_move_event(double x, double y) {
    cursor_delta_x = x - cursor_x;
    cursor_delta_y = y - cursor_y;
    cursor_x = x;
    cursor_y = y;
  }
  
  void Input::on_loop() {
    for (int i = 0; i < key_count; i++) 
      if (keys[i]) keys[i]++;
    cursor_delta_x = 0;
    cursor_delta_y = 0;
  }
  
  void Input::set_camera_cursor_mode() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   // if (glfwRawMouseMotionSupported())
   //   glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }
  
  int Input::get_key(int key) {
    return keys[key];
  }
  
  Point2f Input::get_cursor_pos() {
    return Point2f(cursor_x, cursor_y);
  }
  
  Point2f Input::get_cursor_delta() {
    return Point2f(cursor_delta_x, cursor_delta_y);
  }
}

#endif
