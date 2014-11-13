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
	vec3 vec = vec3(vec4(0.1f, 0.0f, 0.0f, 1.0f) * rotationMatrix());
	lookAt += vec;
	position += vec;
}

void GCamera::moveLeft(){
	vec3 vec = vec3(vec4(-0.1f, 0.0f, 0.0f, 1.0f) * rotationMatrix());
	lookAt += vec;
	position += vec;
	
}

void GCamera::moveUp(){
	vec3 vec = vec3(vec4(0.0f, 0.1f, 0.0f, 1.0f) * rotationMatrix());
	lookAt += vec;
	position += vec;
}

void GCamera::moveDown(){
	vec3 vec = vec3(vec4(0.0f, -0.1f, 0.0f, 1.0f) * rotationMatrix());
	lookAt += vec;
	position += vec;
}

void GCamera::lookRight(){
	angleZ += 1.0;
	rotate();
	
}

void GCamera::lookLeft(){
	angleZ -= 1.0;
	rotate();
	
}

void GCamera::lookUp(){
	angleX -= 1.0;
	rotate();
	
}
void GCamera::lookXZ(int amountX, int amountZ){
	angleX -= amountX * 0.1;
	angleZ += amountZ * 0.1;
	rotate();
}

void GCamera::lookDown(){
	angleX += 1.0;
	rotate();
	
}


void GCamera::rotate(){
	vec4 rotation = vec4(0.0f, 1.0f, 0.0f, 1.0f) * rotationMatrix();
	//vec4 rotation = vec4(direction(), 1.0f) * rotationMatrix();
	lookAt = position + vec3(rotation);


}




