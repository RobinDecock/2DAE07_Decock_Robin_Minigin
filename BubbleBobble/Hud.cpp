#include "ProjectPCH.h"
#include "Hud.h"


#include "ResourceManager.h"
#include "TextComponent.h"
#include "Font.h"
Hud::~Hud()
{
}

void Hud::Initialize()
{
	scoreObject = new GameObject();
	std::shared_ptr<Font> pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf",18);
	scoreObject->AddComponent(NEW(TextComponent)(pFont));
	AddChild(scoreObject);
}



void Hud::Update(float elapsedSec)
{
	scoreObject->GetComponent<TextComponent>()->SetText(std::to_string(m_Score));
}

void Hud::LateUpdate(float elapsedSec)
{
}

void Hud::Draw()
{
}
