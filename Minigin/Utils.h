#pragma once
#include "GeneralStructs.h"

class Utils
{
public:
	static float distance(glm::vec2 pos1, glm::vec2 pos2)
	{
		return static_cast<float>(sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));
	}

	static int distance(int2 pos1, int2 pos2)
	{
		return static_cast<int>(sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));
	}
};


inline b2Vec2 make_b2Vec2(glm::vec2 var)
{
	return b2Vec2(var.x, var.y);
}

