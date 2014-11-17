#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include "Game.h"
#include "ShaderProgram.h"
#include "GCamera.h"
#include "GameObject.h"
#include "Triangle.h"
#include "Cube.h"
#include "InsideOutCube.h"
#include "Landscape.h"

GLuint vao;
ShaderProgram *shaderProgram;

class MyGame : public Game{
private:
	GameObject* triangle;
	GameObject* triangle2;
	GameObject* cube;
	GameObject* landscape;
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.writeOnShader(*shaderProgram);

}



void MyGame::initialize()
{
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE); //what is it for?
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);


	//create GLSL Shaders, link into a GLSL program
	std::vector<GLuint> shaderList;

	shaderProgram = new ShaderProgram();
	shaderProgram->CreateShader("vertexShader.vsh", GL_VERTEX_SHADER);
	shaderProgram->CreateShader("fragmentShader.fsh", GL_FRAGMENT_SHADER);
	shaderProgram->Link();

	camera = GCamera();

	//initializeVertexBuffer(); //load data into a vertex buffer

	triangle = new Triangle(shaderProgram);
	//triangle->setPosition(vec3(0.0f, 0.0f, 0.0f));
	triangle->setAngle(vec3(45.0f, 0.0f, 0.0f));


	cube = new Cube(shaderProgram); //8 36
	cube->setScale(0.2f);
	
	this->addGameObject(triangle);
	//this->addGameObject(triangle2);
	this->addGameObject(cube);

	this->addGameObject(new InsideOutCube(shaderProgram));

	landscape = new Landscape(shaderProgram);

	this->addGameObject(landscape);

	//glGenVertexArrays(1, &vao); //create a Vertex Array Object
	//glBindVertexArray(vao); //make the VAO active

}


int main(int argc, char* args[])
{
	MyGame game = MyGame();

	game.startMainLoop();

	return 0;
}