#include "GameObject.h"


float vertexPositions[] = {
	0.0f, 0.5f, 0.0f, 1.0f,
	-0.4330127f, -0.25f, 0.0f, 1.0f,
	0.4330127f, -0.25f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f
};
GameObject::GameObject()
{
	//start indexes>
	for (int i = 0; i < 1 * 3; i++)
		indexData[i] = i;

	glGenBuffers(1, &indexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	rebuffer();
}


GameObject::~GameObject()
{
}

void GameObject::rebuffer(){
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	

	glGenVertexArrays(1, &vaoObject1);
	glBindVertexArray(vaoObject1);

	int numberOfVertices = 1 * 3;

	size_t colorDataOffset = sizeof(float) * 4 * numberOfVertices;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);

	needRebuffer = false;
}

void GameObject::draw(){
	if (needRebuffer)
		rebuffer();
	glBindVertexArray(vaoObject1);
	//ARRAY_COUNT(indexData)
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void GameObject::setVertexNumbers(int numbers){ vertexNumbers = numbers; }

void GameObject::setPositionVertex(int index, glm::vec4 position){
	needRebuffer = true;
	vertexPositions[index] = position.x;
	vertexPositions[index + 1] = position.y;
	vertexPositions[index + 2] = position.z;
	vertexPositions[index + 3] = position.w;

}
void GameObject::setColorVertex(int index, glm::vec4 position){
	needRebuffer = true;
	vertexPositions[4 * vertexNumbers + index] = position.x;
	vertexPositions[4 * vertexNumbers + index + 1] = position.y;
	vertexPositions[4 * vertexNumbers + index + 2] = position.z;
	vertexPositions[4 * vertexNumbers + index + 3] = position.w;
}
