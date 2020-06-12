#pragma once
#include "SDLS.h"
#include "BaseComponent.h"
#include "Texture2D.h"
#include "GLMS.h"
struct int4;
struct SDL_Texture;

class TextureComponent final : public BaseComponent
{
public:

	explicit TextureComponent(std::string filePath);
	~TextureComponent();

	TextureComponent(const TextureComponent&) = delete;
	TextureComponent(TextureComponent&&) = delete;
	TextureComponent& operator=(const TextureComponent&) = delete;
	TextureComponent& operator=(const TextureComponent&&) = delete;
	void Draw() override;
	void SetSourceRectangle(SDL_Rect rect);
	void SetSourceRectangle(int4 rect);
	void SetDestinationRectangle(SDL_Rect rect);
	int GetWidth() const;
	int GetHeight() const;
	Texture2D* GetSDLTexture();
	SDL_Rect GetDestinationRectangle() const { return m_Texture->GetDestRect(); }
	SDL_Rect GetSourceRectangle() const { return m_Texture->GetSrcRect(); }

	void SetPivot(glm::vec2 point)const { m_Texture->SetPivot(point); }
	glm::vec2 GetPivot() const { return m_Texture->GetPivot(); }

	float GetAngle() const { return m_Texture->GetAngle(); }
	void SetAngle(float a) { m_Texture->SetAngle(a); }
	void SetUseCam(bool b) { useCam = b; }
protected:
	Texture2D* m_Texture = nullptr;
	bool useCam = true;
	
};
