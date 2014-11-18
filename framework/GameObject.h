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
	bool isVertexCountSet = false;
	
	GLuint vertexBufferObject;
	GLuint indexBufferObject;
	GLuint vaoObject1;

	ShaderProgram* shaderProgram;

	vector<float> vertexData;
	int vertexCount = NULL;
	vector<GLshort> indexData;
	int indexCount = NULL;

	vector<int> attributesData;

	

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	mat4 rotationMatrix(){ return rotate(angleX, vec3(1, 0, 0)) * rotate(angleY, vec3(0, 1, 0)) * rotate(angleZ, vec3(0, 0, 1)); }

	vec3 velocity;

	int getAttributeSkip(int attributeIndex);




	vec3 vertexNormal(int triangleIndex1, int triangleIndex2, int triangleIndex3);
protected:
	float mscale = 1.0f;
	float angleX = 0.0f;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	void rebuffer();
	void getTriangleFromIndex(int triangleIndex, vec3* out);
public:
	//GameObject();
	GameObject(ShaderProgram* shaderProgram);
	~GameObject();

	void update();
	void draw();

	void setPosition(vec3 position);
	void setScale(float scale);
	void setAngle(vec3 angles);
	mat4 modelMatrix(void);

	void setIndex(int position, GLshort index);
	void setIndexCount(int count);

	void setVertexCount(int count);
	void activateAttribute(int width);
	void setAttribute(int attributeType, int index, vec3 data);
	void setAttribute(int attributeType, int index, vec4 data);


	double rotationX = 0.0f;
	double rotationY = 0.0f;
	double rotationZ = 0.0f;
	
};

