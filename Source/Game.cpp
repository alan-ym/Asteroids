#include "Game.h"
#include <SDL.h>
#include <string>
#include <stdexcept>

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		const std::string error = SDL_GetError();
		throw std::runtime_error("SDL could not initialize. SDL error: " + error);
	}

	window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (!window)
	{
		const std::string error = SDL_GetError();
		SDL_Quit();
		throw std::runtime_error("Window could not be created. SDL error: " + error);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		const std::string error = SDL_GetError();
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw std::runtime_error("Renderer could not be created. SDL error: " + error);
	}
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	//Game loop
	bool isRunning = true;
	while (isRunning)
	{
		//Input Handling
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}

		//Rendering
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
}
