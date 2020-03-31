#ifndef TEXTURE_CPP
#define TEXTURE_CPP

#include "Texture.h"

#include <stdio.h>

#include "util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace agl {
  void Texture::free() {
    if (image_data == NULL) return;
    
    if (source_is_image) // if stb loader was used
      stbi_image_free(image_data);
    else 
      delete image_data;
    
    image_data = NULL;
  }
  
  bool Texture::init() {
    
    glGenTextures(1, &texture_object);
    
    glBindTexture(texture_target, texture_object);

    // Format of the image, based on the number of channels
    GLenum format;
    if (n == 3) format = GL_RGB;
    else if (n == 4) format = GL_RGBA;
    
    if (texture_target == GL_TEXTURE_1D) {
      glTexImage1D(
          texture_target,
          0,
          GL_RGBA,
          width,
          0,
          format,
          GL_UNSIGNED_BYTE,
          (const GLvoid*) image_data
      );
    }
    else if (texture_target == GL_TEXTURE_2D) {
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
    } else {
       printf("%sTexture target is not supported%s\n", 
        ANSI_COLOR_RED, 
        ANSI_END_COLOR
      );
      return false;
    }
    
    glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    return true;
  }
  
  Texture::Texture(std::string filename, GLenum texture_target) {
    source_is_image = true;
    
    this->texture_target = texture_target;
    image_data = stbi_load(filename.c_str(), &width, &height, &n, 0);
    
    if (image_data == NULL) {
      printf("%sCouldn't load image at %s%s\n",
        ANSI_COLOR_RED,
        filename.c_str(),
        ANSI_END_COLOR
      );
    }
    printf("Loaded image at %s\n", filename.c_str());
    if (!init()) {
      printf("%sCouldn't create texture%s\n", 
        ANSI_COLOR_RED, 
        ANSI_END_COLOR
      );
    }
  }
  
  Texture::Texture(
      GLenum texture_target, 
      unsigned char* data, 
      int w, 
      int h, 
      int n
  ) {
    source_is_image = false;
    
    if (data == NULL) {
      printf("%sImage data input is null pointer%s\n", 
        ANSI_COLOR_RED, 
        ANSI_END_COLOR
      );
    }
    
    if (h > 1 && texture_target != GL_TEXTURE_1D) {
      printf("%sImage data height doesn't match texture target%s\n", 
        ANSI_COLOR_RED, 
        ANSI_END_COLOR
      );
    }
    this->width = w;
    this->height = h;
    this->n = n;
    this->texture_target = texture_target;
    this->image_data = data;
    if (!init()) {
      printf("%sCouldn't create texture%s\n", 
        ANSI_COLOR_RED, 
        ANSI_END_COLOR
      );
    }
  }
  
  Texture::~Texture() {
    printf("Freeing texture ... ");
    free();
    printf("texture freed\n");
  }
  
  void Texture::bind(GLenum texture_unit) {
    glActiveTexture(texture_unit);
    glBindTexture(texture_target, texture_object);
  }
}

#endif
