#ifndef KEYBOARD_CPP
#define KEYBOARD_CPP

#include "Input.h"

#include <iostream>

namespace agl {

  Input::Input(AGL* agl) {
    this->agl = agl;
    this->window = agl->get_graphics()->get_window();

    glfwSetWindowUserPointer(window, (void*)this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);
    disable_cursor();
  }

  void Input::key_callback(
      GLFWwindow* window, 
      int key, 
      int scancode, 
      int action, 
      int mods
  ) {
    ((Input*)glfwGetWindowUserPointer(window))->
        key_event(key, scancode, action, mods);
  }
  
  void Input::key_event(int key, int scancode, int action, int mods) {
    if (key > -1 && key < key_count) {
      if (action == GLFW_PRESS) {
        keys[key] = 1;
        ImGui::GetIO().KeysDown[key] = true;
      }
      else if (action == GLFW_RELEASE) {
        keys[key] = 0;
        ImGui::GetIO().KeysDown[key] = false;
      }
    }
  }
  
  void Input::cursor_pos_callback(GLFWwindow* window, double x, double y) {
    ((Input*)glfwGetWindowUserPointer(window))->
      cursor_move_event(x, y);
  }
  
  void Input::mouse_scroll_callback(GLFWwindow* window, double x, double y) {
    ((Input*)glfwGetWindowUserPointer(window))->mouse_scroll_event(x, y);
  }
  
  void Input::cursor_move_event(double x, double y) {
    cursor_delta_x = x - cursor_x;
    cursor_delta_y = y - cursor_y;
    cursor_x = x;
    cursor_y = y;
  }
  
  void Input::mouse_scroll_event(double x, double y) {
    scroll_x = x;
    scroll_y = y;
  }
  
  void Input::on_loop() {
    for (int i = 0; i < key_count; i++) 
      if (keys[i]) keys[i]++;
    cursor_delta_x = 0;
    cursor_delta_y = 0;
    
    scroll_x = 0;
    scroll_y = 0;

    glfwPollEvents();
    
    agl->input_func();
  }
  
  void Input::disable_cursor() {
    cursor_disabled = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    cursor_delta_x = 0;
    cursor_delta_y = 0;
   // if (glfwRawMouseMotionSupported())
   //   glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }
  
  void Input::enable_cursor() {
    cursor_disabled = false;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, width / 2, height / 2);
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
  
  Point2f Input::get_scroll() {
    return Point2f(scroll_x, scroll_y);
  }
  
  bool Input::is_cursor_disabled() {
    return cursor_disabled;
  }
}

#endif
