#include <iostream>

#include "Graphics.h"
#include "Buffer.h"

using namespace agl;

class Alma {
  public:
  Buffer buffer;
  
  Alma() {}
  
  void init() {
    buffer = Buffer(GL_TRIANGLES);
    buffer.init();
    vector<Point> vertices = {
        Point(1, -1, 0), 
        Point(0, -0.5, 0),
        Point(0, 0, 1),
        Point(-1, 0.5, 1), 
        Point(0, 1, 0)
    };
    vector<unsigned int> indices = {0, 1, 2, 3, 4, 3, 4};
    
    buffer.add(vertices, indices);
  }
  
  void draw() {
    buffer.draw();
  }
};

Alma alma;

void test_loop() {
  alma.draw();  
}

int main() {
  Graphics graphics(test_loop);
  
  graphics.init("cica");
  
  alma.init();
  
  graphics.loop();
}
