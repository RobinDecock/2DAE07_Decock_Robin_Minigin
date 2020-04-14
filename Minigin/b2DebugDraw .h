#pragma once
#include "Box2D/Box2D.h"
#include "Renderer.h"
#include <vector>
class b2DebugDraw :public b2Draw
{
public:
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	void DrawTransform(const b2Transform& xf) override;
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;
};

inline void b2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	SDL_Point* points= new SDL_Point[vertexCount];
	for(int i=0;i<vertexCount;i++)
	{
		points[i]={ (int)vertices[i].x,(int)vertices[i].y };
	}

	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), color.r * 255.0f, color.g * 255.0f, color.b * 255.0f, color.a * 255.0f);
	for(int i = 0;i<vertexCount;i++)
	{
		SDL_RenderDrawLines(Renderer::GetSDLRenderer(), points, vertexCount);
	}
}

inline void b2DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), color.r * 255.0f, color.g * 255.0f, color.b * 255.0f, color.a * 255.0f);
	SDL_Point* points = new SDL_Point[vertexCount];
	for (int i=0; i < vertexCount; i++)
	{
		points[i] = { (int)vertices[i].x,(int)vertices[i].y };
	}


	for (int i = 0; i < vertexCount; i++)
	{
		SDL_RenderDrawLines(Renderer::GetSDLRenderer(), points, vertexCount);
	}
}

inline void b2DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
}

inline void b2DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
}

inline void b2DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), color.r*255.0f, color.g * 255.0f, color.b * 255.0f, color.a * 255.0f);
	SDL_RenderDrawLine(Renderer::GetSDLRenderer(),p1.x,p1.y,p2.x,p2.y);
}

inline void b2DebugDraw::DrawTransform(const b2Transform& xf)
{
}

inline void b2DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}
