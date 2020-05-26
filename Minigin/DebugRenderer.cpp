#include "MiniginPCH.h"
#include "DebugRenderer.h"
#include "Camera.h"
#include "Renderer.h"
Camera * DebugRenderer::m_pCamera = nullptr;
void DebugRenderer::DrawLine(glm::vec2 p1,glm::vec2 p2,Color color)
{
	glm::vec2 point1;
	glm::vec2 point2;
	if (m_pCamera != nullptr)
	{
		point1 = m_pCamera->GetViewMatrix() * glm::vec4(p1, 0, 1);
		point2 = m_pCamera->GetViewMatrix() * glm::vec4(p2, 0, 1);
	}
	else
	{
		point1 = glm::vec4(p1, 0, 1);
		point2 = glm::vec4(p2, 0, 1);
	}

	//DRAW ORIGIN
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), (int)color.r, (int)color.g, (int)color.b, (int)SDL_ALPHA_OPAQUE);
	
	if (SDL_RenderDrawLine(Renderer::GetSDLRenderer(), (int)point1.x, (int)point1.y, (int)point2.x, (int)point2.y) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}

void DebugRenderer::DrawPoint(glm::vec2 pos)
{
	glm::vec2 point1;
	if (m_pCamera != nullptr)
	{
		point1 = m_pCamera->GetViewMatrix() * glm::vec4(pos, 0, 1);

	}
	else
	{
		point1 = glm::vec4(pos, 0, 1);
	}
	SDL_RenderDrawPoint(Renderer::GetSDLRenderer(), point1.x, point1.y);

}


void DebugRenderer::SetCamera(Camera* cam)
{
	m_pCamera = cam;
}
