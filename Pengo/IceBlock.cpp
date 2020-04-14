#include "MiniginPCH.h"
#include "IceBlock.h"
#include "GeneralStructs.h"
#include "BoxCollider2D.h"
#include "Snobee.h"

IceBlock::IceBlock(PlayField * playField)
{
	m_pPlayField = playField;
}

void IceBlock::Initialize()
{
	m_Tag = "IceBlock";
	m_Sprite = new SpriteComponent("IceBlock.png");
	m_Transform.SetScale(2, 2);
	AddComponent(m_Sprite);
	m_Sprite->SetSpriteData(IceBlockSprites[false]);

	Block::Initialize();
}

void IceBlock::Render()const
{
	Block::Render();
}


void IceBlock::Update(float elapsedSec)
{
	Block::Update(elapsedSec);
}

void IceBlock::OnTrigger(BoxCollider2D* trigger, BoxCollider2D* receive)
{
	UNREFERENCED_PARAMETER(trigger);
	UNREFERENCED_PARAMETER(receive);
	if (!m_IsActive)return;
	if(receive->GetGameObject()->GetTag()=="Snobee"&&	receive->GetGameObject()->GetIsActive())
	{
		dynamic_cast<Snobee*>(receive->GetGameObject())->Kill();
		receive->GetGameObject()->SetActive(false);
	}
}



void IceBlock::Break()
{
	if(broken==false)
	{
		broken = true;
		m_Sprite->SetSpriteData(IceBlockSprites[true]);
	}

}

IceBlock::~IceBlock()
{
}
