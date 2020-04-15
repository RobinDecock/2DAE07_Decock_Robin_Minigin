#pragma once
#include "Box2D/Box2D.h"
#include "Renderer.h"
#include <vector>
#include "Camera.h"
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
	void SetCamera(Camera * p)
	{
		m_pCamera = p;
	}
private:
	Camera *m_pCamera = nullptr;
};

inline void b2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<glm::vec4> glmPoints;

	for (int i = 0; i < vertexCount; i++)
	{
		glmPoints.push_back({ (int)vertices[i].x,(int)vertices[i].y,0,1 });
		glmPoints[i] = m_pCamera->GetViewMatrix() * glmPoints[i];
	}


	
	SDL_Point* points= new SDL_Point[vertexCount];
	for(int i=0;i<vertexCount;i++)
	{
		points[i]={ (int)glmPoints[i].x,(int)glmPoints[i].y };
	}
	
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), color.r * 255.0f, color.g * 255.0f, color.b * 255.0f, color.a * 255.0f);
	SDL_RenderDrawLines(Renderer::GetSDLRenderer(), points, vertexCount);

	delete points;
	points = nullptr;
}

inline void b2DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<glm::vec4> glmPoints;

	for (int i = 0; i < vertexCount; i++)
	{
		glmPoints.push_back({ (int)vertices[i].x,(int)vertices[i].y,0,1 });
		glmPoints[i] = m_pCamera->GetViewMatrix() * glmPoints[i];
	}



	SDL_Point* points = new SDL_Point[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		points[i] = { (int)glmPoints[i].x,(int)glmPoints[i].y };
	}

	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), color.r * 255.0f, color.g * 255.0f, color.b * 255.0f, color.a * 255.0f);
	SDL_RenderDrawLines(Renderer::GetSDLRenderer(), points, vertexCount);

	delete points;
	points = nullptr;
	
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

	glm::vec4 point1 = { p1.x,p1.y,0,1 };

	glm::vec4 point2 = { p2.x,p2.y,0,1 };

	point1 = m_pCamera->GetViewMatrix() * point1;
	point2 = m_pCamera->GetViewMatrix() * point2;
	
	SDL_RenderDrawLine(Renderer::GetSDLRenderer(), point1.x, point1.y, point2.x, point2.y);
}

inline void b2DebugDraw::DrawTransform(const b2Transform& xf)
{
}

inline void b2DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}
