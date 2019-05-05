#version 330 core

in vec2 texcoord_fs;
in vec3 pos_in;

// Ouput data
out vec4 color;

uniform sampler2D sampler;

void main() {
	color = texture2D(sampler, texcoord_fs.st) + vec4(pos_in.x, pos_in.y, 0.0, 1.0);
	color.a = abs(pos_in.z - pos_in.x);
}
