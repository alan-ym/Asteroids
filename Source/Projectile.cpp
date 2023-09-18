#include "Projectile.h"
#include <SDL.h>

void Projectile::update(const float& deltaTime)
{
	//Update age
	age += deltaTime;
	if (age > lifetime)
	{
		isAlive = false;
	}

	//Update location
	location += velocity * deltaTime;
	wrapLocationToScreen();
}

void Projectile::render(SDL_Renderer* renderer) const
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	const SDL_Rect drawRect = { static_cast<int>(location.x) - radius, static_cast<int>(location.y) - radius, radius * 2, radius * 2 };
	SDL_RenderFillRect(renderer, &drawRect);
}
