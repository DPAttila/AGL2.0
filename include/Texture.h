#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "glad/glad.h"

namespace agl {
  class Texture {
    unsigned char* image_data;
    
    /**
     * True, if the image data was loaded from an image file using stb loader
     * False, if the image data was acquired otherwise
     */
    bool source_is_image;
    
    /**
     * Width and height of image
     */
    int width, height;
    
    /**
     * Number of 8-bit components per pixel
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
    
    /**
     * Initializes the texture (Called by the constrcutors)
     */
    bool init();
    
    public:
    /**
     * Loads the image from the file specified using stb_image
     * See stb/stb_image.h
     * @param[in] filename The file to load the image from
     * @param[in] texture_target Type of the texture target
     */
    Texture(std::string filename, GLenum texture_target = GL_TEXTURE_2D);
    
    /**
     * Creates the texture using the image data specified
     * @param[in] data Pointer to the image data, 
     * which should have RGB format
     * @param[in] texture_target Type of the texture target
     * @param[in] w Width of the data in pixels
     * @param[in] h Height of the data in pixels
     * @param[in] n Number of 8-bit components per pixel
     */
    Texture(
        GLenum texture_target, 
        unsigned char* data, 
        int w, 
        int h = 1, 
        int n = 3
    );
    
    ~Texture();
    
    /**
     * Binds the texture object to the texture unit specified
     * See http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html
     */
    void bind(GLenum texture_unit);
    
    GLuint get_texture_object_handle();
  };
}

#endif
