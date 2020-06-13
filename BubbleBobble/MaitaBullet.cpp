#include "ProjectPCH.h"
#include "MaitaBullet.h"



#include "AnimLoader.h"
#include "AutoDestroyComponent.h"
#include "BoxTrigger.h"
#include "Bub.h"
#include "BubbleBobble.h"
#include "RigidbodyComponent.h"
#include "TextureComponent.h"

void MaitaBullet::Initialize()
{
	auto pTexC = new TextureComponent("Enemies.png");
	AddComponent(pTexC);
	pTexC->SetSourceRectangle(Anim::Loader::Load("../BubbleBobble/Resources/Enemies.anim")[6].Src);
	pTexC->SetFlip(m_IsRight);
	AddComponent(new AutoDestroyComponent(4.0f));
	
	m_pRigid = new RigidbodyComponent(false);
	AddComponent(m_pRigid);
	AddComponent(new BoxTrigger({ 10,10 }));

	this->AddContactCallback([this](b2Fixture* thisFix, b2Fixture* other, b2Contact* contact, ContactType type)
		{
			if (type == ContactType::BeginContact)
			{

				if ((other->GetFilterData().categoryBits & LayerMask::Player) == LayerMask::Player)
				{
					Bub* pBub = static_cast<Bub*>(other->GetUserData());
					pBub->Attack();
				}
			}
		});
	
}

void MaitaBullet::PhysicsUpdate(float elapsedSec)
{
	m_pRigid->GetBody()->SetLinearVelocity(b2Vec2((m_IsRight ? 1.0f : -1.0f) * maxVelX,0));
}
