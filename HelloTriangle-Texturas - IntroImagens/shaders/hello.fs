#version 450

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D tex_buffer;

//Texture coords offsets for animation
uniform vec2 offset;

out vec4 color;

void main()
{
	color = texture(tex_buffer,texCoord+offset);
	//float media = (color.r + color.g + color.b)/3.0;
	//color.r = media;
	//color.g = media;
	//color.b = media;
}