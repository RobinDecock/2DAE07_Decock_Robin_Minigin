#include "ProjectPCH.h"
#include "EnemyCommands.h"

#include "RigidbodyComponent.h"
#include "BaseEnemy.h"
#include "EffectorComponent.h"
#include "BoxCollider.h"
#include "MaitaBullet.h"
#include "Maita.h"
#include "TransformComponent.h"
void EC::MoveHorizontal::execute(float elapsedSec, float axisValue)
{
	RigidbodyComponent* rigid = m_pEnemy->GetComponent<RigidbodyComponent>();
	float maxVelX = m_pEnemy->GetMaxVelX();
	b2Vec2 vel = rigid->GetBody()->GetLinearVelocity();
	vel.x += ((axisValue > 0) ? 1.0f : -1.0f) * maxVelX;
	
	rigid->GetBody()->SetLinearVelocity(vel);
}

void EC::Jump::execute(float elapsedSec)
{
	if (m_pEnemy->GetIsOnGround())
	{
		RigidbodyComponent* rigid = m_pEnemy->GetComponent<RigidbodyComponent>();
		float impulse = rigid->GetBody()->GetMass() * -m_pEnemy->GetJumpStrength();
		rigid->GetBody()->ApplyLinearImpulse(b2Vec2(0, impulse), rigid->GetBody()->GetWorldCenter(), true);
	}
}





void EC::Shoot::execute(float elapsedSec)
{
	MaitaBullet* bubble = new MaitaBullet(m_pEnemy->IsRight());
	bubble->SetPosition(m_pEnemy->GetTransform()->GetPosition());
	m_pEnemy->GetScene()->Add(bubble);
}

void EC::GoDown::execute(float elapsedSec, float axisValue)
{
	if (axisValue < -0.1f)
	{
		if (m_pEnemy->m_OnPlatform != nullptr)
		{
			std::cout << "Added Ignore" << std::endl;
			m_pEnemy->m_OnPlatform->GetComponent<EffectorComponent>()->AddIgnore(m_pEnemy->m_pBoxCol->GetFixture());
		}
	}
}
