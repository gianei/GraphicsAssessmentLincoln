#include "GameObject.h"





GameObject::GameObject(ShaderProgram* shaderProgram, int vertexNumber, int indexNumber)
{
	vertexNumbers = vertexNumber;
	vertexPositions.resize(vertexNumbers * 4 * 2);// = new float[vertexNumbers * 4 * 2];
	indexNumbers = indexNumber;
	indexData.resize(indexNumbers);// = new GLshort[indexNumbers];
	this->shaderProgram = shaderProgram;
	//start indexes>
	for (int i = 0; i < indexNumbers; i++)
		indexData[i] = i;

	

	rebuffer();
}




GameObject::~GameObject()
{
}

void GameObject::rebuffer(){
	
	//TODO use glBufferSubData


	/*vector<float> positions = {
		0.0f, 0.5f, 0.0f, 1.0f,
		-0.4330127f, -0.25f, 0.0f, 1.0f,
		0.4330127f, -0.25f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f };
	float pos[24] = {
		0.0f, 0.5f, 0.0f, 1.0f,
		-0.4330127f, -0.25f, 0.0f, 1.0f,
		0.4330127f, -0.25f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f };*/
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * (sizeof(float)), &indexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), &vertexPositions, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * (sizeof(float)), &vertexPositions[0], GL_STATIC_DRAW);
	//24 * (sizeof(float))
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

	shaderProgram->SetVariable(MODEL_SHADER_VARIABLE_NAME, modelMatrix());
	shaderProgram->Activate();

	glBindVertexArray(vaoObject1);
	//ARRAY_COUNT(indexData)
	glDrawElements(GL_TRIANGLES, indexNumbers, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void GameObject::setVertexNumbers(int numbers){ vertexNumbers = numbers; }

void GameObject::setPositionVertex(int index, glm::vec4 position){
	needRebuffer = true;
	vertexPositions[index * 4] = position.x;
	vertexPositions[index * 4 + 1] = position.y;
	vertexPositions[index * 4 + 2] = position.z;
	vertexPositions[index * 4 + 3] = position.w;

}
void GameObject::setColorVertex(int index, glm::vec4 position){
	needRebuffer = true;
	vertexPositions[4 * vertexNumbers + index * 4] = position.x;
	vertexPositions[4 * vertexNumbers + index * 4 + 1] = position.y;
	vertexPositions[4 * vertexNumbers + index * 4 + 2] = position.z;
	vertexPositions[4 * vertexNumbers + index * 4 + 3] = position.w;
}

void GameObject::setIndexVertex(int index, GLshort data){
	indexData[index] = data;
}

void GameObject::setPosition(vec3 position){ this->position = position; }
void GameObject::setScale(float scale){ this->mscale = scale; }
void GameObject::setAngle(vec3 angles){ angleX = angles.x; angleY = angles.y; angleZ = angles.z; }

mat4 GameObject::modelMatrix(void){
	return
		glm::translate(position) *
		glm::scale(vec3(mscale, mscale, mscale)) *
		rotationMatrix();
}
