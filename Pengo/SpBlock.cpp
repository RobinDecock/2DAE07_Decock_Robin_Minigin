#include "MiniginPCH.h"
#include "SpBlock.h"
#include "GeneralStructs.h"
#include "BoxCollider2D.h"
#include "Snobee.h"

SpBlock::SpBlock()
{
}

void SpBlock::Initialize()
{
	m_Tag = "SpBlock";
	m_Sprite = new SpriteComponent("SpBlock.png");
	m_Transform.SetScale(2, 2);
	AddComponent(m_Sprite);
	m_Sprite->SetSpriteData(SpBlockSprites[false]);

	Block::Initialize();
}

void SpBlock::Render()const
{
	Block::Render();
}


void SpBlock::Update(float elapsedSec)
{
	Block::Update(elapsedSec);
}

void SpBlock::OnTrigger(BoxCollider2D* trigger, BoxCollider2D* receive)
{
	UNREFERENCED_PARAMETER(trigger);
	UNREFERENCED_PARAMETER(receive);
	if (!m_IsActive)return;
	if (receive->GetGameObject()->GetTag() == "Snobee"&&	receive->GetGameObject()->GetIsActive() && inAction)
	{
		dynamic_cast<Snobee*>(receive->GetGameObject())->Kill();
		receive->GetGameObject()->SetActive(false);
	}
}



void SpBlock::Break()
{
	if (broken == false)
	{
		broken = true;
		m_Sprite->SetSpriteData(SpBlockSprites[true]);
	}

}

SpBlock::~SpBlock()
{
}
