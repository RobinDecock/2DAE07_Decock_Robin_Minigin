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
#include "SoundManager.h"
#include "TransformComponent.h"

BaseItem::~BaseItem()
{
	
}

void BaseItem::Initialize()
{
	ItemManager::GetInstance().AddItem(this);
	AddComponent(new RigidbodyComponent(false));
	BoxCollider *pBoxC = new BoxCollider(glm::vec2(8, 4),glm::vec2(0,7));
	pBoxC->SetCategory(LayerMask::None);
	pBoxC->SetIgnoreMask(LayerMask::Player | LayerMask::Bubbles | LayerMask::Enemies | LayerMask::Roof);
	AddComponent(pBoxC);
	BoxTrigger* pBoxT = new BoxTrigger(glm::vec2(4, 4));
	AddComponent(pBoxT);
	m_Tag = "Item";
	
	this->AddContactCallback([this](b2Fixture* thisFix, b2Fixture* otherFix, b2Contact* contact, ContactType type)
		{
			UNREF(contact);
			UNREF(thisFix);
			if(type==ContactType::BeginContact&& (otherFix->GetFilterData().categoryBits&LayerMask::Player)==LayerMask::Player)
			{
				if(pickedup)
				{
					__debugbreak();
				}
				
				pickedup = true;
				Bub* bubRef = static_cast<Bub*>(otherFix->GetUserData());
				bubRef->AddScore(scoreValue);
				ItemManager::GetInstance().RemoveItem(this);
				ScoreAnnouncer* announcer = new ScoreAnnouncer(scoreValue);
				m_ParentScene->Add(announcer);
				announcer->SetPosition(m_Transform->Get2DPosition());
				SoundManager::PlayFX("../BubbleBobble/Resources/Audio/ItemPickUpSound.wav");
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
