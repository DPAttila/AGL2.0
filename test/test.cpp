#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <unistd.h>

#include "AGL.h"
#include "imgui.h"
#include "Buffer.h"
#include "Graphics.h"
#include "geometry_generator.h"

using namespace agl;

class Alma {
  public:
  AGL* gl;
  Buffer* buffer;
  
  Alma() {}
  
  ~Alma() {
    delete buffer;
  }
  void init(AGL* graphics) {
    buffer = new Buffer(graphics);
    this->gl = graphics;
  
    buffer->load("test/obj-data/train.obj");
    buffer->translate(Point(0, 0, 5));
    //buffer->set_texture("test/green.png");
}
  
  void draw() {    
    buffer->draw();
  }
};

AGL ati_gl;
  
Alma alma;
Point2f d = Point2f(0, 0);

void input() {
 /* 
  if (ati_gl.get_key(GLFW_KEY_Q))
    ati_gl.finish();
  if (ati_gl.is_cursor_disabled()) {
    if (ati_gl.get_key(GLFW_KEY_W)) // W
      ati_gl.move_camera_forward();
    if (ati_gl.get_key(GLFW_KEY_A)) // A
      ati_gl.move_camera_left();
    if (ati_gl.get_key(GLFW_KEY_S)) // S
      ati_gl.move_camera_backwards();
    if (ati_gl.get_key(GLFW_KEY_D)) // D
      ati_gl.move_camera_right();
    
    if (ati_gl.get_key(GLFW_KEY_UP)) 
        d.y = -0.05;
    else if (ati_gl.get_key(GLFW_KEY_DOWN))
        d.y = 0.05;
    else
        d.y = 0;
    
    if (ati_gl.get_key(GLFW_KEY_RIGHT))
        d.x = 0.05;
    else if (ati_gl.get_key(GLFW_KEY_LEFT))
        d.x = -0.05;
    else
        d.x = 0;
    
    if (d.x != 0 || d.y != 0)
        ati_gl.turn_camera(d.x, d.y);
  }
  if (ati_gl.get_key(GLFW_KEY_E) == 1) {
    if (ati_gl.is_cursor_disabled()) {
      ati_gl.enable_cursor();
    } else {
      ati_gl.disable_cursor();
    }
  } */

}

void draw() {
   {
      ImGui::Begin("cica");

    ImGui::Text("cica.");
      
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }
      
  alma.draw();
}

void logic() {
}

int main() {

  std::cout << "test started\n";
  
  ati_gl.init("cica", draw, input, logic);
  std::cout << "agl initialized\n";
  
//   Shader *s = new Shader("src/shaders/default.vs", "src/shaders/default_simple.fs");
//   ati_gl.get_graphics()->set_shader(s);
  
  alma.init(&ati_gl);
  
  ati_gl.loop();
}
