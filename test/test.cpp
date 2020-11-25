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

class Alma : public AGL {
public:
  Buffer* buffer;
  Point2f d{0, 0};

  Alma() : AGL("Hello") {

    if (!init_successful) {
      cout << "Init not succesful\n";
    }

    graphics->get_shader_manager()->add_shader(
      "default",
      "test/shaders/default.vs",
      "test/shaders/default.fs"
    );

    buffer = new Buffer(this);
    buffer->load("test/obj-data/bridge_mesh.obj", true);
    buffer->set_texture(new Texture("test/green.png"));
  }
  
  ~Alma() {
    delete buffer;
  }

  void draw_func() {    
    buffer->draw();

    {
      ImGui::Begin("cica");

      ImGui::Text(graphics->get_camera()->get_pos().to_string().c_str());
      
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }
  }

  void input_func() {
    if (input->get_key(GLFW_KEY_Q) || input->get_key(GLFW_KEY_ESCAPE))
      finish();

    if (input->is_cursor_disabled()) {
      if (input->get_key(GLFW_KEY_W)) // W
        graphics->get_camera()->move_forward();
      if (input->get_key(GLFW_KEY_A)) // A
        graphics->get_camera()->move_left();
      if (input->get_key(GLFW_KEY_S)) // S
        graphics->get_camera()->move_backwards();
      if (input->get_key(GLFW_KEY_D)) // D
        graphics->get_camera()->move_right();
      
      if (input->get_key(GLFW_KEY_UP)) 
          d.y = -0.05;
      else if (input->get_key(GLFW_KEY_DOWN))
          d.y = 0.05;
      else
          d.y = 0;
      
      if (input->get_key(GLFW_KEY_RIGHT))
          d.x = 0.05;
      else if (input->get_key(GLFW_KEY_LEFT))
          d.x = -0.05;
      else
          d.x = 0;
      
      if (d.x != 0 || d.y != 0)
          graphics->get_camera()->turn(d.x, d.y);
    }

    if (input->get_key(GLFW_KEY_E) == 1) {
      if (input->is_cursor_disabled()) {
        input->enable_cursor();
      } else {
        input->disable_cursor();
      }
    }
  }

  void logic_func() {
  }
};


int main() {
  std::cout << "test started\n";

  Alma alma;
  
  alma.loop();
}
