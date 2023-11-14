#include "Game.h"
#include "PlayerShip.h"
#include "Asteroid.h"
#include "Projectile.h"
#include <string>
#include <stdexcept>
#include <cmath>

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

	//Spawn asteroids
	spawnAsteroid();
	spawnAsteroid();
	spawnAsteroid();
	spawnAsteroid();

	shouldResetGame = false;
}

void Game::spawnAsteroid()
{
	//Get random distance from player, within safe range
	//(Using default-seeded rand() for simple rng, could be improved later)
	const int minDistance = static_cast<float>(AsteroidRadius::Large) * 6;
	const int maxDistance = windowWidth * 0.5f;
	const int distanceRange = maxDistance - minDistance;
	const int distance = ((rand() / static_cast<float>(RAND_MAX)) * distanceRange) + minDistance;

	//Get random angle from player, avoiding spawning directly ahead
	const float minAngle = playerShip->getRotation() + 45.0f;
	const float maxAngle = playerShip->getRotation() + 315.0f;
	const float angleRange = maxAngle - minAngle;
	const float angle = ((rand() / static_cast<float>(RAND_MAX)) * angleRange) + minAngle;
	const float angleRadians = angle * 0.01745329251f;

	//Create asteroid
	const Vector2D playerToAsteroidVector = Vector2D(std::sin(angleRadians), -std::cos(angleRadians)) * distance;
	const Vector2D asteroidLocation = playerShip->getLocation() + playerToAsteroidVector;
	gameObjects.push_back(new Asteroid(asteroidLocation, AsteroidRadius::Large));
	asteroidCount++;
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
						asteroidCount--;

						//Spawn new asteroids
						switch (asteroid->getRadius())
						{
						case AsteroidRadius::Large:
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Medium));
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Medium));
							asteroidCount += 2;
							break;
						case AsteroidRadius::Medium:
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Small));
							pendingObjects.push_back(new Asteroid(asteroid->getLocation(), AsteroidRadius::Small));
							asteroidCount += 2;
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

	//Spawn a new wave of asteroids when all asteroids have been destroyed
	if (asteroidCount < 1)
	{
		currentWave++;
		const int asteroidsToSpawn = (currentWave * 2) + 2;
		for (int i = 0; i < asteroidsToSpawn; i++)
		{
			spawnAsteroid();
		}
	}
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
