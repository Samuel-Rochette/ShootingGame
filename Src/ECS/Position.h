#pragma once

#include "Components.h"
#include "../Vector2D.h"

class Position : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height;
	int width;
	int speed;

	Position(float x, float y, int w, int h)
	{
		position.x = x;
		position.y = y;
		width = w;
		height = h;
	}

	void update() override
	{
		velocity = entity->getComponent<Velocity>().velocity;
		speed = entity->getComponent<Velocity>().speed;

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};