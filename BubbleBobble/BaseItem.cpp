#include "ProjectPCH.h"
#include "BaseItem.h"

#include "SingleScene.h"
#include "Hud.h"
#include "BoxCollider.h"
#include "RigidbodyComponent.h"
#include "TextureComponent.h"
#include "Utils.h"
#include "ScoreAnnouncer.h"
#include "TransformComponent.h"
BaseItem::~BaseItem()
{
	ScoreAnnouncer* announcer = new ScoreAnnouncer(500);
	announcer->SetPosition(m_Transform->Get2DPosition());
	m_ParentScene->Add(announcer);
}

void BaseItem::Initialize()
{
	AddComponent(NEW(RigidbodyComponent)(false));
	PTR(BoxCollider) pBoxC = NEW(BoxCollider)(glm::vec2(8, 8));
	AddComponent(pBoxC);
	m_Tag = "Item";
	
	this->AddContactCallback([this](b2Fixture* thisFix, b2Fixture* otherFix, b2Contact* contact, ContactType type)
		{
			GameObject* other = static_cast<GameObject*>(otherFix->GetUserData());
			if(other->GetTag()=="PC")
			{
				SingleScene*scene = static_cast<SingleScene*>(m_ParentScene);
				scene->GetHud()->AddScore(scoreValue);
				m_ParentScene->Remove(this,true);
			}
		}
	);
}
void Fries::Initialize()
{
	PTR(TextureComponent) pTexComp = NEW(TextureComponent)("Enemies.png");
	AnimData animData = AnimLoader::Load("../BubbleBobble/Resources/Enemies.anim")[5];
	pTexComp->SetSourceRectangle(make_SDL_Rect(animData.Src));
	AddComponent(pTexComp);

	BaseItem::Initialize();
}

void Melon::Initialize()
{
	PTR(TextureComponent) pTexComp = NEW(TextureComponent)("Enemies.png");
	AnimData animData = AnimLoader::Load("../BubbleBobble/Resources/Enemies.anim")[4];
	pTexComp->SetSourceRectangle(make_SDL_Rect(animData.Src));
	AddComponent(pTexComp);


	BaseItem::Initialize();
}
