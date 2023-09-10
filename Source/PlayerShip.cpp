#include "PlayerShip.h"
#include "Game.h"
#include <cmath>

const float PlayerShip::thrustAcceleration = 400.0f;
const float PlayerShip::dragCoefficient = 0.6f;
const float PlayerShip::rotationSpeed = 270.0f;
const SDL_Point PlayerShip::drawPoints[] = { { 0, -20 }, { 10, 10 }, { 5, 5 }, { -5, 5 }, { -10, 10 }, { 0, -20 } };

void PlayerShip::handleInput(const SDL_Event& event)
{
	if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0)
	{
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_W:
			thrustInput = event.key.state == SDL_PRESSED;
			break;
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
	//Update rotation
	rotation += rotationInput * rotationSpeed * deltaTime;

	//Apply acceleration
	const float rotationRadians = rotation * 0.01745329251f;
	const Vector2D forwardUnitVector(std::sin(rotationRadians), -std::cos(rotationRadians));
	const Vector2D accelerationVector = thrustInput ? forwardUnitVector * thrustAcceleration : Vector2D(0.0f, 0.0f);
	velocity += accelerationVector * deltaTime;

	//Apply drag
	const Vector2D dragVector = -velocity * dragCoefficient;
	velocity += dragVector * deltaTime;

	//Update location
	location += velocity * deltaTime;
	wrapLocationToScreen();
}

void PlayerShip::render(SDL_Renderer* renderer) const
{
	const int numDrawPoints = sizeof(drawPoints) / sizeof(drawPoints[0]);

	//Apply position and rotation to draw points
	SDL_Point adjustedDrawPoints[numDrawPoints];
	for (int i = 0; i < numDrawPoints; i++)
	{
		const float rotationRadians = rotation * 0.01745329251f;
		const float rotatedX = (drawPoints[i].x * std::cos(rotationRadians)) - (drawPoints[i].y * std::sin(rotationRadians));
		const float rotatedY = (drawPoints[i].x * std::sin(rotationRadians)) + (drawPoints[i].y * std::cos(rotationRadians));
		adjustedDrawPoints[i] = { (int)std::round(rotatedX + location.x), (int)std::round(rotatedY + location.y) };
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, adjustedDrawPoints, numDrawPoints);
}

void PlayerShip::wrapLocationToScreen()
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
