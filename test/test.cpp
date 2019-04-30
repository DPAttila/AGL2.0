#include <cmath>
#include <iostream>
#include <unistd.h>

#include "Buffer.h"
#include "Graphics.h"
#include "geometry_generator.h"

using namespace agl;

class Alma {
  public:
  Buffer buffer;
  
  Alma() {}
  
  void init(Graphics* graphics) {
    buffer = Buffer(GL_TRIANGLES);
    buffer.init(graphics);
    
    
    Point p[8] = {
      Point(-1, -1, -1),
      Point(-1, -1, +1),
      Point(-1, +1, -1),
      Point(-1, +1, +1),
      Point(+1, -1, -1),
      Point(+1, -1, +1),
      Point(+1, +1, -1),
      Point(+1, +1, +1)
    };
    
    Point2f t[4] = {
      Point2f(0, 0),
      Point2f(0, 1),
      Point2f(1, 0),
      Point2f(1, 1)
    };
    
    
    vector<Vertex> vertices = {
      Vertex(p[0], t[0]),
      Vertex(p[1], t[1]),
      Vertex(p[2], t[2]),
      Vertex(p[3], t[3]),
      Vertex(p[4], t[0]),
      Vertex(p[5], t[1]),
      Vertex(p[6], t[2]),
      Vertex(p[7], t[3]),
    };
    
    
    vector<unsigned int> indices = {
      
       0, 1, 2,
       3, 2, 1,
       
       4, 6, 5,
       7, 5, 6,
       
       1, 0, 4,
       5, 1, 4,
       
       4, 0, 2,
       6, 4, 2,
     
       1, 5, 3,
       7, 3, 5,
       
       2, 3, 6,
       7, 6, 3
       
    };
    
    /*
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    
    generate_icosahedron(vertices, indices);
    */
    buffer.add(vertices, indices);
    buffer.set_texture("test/test10.png");
    
    buffer.scale(0.8);
  }
  
  void draw() {
    buffer.draw();
  }
};

Graphics graphics;
  
Alma alma;
float counter = 0;

void input() {
  if (graphics.get_key(87)) // W
    graphics.move_camera_forward();
  if (graphics.get_key(65)) // A
    graphics.move_camera_left();
  if (graphics.get_key(83)) // S
    graphics.move_camera_backwards();
  if (graphics.get_key(68)) // D
    graphics.move_camera_right();
  
  Point2f d = graphics.get_cursor_delta();
  d.x /= 1000.0;
  d.y /= 1000.0;
  
  graphics.turn_camera(d.x, d.y);
}

void test_loop() {
  input();
  
  alma.draw();
  //alma.buffer.rotate(Point(counter, 0, counter));
  //alma.buffer.translate(Point(0, 0, counter));
  counter += 0.01;
  
  //graphics.set_camera_pos(Point(0, 0, -3));
  //graphics.orient_camera(Point(sin(counter), 0, cos(counter)));
}

int main() {
   
  graphics.init("cica", test_loop);
  
  alma.init(&graphics);
  
  graphics.loop();
}
