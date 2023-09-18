#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"
#include <SDL.h>

class PlayerShip : public GameObject
{
public:
	PlayerShip(const Vector2D& startingLocation, Game* const game) : GameObject(startingLocation), game(game) {};

	void handleInput(const SDL_Event& event);

	void update(const float& deltaTime) override;

	void render(SDL_Renderer* renderer) const override;

private:
	bool thrustInput = false;
	float rotationInput = 0.0f; //Input axis (-1.0f to 1.0f)
	bool fireInput = false;

	static const float thrustAcceleration;
	static const float dragCoefficient;
	static const float rotationSpeed; //In degrees/second
	static const float projectileSpeed;

	//The points that define the shape of the ship
	static const SDL_Point drawPoints[];

	Game* const game;
};
