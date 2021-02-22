#pragma once

class Level : public Component
{
public:
	Level(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<Position>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = destRect.w = position->width;
		srcRect.h = destRect.h = position->height;
		destRect.x = (int)position->position.x;
		destRect.y = (int)position->position.y;
	}

	void update() override
	{
		destRect.y = (int)position->position.y;

		if (position->position.y >= 640) {
			position->position.y = -1920.0f;
			destRect.y = -1920;
		}
	}

	void draw() override
	{
		TextureManager::Render(texture, srcRect, destRect);
	}

private:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Position* position;

};