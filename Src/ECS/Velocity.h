#pragma once

#include "Components.h"
#include "../Vector2D.h"

class Velocity : public Component
{

public:

	Vector2D velocity;
	int speed;

	Velocity(int sp)
	{
		velocity.zero();
		speed = sp;
	}

	Velocity(int sp, float velocityX, float velocityY)
	{
		velocity.x = velocityX;
		velocity.y = velocityY;
		speed = sp;
	}

};