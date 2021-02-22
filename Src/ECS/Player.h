#pragma once

#include "../Game.h"
#include "ECS.h"

class Player : public Component
{
public:
	Velocity* velocity;
	SDL_Rect playArea;

	void init() override
	{
		velocity = &entity->getComponent<Velocity>();

		playArea.x = playArea.y = 32;
		playArea.h = 576;
		playArea.w = 512;
	}

	void update() override
	{
		state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
		{
			velocity->velocity.y = -0.707f;
			velocity->velocity.x = 0.707f;
		}
		else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
		{
			velocity->velocity.y = -0.707f;
			velocity->velocity.x = -0.707f;
		}
		else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
		{
			velocity->velocity.y = 0.707f;
			velocity->velocity.x = -0.707f;
		}
		else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
		{
			velocity->velocity.y = 0.707f;
			velocity->velocity.x = 0.707f;
		}
		else if (state[SDL_SCANCODE_W])
		{
			velocity->velocity.y = -1;
			velocity->velocity.x = 0;
		}
		else if (state[SDL_SCANCODE_A])
		{
			velocity->velocity.y = 0;
			velocity->velocity.x = -1;
		}
		else if (state[SDL_SCANCODE_S])
		{
			velocity->velocity.y = 1;
			velocity->velocity.x = 0;
		}
		else if (state[SDL_SCANCODE_D])
		{
			velocity->velocity.y = 0;
			velocity->velocity.x = 1;
		}
		else
		{
			velocity->velocity.y = 0;
			velocity->velocity.x = 0;
		}
	}

private:
	const Uint8 *state;
};