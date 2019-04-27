#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "glad/glad.h"

namespace agl {
  class Texture {
    unsigned char* image_data;
    
    /**
     * Width and height of image
     */
    int width, height;
    
    /**
     * Number of 8-bit components per pixel
     * I guess it will always be 4 in our case
     */
    int n;
    
    /**
     * Handle to the texture object 
     * (the texture object contains the actual image data)
     * See http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html
     */
    GLuint texture_object;
    
    /**
     * should be one of: GL_TEXTURE_1D, GL_TEXTURE_2D, etc.
     * See http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html
     */
    GLenum texture_target;
    
    /**
     * Frees the memory allocated for the image data
     * (actually it just calls the corresponding stb_image function)
     */
    void free();
    
    public:
    Texture();
    
    ~Texture();
    
    /**
     * Loads the image from the file specified using stb_image
     * See stb/stb_image.h
     * @param[in] filename The file to load the image from
     * @param[in] texture_target Type of the texture target
     */
    bool init(GLenum texture_target, std::string filename);
    
    /**
     * Binds the texture object to the texture unit specified
     * See http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html
     */
    void bind(GLenum texture_unit);
  };
}

#endif
