#pragma once

#include "GameObject.h"
#include <SDL.h>

enum class AsteroidRadius
{
	Small = 10,
	Medium = 20,
	Large = 40
};

class Asteroid : public GameObject
{
public:
	Asteroid(const Vector2D& startingLocation, const AsteroidRadius& inRadius);

	void update(const float& deltaTime) override;

	void render(SDL_Renderer* renderer) const override;

private:
	const int radius;

	static const int minSpeed = 10;
	static const int maxSpeed = 50;

	//The points that define the shape of the asteroid
	static const int numDrawPoints = 12;
	SDL_Point drawPoints[numDrawPoints];
};
