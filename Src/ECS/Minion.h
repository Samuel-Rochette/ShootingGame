#pragma once

#include "../Game.h"
#include "../Vector2D.h"
#include "Instruction.h"
#include "ECS.h"

#include <map>;

class Minion : public Component
{
public:

	Velocity* velocity;

	const float PI = 3.14159265;

	Vector2D speed;

	std::map<int, Instruction*> Instructions;
	std::map<int, Vector2D*> Vectors;

	void init() override
	{
		velocity = &entity->getComponent<Velocity>();
	}

	void update() override
	{
		int frames = Game::frames;
		speed.x = 0;
		speed.y = 0;

		Instruction* action = Instructions[frames];
		
		if (action != nullptr)
		{
			Vectors[Vectors.size()] = new Vector2D();

			Vectors[Vectors.size() - 1]->x = action->vectorX;
			Vectors[Vectors.size() - 1]->y = action->vectorY;
			Vectors[Vectors.size() - 1]->ang = action->angle;
			Vectors[Vectors.size() - 1]->crv = action->curve;
			Vectors[Vectors.size() - 1]->end = action->end;
		}

		for (int i = 0; i < Vectors.size(); i++)
		{
			Vectors[i]->ang += Vectors[i]->crv;
			float rad = Vectors[i]->ang * PI / 180;

			speed.x += sin(rad) * Vectors[i]->x;
			speed.y += cos(rad) * Vectors[i]->y * -1;

			if (Vectors[i]->end <= frames) {
				Vectors.erase(i);
			}
		}

		velocity->setVelocity(speed.x, speed.y);
	}

	void addInstruction(int st, int ed, float vecX, float vecY, float ang, float crv)
	{
		Instructions.insert(std::make_pair(st, new Instruction(ed, vecX, vecY, ang, crv)));
	}
};