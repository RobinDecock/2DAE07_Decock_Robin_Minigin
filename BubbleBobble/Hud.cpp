#include "ProjectPCH.h"
#include "Hud.h"
#include "ResourceManager.h"
#include "PlayerHud.h"
#include "Settings.h"
#include "SingleScene.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "TextComponent.h"

Hud::Hud()
{
	m_pInstance = this;
}

Hud::~Hud()
{
}

void Hud::Initialize()
{
}



void Hud::Update(float elapsedSec)
{
	
}




void Hud::LateUpdate(float elapsedSec)
{
}

void Hud::Draw()const
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = Settings::GetWindowSize().x;
	rect.h = 40;
	SDL_SetRenderDrawColor(Renderer::GetSDLRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Renderer::GetSDLRenderer(),& rect);
}

void Hud::AddLifeCounter(PlayerHud* counter)
{
	counters.push_back(counter);
	this->AddChild(counter);
	for (unsigned int i = 0; i < counters.size(); i++)
	{
		counters[i]->GetTransform()->SetPosition(glm::vec2(50+150*i, 16));
	}

}
