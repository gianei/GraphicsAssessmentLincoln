#include "Landscape.h"
#include "Matrix.h"
#include <random>
#include <math.h>


double Landscape::getClosestDistance(vec2 point){
	float distance = 1000;
	for (int i = 0; i < pointNumbers; i++){
		float myDistance = getEuclidianDistance(point, points[i]);
		//float myDistance = getManhattanDistance(point, points[i]);
		if (myDistance < distance)
			distance = myDistance;
	}
	return distance;
}

double Landscape::getManhattanDistance(vec2 origin, vec2 dest){
	double x_difference = origin.x - dest.x;
	double y_difference = origin.y - dest.y;

	return abs(x_difference) + abs(y_difference);
}
double Landscape::getEuclidianDistance(vec2 origin, vec2 dest){
	double x_difference = origin.x - dest.x;
	double y_difference = origin.y - dest.y;

	return sqrt(x_difference * x_difference + y_difference * y_difference);
}

Landscape::Landscape(ShaderProgram* shaderProgram)
	:GameObject(shaderProgram)
{
	int squareNumbersAtSide = 99;
	//vertexCount = (side + 1)^2
	//index count = side * side * 6 //two triangels  per square
	//image = Matrix(100, 100);
	pointNumbers = 30;
	points = vector<vec2>(pointNumbers);

	//populte random points
	std::random_device generatorPints;
	std::uniform_int_distribution<int> distributionPoints(0, 99);
	for (int i = 0; i < pointNumbers; i++){
		points[i] = vec2(distributionPoints(generatorPints), distributionPoints(generatorPints));
	}

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++){
		image.set(getClosestDistance(vec2(i, j)), i, j);
		}






	vector<vec3> normals = vector<vec3>(squareNumbersAtSide * squareNumbersAtSide * 2);


	std::random_device generator;
	std::uniform_real_distribution<double> distributionPosition(0.0f, 0.5f);
	setScale(0.1f);
	setPosition(vec3(-5, -5, -5));

	setVertexCount((squareNumbersAtSide + 1)*(squareNumbersAtSide + 1));
	setIndexCount(squareNumbersAtSide * squareNumbersAtSide * 6);
	activateAttribute(3);
	activateAttribute(4);
	activateAttribute(3);

	//TODO fix this, rebuffer is overkill
	this->rebuffer();

	setAttribute(0, 0, vec3(0.0f, 0.0f, distributionPosition(generator)));
	setAttribute(0, 1, vec3(1.0f, 0.0f, distributionPosition(generator)));
	setAttribute(0, 2, vec3(1.0f, 1.0f, distributionPosition(generator)));
	setAttribute(0, 3, vec3(0.0f, 1.0f, distributionPosition(generator)));
	for (int i = 0; i <= squareNumbersAtSide; i++)
		for (int j = 0; j <= squareNumbersAtSide; j++){	
		float myRandom = distributionPosition(generator);
		//setAttribute(0, i * (squareNumbersAtSide + 1) + j, vec3(i * 1.0f, j * 1.0f, 4 * myRandom));
		//setAttribute(0, i * (squareNumbersAtSide + 1) + j, vec3(i * 1.0f, j * 1.0f, pow(j*0.05f + i * 0.01f, 2) + myRandom));
		setAttribute(0, i * (squareNumbersAtSide + 1) + j, vec3(i * 1.0f, j * 1.0f, image.get(i,j) * 0.5f));
		//setAttribute(1, i * (squareNumbersAtSide + 1) + j, vec4(0.5f + myRandom, 0.5f + myRandom* 0.1, 0.5f + myRandom* 0.1, 1.0f));
		//setAttribute(1, i * (squareNumbersAtSide + 1) + j, vec4(0.5f, 0.5f, 0.5f, 1.0f));
		//setAttribute(1, i * (squareNumbersAtSide + 1) + j, vec4(image.get(i, j) * 0.05f, image.get(i, j) * 0.1f, image.get(i, j) * 0.5f, 1.0f));
		setAttribute(1, i * (squareNumbersAtSide + 1) + j, vec4(0.5f + image.get(i, j) * 0.005f, 0.5 + image.get(i, j) * 0.005f, 0.5 + image.get(i, j) * 0.05f, 1.0f));
		}

	//setting indexs
	for (int i = 0; i < squareNumbersAtSide; i++)
		for (int j = 0; j < squareNumbersAtSide; j++){
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 0, i * (squareNumbersAtSide + 1) + j);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 1, (i + 1) * (squareNumbersAtSide + 1) + j);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 2, (i + 1) * (squareNumbersAtSide + 1) + j + 1);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 3, (i + 1) * (squareNumbersAtSide + 1) + j + 1);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 4, i * (squareNumbersAtSide + 1) + j + 1);
			setIndex((i * squareNumbersAtSide) * 6 + (j * 6) + 5, i * (squareNumbersAtSide + 1) + j);
		}


	for (int i = 0; i < squareNumbersAtSide * squareNumbersAtSide * 2; i++)
		normals[i] = triangleNormal(i);

	//set vertices normals
	for (int i = 0; i <= squareNumbersAtSide; i++)
		for (int j = 0; j <= squareNumbersAtSide; j++){
		//set a up normal for the borders
		if (i == 0 || i == squareNumbersAtSide || j == 0 || j == squareNumbersAtSide){
			setAttribute(2, i * (squareNumbersAtSide + 1) + j, vec3(0,0,1));
		}
		else {
			//TODO this can be wrong
			setAttribute(2, i * (squareNumbersAtSide + 1) + j,
				normalize(
				normals[((i - 1) * 2 * squareNumbersAtSide) + ((j - 1) * 2 + 0)] + 
				normals[((i - 1) * 2 * squareNumbersAtSide) + ((j - 1) * 2 + 1)] +
				normals[((i - 1) * 2 * squareNumbersAtSide) + ((j - 1) * 2 + 2)] +
				normals[(i * 2 * squareNumbersAtSide) + ((j - 1) * 2 + 0)] +
				normals[(i * 2 * squareNumbersAtSide) + ((j - 1) * 2 + 1)] +
				normals[(i * 2 * squareNumbersAtSide) + ((j - 1) * 2 + 2)]));
		}
		}


	return;

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


vec3 Landscape::triangleNormal(int triangleIndex){
	vec3* triangle = new vec3[3];

	getTriangleFromIndex(triangleIndex, triangle);
	/*triangle(v1, v2, v3)
	edge1 = v2 - v1
	edge2 = v3 - v1
	triangle.normal = cross(edge1, edge2).normalize()*/

	vec3 norm = normalize(cross(triangle[1] - triangle[0], triangle[2] - triangle[0]));
	return norm;

}

Landscape::~Landscape()
{
	
}
