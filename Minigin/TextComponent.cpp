#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Font.h"
#include "Texture2D.h"
TextComponent::TextComponent(std::shared_ptr<Font> font) :
	m_NeedsUpdate(false), m_Font(font), m_Color({ 255,255,255 })
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
		Renderer::RenderTexture(*m_Texture,pos.x-m_Text.size()*4,pos.y);
	}
}

void TextComponent::Update(float elapsedSec)
{
	UNREF(elapsedSec);
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Draw text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetSDLRenderer(), surf);


		if(m_Texture!=nullptr)
		{
			delete m_Texture;
		}

		m_Texture = new Texture2D(texture);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		
		SDL_FreeSurface(surf);
		m_NeedsUpdate = false;
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}


TextComponent::~TextComponent()
{
	delete m_Texture;
	m_Texture = nullptr;
}
