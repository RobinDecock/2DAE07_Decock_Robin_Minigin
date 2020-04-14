#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

TextComponent::TextComponent(std::shared_ptr<Font> font) :
	m_NeedsUpdate(false), m_Font(font)
{
}

void TextComponent::Initialize()
{
}

void TextComponent::Draw()
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_pGameObject->GetTransform()->GetPosition();
		//Renderer::RenderTexture(*m_Texture,pos.x,pos.y);
	}
}

void TextComponent::Update(float elapsedSec)
{
	UNREF(elapsedSec);
	if (m_NeedsUpdate)
	{
		const SDL_Color color = {255, 255, 255}; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Draw text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		//m_Texture = NEWTextureComponent>(texture);
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}


TextComponent::~TextComponent()
{
}
