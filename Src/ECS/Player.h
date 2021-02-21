#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class Player : public Component
{
public:
	Velocity* velocity;

	void init() override
	{
		velocity = &entity->getComponent<Velocity>();
	}

	void update() override
	{
		state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
		{
			velocity->velocity.y = -0.707;
			velocity->velocity.x = 0.707;
		}
		else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
		{
			velocity->velocity.y = -0.707;
			velocity->velocity.x = -0.707;
		}
		else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
		{
			velocity->velocity.y = 0.707;
			velocity->velocity.x = -0.707;
		}
		else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
		{
			velocity->velocity.y = 0.707;
			velocity->velocity.x = 0.707;
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