#pragma once
#include "GameObject.h"
#include "Matrix.h"
class Landscape :
	public GameObject
{
private:
	Matrix image = Matrix(100, 100);
	int pointNumbers;
	vector<vec2> points;

	vec3 triangleNormal();
	vec4 getRandomColor();
	vec3 getRandomPosition();
	vec3 triangleNormal(int triangleIndex);

	double getClosestDistance(vec2 point);
	double getManhattanDistance(vec2 origin, vec2 dest);
	double getEuclidianDistance(vec2 origin, vec2 dest);
public:
	Landscape(ShaderProgram* shaderProgram);
	~Landscape();
};

