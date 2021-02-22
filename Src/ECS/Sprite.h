#pragma once

#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include "../Collision.h"
#include <map>
#include <string>

class Sprite : public Component
{
private:
	Position* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;
	std::map<std::string, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	Sprite(const char* path)
	{
		setTex(path);
	}

	Sprite(const char* path, bool isAnimated)
	{
		animated = true;

		setTex(path);
	}

	~Sprite()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void addAnimation(int index, int frames, int speed)
	{
		std::string name = "Animation" + std::to_string(index);

		animations[name] = Animation(index, frames, speed);

		play("Animation0");
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
		if (animated && frames > 0)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * position->height;

		destRect.x = (int)position->position.x;
		destRect.y = (int)position->position.y;

	}

	void draw() override
	{
		TextureManager::Render(texture, srcRect, destRect);
	}

	void play(std::string animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};