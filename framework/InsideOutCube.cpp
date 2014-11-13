#include "InsideOutCube.h"


InsideOutCube::InsideOutCube(ShaderProgram* shaderProgram)
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
	setIndex(1, 2);
	setIndex(2, 1);
	setIndex(3, 2);
	setIndex(4, 0);
	setIndex(5, 3);

	setIndex(6, 1);
	setIndex(7, 2);
	setIndex(8, 5);
	setIndex(9, 2);
	setIndex(10, 6);
	setIndex(11, 5);

	setIndex(12, 6);
	setIndex(13, 4);
	setIndex(14, 5);
	setIndex(15, 7);
	setIndex(16, 4);
	setIndex(17, 6);

	setIndex(18, 3);
	setIndex(19, 4);
	setIndex(20, 7);
	setIndex(21, 0);
	setIndex(22, 4);
	setIndex(23, 3);

	setIndex(24, 6);
	setIndex(25, 3);
	setIndex(26, 7);
	setIndex(27, 2);
	setIndex(28, 3);
	setIndex(29, 6);

	setIndex(30, 0);
	setIndex(31, 1);
	setIndex(32, 5);
	setIndex(33, 5);
	setIndex(34, 4);
	setIndex(35, 0);

	setScale(10);
}


InsideOutCube::~InsideOutCube()
{
}
