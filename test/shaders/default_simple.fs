#version 330 core

in vec2 texcoord_fs;
in vec3 pos_in;
in vec3 normal_in;

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
    light.intensity = 0.5;
    light.direction = vec3(1.0, -5.0, 0.2);
    
    float diffuse_factor = dot(normalize(normal_in), -light.direction);
    
    vec4 diffuse_color;
    
    if (diffuse_factor > 0)
        diffuse_color = vec4(light.color * light.intensity * diffuse_factor, 1.0);
    else 
        diffuse_color = vec4(0.5, 0.5, 0.5, 1.0);
    
    color = texture2D(sampler, texcoord_fs.st) * diffuse_color;
}
