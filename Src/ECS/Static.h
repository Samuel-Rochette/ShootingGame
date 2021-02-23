#pragma once

class Static : public Component
{
public:
	Static(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<Position>();

		srcRect.x = destRect.x = (int)position->position.x;
		srcRect.y = destRect.y = (int)position->position.y;
		srcRect.w = destRect.w = position->width;
		srcRect.h = destRect.h = position->height;
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