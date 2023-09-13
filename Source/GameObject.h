#pragma once

#include "Vector2D.h"

class GameObject
{
public:
	GameObject() {};
	GameObject(const Vector2D& startingLocation) : location(startingLocation) {};

protected:
	Vector2D location = { 0.0f, 0.0f };
	Vector2D velocity = { 0.0f, 0.0f };
	float rotation = 0.0f;

	void wrapLocationToScreen();
};
