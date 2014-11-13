#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//#include <glm/gtx/rotate_vector.hpp>
#include "ShaderProgram.h"

using namespace glm;

#define VIEW_SHADER_VARIABLE_NAME "view"
#define PROJECTION_SHADER_VARIABLE_NAME "projection"
#define MODEL_SHADER_VARIABLE_NAME "model"

class GCamera
{
public:
	GCamera();
	~GCamera();

	void writeOnShader(ShaderProgram &shaderProgram);

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void lookLeft();
	void lookRight();
	void lookUp();
	void lookXZ(int amountX, int amountZ);
	void lookDown();


private:
	vec3 position = vec3(0.0f, -1.0f, 0.0f);
	vec3 lookAt = vec3(0.0f, 0.0f, 0.0f);
	vec3 up = vec3(0.0f, 0.0f, 1.0f);

	float angleX = 0.0f;
	float angleY = 0.0f;
	float angleZ = 0.0f;
	mat4 rotationMatrix(){ return glm::rotate(angleX, vec3(1, 0, 0)) * glm::rotate(angleY, vec3(0, 1, 0)) * glm::rotate(angleZ, vec3(0, 0, 1)); }

	float fieldOfView = 55.0f;
	float aspectRatio = 1.0f;
	float near = 0.2f;
	float far = 20.0f;

	mat4 view();
	mat4 projection();
	vec3 direction();
	void rotate();
};

