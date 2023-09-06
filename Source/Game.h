#pragma once

#include <SDL.h>

class Game
{
public:
	//Initializes SDL and creates the window and renderer. Throws on error.
	Game();
	
	//Frees resources and shuts down SDL.
	~Game();

	//Starts the game loop.
	void run();

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	static const int windowWidth = 1024;
	static const int windowHeight = 768;

	Uint64 lastFrameTime = 0;
	Uint64 currentFrameTime = 0;
};
