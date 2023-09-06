#pragma once

#include <SDL.h>

class PlayerShip
{
public:
	PlayerShip() {};
	PlayerShip(const SDL_Point& startingLocation) : location(startingLocation) {};

	void handleInput(const SDL_Event& event);

	//Updates the ship's location and rotation
	void update(const float& deltaTime);

	//Draws the ship based on the draw points, location, and rotation
	void render(SDL_Renderer* renderer) const;

private:
	//The points that define the shape of the ship
	static const SDL_Point drawPoints[];

	SDL_Point location = { 0, 0 };
	float rotation = 0.0f;

	//Rotation speed (in degrees/second)
	float rotationSpeed = 360.0f;

	//Rotation input axis (-1.0f to 1.0f)
	float rotationInput = 0.0f;
};
