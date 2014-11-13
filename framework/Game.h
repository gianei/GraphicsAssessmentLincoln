#include <GL/glew.h>
#include <SDL.h>
#include "GCamera.h"
#include "GameObject.h"

class Game {
protected:
	GCamera camera;
private:
	SDL_Window *win; //pointer to the SDL_Window
	SDL_GLContext context; //the SDL_GLContext

	bool listenMouse = true;

	vector<GameObject*>* gameObjects = new vector<GameObject*>;

	void initializeSDL();
	void createWindow();
	void setGLAttributes();
	void createContext();
	void initGlew();
	void cleanUp();

	void Game::keyDown(SDL_KeyboardEvent* e);

	

public:
	Game();
	void startMainLoop();

	void virtual render() = 0;
	void virtual initialize() = 0;

	void addGameObject(GameObject* gameObject);
	

};