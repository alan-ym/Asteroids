#pragma once

#include "GameObject.h"

struct SDL_Renderer;

class Projectile : public GameObject
{
public:
	Projectile(const Vector2D& startingLocation, const Vector2D& velocity) : GameObject(startingLocation, velocity) {};

	void update(const float& deltaTime) override;

	void render(SDL_Renderer* renderer) const override;

private:
	float age = 0.0f; //In seconds
	const float lifetime = 1.0f;

	const int radius = 1;
};
