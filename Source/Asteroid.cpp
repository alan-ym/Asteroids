#include "Asteroid.h"
#include <cmath>

Asteroid::Asteroid(const Vector2D& startingLocation, const AsteroidRadius& inRadius) : GameObject(startingLocation), radius(inRadius)
{
	//Generate random velocity
	//(Using default-seeded rand() for simple rng, could be improved later)
	const int speedRange = maxSpeed - minSpeed;
	const float speed = ((rand() / static_cast<float>(RAND_MAX)) * speedRange) + minSpeed;
	const float velocityAngle = (rand() / static_cast<float>(RAND_MAX)) * 6.28318530718f;
	velocity = Vector2D(std::sin(velocityAngle), std::cos(velocityAngle)) * speed;

	//Generate draw points for the asteroid
	float drawRadius = static_cast<float>(radius);
	for (int i = 0; i < numDrawPoints - 1; i++)
	{
		//Add random variation by adjusting each point's distance from the asteroid's center
		const float variationRange = drawRadius * 0.5f;
		const float variation = ((rand() / static_cast<float>(RAND_MAX)) * variationRange) - (variationRange * 0.5f);

		//Add points in a circle around the asteroid's center
		const float centralAngle = (i / static_cast<float>(numDrawPoints - 1)) * 6.28318530718f;
		const int pointX = static_cast<int>(std::sin(centralAngle) * (drawRadius + variation));
		const int pointY = static_cast<int>(std::cos(centralAngle) * (drawRadius + variation));
		drawPoints[i] = { pointX, pointY };
	}
	//Include the first point again as the last element to close the shape
	drawPoints[numDrawPoints - 1] = drawPoints[0]; 
}

void Asteroid::update(const float& deltaTime)
{
	location += velocity * deltaTime;
	wrapLocationToScreen();
}

void Asteroid::render(SDL_Renderer* renderer) const
{
	//Apply position to draw points
	SDL_Point adjustedDrawPoints[numDrawPoints];
	for (int i = 0; i < numDrawPoints; i++)
	{
		const int adjustedX = static_cast<int>(std::round(drawPoints[i].x + location.x));
		const int adjustedY = static_cast<int>(std::round(drawPoints[i].y + location.y));
		adjustedDrawPoints[i] = { adjustedX, adjustedY };
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, adjustedDrawPoints, numDrawPoints);
}
