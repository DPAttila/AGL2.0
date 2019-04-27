#version 330 core

in vec2 texcoord_fs;

// Ouput data
out vec4 color;

uniform sampler2D sampler;

void main()
{
	color = texture2D(sampler, texcoord_fs.st);
};
