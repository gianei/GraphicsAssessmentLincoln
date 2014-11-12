#include "Triangle.h"


Triangle::Triangle(ShaderProgram* shaderProgram)
	:GameObject(shaderProgram)
{
	setIndexCount(3);
	setVertexCount(3);
	activateAttribute(3);
	activateAttribute(4);
	setAttribute(0, 0, vec3(0.0f, 0.577f, 0.0f));
	setAttribute(0, 1, vec3(-0.5f, -0.289f, 0.0f));
	setAttribute(0, 2, vec3(0.5f, -0.289f, 0.0f));
	setAttribute(1, 0, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	setAttribute(1, 1, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	setAttribute(1, 2, vec4(1.0f, 0.0f, 0.0f, 1.0f));
}


Triangle::~Triangle()
{
}
