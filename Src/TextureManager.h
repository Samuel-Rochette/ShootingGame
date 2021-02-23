#pragma once

#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* path);
	static SDL_Texture* LoadText(const char* message);
	static void Render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
};