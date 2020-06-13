#include "ProjectPCH.h"
#include "EnemyStates.h"
#include "BaseEnemy.h"
#include "BubbleBobble.h"
#include "EnemyCommands.h"
#include "Utils.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "EffectorComponent.h"
#include "Maita.h"
State *WanderState::Execute(float elapsedSec)
{
	glm::vec2 pos = m_pEnemy->GetTransform()->Get2DPosition();

	auto playerRaycast = RaycastCallback(LayerMask::Player);
	const float& viewDist = m_pEnemy->viewDist;

	const bool& isRight = m_pEnemy->m_IsRight;
	m_pEnemy->GetScene()->RayCast(&playerRaycast, make_b2Vec2(pos), make_b2Vec2(pos + glm::vec2((isRight ? 1 : -1) * viewDist, 0)));
	if (playerRaycast.hasHit())
	{
		auto lockedPlayer = static_cast<Bub*>(playerRaycast.GetFixHit()->GetUserData());

		switch(m_pEnemy->m_EnemyType)
		{
		case BaseEnemy::EnemyType::Maita:
			return new PursuePlayerAndShoot(m_pEnemy, lockedPlayer);
		case BaseEnemy::EnemyType::ZenChan:
			return new PursuePlayer(m_pEnemy, lockedPlayer);
		}
		
	}

#pragma region WalkLogic
	RigidbodyComponent* m_pRigid = m_pEnemy->m_pRigid;
	const float & velY = m_pRigid->GetBody()->GetLinearVelocity().y;
	
	const bool& foundWall = m_pEnemy->foundWall&m_pEnemy->m_IsOnGround;

	bool& goingRight = m_pEnemy->m_GoingRight;
	
	if (m_WalkDelay == -1 || foundWall)
	{
		
		if (foundWall)
		{
			goingRight = !goingRight;
		}
		else
		{
			goingRight = rand() % 2;
		}

		const float& maxDelay = m_pEnemy->m_MaxWalkDelay;
		const float& minDelay = m_pEnemy->m_MinWalkDelay;
		m_WalkDelay = (rand() % ((int)((maxDelay - minDelay) * 10.0f))) / 10.0f + minDelay;
	}

	if (m_WalkTimer > m_WalkDelay)
	{
		m_WalkTimer = 0.0f;
		m_WalkDelay = -1.0f;
	}
	else
	{
		m_WalkTimer += elapsedSec;
		const float& m_MaxVelocity = m_pEnemy->m_MaxXVelocity;
		m_pRigid->GetBody()->SetLinearVelocity(b2Vec2((goingRight ? 1 : -1) * m_MaxVelocity, velY));
	}
#pragma  endregion 

#pragma region JumpFallLogic
	//Jump Fall Logic
	const GameObject* pRoof = m_pEnemy->m_pRoof;
	const GameObject* m_OnPlatform = m_pEnemy->m_OnPlatform;

	float& jumpTimer = m_pEnemy->m_JumpTimer;
	const float& jumpDelay = m_pEnemy->m_JumpDelay;



	if (jumpTimer > jumpDelay)
	{
		jumpTimer = 0.0f;

		if (pRoof != nullptr && m_OnPlatform != nullptr)
		{
			int random = rand() % 3;

			if (random == 0 || random == 1)
			{
				//Jump
				EC::Jump JumpC = m_pEnemy->m_pJumpC;
				JumpC.execute(elapsedSec);
			}
			else
			{
				//FallDown
				EC::GoDown GoDownC = m_pEnemy->m_pGoDownC;
				GoDownC.execute(elapsedSec, -1.0f);
			}

		}
		else if (pRoof != nullptr)
		{
			EC::Jump JumpC = m_pEnemy->m_pJumpC;
			JumpC.execute(elapsedSec);
		}
		else if (m_OnPlatform != nullptr)
		{
			EC::GoDown GoDownC = m_pEnemy->m_pGoDownC;
			GoDownC.execute(elapsedSec, -1.0f);
		}
	}
	else
	{
		jumpTimer += elapsedSec;
	}
#pragma endregion
	return nullptr;
}

