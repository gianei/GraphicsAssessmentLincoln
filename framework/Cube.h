#pragma once
#include "GameObject.h"
class Cube :
	public GameObject
{
public:
	Cube(ShaderProgram* shaderProgram);
	~Cube();
};

