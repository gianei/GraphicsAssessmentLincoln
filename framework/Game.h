#include <GL/glew.h>
#include <SDL.h>
#include "GCamera.h"
#include "GameObject.h"
#include "Cube.h"

class Game {
protected:
	GCamera camera;
	vec3 lightPosition = vec3(5.0f, 5.0f, 20.0f); //TODO not in the correct place
	Cube* light;//TODO wrong place;
	bool listenMouse = true;
private:
	SDL_Window *win; //pointer to the SDL_Window
	SDL_GLContext context; //the SDL_GLContext

	

	vector<GameObject*>* gameObjects = new vector<GameObject*>;

	void initializeSDL();
	void createWindow();
	void setGLAttributes();
	void createContext();
	void initGlew();
	void cleanUp();

	virtual void Game::keyDown(SDL_KeyboardEvent* e) = 0;

	

public:
	Game();
	void startMainLoop();

	void virtual render() = 0;
	void virtual initialize() = 0;

	void addGameObject(GameObject* gameObject);
	void removeGameObject();
	

};