#include <cmath>
#include <iostream>
#include <unistd.h>

#include "Graphics.h"
#include "Buffer.h"

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
      Vertex(p[0], t[2]),
      Vertex(p[1], t[3]),
      Vertex(p[2], t[0]),
      Vertex(p[3], t[1]),
      Vertex(p[4], t[1]),
      Vertex(p[5], t[0]),
      Vertex(p[6], t[3]),
      Vertex(p[7], t[2]),
    };
    
    vector<unsigned int> indices = {
       0, 1, 2,
       3, 2, 1,
       
       4, 5, 6,
       7, 6, 5,
       
       0, 1, 4,
       5, 4, 1,
           
       0, 2, 4,
       6, 4, 2,
     
       1, 3, 5,
       7, 5, 3,
       
       2, 3, 6,
       7, 6, 3
    };
    
    buffer.add(vertices, indices);
    buffer.set_texture("test/test8.png");
    
    buffer.scale(0.8);
  }
  
  void draw() {
    buffer.draw();
  }
};

Alma alma;
float counter = 0;

void test_loop() {
  alma.draw();
  alma.buffer.rotate(Point(counter, counter, 0));
  counter+=0.01;
}

int main() {
   
  Graphics graphics(test_loop);
  
  graphics.init("cica");
  
  alma.init(&graphics);
  
  graphics.loop();
}
