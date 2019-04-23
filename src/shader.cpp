#ifndef SHADER_CPP
#define SHADER_CPP

#include "shader.h"

#include <vector>
#include <fstream>
#include <sstream>

#include "util.h"

using namespace std;

namespace agl {
  GLuint load_shaders(string vertex_file_path, string fragment_file_path) {
    // Creates the shaders
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Read sthe vertex shader from the file
    string vertex_shader_code;
    ifstream vertex_shader_stream(vertex_file_path, ios::in);
    if (vertex_shader_stream.is_open()) {
      stringstream sstr;
      sstr << vertex_shader_stream.rdbuf();
      vertex_shader_code = sstr.str();
      vertex_shader_stream.close();
    }
    
    // Reads the fragment shader from the file
    string fragment_shader_code;
    ifstream fragment_shader_stream(fragment_file_path, ios::in);
    if (fragment_shader_stream.is_open()) {
      stringstream sstr;
      sstr << fragment_shader_stream.rdbuf();
      fragment_shader_code = sstr.str();
      fragment_shader_stream.close();
    }
    
    GLint result = GL_FALSE;
    int info_log_length;
    
    // Compiles the vertex shader
    log("compiling shader " + vertex_file_path);
    const char* vertex_source_pointer = vertex_shader_code.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_source_pointer, NULL);
    glCompileShader(vertex_shader_id);
    
    // Checks the vertex shader
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
      vector<char> vertex_shader_error_message(info_log_length+1);
      glGetShaderInfoLog(
          vertex_shader_id, 
          info_log_length, 
          NULL, 
          &vertex_shader_error_message[0]
      );
      alert(string(vertex_shader_error_message.begin(), vertex_shader_error_message.end()));
    }
  
    // Compiles the fragment shader
    log("compiling shader: " + fragment_file_path);
    const char* fragment_shader_pointer = fragment_shader_code.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_shader_pointer, NULL);
    glCompileShader(fragment_shader_id);
    
    // Checks the fragment shader
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
      vector<char> fragment_shader_error_message(info_log_length+1);
      glGetShaderInfoLog(
          fragment_shader_id,
          info_log_length,
          NULL,
          &fragment_shader_error_message[0]
      );
      alert(string(fragment_shader_error_message.begin(), fragment_shader_error_message.end()));
    }
    
    // Links the program
    log("linking program");
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    
    // Checks the program
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
      vector<char> program_error_message(info_log_length+1);
      glGetProgramInfoLog(
        program_id,
        info_log_length,
        NULL,
        &program_error_message[0]
      );
      alert(string(program_error_message.begin(), program_error_message.end()));
    }
    
    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);
    
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
    
    return program_id;
  }
}

#endif
