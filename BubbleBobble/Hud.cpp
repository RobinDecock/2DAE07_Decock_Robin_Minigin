#include "ProjectPCH.h"
#include "Hud.h"
#include "ResourceManager.h"
#include "LifeCounter.h"
#include "Settings.h"
#include "SingleScene.h"
#include "TransformComponent.h"
#include "Renderer.h"

Hud::Hud()
{
	m_pInstance = this;
}

Hud::~Hud()
{
}

void Hud::Initialize()
{
	
	//scoreObject = new GameObject();
	//Font> pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf",18);
	//scoreObject->AddComponent(NEW(TextComponent)(pFont));
	//AddChild(scoreObject);
	//scoreObject->SetPosition(glm::vec2(Settings::GetWindowSize().x / 2.0f, 0));
}



void Hud::Update(float elapsedSec)
{
	//scoreObject->GetComponent<TextComponent>()->SetText(std::to_string(m_Score));
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

void Hud::AddLifeCounter(LifeCounter* counter)
{
	counters.push_back(counter);
	this->AddChild(counter);
	for (unsigned int i = 0; i < counters.size(); i++)
	{
		counters[i]->GetTransform()->SetPosition(glm::vec2(50+150*i, 16));
	}

}
