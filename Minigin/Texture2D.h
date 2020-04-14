#pragma once
#include <SDL.h>
#include "vec2.hpp"
class Texture2D
{
public:
	Texture2D(SDL_Texture* texture)
	{
		m_Texture = texture;

		SDL_QueryTexture(texture, nullptr, nullptr, &m_Width, &m_Height);
		m_destinationRectangle.w = m_Width;
		m_destinationRectangle.h = m_Height;
		m_sourceRectangle.w = m_Width;
		m_sourceRectangle.h = m_Height;
	}

	~Texture2D()
	{
		SDL_DestroyTexture(m_Texture);
	}

	SDL_Texture* GetSDLTexture() const { return m_Texture; }

	void SetSrcRect(SDL_Rect srcRect) { m_sourceRectangle = srcRect; }
	void SetDestRect(SDL_Rect destRect) { m_destinationRectangle = destRect; }
	void SetPivot(glm::vec2 pivot) { m_Pivot = pivot; }
	void SetAngle(float angle) { m_Angle = angle; }

	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }

	SDL_Rect GetSrcRect() const { return m_sourceRectangle; }
	SDL_Rect GetDestRect() const { return m_destinationRectangle; }
	glm::vec2 GetPivot() const { return m_Pivot; }
	float GetAngle() const { return m_Angle; }
private:
	SDL_Rect m_sourceRectangle{};
	SDL_Rect m_destinationRectangle{};
	glm::vec2 m_Pivot = glm::vec2(0.5f, 0.5f);
	float m_Angle{};
	int m_Width{};
	int m_Height{};
	SDL_Texture* m_Texture = nullptr;
};
