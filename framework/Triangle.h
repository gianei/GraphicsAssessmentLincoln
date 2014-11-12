#pragma once
#include "GameObject.h"
class Triangle :
	public GameObject
{
public:
	Triangle(ShaderProgram* shaderProgram);
	~Triangle();
};

