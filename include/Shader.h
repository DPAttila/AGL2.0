#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glad/glad.h"

namespace agl {
  /**
   * @brief This class encapsulates shader functionality. 
   * It creates, uses and destroys shaders.
   *
   * If a buffer (or any other entity) uses the shader in some way, it
   * should subscribe() to it, so the shader will know it mustn't get 
   * destroyed yet. When the buffer doesn't need the shader anymore, 
   * it should unsubscribe(), so it can decide if it can be destroyed
   * safely.
   *
   * Some restrictions:
   * The sampler used in the shader has to be called "sampler"
   * The wvp matrix has to be called "wvp"
   */
  class Shader {
    /**
     * Handle to the shader program
     */
    GLuint program_id;
    
    /**
     * Handle to the sampler (used for textures)
     * See ogldev tutorial 16
     */
    GLuint sampler_id;
    
    /**
     * Handle to the WVP matrix uniform variable in the shader
     */
    GLuint wvp_matrix_location;

    /**
     * Count of the users of the shader.\n
     * If the last user unsubscribes (so there are 0 users left) and
     * #deletable == true, it gets destrcuted
     */
    unsigned int num_users;
    
    /**
     * If set to false, the object will not be 
     * destructed when #num_users reaches 0
     * Default is true
     */
    bool deletable;
    
    ~Shader();
    
    /**
     * Creates the shader program using the 
     * provided strings as the shader sources
     * @param[in] vertex_shader The vertex shader source code
     * @param[in] fragment_shader The fragment shader source code
     * @returns True if the shader was initialized correctly, false otherwise
     */
    bool init(const char* vertex_source, const char* fragment_source);
    
    /**
     * Compiles the source provided
     * param[in] The source to be compiled
     * param[out] The id of the shader compiled 
     * (This parameter has to be generated 
     * prior to this call using glCreate)
     */
    bool compile_source(const char* source, GLuint &shader_id);
    
    /**
     * @returns true if there was no error 
     * compiling the shader, false otherwise
     */
    bool check_shader(GLuint shader_id);
    
    /**
     * @returns true if there was no error
     * linking the program, false otherwise
     */
    bool check_program(GLuint program_id);
    
    public:
    /**
     * Constructs, creates the shader program using the 
     * provided strings as the shader sources
     * @param[in] vertex_shader The vertex shader source code
     * @param[in] fragment_shader The fragment shader source code
     */
    Shader(const char* vertex_source, const char* fragment_source);

    /**
     * Constructs, creates the shader program using the
     * source code read from the file paths specified
     * @param[in] vs_path Path to the vertex shader source code
     * @param[in] fs_path Path to the fragment shader source code
     * @returns True if the shader was initialized correctly, false otherwise
     */
    Shader(std::string vs_path, std::string fs_path);

    /**
     * Constructs, initializng a basic, predefined shader program
     * @returns True if the shader was initialized correctly, false otherwise
     */
    Shader();    
    
    /**
     * Uses the shader
     */
    void use();

    /**
     * Users of the shader have to signal their intention of using 
     * the shader by calling this function. \n
     * It increases #num_users by one
     */
    void subscribe();
    
    /**
     * Users of the shader have to signal that they no 
     * longer need the shader using this function. \n
     * It decreases #num_users by one and calls the destructor if
     * it reaches 0 and the object is deletable.
     */
    void unsubscribe();
    
    void set_deletable(bool deletable);
    
    GLuint get_wvp_matrix_location();
  };
}

#endif
