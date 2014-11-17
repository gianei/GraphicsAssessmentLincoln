#pragma once
#include "D:\GoogleDrive\Documents\Programming\GitHub\GraphicsAssessmentLincoln\framework\GameObject.h"
class Landscape :
	public GameObject
{
private:
	vec3 triangleNormal();
	vec4 getRandomColor();
	vec3 getRandomPosition();
	vec3 triangleNormal(int triangleIndex);
public:
	Landscape(ShaderProgram* shaderProgram);
	~Landscape();
};

