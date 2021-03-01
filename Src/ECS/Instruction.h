#pragma once

class Instruction
{
public:

	float end;
	float vectorX;
	float vectorY;
	float angle;
	float curve;

	Instruction(int ed, float vecX, float vecY, float ang, float crv)
	{
		end = ed;
		vectorX = vecX;
		vectorY = vecY;
		angle = ang;
		curve = crv;
	}
};
