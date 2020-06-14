#include "ProjectPCH.h"
#include "PlayerCommands.h"

#include "RigidbodyComponent.h"
#include "Bubble.h"
#include "Bub.h"
#include "EffectorComponent.h"
#include "TransformComponent.h"
#include "GameScene.h"
#include "BoxCollider.h"
#include "SoundManager.h"

void PC::GoDown::Execute(float elapsedSec,float axisValue)
{
	UNREF(elapsedSec);
	if(axisValue<-0.1f)
	{
		if (m_pBub->m_pPlatformEff != nullptr)
		{
			m_pBub->m_pPlatformEff->AddIgnore(m_pBub->m_pBoxCol->GetFixture());
		}
	}
}

void PC::Jump::Execute(float elapsedSec)
{
	UNREF(elapsedSec);
	SoundManager::PlayFX("../BubbleBobble/Resources/Audio/BubJumpSound.wav");
	RigidbodyComponent* rigid = m_pBub->m_pRigid;
	float impulse = rigid->GetBody()->GetMass() * -200;
	rigid->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	rigid->GetBody()->ApplyLinearImpulse(b2Vec2(0, impulse), rigid->GetBody()->GetWorldCenter(), true);
}

void PC::MoveHorizontal::Execute(float elapsedSec, float axisValue)
{
	UNREF(elapsedSec);
	RigidbodyComponent* rigid = m_pBub->m_pRigid;
	b2Vec2 vel = rigid->GetBody()->GetLinearVelocity();

	float scale = m_pBub->m_IsOnGround ? 1.0f : 0.5f;
	
	vel.x += ((axisValue>0)?1:-1 )* m_pBub->m_MaxXVel* scale;

	if(abs(vel.x)* m_pBub->m_MaxXVel)
	{
		vel.x = ((axisValue > 0) ? 1 : -1)*m_pBub->m_MaxXVel;
	}
	
	m_pBub->m_IsRight = axisValue > 0;
	rigid->GetBody()->SetLinearVelocity(vel);
}

void PC::ShootBubble::Execute(float elapsedSec)
{
	UNREF(elapsedSec);
	m_pBub->m_Blackboard.SetKeyValue((int)Bub::BKey::IsBurping, true);
	Bubble* bubble = new Bubble(m_pBub->m_IsRight,m_pBub->m_PlayerId);
	bubble->SetPosition(m_pBub->GetTransform()->GetPosition());
	m_pBub->GetScene()->Add(bubble);
}
