#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

smooth out vec4 theColor;

void main()
{
	theColor = color;
	gl_Position = projection * view * model * vec4(position, 1.0f);
	// 
}
