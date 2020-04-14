#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "TextureComponent.h"
#include "GameObject.h"
dae::TextObject::TextObject(std::shared_ptr<Font> font)
{
	m_pTextComp = new TextComponent(font);
	AddComponent(m_pTextComp);
}

void dae::TextObject::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
	GameObject::Update(elapsedSec);
}

void dae::TextObject::Render() const
{
	GameObject::Render();
}

void dae::TextObject::SetText(const std::string& text)
{
	m_pTextComp->SetText(text);
}


