#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glad/glad.h"

using namespace std;

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
   * Some restrictions:\n
   * The sampler used in the shader has to be called "sampler"\n
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
     * Handle to the world matrix uniform variable in the shader
     */
    GLuint world_matrix_location;

    /**
     * Count of the users of the shader.\n
     * If the last user unsubscribes (so there are 0 users left)
     */
    unsigned int num_users;
    
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
     * @param[in] source The source to be compiled
     * @param[out] shader_id The id of the shader compiled 
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
    
    /**
     * Reads the shader from a file
     * @param[in] path The path to the source file
     * @returns the path read from the file
     */
    string read_source(string path);
    
    public:
    /**
     * Constructs, creates the shader program using the 
     * provided strings as the shader sources
     * If the strings are paths, they are read, and the file content will be
     * the shader sources (a string is considerd a path if it contains the
     * .fs or .vs extensions)
     * @param[in] vertex_shader The vertex shader source code or path
     * @param[in] fragment_shader The fragment shader source code or path
     */
    Shader(string vertex_source, string fragment_source);

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
    
    GLuint get_wvp_matrix_location();
    
    GLuint get_world_matrix_location();
  };
}

#endif
