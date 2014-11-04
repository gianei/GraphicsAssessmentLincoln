#include "GCamera.h"


GCamera::GCamera()
{
}


GCamera::~GCamera()
{
}

mat4 GCamera::view(){
	return glm::lookAt(position, lookAt, up);
}

mat4 GCamera::projection(){
	return glm::perspective(fieldOfView, aspectRatio, near, far);
}

void GCamera::writeOnShader(ShaderProgram &shaderProgram){
	shaderProgram.SetVariable(VIEW_SHADER_VARIABLE_NAME, view());
	shaderProgram.SetVariable(PROJECTION_SHADER_VARIABLE_NAME, projection());
}

vec3 GCamera::direction(){
	return normalize(lookAt - position);
}

void GCamera::moveRight(){
	lookAt += vec3(0.1f, 0.0f, 0.0f);
	position += vec3(0.1f, 0.0f, 0.0f);	
}

void GCamera::moveLeft(){
	lookAt += vec3(-0.1f, 0.0f, 0.0f);
	position += vec3(-0.1f, 0.0f, 0.0f);
	
}

void GCamera::moveUp(){
	lookAt += vec3(0.0f, 0.0f, 0.1f);
	position += vec3(0.0f, 0.0f, 0.1f);
}
void GCamera::moveDown(){
	lookAt += vec3(0.0f, 0.0f, -0.1f);
	position += vec3(0.0f, 0.0f, -0.1f);
}

void GCamera::lookRight(){
	rotate(0.4f, 1, true, vec3(0, 0, 1));
}

void GCamera::lookLeft(){
	rotate(0.4f, 1, false, vec3(0, 0, 1));
}

void GCamera::lookUp(){
	rotate(0.4f, 1, false, vec3(1, 0, 0));
}
void GCamera::lookDown(){
	rotate(0.4f, 1, true, vec3(1, 0, 0));
}


void GCamera::rotate(float angularSpeed, float deltaTime, bool clockwise, vec3 axis){
	int myDirection = clockwise ? -1 : 1;
	lookAt = position + glm::rotate(direction(), angularSpeed * deltaTime * myDirection, axis);

}


