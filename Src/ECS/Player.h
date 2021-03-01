#pragma once

#include "../Game.h"
#include "ECS.h"

class Player : public Component
{
public:

	Velocity* velocity;
	SDL_Rect playArea;

	float vecX;
	float vecY;
	float speed;

	void init() override
	{
		velocity = &entity->getComponent<Velocity>();

		playArea.x = playArea.y = 32;
		playArea.h = 576;
		playArea.w = 512;

		vecX = 0.0;
		vecY = 0.0;
		speed = 0.0;
	}

	void update() override
	{
		state = SDL_GetKeyboardState(NULL);
		speed = 0.0;

		if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
		{
			speed = 5.0;
			vecX = 0.707;
			vecY = -0.707;
		}
		else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
		{
			speed = 5.0;
			vecX = -0.707;
			vecY = -0.707;
		}
		else if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT])
		{
			speed = 5.0;
			vecX = -0.707;
			vecY = 0.707;
		}
		else if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT])
		{
			speed = 5.0;
			vecX = 0.707;
			vecY = 0.707;
		}
		else if (state[SDL_SCANCODE_UP])
		{
			speed = 5.0;
			vecX = 0.0;
			vecY = -1.0;
		}
		else if (state[SDL_SCANCODE_LEFT])
		{
			speed = 5.0;
			vecX = -1.0;
			vecY = 0;
		}
		else if (state[SDL_SCANCODE_DOWN])
		{
			speed = 5.0;
			vecX = 0.0;
			vecY = 1.0;
		}
		else if (state[SDL_SCANCODE_RIGHT])
		{
			speed = 5.0;
			vecX = 1.0;
			vecY = 0.0;
		}
		else
		{
			speed = 0;
		}

		if (state[SDL_SCANCODE_ESCAPE])
		{
			Game::isPaused = true;
		}

		velocity->setVelocity(vecX * speed, vecY * speed);
	}

private:
	const Uint8 *state;
};