#pragma once

#include "../TextureManager.h"

class Text : public Component
{
private:
	Position* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect, selectedRect;

	int fontSize;
	const char* message;
	int sceneNum;
	bool menuItem;
	bool isSelected;

public:
	Text(const char* m, int size)
	{
		message = m;
		fontSize = size;
		menuItem = false;
		setTex();
	}

	Text(const char* m, int size, int scene)
	{
		message = m;
		fontSize = size;
		menuItem = true;
		sceneNum = scene;
		setTex();
	}

	~Text()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex()
	{
		texture = TextureManager::LoadText(message, fontSize);
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

		selectedRect.x = (int)position->position.x - 8;
		selectedRect.y = (int)position->position.y - 8 ;
		selectedRect.h = position->height + 8;
		selectedRect.w = position->width + 8;
	}

	void update() override
	{
		destRect.x = (int)position->position.x;
		destRect.y = (int)position->position.y;

		if (Collision::isWithin(Game::mouse, 1, 1, destRect) && menuItem)
		{
			isSelected = true;
			texture = TextureManager::LoadText(message, fontSize + 8);
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				Game::changeScene(sceneNum);
			}
		}
		else
		{
			isSelected = false;
			texture = TextureManager::LoadText(message, fontSize);
		}

	}

	void draw() override
	{
		if (isSelected)
		{

			TextureManager::Render(texture, srcRect, selectedRect);
		}
		else
		{
			TextureManager::Render(texture, srcRect, destRect);

		}
	}
};