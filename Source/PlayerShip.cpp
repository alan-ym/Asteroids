#include "PlayerShip.h"
#include <cmath>

const float PlayerShip::thrustAcceleration = 500.0f;
const float PlayerShip::dragCoefficient = 0.5f;
const float PlayerShip::rotationSpeed = 270.0f;
const float PlayerShip::projectileSpeed = 500.0f;
const SDL_Point PlayerShip::drawPoints[] = { { 0, -20 }, { 10, 10 }, { 5, 5 }, { -5, 5 }, { -10, 10 }, { 0, -20 } };

void PlayerShip::handleInput(const SDL_Event& event)
{
	if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0)
	{
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_SPACE:
			fireInput = event.key.state == SDL_PRESSED;
			break;
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
	//Calculate forward vector
	const float rotationRadians = rotation * 0.01745329251f;
	const Vector2D forwardUnitVector(std::sin(rotationRadians), -std::cos(rotationRadians));

	//Fire projectile
	if (fireInput)
	{
		const Vector2D projectileSpawnLocation = location + (forwardUnitVector * 20);
		const Vector2D projectileVelocity = velocity + (forwardUnitVector * projectileSpeed);
		game->spawnProjectile(projectileSpawnLocation, projectileVelocity);
		fireInput = false;
	}

	//Update rotation
	rotation += rotationInput * rotationSpeed * deltaTime;

	//Apply acceleration to velocity
	const Vector2D accelerationVector = thrustInput ? forwardUnitVector * thrustAcceleration : Vector2D(0.0f, 0.0f);
	velocity += accelerationVector * deltaTime;

	//Apply drag to velocity
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
		adjustedDrawPoints[i] = { static_cast<int>(std::round(rotatedX + location.x)), static_cast<int>(std::round(rotatedY + location.y)) };
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, adjustedDrawPoints, numDrawPoints);
}
