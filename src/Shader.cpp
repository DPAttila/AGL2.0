#ifndef SHADER_CPP
#define SHADER_CPP

#include "Shader.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>

#include "util.h"

namespace agl {
  bool Shader::check_shader(GLuint shader_id) {
    GLint result;
    int info_log_length;
    
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    
    if (info_log_length > 0) {
      char shader_error_message[info_log_length+1];
      glGetShaderInfoLog(
        shader_id,
        info_log_length,
        NULL,
        shader_error_message
      );
      printf(
          "%s%s%s\n", 
          ANSI_COLOR_RED, 
          shader_error_message, 
          ANSI_END_COLOR
      );
    }
    
    if (result == GL_TRUE) 
      return true;
    else 
      return false;
  }
  
  bool Shader::check_program(GLuint program_id) {
    GLint result;
    int info_log_length;
    
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    
    if (info_log_length > 0) {
      char program_error_message[info_log_length+1];
      glGetShaderInfoLog(
        program_id,
        info_log_length,
        NULL,
        program_error_message
      );
      printf(
          "%s%s%s\n", 
          ANSI_COLOR_RED, 
          program_error_message, 
          ANSI_END_COLOR
      );
    }
    
    if (result == GL_TRUE) 
      return true;
    else 
      return false;
  }
  
  bool Shader::compile_source(const char* source, GLuint &shader_id) {
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);
    
    return check_shader(shader_id);
  }
  
  bool Shader::init(const char* vertex_source, const char* fragment_source) {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    
    GLint result = GL_FALSE;
    int info_log_length;
    
    // Compiles the vertex shader
    printf("Compiling vertex shader\n");
    if (!compile_source(vertex_source, vertex_shader_id))
      return false;
    
    // Compiles the fragment shader
    printf("Compiling fragment shader\n");
    if (!compile_source(fragment_source, fragment_shader_id))
      return false;
    
    // Links the program
    printf("Linking shader program\n");
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    
    if (!check_program(program_id))
      return false;
    
    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);
    
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    
    num_users = 0;
    deletable = true;
    
    sampler_id = glGetUniformLocation(program_id, "sampler");
    wvp_matrix_location = glGetUniformLocation(program_id, "wvp");
    
    return true;
  }
  
  Shader::Shader(const char* vertex_source, const char* fragment_source) {
    if (!init(vertex_source, fragment_source))
      printf(ANSI_COLOR_RED "Couldn't create shader\n" ANSI_END_COLOR);
  }
  
  Shader::~Shader() {
    glDeleteProgram(program_id);
  }
  
  Shader::Shader(std::string vs_path, std::string fs_path) {
    // Reads sthe vertex shader from the file
    std::string vertex_shader_code;
    std::ifstream vertex_shader_stream(vs_path, std::ios::in);
    if (vertex_shader_stream.is_open()) {
      std::stringstream sstr;
      sstr << vertex_shader_stream.rdbuf();
      vertex_shader_code = sstr.str();
      vertex_shader_stream.close();
    }
    
    // Reads the fragment shader from the file
    std::string fragment_shader_code;
    std::ifstream fragment_shader_stream(fs_path, std::ios::in);
    if (fragment_shader_stream.is_open()) {
      std::stringstream sstr;
      sstr << fragment_shader_stream.rdbuf();
      fragment_shader_code = sstr.str();
      fragment_shader_stream.close();
    }
    
    if (!init(vertex_shader_code.c_str(), fragment_shader_code.c_str()))
      printf(ANSI_COLOR_RED "Couldn't create shader\n" ANSI_END_COLOR);
  }
  
  Shader::Shader() {
    const char* vertex_source = 
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec2 texcoord;\n"
        "uniform mat4 wvp;\n"
        "out vec2 texcoord_fs;\n"
        "out vec3 pos_in;\n"
        "void main() {\n"
        "  gl_Position = wvp * vec4(position, 1.0);\n"
        "  texcoord_fs = texcoord;\n"
        "  pos_in = position;\n"
        "}";
    
    const char* fragment_source = 
        "#version 330 core\n"
        "in vec2 texcoord_fs;\n"
        "in vec3 pos_in;\n"
        "out vec4 color;\n"
        "uniform sampler2D sampler;\n"
        "void main() {\n"
	      "  color = texture2D(sampler, texcoord_fs.st);\n"
        "}\n";
    
    if (!init(vertex_source, fragment_source))
      printf(ANSI_COLOR_RED "Couldn't create shader\n" ANSI_END_COLOR);
    deletable = false;
  }
  
  void Shader::use() {
    glUseProgram(program_id);
    glUniform1i(sampler_id, 0);
  }
  
  void Shader::subscribe() {
    num_users++;
  }
  
  void Shader::unsubscribe() {
    num_users--;
    
    if (num_users <= 0 && deletable) delete this;
  }
  
  void Shader::set_deletable(bool deletable) {
    this->deletable = deletable;
    if (num_users <= 0 && deletable) delete this;
  }
  
  GLuint Shader::get_wvp_matrix_location() {
    return wvp_matrix_location;
  }
}

#endif
