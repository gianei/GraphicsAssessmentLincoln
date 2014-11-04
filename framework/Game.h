#include <GL/glew.h>
#include <SDL.h>

class Game {
private:
	SDL_Window *win; //pointer to the SDL_Window
	SDL_GLContext context; //the SDL_GLContext

	void initializeSDL();
	void createWindow();
	void setGLAttributes();
	void createContext();
	void initGlew();
	void cleanUp();

	

public:
	Game();
	void startMainLoop();

	void virtual render() = 0;
	void virtual initialize() = 0;
	

};