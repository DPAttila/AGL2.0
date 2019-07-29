#version 330 core

in vec2 texcoord_fs;
in vec3 pos_in;
in vec3 normal_in;

// Ouput data
out vec4 color;

uniform sampler2D sampler;

void main() {
  color = texture2D(sampler, texcoord_fs.st);
  color.rgb *= (vec3(1.0, 1.0, 1.0) + normal_in)/2.0;
}
