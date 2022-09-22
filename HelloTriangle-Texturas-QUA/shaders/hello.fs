#version 450

out vec4 color;

in vec2 texCoords;

uniform sampler2D tex_buffer;

void main()
{
	color = texture(tex_buffer, texCoords);
}
