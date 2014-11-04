#version 330
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

smooth out vec4 theColor;

void main()
{
	theColor = color;
	gl_Position = projection * view * model * position;
	// 
}
