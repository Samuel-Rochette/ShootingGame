#pragma once

#include "../Vector2D.h"
#include "Player.h"
#include "../Collision.h"

class Position : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height;
	int width;

	Position(float x, float y, int w, int h)
	{
		position.x = x;
		position.y = y;
		width = w;
		height = h;
	}

	void update() override
	{
		if (entity->hasComponent<Velocity>())
		{
			velocity = entity->getComponent<Velocity>().velocity;

			position.x += velocity.x;
			position.y += velocity.y;
		}

		if (entity->hasComponent<Player>() &&
			!Collision::isWithin(position, width, height, entity->getComponent<Player>().playArea))
		{
			position = Collision::correctPosition(position, width, height, entity->getComponent<Player>().playArea);
		}


	}

};