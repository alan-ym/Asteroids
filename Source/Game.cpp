#include "Game.h"
#include "PlayerShip.h"
#include "Asteroid.h"
#include "Projectile.h"
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
	//Deallocate all game objects
	for (GameObject* gameObject : gameObjects)
	{
		delete gameObject;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	resetGame();

	//Game loop
	while (isRunning)
	{
		//Calculate delta time
		lastFrameTime = currentFrameTime;
		currentFrameTime = SDL_GetTicks64();
		float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;

		handleInput();
		update(deltaTime);
		render();

		if (shouldResetGame)
		{
			resetGame();
		}
	}
}

void Game::spawnProjectile(const Vector2D& location, const Vector2D& velocity)
{
	pendingObjects.push_back(new Projectile(location, velocity));
}

void Game::resetGame()
{
	//Deallocate and remove any existing game objects
	if (!gameObjects.empty())
	{
		for (GameObject* gameObject : gameObjects)
		{
			delete gameObject;
		}
		gameObjects.clear();
	}

	//Create player ship
	const Vector2D screenCenter(windowWidth / 2, windowHeight / 2);
	playerShip = new PlayerShip(screenCenter, this);
	gameObjects.push_back(playerShip);

	//Create test asteroids
	const Vector2D testAsteroidOneLocation(windowWidth / 4, windowHeight / 2);
	gameObjects.push_back(new Asteroid(testAsteroidOneLocation, AsteroidRadius::Large));
	const Vector2D testAsteroidTwoLocation((windowWidth / 4) * 3, windowHeight / 2);
	gameObjects.push_back(new Asteroid(testAsteroidTwoLocation, AsteroidRadius::Large));

	shouldResetGame = false;
}

void Game::handleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		playerShip->handleInput(event);

		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}
}

void Game::update(const float& deltaTime)
{
	//Update all game objects
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->update(deltaTime);
	}

	//Handle collisions
	for (GameObject* gameObject : gameObjects)
	{
		if (Asteroid* asteroid = dynamic_cast<Asteroid*>(gameObject))
		{
			for (GameObject* other : gameObjects)
			{
				//Check for collisions between asteroids and the player ship
				if (other == playerShip)
				{
					if (asteroid->checkForCircleCollision(playerShip))
					{
						shouldResetGame = true;
						break;
					}
				}

				//Check for collisions between asteroids and projectiles
				if (Projectile* projectile = dynamic_cast<Projectile*>(other))
				{
					if (asteroid->checkForCircleCollision(projectile))
					{
						asteroid->setIsAlive(false);
						projectile->setIsAlive(false);

						//Spawn new asteroids
						switch (asteroid->getRadius())
						{
						case AsteroidRadius::Large:
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Medium));
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Medium));
							break;
						case AsteroidRadius::Medium:
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Small));
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Small));
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Small));
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Small));
							break;
						}

						break;
					}
				}
			}
		}
	}

	//Deallocate and remove all dead game objects
	std::vector<GameObject*>::iterator it = gameObjects.begin();
	while(it != gameObjects.end())
	{
		GameObject* gameObject = *it;
		if (!gameObject->getIsAlive())
		{
			delete gameObject;
			it = gameObjects.erase(it);
		}
		else
		{
			it++;
		}
	}

	//Add newly spawned game objects
	gameObjects.insert(gameObjects.end(), pendingObjects.begin(), pendingObjects.end());
	pendingObjects.clear();
}

void Game::render() const
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	//Render all game objects
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->render(renderer);
	}

	SDL_RenderPresent(renderer);
}
