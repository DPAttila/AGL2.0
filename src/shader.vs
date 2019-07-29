#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
// Coordinates on the texture (normalized in the [0,1] range)
layout(location = 1) in vec2 texcoord;

layout(location = 2) in vec3 normal;

// Uniform world matrix, remains the same throughout the draw call
uniform mat4 wvp;

out vec2 texcoord_fs;
out vec3 pos_in;
out vec3 normal_in;

void main() {
  gl_Position = wvp * vec4(position, 1.0);
  texcoord_fs = texcoord;
  pos_in = position;
  normal_in = normal;
}
