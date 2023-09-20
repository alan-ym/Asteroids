#pragma once

#include "Vector2D.h"

struct SDL_Renderer;

class GameObject
{
public:
	GameObject() {};
	GameObject(const Vector2D& startingLocation) : location(startingLocation) {}
	GameObject(const Vector2D& startingLocation, const Vector2D& velocity) : location(startingLocation), velocity(velocity) {}

	virtual void update(const float& deltaTime) {}

	virtual void render(SDL_Renderer* renderer) const {}

	bool getIsAlive() const { return isAlive; }
	void setIsAlive(const bool& inIsAlive) { isAlive = inIsAlive; }

	Vector2D getLocation() const { return location; }

	bool checkForCircleCollision(const GameObject* const other) const;
	virtual float getCircleCollisionRadius() const { return 0.0f; }

protected:
	bool isAlive = true;
	
	Vector2D location = { 0.0f, 0.0f };
	Vector2D velocity = { 0.0f, 0.0f };
	float rotation = 0.0f; //In degrees

	void wrapLocationToScreen();
};
