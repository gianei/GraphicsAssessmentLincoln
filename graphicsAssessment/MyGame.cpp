#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include "Game.h"
#include "ShaderProgram.h"
#include "GCamera.h"

GLuint vao;
ShaderProgram *shaderProgram;

class MyGame : public Game{
private:
	
public:
	void render();
	void initialize();
};

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


	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject); //bind positionBufferObject

	glEnableVertexAttribArray(0); //this 0 corresponds to the location = 0 in the GLSL for the vertex shader.
	glEnableVertexAttribArray(1);
	//more generically, use glGetAttribLocation() after GLSL linking to obtain the assigned attribute location.

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //define **how** values are reader from positionBufferObject in Attrib 0
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 4 * 3));

	camera.writeOnShader(*shaderProgram);
	shaderProgram->SetVariable(MODEL_SHADER_VARIABLE_NAME, glm::mat4());
	shaderProgram->Activate();

	glDrawArrays(GL_TRIANGLES, 0, 3); //Draw something, using Triangles, and 3 vertices - i.e. one lonely triangle

	glDisableVertexAttribArray(0); //cleanup
	glUseProgram(0); //clean up
}



void MyGame::initialize()
{
	//create GLSL Shaders, link into a GLSL program
	std::vector<GLuint> shaderList;

	shaderProgram = new ShaderProgram();
	shaderProgram->CreateShader("vertexShader.vsh", GL_VERTEX_SHADER);
	shaderProgram->CreateShader("fragmentShader.fsh", GL_FRAGMENT_SHADER);
	shaderProgram->Link();

	camera = GCamera();

	initializeVertexBuffer(); //load data into a vertex buffer

	glGenVertexArrays(1, &vao); //create a Vertex Array Object
	glBindVertexArray(vao); //make the VAO active

}

int main(int argc, char* args[])
{
	MyGame game = MyGame();

	game.startMainLoop();

	return 0;
}