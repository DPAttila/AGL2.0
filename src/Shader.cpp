#ifndef SHADER_CPP
#define SHADER_CPP

#include "Shader.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>

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
    
    sampler_id = glGetUniformLocation(program_id, "sampler");
    wvp_matrix_location = glGetUniformLocation(program_id, "wvp");
    world_matrix_location = glGetUniformLocation(program_id, "world");
    
    return true;
  }
  
  Shader::~Shader() {
    glDeleteProgram(program_id);
  }
  
  string Shader::read_source(string path) {
    std::string shader_code;
    std::ifstream shader_stream(path, std::ios::in);
    if (shader_stream.is_open()) {
      std::stringstream sstr;
      sstr << shader_stream.rdbuf();
      shader_code = sstr.str();
      shader_stream.close();
    }
    
    return shader_code;
  }
  
  Shader::Shader(string vertex_source, string fragment_source) {
    
    if (vertex_source.find(".vs") != string::npos)
      vertex_source = read_source(vertex_source);
    
    if (fragment_source.find(".fs") != string::npos)
      fragment_source = read_source(fragment_source); 
    
    if (!init(vertex_source.c_str(), fragment_source.c_str())) {
      compile_successful = false;
      printf(ANSI_COLOR_RED "Couldn't create shader\n" ANSI_END_COLOR);
    } else {
      compile_successful = true;
    }
  }
  
  void Shader::use() {
    glUseProgram(program_id);
    glUniform1i(sampler_id, 0);
  }
  
  GLuint Shader::get_wvp_matrix_location() {
    return wvp_matrix_location;
  }
  
  GLuint Shader::get_world_matrix_location() {
    return world_matrix_location;
  }
  
  bool Shader::is_compile_successful() {
    return compile_successful;
  }
}

#endif
