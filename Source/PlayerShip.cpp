#include "PlayerShip.h"
#include <cmath>

const SDL_Point PlayerShip::drawPoints[] = { { 0, -20 }, { 10, 10 }, { 5, 5 }, { -5, 5 }, { -10, 10 }, { 0, -20 } };

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
