#include "GameObject.h"
#include "Game.h"

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
