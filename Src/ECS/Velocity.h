#pragma once

#include "Components.h"
#include "../Vector2D.h"

const float PI = 3.14159265;

class Velocity : public Component
{

public:

	Vector2D velocity;

	Velocity()
	{
		setVelocity(0.0, 0.0);
	}

	Velocity(float velX, float velY)
	{
		setVelocity(velX, velY);
	}

	void setVelocity(float velX, float velY)
	{
		velocity.x = velX;
		velocity.y = velY;
	}

	void addVector(float speed, int angle)
	{
		float rad = angle * PI / 180;
		velocity.x += sin(rad) * speed;
		velocity.y += cos(rad) * speed * -1;
	}
};