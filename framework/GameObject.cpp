#include "GameObject.h"


GameObject::GameObject(ShaderProgram* shaderProgram)
{
	this->shaderProgram = shaderProgram;
}

GameObject::~GameObject()
{
}

void GameObject::rebuffer(){
	//TODO use glBufferSubData

	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * (sizeof(float)), &indexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * (sizeof(float)), &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vaoObject1);
	glBindVertexArray(vaoObject1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	for (int i = 0; i < attributesData.size(); i++)
	{
		int skip = getAttributeSkip(i);
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attributesData[i], GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * getAttributeSkip(i)));
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);

	needRebuffer = false;
}

void GameObject::update(){
	position += velocity;

	angleZ += rotationZ;
	if (angleZ > 360)
		angleZ -= 360.0f;
	
}

void GameObject::draw(){
	shaderProgram->Activate();
	if (needRebuffer)
		rebuffer();

	shaderProgram->SetVariable(MODEL_SHADER_VARIABLE_NAME, modelMatrix());
	shaderProgram->Activate();

	glBindVertexArray(vaoObject1);
	//ARRAY_COUNT(indexData)
	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void GameObject::setVertexCount(int count){
	if (isVertexCountSet)
		throw std::runtime_error("vertexCount cannot be set twice");
	vertexCount = count;
	isVertexCountSet = true;
}

int GameObject::getAttributeSkip(int attributeType){
	needRebuffer = true;
	if (attributesData.size() - 1 < attributeType)
		throw std::runtime_error("AttributeIndex not activated");

	int skip = 0;
	for (int i = 0; i < attributeType; i++){
		skip += attributesData[i] * vertexCount;
	}

	return skip;
}

void GameObject::setAttribute(int attributeType, int index, vec3 data){
	if (index >= vertexCount)
		throw std::out_of_range("vertexCount not set");
	if (attributeType >= attributesData.size())
		throw std::out_of_range("attribute not set");
	int skip = getAttributeSkip(attributeType);
	vertexData[skip + index * 3] = data.x;
	vertexData[skip + index * 3 + 1] = data.y;
	vertexData[skip + index * 3 + 2] = data.z;
}

void GameObject::setAttribute(int attributeType, int index, vec4 data){
	if (index >= vertexCount)
		throw std::out_of_range("vertexCount not set");
	if (attributeType >= attributesData.size())
		throw std::out_of_range("attribute not set");
	int skip = getAttributeSkip(attributeType);
	vertexData[skip + index * 4] = data.x;
	vertexData[skip + index * 4 + 1] = data.y;
	vertexData[skip + index * 4 + 2] = data.z;
	vertexData[skip + index * 4 + 3] = data.w;
}

void GameObject::activateAttribute(int width){
	if (NULL == vertexCount){
		throw std::runtime_error("VertexCount not set");
	}
	attributesData.push_back(width);
	int oldSize = vertexData.size();
	vertexData.resize(oldSize + width * vertexCount);
}

void GameObject::setIndexCount(int count){
	indexCount = count;
	indexData.resize(count);
	for (int i = 0; i < count; i++)
		indexData[i] = i;
}

void GameObject::setIndex(int position, GLshort index){
	if (index >= vertexCount)
		throw std::out_of_range("index not existent in vertexs");
	indexData[position] = index;
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



vec3 GameObject::vertexNormal(int triangleIndex1, int triangleIndex2, int triangleIndex3){
	/*vertex v1, v2, v3, ....
		triangle tr1, tr2, tr3 // all share vertex v1
		v1.normal = normalize(tr1.normal + tr2.normal + tr3.normal)*/
	return vec3();
}
void GameObject::getTriangleFromIndex(int triangleIndex, vec3* out){
	if (triangleIndex * 3 >= indexCount)
		throw std::out_of_range("triangle index out of range");
	out[0] = vec3(
		vertexData[indexData[triangleIndex * 3 + 0] * attributesData[0] + 0],
		vertexData[indexData[triangleIndex * 3 + 0] * attributesData[0] + 1],
		vertexData[indexData[triangleIndex * 3 + 0] * attributesData[0] + 2]);
	out[1] = vec3(
		vertexData[indexData[triangleIndex * 3 + 1] * attributesData[0] + 0],
		vertexData[indexData[triangleIndex * 3 + 1] * attributesData[0] + 1],
		vertexData[indexData[triangleIndex * 3 + 1] * attributesData[0] + 2]);
	out[2] = vec3(
		vertexData[indexData[triangleIndex * 3 + 2] * attributesData[0] + 0],
		vertexData[indexData[triangleIndex * 3 + 2] * attributesData[0] + 1],
		vertexData[indexData[triangleIndex * 3 + 2] * attributesData[0] + 2]);

}

