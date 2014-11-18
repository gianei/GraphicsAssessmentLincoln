#include "Piramid.h"


Piramid::Piramid(ShaderProgram* shaderProgram)
	:GameObject(shaderProgram)
{
	setIndexCount(3);
	setVertexCount(4);
	activateAttribute(3);
	activateAttribute(4);
	setAttribute(0, 0, vec3(0.0f, 0.577f, 0.0f));
	setAttribute(0, 1, vec3(-0.5f, -0.289f, 0.0f));
	setAttribute(0, 2, vec3(0.5f, -0.289f, 0.0f));
	setAttribute(0, 3, vec3(0.0f, 0.144f, 1.0f));
	setAttribute(1, 0, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	setAttribute(1, 1, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	setAttribute(1, 2, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	setAttribute(1, 3, vec4(1.0f, 1.0f, 0.0f, 1.0f));

	setIndex(0, 0);
	setIndex(1, 2);
	setIndex(2, 1);

	/*setIndex(3, 0);
	setIndex(4, 1);
	setIndex(5, 3);

	setIndex(6, 1);
	setIndex(7, 2);
	setIndex(8, 3);*/

	/*setIndex(9, 2);
	setIndex(10, 0);
	setIndex(11, 3);*/
}


Piramid::~Piramid()
{
}
