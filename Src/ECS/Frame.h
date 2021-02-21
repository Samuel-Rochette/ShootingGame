#pragma once

#include "Components.h"

class Frame : public Component
{
public:
	Frame(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
		srcRect.w = destRect.w = 800;
		srcRect.h = destRect.h = 640;
	}
	
	void draw() override
	{
		TextureManager::Render(texture, srcRect, destRect);
	}

private:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

};