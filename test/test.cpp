#include <cmath>
#include <iostream>

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
    vector<Point> vertices = {
        Point(1, -1, 0),
        Point(1, 1, 0),
        Point(0, 0, 0)
    };
    vector<unsigned int> indices = {0, 1, 2};
    
    buffer.add(vertices, indices);
  }
  
  void draw() {
    buffer.draw();
  }
};

Alma alma;
float counter = 0;

void test_loop() {
  alma.draw();  
  alma.buffer.translate(Point(0, sin(counter), 0));
  alma.buffer.scale(sin(counter));
  alma.buffer.rotate(Point(counter, 0, 0));
  counter+= 0.01;
}

int main() {
  Graphics graphics(test_loop);
  
  graphics.init("cica");
  
  alma.init(&graphics);
  
  graphics.loop();
}
