#include "ProjectPCH.h"
#include "Zen.h"
#include "AnimatorState.h"
#include "AnimLoader.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "BaseItem.h"
#include "BoxTrigger.h"
#include "Bub.h"
#include "BubbleBobble.h"
#include "EffectorComponent.h"
#include "GameScene.h"
#include "TransformComponent.h"
#include "LevelSegment.h"
#include "Utils.h"

Zen::Zen(LevelSegment* segment)
{
	m_pLevelSegment = segment;
}

Zen::~Zen()
{
	Melon* melon = new Melon();
	melon->SetPosition(m_Transform->Get2DPosition());
	m_ParentScene->Add(melon);
	m_pLevelSegment->Remove(this);
}

void Zen::Initialize()
{
	m_pRigid = NEW(RigidbodyComponent)();
	AddComponent(m_pRigid);
	m_pBoxCol = NEW(BoxCollider)(glm::vec2(14, 14));
	AddComponent(m_pBoxCol);
	m_pBoxCol->SetCategory(LayerMask::Enemies);

	auto pTrigger = NEW(BoxTrigger)(glm::vec2(28, 28));
	AddComponent(pTrigger);
	pTrigger->SetCategory(LayerMask::Enemies);
	pTrigger->SetIgnoreMask(LayerMask::Player|LayerMask::Bubbles);

	
	//STATES
	auto pRoot = NEW(AnimatorState)(0,"ZenChan");
	auto pBubbled = NEW(AnimatorState)(3,"ZenChanBubble");
	m_pSprite = std::make_shared<SpriteComponent>("Enemies.png");
	AddComponent(m_pSprite);
	m_pAnimator = std::make_shared<Animator>(m_pSprite,pRoot, m_Blackboard);
	AddComponent(m_pAnimator);

	std::map<int, AnimData> animData = AnimLoader::Load("../BubbleBobble/Resources/Enemies.anim");
	
	m_pAnimator->SetAnimData(animData);

	////BLACKBOARD KEYS
	m_Blackboard.AddKey((int)BlackboardKey::InBubble,ValueType::boolValue);
	////LINKS
	m_pAnimator->LinkStates(pRoot, pBubbled, Req((int)BlackboardKey::InBubble, true));
	m_pAnimator->LinkStates(pBubbled, pRoot, Req((int)BlackboardKey::InBubble, false));


	this->AddContactCallback([this](b2Fixture *thisFix, b2Fixture* otherFix, b2Contact* contact, ContactType type)
		{
			
			GameObject* other = static_cast<GameObject*>(otherFix->GetUserData());
			if (type != ContactType::BeginContact)return;
			if (!m_IsBubbled&&other->GetTag() == "Bubble")
			{
				m_ParentScene->Remove(other);
				m_pRigid->SetGravityScale(0.0f);
				m_pRigid->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
				m_IsBubbled = true;
			}
			else if (other->GetTag() == "PC")
			{
				if(type == ContactType::BeginContact)
				{
					lockedPlayer = other;
					m_Behaviour = Behaviour::Locked;
					if (m_IsBubbled)
					{
						m_ParentScene->Remove(this, true);
					}
					else
					{
						static_cast<Bub*>(other)->Attack();
					}
				}
				else if(type ==ContactType::EndContact)
				{
					lockedPlayer = nullptr;
					m_Behaviour = Behaviour::Wandering;
				}
			}
		
		}
	);
}



void Zen::Update(float elapsedSec)
{
	BaseEnemy::Update(elapsedSec);
	
	m_pSprite->SetFlip(m_IsRight);
	m_Blackboard.SetKeyValue((int)BlackboardKey::InBubble, m_IsBubbled);
	glm::vec2 pos = m_Transform->Get2DPosition();
	
	auto groundRaycast = RaycastCallback(LayerMask::Platform | LayerMask::Ground);
	m_ParentScene->RayCast(&groundRaycast, make_b2Vec2(pos), make_b2Vec2(pos + glm::vec2(0, 10)));
	m_IsOnGround = groundRaycast.hasHit();

	if (groundRaycast.m_CategoryHit == LayerMask::Platform)
	{
		GameObject* platform = static_cast<GameObject*>(groundRaycast.GetFixHit()->GetUserData());
		m_OnPlatform = platform;
	}
	else
	{
		m_OnPlatform = nullptr;
	}
	
	m_IsRight = m_pRigid->GetVelocity().x > 0.0f;
}

