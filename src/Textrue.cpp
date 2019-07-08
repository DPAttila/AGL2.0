#ifndef TEXTURE_CPP
#define TEXTURE_CPP

#include "Texture.h"

#include <stdio.h>

#include "util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace agl {
  void Texture::free() {
    if (image_data != NULL)
      stbi_image_free(image_data);
  }
  
  Texture::Texture() {
    image_data = NULL;
  }
  
  Texture::~Texture() {
    printf("Texture freed\n");
    free();
  }
  
  bool Texture::init(GLenum texture_target, std::string filename) {
    free();
    
    this->texture_target = texture_target;
    image_data = stbi_load(filename.c_str(), &width, &height, &n, 0);
    
    // Format of the image, based on the number of channels
    GLenum format;
    if (n == 3) format = GL_RGB;
    else if (n == 4) format = GL_RGBA;
    
    if (image_data == NULL) {
      printf("%sCouldn't load image at %s%s\n",
        ANSI_COLOR_RED,
        filename.c_str(),
        ANSI_END_COLOR
      );
      return false;
    }
    printf("Loaded image at %s\n", filename.c_str());
    
    glGenTextures(1, &texture_object);
    glBindTexture(texture_target, texture_object);
    glTexImage2D(
        texture_target, 
        0, 
        GL_RGBA, 
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        (const GLvoid*) image_data
    );
    glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    return true;
  }
  
  void Texture::bind(GLenum texture_unit) {
    glActiveTexture(texture_unit);
    glBindTexture(texture_target, texture_object);
  }
}

#endif
