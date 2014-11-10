#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include "Game.h"
#include "ShaderProgram.h"
#include "GCamera.h"
#include "GameObject.h"

GLuint vao;
ShaderProgram *shaderProgram;

class MyGame : public Game{
private:
	GameObject* triangle;
	GameObject* triangle2;
	GameObject* cube;
public:
	void render();
	void initialize();
	//MyGame();
};


vec3 position(0.1f, 0.0f, 0.0f);
float mscale = 1.0f;
float angleX = 45.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

mat4 rotationMatrix(){ return glm::rotate(angleX, vec3(1, 0, 0)) * glm::rotate(angleY, vec3(0, 1, 0)) * glm::rotate(angleZ, vec3(0, 0, 1)); }


mat4 ModelMatrix(void){
	return
		glm::translate(position) *
		glm::scale(vec3(mscale, mscale, mscale)) *
		rotationMatrix();
}

//using namespace std;

GLuint positionBufferObject;
GLuint theProgram; //GLuint that we'll fill in to refer to the GLSL program (only have 1 at this point)

const float vertexPositions[] = {
	0.0f, 0.5f, 0.0f, 1.0f,
	-0.4330127f, -0.25f, 0.0f, 1.0f,
	0.4330127f, -0.25f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f
};



void initializeVertexBuffer()
{
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	std::cout << "positionBufferObject created OK! GLUint is: " << positionBufferObject << std::endl;
}


void MyGame::render(){
	glClear(GL_COLOR_BUFFER_BIT);

	camera.writeOnShader(*shaderProgram);

}



void MyGame::initialize()
{
	glEnable(GL_CULL_FACE);
	//create GLSL Shaders, link into a GLSL program
	std::vector<GLuint> shaderList;

	shaderProgram = new ShaderProgram();
	shaderProgram->CreateShader("vertexShader.vsh", GL_VERTEX_SHADER);
	shaderProgram->CreateShader("fragmentShader.fsh", GL_FRAGMENT_SHADER);
	shaderProgram->Link();

	camera = GCamera();

	//initializeVertexBuffer(); //load data into a vertex buffer

	triangle = new GameObject(shaderProgram, 3, 3);
	triangle->setPositionVertex(0, vec4(0.0f, 0.5f, 0.0f, 1.0f));
	triangle->setPositionVertex(1, vec4(-0.4330127f, -0.25f, 0.0f, 1.0f));
	triangle->setPositionVertex(2, vec4(0.4330127f, -0.25f, 0.0f, 1.0f));
	triangle->setColorVertex(0, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	triangle->setColorVertex(1, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	triangle->setColorVertex(2, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//TODO remove this
	triangle->setPosition(vec3(0.0f, 0.0f, 0.1f));

	triangle2 = new GameObject(shaderProgram, 3, 3);
	triangle2->setPositionVertex(0, vec4(0.0f, 0.5f, 0.0f, 1.0f));
	triangle2->setPositionVertex(1, vec4(-0.4330127f, -0.25f, 0.0f, 1.0f));
	triangle2->setPositionVertex(2, vec4(0.4330127f, -0.25f, 0.0f, 1.0f));
	triangle2->setVertexNumbers(3);
	triangle2->setPositionVertex(0, vec4(0.5f, 0.5f, 0.0f, 1.0f));
	triangle2->setColorVertex(0, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	triangle2->setColorVertex(1, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	triangle2->setColorVertex(2, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	triangle2->setAngle(vec3(45.0f, 0.0f, 0.0f));
	//triangle2->setPosition(vec3(0.0f, 0.0f, 0.1f));


	cube = new GameObject(shaderProgram, 8, 36); //8 36
	//cube->setVertexNumbers(8);
	cube->setPositionVertex(0, vec4(-0.5f, -0.5f, -0.5f, 1.0f));
	cube->setPositionVertex(1, vec4(0.5f, -0.5f, -0.5f, 1.0f));
	cube->setPositionVertex(2, vec4(0.5f, -0.5f, 0.5f, 1.0f));
	cube->setPositionVertex(3, vec4(-0.5f, -0.5f, 0.5f, 1.0f));
	cube->setPositionVertex(4, vec4(-0.5f, 0.5f, -0.5f, 1.0f));
	cube->setPositionVertex(5, vec4(0.5f, 0.5f, -0.5f, 1.0f));
	cube->setPositionVertex(6, vec4(0.5f, 0.5f, 0.5f, 1.0f));
	cube->setPositionVertex(7, vec4(-0.5f, 0.5f, 0.5f, 1.0f));
	cube->setColorVertex(0, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	cube->setColorVertex(1, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	cube->setColorVertex(2, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	cube->setColorVertex(3, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	cube->setColorVertex(4, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	cube->setColorVertex(5, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	cube->setColorVertex(5, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	cube->setColorVertex(7, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	cube->setScale(0.2f);


	cube->setIndexVertex(0, 0);
	cube->setIndexVertex(1, 1);
	cube->setIndexVertex(2, 2);
	cube->setIndexVertex(3, 2);
	cube->setIndexVertex(4, 3);
	cube->setIndexVertex(5, 0);

	cube->setIndexVertex(6, 1);
	cube->setIndexVertex(7, 5);
	cube->setIndexVertex(8, 2);
	cube->setIndexVertex(9, 2);
	cube->setIndexVertex(10, 5);
	cube->setIndexVertex(11, 6);

	cube->setIndexVertex(12, 6);
	cube->setIndexVertex(13, 5);
	cube->setIndexVertex(14, 4);
	cube->setIndexVertex(15, 7);
	cube->setIndexVertex(16, 6);
	cube->setIndexVertex(17, 4);

	cube->setIndexVertex(18, 3);
	cube->setIndexVertex(19, 7);
	cube->setIndexVertex(20, 4);
	cube->setIndexVertex(21, 0);
	cube->setIndexVertex(22, 3);
	cube->setIndexVertex(23, 4);

	cube->setIndexVertex(24, 6);
	cube->setIndexVertex(25, 7);
	cube->setIndexVertex(26, 3);
	cube->setIndexVertex(27, 2);
	cube->setIndexVertex(28, 6);
	cube->setIndexVertex(29, 3);

	cube->setIndexVertex(30, 0);
	cube->setIndexVertex(31, 5);
	cube->setIndexVertex(32, 1);
	cube->setIndexVertex(33, 5);
	cube->setIndexVertex(34, 0);
	cube->setIndexVertex(35, 4);

	cube->setScale(0.2f);
	
	this->addGameObject(triangle);
	this->addGameObject(triangle2);
	this->addGameObject(cube);

	glGenVertexArrays(1, &vao); //create a Vertex Array Object
	glBindVertexArray(vao); //make the VAO active

}


int main(int argc, char* args[])
{
	MyGame game = MyGame();

	game.startMainLoop();

	return 0;
}