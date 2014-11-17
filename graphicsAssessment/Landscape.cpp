#include "Landscape.h"
#include <random>

Landscape::Landscape(ShaderProgram* shaderProgram)
	:GameObject(shaderProgram)
{
	int squareNumbersAtSide = 200;
	//vertexCount = (side + 1)^2
	//index count = side * side * 6 //two triangels  per square



	std::random_device generator;
	std::uniform_real_distribution<double> distributionPosition(0.0f, 0.5f);
	setScale(0.05f);
	setPosition(vec3(-5, -5, -2));

	setVertexCount((squareNumbersAtSide + 1)*(squareNumbersAtSide + 1));
	setIndexCount(squareNumbersAtSide * squareNumbersAtSide * 6);
	activateAttribute(3);
	activateAttribute(4);

	//TODO fix this, rebuffer is overkill
	this->rebuffer();

	setAttribute(0, 0, vec3(0.0f, 0.0f, distributionPosition(generator)));
	setAttribute(0, 1, vec3(1.0f, 0.0f, distributionPosition(generator)));
	setAttribute(0, 2, vec3(1.0f, 1.0f, distributionPosition(generator)));
	setAttribute(0, 3, vec3(0.0f, 1.0f, distributionPosition(generator)));
	for (int i = 0; i <= squareNumbersAtSide; i++)
		for (int j = 0; j <= squareNumbersAtSide; j++){	
		float myRandom = distributionPosition(generator);
		setAttribute(0, i * (squareNumbersAtSide + 1) + j, vec3(i * 1.0f, j * 1.0f, 2 * myRandom));
		setAttribute(1, i * (squareNumbersAtSide + 1) + j, vec4(myRandom, myRandom, myRandom, 1.0f));
		}

	for (int i = 0; i < squareNumbersAtSide; i++)
		for (int j = 0; j < squareNumbersAtSide; j++){
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 0, i * (squareNumbersAtSide + 1) + j);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 1, (i + 1) * (squareNumbersAtSide + 1) + j);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 2, (i + 1) * (squareNumbersAtSide + 1) + j + 1);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 3, (i + 1) * (squareNumbersAtSide + 1) + j + 1);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 4, i * (squareNumbersAtSide + 1) + j + 1);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 5, i * (squareNumbersAtSide + 1) + j);
		}


}

vec4 Landscape::getRandomColor(){
	std::random_device generator;
	std::uniform_real_distribution<double> distributionColor(0.0f, 1.0f);
	vec4 color = vec4();
	color.r = color.g = color.b = distributionColor(generator);
	color.w = 1.0f;
	return color;
}
vec3 Landscape::getRandomPosition(){
	std::random_device generator;
	std::uniform_real_distribution<double> distributionPosition(0.0f, 0.5f);
	vec3 position = vec3();
	position.z = distributionPosition(generator);
	position.y = distributionPosition(generator);
	//position.w = 1.0f;
	return position;
}


Landscape::~Landscape()
{
}
