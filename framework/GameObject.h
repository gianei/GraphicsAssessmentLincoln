#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>

class GameObject
{
private:
	bool needRebuffer = false;
	int vertexNumbers;
	GLuint vertexBufferObject;
	GLuint indexBufferObject;
	GLuint vaoObject1;


	GLshort indexData[3];

	void rebuffer();

public:
	GameObject();
	~GameObject();

	void setVertexNumbers(int numbers);
	void setPositionVertex(int index, glm::vec4 position);
	void setColorVertex(int index, glm::vec4 position);
	void draw();
};

