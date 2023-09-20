#pragma once

#include "Vector2D.h"
#include <vector>
#include <SDL.h>

class GameObject;
class PlayerShip;

class Game
{
public:
	//Initializes SDL and creates the window and renderer. Throws on error.
	Game();
	
	//Frees resources and shuts down SDL.
	~Game();

	//Starts the game loop.
	void run();

	void spawnProjectile(const Vector2D& location, const Vector2D& velocity);

	static const int windowWidth = 1024;
	static const int windowHeight = 768;

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool isRunning = true;
	
	Uint64 lastFrameTime = 0;
	Uint64 currentFrameTime = 0;

	PlayerShip* playerShip = nullptr;

	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> pendingObjects;

	bool shouldResetGame = false;
	void resetGame();

	void handleInput();
	void update(const float& deltaTime);
	void render() const;
};
