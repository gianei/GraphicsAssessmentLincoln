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
#include "Piramid.h"

GLuint vao;
ShaderProgram *shaderProgram;
ShaderProgram *shaderProgramGurro;
ShaderProgram *shaderProgramGUI;

class MyGame : public Game{
private:
	GameObject* triangle;
	GameObject* triangle2;
	GameObject* cube;
	GameObject* landscape;
protected:
	void keyDown(SDL_KeyboardEvent* e);
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
	camera.writeOnShader(*shaderProgramGurro);

	shaderProgramGurro->SetVariable("modelSpaceLightPos", lightPosition);

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

	shaderProgramGurro = new ShaderProgram();
	shaderProgramGurro->CreateShader("vertexShaderG.vsh", GL_VERTEX_SHADER);
	shaderProgramGurro->CreateShader("fragmentShaderG.fsh", GL_FRAGMENT_SHADER);
	shaderProgramGurro->Link();

	shaderProgramGUI = new ShaderProgram();
	shaderProgramGUI->CreateShader("vertexShaderGUI.vsh", GL_VERTEX_SHADER);
	shaderProgramGUI->CreateShader("fragmentShader.fsh", GL_FRAGMENT_SHADER);
	shaderProgramGUI->Link();

	Triangle* triangleGUI = new Triangle(shaderProgramGUI);
	triangleGUI->setScale(0.20);
	triangleGUI->setPosition(vec3(-0.875f, -0.875f, 0.0f));
	triangleGUI->rotationZ = 0.05f;
	this->addGameObject(triangleGUI);

	Triangle* rightTriangle = new Triangle(shaderProgramGUI);
	rightTriangle->setAttribute(0, 0, vec3(0.3f, 1.0f, 0.0f));
	rightTriangle->setAttribute(1, 0, vec4(1.0f, 1.0f, 0.0f, 1.0f));
	rightTriangle->setAttribute(1, 1, vec4(0.5f, 0.0f, 0.0f, 1.0f));
	rightTriangle->setAttribute(1, 2, vec4(0.5f, 0.0f, 0.0f, 1.0f));
	rightTriangle->setScale(0.20);
	rightTriangle->setPosition(vec3(0.875f, -0.875f, 0.0f));
	this->addGameObject(rightTriangle);

	camera = GCamera();

	//initializeVertexBuffer(); //load data into a vertex buffer

	Piramid* piramid1 = new Piramid(shaderProgram);
	piramid1->setPosition(vec3(2, 0, 0));
	piramid1->setScale(0.25);
	piramid1->rotationX = 0.1f;
	this->addGameObject(piramid1);
	Piramid* piramid4 = new Piramid(shaderProgram);
	piramid4->setPosition(vec3(2.5f, 0.5f, 0));
	piramid4->setScale(0.25);
	piramid4->rotationY = 0.1f;
	this->addGameObject(piramid4);
	Piramid* piramid2 = new Piramid(shaderProgram);
	piramid2->setPosition(vec3(3, 1, 0));
	piramid2->setScale(0.5);
	piramid2->rotationZ = 0.1f;
	this->addGameObject(piramid2);
	Piramid* piramid3 = new Piramid(shaderProgram);
	piramid3->setPosition(vec3(4, 2, 0));
	piramid3->rotationX = 0.1f;
	piramid3->rotationY = 0.1f;
	piramid3->rotationZ = 0.1f;
	this->addGameObject(piramid3);


	triangle = new Triangle(shaderProgram);
	//triangle->setPosition(vec3(0.0f, 0.0f, 0.0f));	
	triangle->setAngle(vec3(45.0f, 0.0f, 0.0f));


	cube = new Cube(shaderProgram); //8 36
	cube->rotationX = 0.1f;
	cube->rotationY = 0.1f;
	cube->rotationZ = 0.1f;
	cube->setScale(0.2f);
	
	this->addGameObject(triangle);
	//this->addGameObject(triangle2);
	this->addGameObject(cube);

