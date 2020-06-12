#include "ProjectPCH.h"
#include "BaseItem.h"

#include "SingleScene.h"
#include "Hud.h"
#include "BoxCollider.h"
#include "BoxTrigger.h"
#include "BubbleBobble.h"
#include "RigidbodyComponent.h"
#include "TextureComponent.h"
#include "Utils.h"
#include "ScoreAnnouncer.h"
#include "AnimLoader.h"
#include "ItemManager.h"
#include "TransformComponent.h"

void BaseItem::PickUp()
{
	ScoreAnnouncer* announcer = new ScoreAnnouncer(500);
	announcer->SetPosition(m_Transform->Get2DPosition());

	m_ParentScene->Add(announcer);
	ItemManager::GetInstance().RemoveItem(this);
	
}

void BaseItem::Initialize()
{
	ItemManager::GetInstance().AddItem(this);
	AddComponent(new RigidbodyComponent(false));
	BoxCollider *pBoxC = new BoxCollider(glm::vec2(4, 8));
	pBoxC->SetIgnoreMask(LayerMask::Player|LayerMask::Bubbles|LayerMask::Enemies);
	AddComponent(pBoxC);
	BoxTrigger* pBoxT = new BoxTrigger(glm::vec2(8, 8));
	AddComponent(pBoxT);
	m_Tag = "Item";
	
	this->AddContactCallback([this](b2Fixture* thisFix, b2Fixture* otherFix, b2Contact* contact, ContactType type)
		{
			if(type==ContactType::BeginContact&& (otherFix->GetFilterData().categoryBits&LayerMask::Player)==LayerMask::Player)
			{
				SingleScene*scene = static_cast<SingleScene*>(m_ParentScene);
				scene->GetHud()->AddScore(scoreValue);
				PickUp();
			}
		}
	);
}
void Fries::Initialize()
{
	TextureComponent* pTexComp = new TextureComponent("Enemies.png");
	AnimData animData = Anim::Loader::Load("../BubbleBobble/Resources/Enemies.anim")[5];
	pTexComp->SetSourceRectangle(make_SDL_Rect(animData.Src));
	AddComponent(pTexComp);

	BaseItem::Initialize();
}

void Melon::Initialize()
{
	TextureComponent* pTexComp = new TextureComponent("Enemies.png");
	AnimData animData = Anim::Loader::Load("../BubbleBobble/Resources/Enemies.anim")[4];
	pTexComp->SetSourceRectangle(make_SDL_Rect(animData.Src));
	AddComponent(pTexComp);


	BaseItem::Initialize();
}