void Zen::LateUpdate(float elapsedSec)
{
}

void Zen::Draw()
{

}


void Zen::HandleInput(float elapsedSec)
{
}

void Zen::HandleAI(float elapsedSec)
{
	//Check FOV for PC
	glm::vec2 pos = m_Transform->Get2DPosition();
	auto PlayerDetectRaycast = RaycastCallback(LayerMask::Player);
	float viewDist = 50.0f;
	m_ParentScene->RayCast(&PlayerDetectRaycast, make_b2Vec2(pos), make_b2Vec2(pos + glm::vec2((m_IsRight ? 1 : -1) * viewDist, 0)));
	if (PlayerDetectRaycast.hasHit())
	{
		lockedPlayer = static_cast<Bub*>(PlayerDetectRaycast.GetFixHit()->GetUserData());
		m_Behaviour = Locked;
	}

	//Use Behaviours
	if (m_Behaviour == Behaviour::Wandering)
	{
		if (m_IsOnGround)
		{
			if (walkDelay == -1)
			{
				walkDelay = (rand() % ((int)((maxDelay - minDelay) * 10.0f))) / 10.0f + minDelay;
			}

			if (walkTimer > walkDelay)
			{
				walkTimer = 0.0f;
				walkDelay = -1.0f;
				currVelocity = (2 * (rand() % 2) - 1) * m_MaxVelocity;
			}

			b2Vec2 vel = m_pRigid->GetBody()->GetLinearVelocity();
			vel.x = currVelocity;
			m_pRigid->GetBody()->SetLinearVelocity(vel);
		}
	}
	else if (m_Behaviour == Behaviour::Locked)
	{
		b2Vec2 vel = m_pRigid->GetBody()->GetLinearVelocity();

		glm::vec2 playerPos = lockedPlayer->GetTransform()->Get2DPosition();


		glm::vec2 pos = m_Transform->Get2DPosition();
		glm::vec2 diff = playerPos - pos;
		vel.x = ((pos.x - playerPos.x) < 0) ? m_MaxVelocity : -m_MaxVelocity;
		m_pRigid->GetBody()->SetLinearVelocity(vel);
		if (m_IsOnGround)
		{
			if (diff.y < -10 && jumpTimer>jumpDelay)
			{
				float impulse = m_pRigid->GetBody()->GetMass() * -30;
				m_pRigid->GetBody()->ApplyLinearImpulse(b2Vec2(0, impulse), m_pRigid->GetBody()->GetWorldCenter(), true);
				jumpTimer = 0.0f;
			}
			else if (diff.y > 10&&m_OnPlatform!=nullptr)
			{
				m_OnPlatform->GetComponent<EffectorComponent>()->AddIgnore(this->m_pBoxCol->GetFixture());
			}
		}
		if (jumpTimer < jumpDelay)
		{
			jumpTimer += elapsedSec;

		}
	}
}

void Zen::SetControlled(int PlayerId)
{
	m_pJumpC = new EC::Jump(this);
	m_pMoveHC = new EC::MoveHorizontal(this);
	m_pInputHandler = new InputHandler();

	//TODO MAKE STATIC MAP WITH CONTROLLER PER PLAYERID
	
	//KEYBOARD
	m_pInputHandler->AddInputButton(ButtonInput(KEY_UP), m_pJumpC);
	m_pInputHandler->AddInputAxis(AxisInput(KEY_RIGHT, KEY_LEFT), m_pMoveHC);

	//CONTROLLER
	m_pInputHandler->AddInputButton(ButtonInput(XINPUT_GAMEPAD_A, true),m_pJumpC);
	m_pInputHandler->AddInputAxis(AxisInput((int)JoyStick::LX), m_pMoveHC);
}