State *PursuePlayer::Execute(float elapsedSec)
{
	RigidbodyComponent* m_pRigid = m_pEnemy->m_pRigid;
	const float& maxVelocity = m_pEnemy->m_MaxXVelocity;

	float& jumpTimer = m_pEnemy->m_JumpTimer;
	const float& jumpDelay = m_pEnemy->m_JumpDelay;
	
	glm::vec2 playerPos = m_pLockedPlayer->GetTransform()->Get2DPosition();


	glm::vec2 pos = m_pEnemy->GetTransform()->Get2DPosition();
	glm::vec2 diff = playerPos - pos;
	int xDir = ((pos.x - playerPos.x) <= 0) ? 1 : -1;

	b2Vec2 vel = m_pRigid->GetBody()->GetLinearVelocity();
	vel.x = float(xDir * maxVelocity);
	
	m_pRigid->GetBody()->SetLinearVelocity(vel);



	auto playerRaycast = RaycastCallback(LayerMask::Player);
	const float& viewDist = m_pEnemy->viewDist;

	const bool& isRight = m_pEnemy->m_IsRight;
	m_pEnemy->GetScene()->RayCast(&playerRaycast, make_b2Vec2(pos), make_b2Vec2(pos + glm::vec2((isRight ? 1 : -1) * viewDist, 0)));
	if (playerRaycast.hasHit())
	{
		Bub * detectedPlayer= static_cast<Bub*>(playerRaycast.GetFixHit()->GetUserData());
		if(detectedPlayer==m_pEnemy->lockedPlayer)
		{
			m_LockedTimer = 0.0f;
		}
	}

	

	const bool& onGround = m_pEnemy->GetIsOnGround();
	GameObject* pOnPlatform = m_pEnemy->m_OnPlatform;
	if (onGround)
	{
		if (diff.y < -10 && jumpTimer>jumpDelay)
		{
			EC::Jump& JumpC = m_pEnemy->m_pJumpC;
			JumpC.execute(elapsedSec);
			jumpTimer = 0.0f;
			
		}
		else if (diff.y > 10&& pOnPlatform !=nullptr)
		{
			EC::GoDown& GoDownC = m_pEnemy->m_pGoDownC;
			GoDownC.execute(elapsedSec, -1.0f);
			jumpTimer = 0.0f;
		}
		
	}
	
	if (jumpTimer < jumpDelay)
	{
		jumpTimer += elapsedSec;

	}


	m_LockedTimer += elapsedSec;
	const float& lockedDelay = m_pEnemy->m_LockedDelay;
	if (m_LockedTimer >= lockedDelay)
	{
		return new WanderState(m_pEnemy);
	}
	
	return nullptr;
}

PursuePlayerAndShoot::PursuePlayerAndShoot(BaseEnemy* pEnemy, Bub* lockedPlayer) : PursuePlayer(pEnemy, lockedPlayer)
{
	Maita* mp = static_cast<Maita*>(m_pEnemy);
	m_ShootTimer = mp->m_ShootDelay;
}

State* PursuePlayerAndShoot::Execute(float elapsedSec)
{
	State* state = PursuePlayer::Execute(elapsedSec);
	if(state!=nullptr)
	{
		return state;
	}

	Maita* mp = static_cast<Maita*>(m_pEnemy);
	const float& shootDelay = mp->m_ShootDelay;

	std::cout << "ShootTimer" << m_ShootTimer << std::endl;
	if(m_ShootTimer>shootDelay)
	{
		ButtonCommand& ShootC = mp->m_pShootC;
		ShootC.execute(elapsedSec);
		m_ShootTimer = 0.0f;
	}
	else
	{
		m_ShootTimer += elapsedSec;
	}
	return nullptr;
	
}
