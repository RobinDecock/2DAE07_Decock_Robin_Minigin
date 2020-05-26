#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "Texture2D.h"
SDL_Renderer * Renderer::m_Renderer = nullptr;
void Renderer::Init(SDL_Window* window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Clear()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0,2, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_Renderer);
}

void Renderer::Render()
{
	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture)
{
	SDL_Rect dstRect = texture.GetDestRect();
	SDL_Rect srcRect = texture.GetSrcRect();
	glm::vec2 pivot = texture.GetPivot();
	SDL_Point pivotOffset;
	//TODO MOVE THIS CRAP TO THE COMP ITSELF

	pivotOffset.x = int(pivot.x * dstRect.w);
	pivotOffset.y = int(pivot.y * dstRect.h);

	dstRect.x -= pivotOffset.x;
	dstRect.y -= pivotOffset.y;

	SDL_RenderCopyEx(m_Renderer, texture.GetSDLTexture(), &srcRect, &dstRect, texture.GetAngle(), &pivotOffset,
	                 texture.GetFlipped()?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y)
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
