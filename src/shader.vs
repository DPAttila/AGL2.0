#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;

// Uniform world matrix, remains the same throughout the draw call
uniform mat4 world;

void main() {
    gl_Position = world * vec4(position, 1.0);
}
