#include <iostream>
#include <vector>
#include <algorithm>


#include "Game.h"

void Game::initializeSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	std::cout << "SDL initialised OK!\n";
}

void Game::createWindow()
{
	win = SDL_CreateWindow("Hello World!", 100, 100, 600, 600, SDL_WINDOW_OPENGL); //same height and width makes the window square ...
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	std::cout << "SDL CreatedWindow OK!\n";
}

void Game::setGLAttributes()
{
	// set the opengl context version
	int major = 3;
	int minor = 3;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //core profile
	std::cout << "Set OpenGL context to version " << major << "." << minor << " OK!\n";
}

void Game::createContext()
{
	context = SDL_GL_CreateContext(win);
	if (context == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		//exit(1);
	}
	std::cout << "Created OpenGL context OK!\n";
}

void Game::initGlew()
{
	GLenum rev;
	glewExperimental = GL_TRUE; //GLEW isn't perfect - see https://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
	rev = glewInit();
	if (GLEW_OK != rev){
		std::cout << "GLEW Error: " << glewGetErrorString(rev) << std::endl;
		SDL_Quit();
		exit(1);
	}
	else {
		std::cout << "GLEW Init OK!\n";
	}
}


void Game::cleanUp()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	std::cout << "Cleaning up OK!\n";
}

void Game::startMainLoop(){
	initialize();

	while (true){

		//GET INPUT HERE - PLACEHOLDER

		//UPDATE SIMULATION - PLACEHOLDER

		render(); //RENDER HERE - PLACEHOLDER

		SDL_GL_SwapWindow(win);; //present the frame buffer to the display (swapBuffers)

	}

	cleanUp();
	SDL_Quit();
}

Game::Game(){
	initializeSDL();
	createWindow();
	setGLAttributes();
	createContext();
	initGlew();

	
}




