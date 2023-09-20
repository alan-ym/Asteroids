#include "GameObject.h"
#include "Game.h"

bool GameObject::checkForCircleCollision(const GameObject* const other) const
{
	const Vector2D differenceVector = location - other->getLocation();
	const float distanceSquared = (differenceVector.x * differenceVector.x) + (differenceVector.y * differenceVector.y);
	const float collisionThreshold = getCircleCollisionRadius() + other->getCircleCollisionRadius();
	return distanceSquared <= collisionThreshold * collisionThreshold;
}

void GameObject::wrapLocationToScreen()
{
	if (location.x < 0.0f)
	{
		location.x += Game::windowWidth;
	}
	else if (location.x > Game::windowWidth)
	{
		location.x -= Game::windowWidth;
	}

	if (location.y < 0.0f)
	{
		location.y += Game::windowHeight;
	}
	else if (location.y > Game::windowHeight)
	{
		location.y -= Game::windowHeight;
	}
}
