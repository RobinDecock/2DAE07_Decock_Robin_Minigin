#pragma once
#include "GeneralStructs.h"
#pragma warning(disable:4996)
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

inline b2Vec2 make_b2Vec2(const glm::vec2& var)
{
	return b2Vec2(var.x, var.y);
}
inline glm::vec2 make_glmVec2(const b2Vec2& var)
{
	return  glm::vec2(var.x, var.y);
}
inline SDL_Rect make_SDL_Rect(int4 var)
{
	SDL_Rect rect;
	rect.x = var.x;
	rect.y = var.y;
	rect.w = var.w;
	rect.h = var.h;
	return rect;
}
inline SDL_Rect make_SDL_Rect(Rectf var)
{
	SDL_Rect rect;
	rect.x = (int)var.x;
	rect.y = (int)var.y;
	rect.w = (int)var.w;
	rect.h = (int)var.h;
	return rect;
}

class RaycastCallback:public b2RayCastCallback
{
public:
	RaycastCallback(uint16 category):m_Category(category){}
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
	bool hasHit() { return hit; }
	b2Fixture* GetFixHit() { return fixHit; }
	uint16 m_CategoryHit = 0;
private:
	uint16 m_Category;

	bool hit = false;
	b2Fixture* fixHit = nullptr;
};

inline float32 RaycastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
	float32 fraction)
{
	UNREF(fraction);
	UNREF(point);
	UNREF(normal);
	hit = (fixture->GetFilterData().categoryBits & m_Category) == fixture->GetFilterData().categoryBits;
	if(hit)
	{
		m_CategoryHit = fixture->GetFilterData().categoryBits;
		fixHit = fixture;
	}
	else
	{
		return -1;
	}
	return 0;

	

}

