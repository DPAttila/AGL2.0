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
  float counter = 0;
  Point direction;
  Point pos;
  
  int num_trains;
  float counter_speed;
  float radius;
  
  int model_num;
  int current_model;
  
  vector<string> files;
  
  Alma() {}
  
  ~Alma() {
    delete buffer;
  }
  void init(AGL* graphics) {
    buffer = new Buffer(graphics);
    this->gl = graphics;
    
    //buffer->load("../../Downloads/kenney/Models/obj/ground_dirt.obj", false);
    
    //buffer->set_texture("test/obj-data/rail2.jpg");
    direction = Point(0, 0, 0);
    pos = Point(0, 0, 0);
    
    counter_speed = 0;
    radius = 10;
    num_trains = 1;
    
    ifstream in("test/models.txt");
    
    string a;
    for (int i = 0; i < 302; i++) {
      in >> a;
      files.push_back(a);
    }
    
    model_num = 0;
    current_model = -1;
  }
  
  void draw() {
    if (model_num != current_model) {
      current_model = model_num;
      delete buffer;
      buffer = new Buffer(gl);
      buffer->load("../../new/" + files[model_num], false);
      //buffer->set_texture("test/obj-data/rail2.jpg");
    }
    
    for (int i = -5; i < 5; i++) {
      for (int j = -5; j < 5; j++) {
        buffer->translate(Point(i*10, 0, j*10));
        buffer->draw();
      }
    }
  }
};

AGL ati_gl;
  
Alma alma;

void input() {
  
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
      
    Point2f d = ati_gl.get_cursor_delta();
    d.x /= 1000.0;
    d.y /= 1000.0;
    
    ati_gl.turn_camera(d.x, d.y);
  }
  if (ati_gl.get_key(GLFW_KEY_E) == 1) {
    if (ati_gl.is_cursor_disabled()) {
      ati_gl.enable_cursor();
    } else {
      ati_gl.disable_cursor();
    }
  } 

}

void draw() {
   {
      ImGui::Begin("cica");

      ImGui::Text("cica.");
      
      ImGui::InputInt("model", &alma.model_num);
      ImGui::SliderInt("num trains", &alma.num_trains, 0, 50);
      ImGui::SliderFloat("counter speed", &alma.counter_speed, 0.0, 0.5);
      ImGui::SliderFloat("radius", &alma.radius, 0.0, 50.0);
      
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }
      
  alma.draw();
}

void logic() {
}

int main() {
   
  ati_gl.init("cica", draw, input, logic);
  Shader *s = new Shader("src/shaders/default.vs", "src/shaders/default.fs");
  ati_gl.get_graphics()->set_shader(s);
  
  alma.init(&ati_gl);
  
  ati_gl.loop();
}
