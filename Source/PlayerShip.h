#pragma once

#include <SDL.h>

class PlayerShip
{
public:
	PlayerShip() {};
	PlayerShip(const SDL_Point& startingLocation) : location(startingLocation) {};

	//Draws the ship based on the draw points, location, and rotation
	void render(SDL_Renderer* renderer) const;

private:
	//The points that define the shape of the ship
	static const SDL_Point drawPoints[];

	SDL_Point location = { 0, 0 };
	int rotation = 0;
};
