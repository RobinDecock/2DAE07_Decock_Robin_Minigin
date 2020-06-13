#include "ProjectPCH.h"
#include "BaseEnemy.h"

#include "BaseItem.h"
#include "LevelSegment.h"
#include "TransformComponent.h"
#include "Bub.h"
#include "BubbleBobble.h"
#include "BoxCollider.h"
#include "Utils.h"
#include "SpriteComponent.h"
BaseEnemy::BaseEnemy(LevelSegment* segment)
{
	m_pLevelSegment = segment;
}

BaseEnemy::~BaseEnemy()
{
	SafeDelete(m_pCurrentState);

}

void BaseEnemy::SetBubbled(bool b)
{
	m_Blackboard.SetKeyValue((int)BlackboardKey::InBubble, b);
	if(b)
	{
		m_pRigid->SetGravityScale(-1.0f);
		m_pRigid->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		m_IsBubbled = true;
		m_pBoxCol->SetIgnoreMask(LayerMask::Player | LayerMask::Enemies);
	}
	else
	{
		m_pRigid->SetGravityScale(6.0f);
		m_pRigid->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		m_IsBubbled = false;
		m_pBoxCol->SetIgnoreMask(LayerMask::Player | LayerMask::Enemies|LayerMask::Roof);
	}
}

void BaseEnemy::Initialize()
{
	this->AddContactCallback([this](b2Fixture* thisFix, b2Fixture* otherFix, b2Contact* contact, ContactType type)
		{
			GameObject* other = static_cast<GameObject*>(otherFix->GetUserData());
			if (type != ContactType::BeginContact||isPaused)return;
			if (other->GetTag() == "PC")
			{
				if (type == ContactType::BeginContact)
				{
					Bub* bub = static_cast<Bub*>(other);
					if (m_IsBubbled)
					{
						singleScene = static_cast<SingleScene*>(m_ParentScene);
						DropItem();
						m_pLevelSegment->RemoveEnemy(this);
					}
					else
					{
						bub->Attack();
						lockedPlayer = nullptr;
					}
				}
				else if (type == ContactType::EndContact)
				{
					lockedPlayer = nullptr;
				}
			}

		}
	);
}


void BaseEnemy::Update(float elapsedSec)
{
	if (isPaused||m_IsBubbled)return;

}



void BaseEnemy::PhysicsUpdate(float elapsedSec)
{
	if (m_IsBubbled)
	{
		m_BubbledTimer += elapsedSec;
		if (m_BubbledTimer >= m_BubbledDelay)
		{
			SetBubbled(false);
			m_BubbledTimer = 0.0f;
		}
		return;
	}
	
	if (isPaused || m_IsBubbled)return;

	m_pSprite->SetFlip(m_IsRight);

	glm::vec2 pos = m_Transform->Get2DPosition();

	auto groundRaycast = RaycastCallback(LayerMask::Platform | LayerMask::Ground);
	m_ParentScene->RayCast(&groundRaycast, make_b2Vec2(pos), make_b2Vec2(pos + glm::vec2(-8, 10)));

	if (!groundRaycast.hasHit())
	{
		m_ParentScene->RayCast(&groundRaycast, make_b2Vec2(pos), make_b2Vec2(pos + glm::vec2(8, 10)));
	}

	m_IsOnGround = groundRaycast.hasHit();

	auto wallRaycast = RaycastCallback(LayerMask::Ground | LayerMask::Platform);
	glm::vec2 beginPoint = pos + glm::vec2(0, -5);
	m_ParentScene->RayCast(&wallRaycast, make_b2Vec2(beginPoint), make_b2Vec2(beginPoint + glm::vec2((m_IsRight ? 1 : -1) * (viewDist / 3.0f), 0)));
	foundWall = wallRaycast.hasHit();



	if (groundRaycast.m_CategoryHit == LayerMask::Platform)
	{
		GameObject* platform = static_cast<GameObject*>(groundRaycast.GetFixHit()->GetUserData());
		m_OnPlatform = platform;
	}
	else
	{
		m_OnPlatform = nullptr;
	}




	auto roofRaycast = RaycastCallback(LayerMask::Platform);
	m_ParentScene->RayCast(&roofRaycast, make_b2Vec2(pos), make_b2Vec2(pos + glm::vec2(0, -40)));

	if (roofRaycast.hasHit())
	{
		m_pRoof = static_cast<GameObject*>(roofRaycast.GetFixHit()->GetUserData());
	}

	
	m_pRigid->GetBody()->SetLinearVelocity(b2Vec2(0, m_pRigid->GetBody()->GetLinearVelocity().y));
	
	State * state = m_pCurrentState->Execute(elapsedSec);

	if(state!=nullptr)
	{
		delete m_pCurrentState;
		m_pCurrentState = state;
	}
	

	if (m_IsControlled&& m_pInputHandler!=nullptr)
	{
		m_pInputHandler->HandleInput(elapsedSec);
	}
	else
	{
		HandleAI(elapsedSec);
	}
	m_IsRight = m_pRigid->GetVelocity().x > 0.0f;
}


void BaseEnemy::DropItem()
{
	ItemType randValue = ItemType(rand() % 2);

	BaseItem* item = nullptr;
	switch (randValue)
	{
	case ItemType::Melon:
		item = new Melon();
		break;
	case ItemType::Fries:
		item = new Fries();
		break;
	default:;
	}

	item->SetPosition(m_Transform->Get2DPosition());
	m_ParentScene->Add(item);
}
