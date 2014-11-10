#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "ShaderProgram.h"
#include "GCamera.h"

using namespace glm;

class GameObject
{
private:
	bool needRebuffer = false;
	int vertexNumbers;
	int indexNumbers;
	GLuint vertexBufferObject;
	GLuint indexBufferObject;
	GLuint vaoObject1;

	ShaderProgram* shaderProgram;

	vector<float> vertexPositions;
	vector<GLshort> indexData;

	void rebuffer();

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	float mscale = 1.0f;
	float angleX = 0.0f;
	float angleY = 0.0f;
	float angleZ = 0.0f;
	mat4 rotationMatrix(){ return rotate(angleX, vec3(1, 0, 0)) * rotate(angleY, vec3(0, 1, 0)) * rotate(angleZ, vec3(0, 0, 1)); }

	vec3 velocity;
public:
	//GameObject();
	GameObject(ShaderProgram* shaderProgram, int vertexNumber, int indexNumber);
	~GameObject();

	void setVertexNumbers(int numbers);
	void setPositionVertex(int index, glm::vec4 position);
	void setIndexVertex(int index, GLshort data);
	void setColorVertex(int index, glm::vec4 position);
	void update();
	void draw();

	void setPosition(vec3 position);
	void setScale(float scale);
	void setAngle(vec3 angles);
	mat4 modelMatrix(void);
};

