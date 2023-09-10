#pragma once

#include "Vector2D.h"
#include <SDL.h>

class PlayerShip
{
public:
	PlayerShip() {};
	PlayerShip(const Vector2D& startingLocation) : location(startingLocation) {};

	void handleInput(const SDL_Event& event);

	//Updates the ship's location and rotation
	void update(const float& deltaTime);

	//Draws the ship based on the draw points, location, and rotation
	void render(SDL_Renderer* renderer) const;

private:
	Vector2D location = { 0.0f, 0.0f };
	Vector2D velocity = { 0.0f, 0.0f };
	float rotation = 0.0f;

	bool thrustInput = false;
	float rotationInput = 0.0f; //Input axis (-1.0f to 1.0f)

	static const float thrustAcceleration;
	static const float dragCoefficient;
	static const float rotationSpeed; //In degrees/second

	//The points that define the shape of the ship
	static const SDL_Point drawPoints[];

	void wrapLocationToScreen();
};
