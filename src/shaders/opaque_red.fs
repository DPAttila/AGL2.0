#version 330 core

in vec2 texcoord_fs;
in vec3 pos_in;
in vec3 normal_in;

in mat4 world_fs;

out vec4 color;

uniform sampler2D sampler;

struct DirectionalLight {
  vec3 color;
  vec3 direction;
  float intensity;
};

DirectionalLight light;

void main() {
  light.color = vec3(1.0, 1.0, 1.0);
  light.intensity = 0.4;
  light.direction = vec3(1.0, -5.0, 1.0);
  
  vec4 ambient_light = vec4(0.9, 0.1, 0.1, 1.0);
  
  float diffuse_factor = dot(normalize(normal_in), -light.direction);
  
  vec4 diffuse_color;
  
  if (diffuse_factor > 0) {
    diffuse_color = vec4(light.color * light.intensity * diffuse_factor, 1.0);
  } else {
    diffuse_color = vec4(0, 0, 0, 0);
  }
  
  
  color = vec4((texture2D(sampler, texcoord_fs.st) * (diffuse_color + ambient_light)).rgb, 0.7);
}
