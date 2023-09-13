#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>

class PlayerShip : public GameObject
{
public:
	PlayerShip() {};
	PlayerShip(const Vector2D& startingLocation) : GameObject(startingLocation) {};

	void handleInput(const SDL_Event& event);

	void update(const float& deltaTime);

	void render(SDL_Renderer* renderer) const;

private:
	bool thrustInput = false;
	float rotationInput = 0.0f; //Input axis (-1.0f to 1.0f)

	static const float thrustAcceleration;
	static const float dragCoefficient;
	static const float rotationSpeed; //In degrees/second

	//The points that define the shape of the ship
	static const SDL_Point drawPoints[];
};
