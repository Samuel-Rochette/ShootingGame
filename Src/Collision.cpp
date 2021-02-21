#include "Collision.h"

bool Collision::aabb(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectB.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::isWithin(Vector2D position, int w, int h, const SDL_Rect& rectB)
{
	if (
		position.x <= rectB.x &&
		position.y <= rectB.y &&
		position.x + w >= rectB.x + rectB.w &&
		position.y + h >= rectB.y + rectB.h
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Vector2D Collision::correctPosition(Vector2D position, int w, int h, const SDL_Rect& rectB)
{

	if (position.x <= rectB.x)
		position.x += rectB.x - position.x;
	else if (position.x + w >= rectB.x + rectB.w)
		position.x += (rectB.x + rectB.w) - (position.x + w);

	if (position.y <= rectB.y)
		position.y += rectB.y - position.y;
	if (position.y + h >= rectB.y + rectB.h)
		position.y += (rectB.y + rectB.h) - (position.y + h);

	return position;
}