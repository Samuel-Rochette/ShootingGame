#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Collision
{
public:
	static bool aabb(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool isWithin(Vector2D position, int w, int h, const SDL_Rect& rectB);
	static Vector2D correctPosition(Vector2D position, int w, int h, const SDL_Rect& rectB);
};