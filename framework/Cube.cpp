#include "Cube.h"


Cube::Cube(ShaderProgram* shaderProgram)
	:GameObject(shaderProgram)
{
	setVertexCount(8);
	setIndexCount(36);
    activateAttribute(3);
	activateAttribute(4);
	setAttribute(0, 0, vec3(-0.5f, -0.5f, -0.5f));
	setAttribute(0, 1, vec3(0.5f, -0.5f, -0.5f));
	setAttribute(0, 2, vec3(0.5f, -0.5f, 0.5f));
	setAttribute(0, 3, vec3(-0.5f, -0.5f, 0.5f));
	setAttribute(0, 4, vec3(-0.5f, 0.5f, -0.5f));
	setAttribute(0, 5, vec3(0.5f, 0.5f, -0.5f));
	setAttribute(0, 6, vec3(0.5f, 0.5f, 0.5f));
	setAttribute(0, 7, vec3(-0.5f, 0.5f, 0.5f));
	setAttribute(1, 0, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	setAttribute(1, 1, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	setAttribute(1, 2, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	setAttribute(1, 3, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	setAttribute(1, 4, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	setAttribute(1, 5, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	setAttribute(1, 5, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	setAttribute(1, 7, vec4(1.0f, 0.0f, 0.0f, 1.0f));

	setIndex(0, 0);
	setIndex(1, 1);
	setIndex(2, 2);
	setIndex(3, 2);
	setIndex(4, 3);
	setIndex(5, 0);

	setIndex(6, 1);
	setIndex(7, 5);
	setIndex(8, 2);
	setIndex(9, 2);
	setIndex(10, 5);
	setIndex(11, 6);

	setIndex(12, 6);
	setIndex(13, 5);
	setIndex(14, 4);
	setIndex(15, 7);
	setIndex(16, 6);
	setIndex(17, 4);

	setIndex(18, 3);
	setIndex(19, 7);
	setIndex(20, 4);
	setIndex(21, 0);
	setIndex(22, 3);
	setIndex(23, 4);

	setIndex(24, 6);
	setIndex(25, 7);
	setIndex(26, 3);
	setIndex(27, 2);
	setIndex(28, 6);
	setIndex(29, 3);

	setIndex(30, 0);
	setIndex(31, 5);
	setIndex(32, 1);
	setIndex(33, 5);
	setIndex(34, 0);
	setIndex(35, 4);
}


Cube::~Cube()
{
}
