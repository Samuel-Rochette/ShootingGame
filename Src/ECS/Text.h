#pragma once

#include "../TextureManager.h"

class Text : public Component
{
private:
	Position* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	Text(const char* message)
	{
		setTex(message);
	}

	~Text()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* message)
	{
		texture = TextureManager::LoadText(message);
	}

	void init() override
	{
		position = &entity->getComponent<Position>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = position->width;
		srcRect.h = position->height;

		destRect.x = (int)position->position.x;
		destRect.y = (int)position->position.y;
		destRect.h = position->height;
		destRect.w = position->width;
	}

	void update() override
	{
		destRect.x = (int)position->position.x;
		destRect.y = (int)position->position.y;
	}

	void draw() override
	{
		TextureManager::Render(texture, srcRect, destRect);
	}
};