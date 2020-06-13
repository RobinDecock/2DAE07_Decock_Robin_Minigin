#include "ProjectPCH.h"
#include "PlayerCommands.h"

#include "RigidbodyComponent.h"
#include "Bubble.h"
#include "Bub.h"
#include "EffectorComponent.h"
#include "TransformComponent.h"
#include "GameScene.h"
#include "BoxCollider.h"

void PC::GoDown::execute(float elapsedSec,float axisValue)
{
	if(axisValue<-0.1f)
	{
		if (m_pBub->m_pPlatformEff != nullptr)
		{
			m_pBub->m_pPlatformEff->AddIgnore(m_pBub->m_pBoxCol->GetFixture());
		}
	}
}

void PC::Jump::execute(float elapsedSec)
{
	RigidbodyComponent* rigid = m_pBub->m_pRigid;
	float impulse = rigid->GetBody()->GetMass() * -90;
	rigid->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	rigid->GetBody()->ApplyLinearImpulse(b2Vec2(0, impulse), rigid->GetBody()->GetWorldCenter(), true);
}

void PC::MoveHorizontal::execute(float elapsedSec, float axisValue)
{
	RigidbodyComponent* rigid = m_pBub->m_pRigid;
	b2Vec2 vel = rigid->GetBody()->GetLinearVelocity();
	vel.x += ((axisValue>0)?1:-1 )* m_pBub->m_MaxXVel ;
	m_pBub->m_IsRight = axisValue > 0;
	rigid->GetBody()->SetLinearVelocity(vel);
}

void PC::ShootBubble::execute(float elapsedSec)
{
	m_pBub->m_Blackboard.SetKeyValue((int)Bub::BKey::IsBurping, true);
	Bubble* bubble = new Bubble(m_pBub->m_IsRight,m_pBub->m_PlayerId);
	bubble->SetPosition(m_pBub->GetTransform()->GetPosition());
	m_pBub->GetScene()->Add(bubble);
}
