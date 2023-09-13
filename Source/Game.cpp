#include "Game.h"
#include "PlayerShip.h"
#include "Asteroid.h"
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
	const Vector2D screenCenter(windowWidth / 2, windowHeight / 2);
	PlayerShip playerShip(screenCenter);

	const Vector2D testAsteroidLocation(windowWidth / 4, windowHeight / 2);
	Asteroid testAsteroid(testAsteroidLocation, AsteroidRadius::Large);

	//Game loop
	bool isRunning = true;
	while (isRunning)
	{
		//Calculate delta time
		lastFrameTime = currentFrameTime;
		currentFrameTime = SDL_GetTicks64();
		float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;

		//Input Handling
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

			playerShip.handleInput(event);
		}

		//Game Logic
		playerShip.update(deltaTime);
		testAsteroid.update(deltaTime);

		//Rendering
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		playerShip.render(renderer);
		testAsteroid.render(renderer);

		SDL_RenderPresent(renderer);
	}
}
