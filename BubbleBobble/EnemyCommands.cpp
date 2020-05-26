#include "ProjectPCH.h"
#include "EnemyCommands.h"

#include "RigidBodyComponent.h"
#include "BaseEnemy.h"
void EC::MoveHorizontal::execute(float elapsedSec, float axisValue)
{
	std::shared_ptr<RigidbodyComponent> rigid = m_pEnemy->GetComponent<RigidbodyComponent>();
	float maxVelX = m_pEnemy->GetMaxVelX();
	b2Vec2 vel = rigid->GetBody()->GetLinearVelocity();
	vel.x += axisValue * maxVelX * elapsedSec;

	if (abs(vel.x) > maxVelX)
	{
		vel.x = ((axisValue > 0) ?1 : -1)* maxVelX;
	}

	rigid->GetBody()->SetLinearVelocity(vel);
}

void EC::Jump::execute(float elapsedSec)
{
	if (m_pEnemy->GetIsOnGround())
	{
		std::shared_ptr<RigidbodyComponent> rigid = m_pEnemy->GetComponent<RigidbodyComponent>();
		float impulse = rigid->GetBody()->GetMass() * -90;
		rigid->GetBody()->ApplyLinearImpulse(b2Vec2(0, impulse), rigid->GetBody()->GetWorldCenter(), true);
	}
}

void EC::Shoot::execute(float elapsedSec)
{
	
}