	Cube* cube2 = new Cube(shaderProgram); //8 36
	cube2->setPosition(vec3(0, 0, -1));
	cube2->setScale(0.4f);
	this->addGameObject(cube2);

	light = new Cube(shaderProgram); //8 36
	light->setPosition(vec3(-5,-5,-5) + lightPosition * 0.1f);
	light->setScale(0.25f);
	light->setAttribute(1, 0, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAttribute(1, 1, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAttribute(1, 2, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAttribute(1, 3, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAttribute(1, 4, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAttribute(1, 5, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAttribute(1, 6, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	light->setAttribute(1, 7, vec4(1.0f, 1.0f, 1.0f, 1.0f));
	this->addGameObject(light);

	this->addGameObject(new InsideOutCube(shaderProgram));

	landscape = new Landscape(shaderProgramGurro);

	this->addGameObject(landscape);

	//glGenVertexArrays(1, &vao); //create a Vertex Array Object
	//glBindVertexArray(vao); //make the VAO active

}

void MyGame::keyDown(SDL_KeyboardEvent* e)
{
	switch (e->keysym.sym)
	{
	case SDLK_a: /* ’A’ key */

		if (e->keysym.mod & KMOD_SHIFT) camera.lookLeft();
		/*{ // one of the shift keys was pressed
		//if (e->keysym.mod & KMOD_LSHIFT) printf("lshift\n");
		//if (e->keysym.mod & KMOD_RSHIFT) printf("rshift\n");
		}*/
		else camera.moveLeft();
		break;
	case SDLK_d:
		if (e->keysym.mod & KMOD_SHIFT) camera.lookRight();
		else camera.moveRight();
		break;
	case SDLK_w:
		if (e->keysym.mod & KMOD_SHIFT) camera.lookUp();
		else camera.moveForward();
		break;
	case SDLK_s:
		if (e->keysym.mod & KMOD_SHIFT) camera.lookDown();
		else camera.moveBackward();
		break;
	case SDLK_e:
		if (e->keysym.mod & KMOD_SHIFT) camera.lookUp();
		else camera.moveUp();
		break;
	case SDLK_q:
		if (e->keysym.mod & KMOD_SHIFT) camera.lookDown();
		else camera.moveDown();
		break;
	case SDLK_LSHIFT: break;
	case SDLK_F1: break;
	case SDLK_ESCAPE:
		listenMouse = !listenMouse;
		break;

	case SDLK_i:
		lightPosition += vec3(0.0f, 0.2f, 0.0f);
		light->setPosition(vec3(-5, -5, -5) + lightPosition * 0.1f);
		break;
	case SDLK_k:
		lightPosition += vec3(0.0f, -0.2f, 0.0f);
		light->setPosition(vec3(-5, -5, -5) + lightPosition * 0.1f);
		break;
	case SDLK_l:
		lightPosition += vec3(0.2f, 0.0f, 0.0f);
		light->setPosition(vec3(-5, -5, -5) + lightPosition * 0.1f);
		break;
	case SDLK_j:
		lightPosition += vec3(-0.2f, 0.0f, 0.0f);
		light->setPosition(vec3(-5, -5, -5) + lightPosition * 0.1f);
		break;
	case SDLK_u:
		lightPosition += vec3(0.0f, 0.0f, -0.2f);
		light->setPosition(vec3(-5, -5, -5) + lightPosition * 0.1f);
		break;
	case SDLK_o:
		lightPosition += vec3(0.0f, 0.0f, 0.2f);
		light->setPosition(vec3(-5, -5, -5) + lightPosition * 0.1f);
		break;
	case SDLK_t:
		//delete landscape;
		this->removeGameObject();
		delete landscape;
		landscape = new Landscape(shaderProgramGurro);
		this->addGameObject(landscape);
	}
}


int main(int argc, char* args[])
{
	MyGame game = MyGame();

	game.startMainLoop();

	return 0;
}