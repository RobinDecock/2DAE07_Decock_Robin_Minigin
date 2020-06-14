#include "MiniginPCH.h"
#include "b2DebugDraw.h"
#include "Camera.h"
#include "Renderer.h"

void b2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<glm::vec4> glmPoints;

	for (int32 i = 0; i < vertexCount; i++)
	{
		glmPoints.push_back({ (int)vertices[i].x,(int)vertices[i].y,0,1 });
	}

	Camera* pCam = m_pCurrentScene->GetCamera();
	if (pCam != nullptr)
	{

		for (int32 i = 0; i < vertexCount; i++)
		{
			glmPoints[i] = pCam->GetViewMatrix() * glmPoints[i];
		}

	}
	int count = int(vertexCount) + 1;
	SDL_Point* points = new SDL_Point[count];
	for (int32 i = 0; i < vertexCount; i++)
	{
		points[i] = { (int)glmPoints[i].x,(int)glmPoints[i].y };
	}
	points[vertexCount] = { (int)glmPoints[0].x, (int)glmPoints[0].y };
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), Uint8(color.r * 255.0f), Uint8(color.g * 255.0f), Uint8(color.b * 255.0f), Uint8(color.a * 255.0f));
	SDL_RenderDrawLines(Renderer::GetSDLRenderer(), points, vertexCount);

	delete[] points;
}

void b2DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<glm::vec4> glmPoints;

	for (int32 i = 0; i < vertexCount; i++)
	{
		glmPoints.push_back({ (int)vertices[i].x,(int)vertices[i].y,0,1 });
	}

	Camera* pCam = m_pCurrentScene->GetCamera();
	if (pCam != nullptr)
	{

		for (int32 i = 0; i < vertexCount; i++)
		{
			glmPoints[i] = pCam->GetViewMatrix() * glmPoints[i];
		}

	}
	int count = int(vertexCount) + 1;
	SDL_Point* points = new SDL_Point[count];
	for (int32 i = 0; i < vertexCount; i++)
	{
		points[i] = { (int)glmPoints[i].x,(int)glmPoints[i].y };
	}
	points[vertexCount] = { (int)glmPoints[0].x, (int)glmPoints[0].y };
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), Uint8(color.r * 255.0f), Uint8(color.g * 255.0f), Uint8(color.b * 255.0f), Uint8(color.a * 255.0f));
	SDL_RenderDrawLines(Renderer::GetSDLRenderer(), points, vertexCount);

	delete[] points;
}

void b2DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
	UNREF(color);
	UNREF(center);
	UNREF(radius);
}

void b2DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
	UNREF(color);
	UNREF(center);
	UNREF(radius);
	UNREF(axis);
}

void b2DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), Uint8(color.r * 255.0f), Uint8(color.g * 255.0f), Uint8(color.b * 255.0f), Uint8(color.a * 255.0f));

	glm::vec4 point1 = { p1.x,p1.y,0,1 };

	glm::vec4 point2 = { p2.x,p2.y,0,1 };

	Camera* pCam = m_pCurrentScene->GetCamera();
	if(pCam !=nullptr)
	{
		
		point1 = pCam->GetViewMatrix() * point1;
		point2 = pCam->GetViewMatrix() * point2;
	}
	


	SDL_RenderDrawLine(Renderer::GetSDLRenderer(), (int)point1.x, (int)point1.y, (int)point2.x, (int)point2.y);
}

void b2DebugDraw::DrawTransform(const b2Transform& xf)
{
	UNREF(xf);
}

void b2DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
	UNREF(p);
	UNREF(size);
	UNREF(color);
}

void b2DebugDraw::SetScene(GameScene* p)
{
	m_pCurrentScene = p;
}

b2DebugDraw::~b2DebugDraw()
{
}
