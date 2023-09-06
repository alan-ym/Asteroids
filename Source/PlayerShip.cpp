#include "PlayerShip.h"
#include <cmath>

const SDL_Point PlayerShip::drawPoints[] = { { 0, -20 }, { 10, 10 }, { 5, 5 }, { -5, 5 }, { -10, 10 }, { 0, -20 } };

void PlayerShip::handleInput(const SDL_Event& event)
{
	if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0)
	{
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_A:
			rotationInput += event.key.state == SDL_PRESSED ? -1.0f : 1.0f;
			break;
		case SDL_SCANCODE_D:
			rotationInput += event.key.state == SDL_PRESSED ? 1.0f : -1.0f;
			break;
		}
	}
}

void PlayerShip::update(const float& deltaTime)
{
	rotation += rotationInput * rotationSpeed * deltaTime;
}

void PlayerShip::render(SDL_Renderer* renderer) const
{
	const int numDrawPoints = sizeof(drawPoints) / sizeof(drawPoints[0]);

	//Apply position and rotation to draw points
	SDL_Point adjustedDrawPoints[numDrawPoints];
	for (int i = 0; i < numDrawPoints; i++)
	{
		float rotationRadians = rotation * 0.01745329251f;
		int rotatedX = (drawPoints[i].x * std::cos(rotationRadians)) - (drawPoints[i].y * std::sin(rotationRadians));
		int rotatedY = (drawPoints[i].x * std::sin(rotationRadians)) + (drawPoints[i].y * std::cos(rotationRadians));
		adjustedDrawPoints[i] = { rotatedX + location.x, rotatedY + location.y };
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, adjustedDrawPoints, numDrawPoints);
}
