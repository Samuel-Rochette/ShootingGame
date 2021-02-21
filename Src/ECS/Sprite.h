#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

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
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	Sprite() = default;
	Sprite(const char* path)
	{
		setTex(path);
	}

	Sprite(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		//                  -TODO-
		// - Accept multiple animation parameters
		// - Create new animation with Animation <NAME> = Animation(index, frames, speed);
		// - Add animation to entity with animations.emplace("<NAME>", <NAME>);
		// - Call play(<NAME>); to set default animation

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
		if (animated)
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

	void play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};