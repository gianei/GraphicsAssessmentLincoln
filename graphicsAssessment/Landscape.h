#pragma once
#include "D:\GoogleDrive\Documents\Programming\GitHub\GraphicsAssessmentLincoln\framework\GameObject.h"
class Landscape :
	public GameObject
{
private:
	vec4 getRandomColor();
	vec3 getRandomPosition();
public:
	Landscape(ShaderProgram* shaderProgram);
	~Landscape();
};

