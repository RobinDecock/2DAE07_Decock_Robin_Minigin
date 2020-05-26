#include "ProjectPCH.h"
#include "Bubble.h"
#include "Animator.h"
#include "AnimatorBlackboard.h"
#include "AnimatorState.h"
#include "AnimLoader.h"
#include "AutoDestroyComponent.h"
#include "BoxTrigger.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "BubbleBobble.h"
AnimatorState* tryied;


Bubble::Bubble(bool isRight,int playerId): m_IsRight(isRight), m_PlayerId(playerId)
{
	m_Tag = "Bubble";
}

Bubble::~Bubble()
{
}


void Bubble::Initialize()
{
	AddComponent(NEW(AutoDestroyComponent)(5.0f));
	m_pRigid = std::make_shared<RigidbodyComponent>(false);
	AddComponent(m_pRigid);

	auto pBoxCol = std::make_shared<BoxCollider>(glm::vec2(16, 16));
	AddComponent(pBoxCol);
	pBoxCol->SetCategory(LayerMask::Bubbles);
	pBoxCol->SetIgnoreMask(LayerMask::Player|LayerMask::Enemies);

	m_pBoxTrigger = std::make_shared<BoxTrigger>(glm::vec2(14, 14));
	AddComponent(m_pBoxTrigger);
	m_pBoxTrigger->SetActive(false);


	this->AddContactCallback([this](b2Fixture* thisFix, b2Fixture* other, b2Contact* contact, ContactType type)
		{
			if(thisFix== m_pBoxTrigger->GetFixture())
			{
				if(other->GetFilterData().categoryBits==LayerMask::Player&& GetComponent<AutoDestroyComponent>()->timer > 1.0f)
				{
					m_Blackboard.SetKeyValue((int)BlackboardKey::IsExploding, true);
				}
			}
		});



	
	m_pSprite = std::make_shared<SpriteComponent>("Bub.png");
	AddComponent(m_pSprite);

	//STATES
	auto pBubble = NEW( AnimatorState)(6, "BubbleV1");
	pBubble->SetLooping(false);
	pBubble->SetSpeed(3.0f);
	auto pBubbleExplode = NEW(AnimatorState)(7, "BubbleV2");
	pBubbleExplode->SetLooping(false);
	pBubbleExplode->SetSpeed(10.0f);
	m_pAnimator = std::make_shared<Animator>(m_pSprite,pBubble, m_Blackboard);
	AddComponent(m_pAnimator);

	std::map<int, AnimData> animData = AnimLoader::Load("../BubbleBobble/Resources/Bub"+ std::to_string(m_PlayerId)+".anim");
	m_pAnimator->SetAnimData(animData);

	//BLACKBOARD KEYS
	m_Blackboard.AddKey((int)BlackboardKey::IsExploding, ValueType::boolValue);

	//LINKS
	m_pAnimator->LinkStates(pBubble, pBubbleExplode, Req((int)BlackboardKey::IsExploding, true));

	m_pRigid->SetGravityScale(-2.0f);

}

void Bubble::LateInitialize()
{
	float impulse = m_pRigid->GetBody()->GetMass() * 500 * (m_IsRight ? 1 : -1);
	m_pRigid->GetBody()->ApplyLinearImpulse(b2Vec2(impulse, 0), m_pRigid->GetBody()->GetWorldCenter() + b2Vec2(impulse, 0), true);
}

void Bubble::Update(float elapsedSec)
{	
	if(GetComponent<AutoDestroyComponent>()->timer>4.5f)
	{
		m_Blackboard.SetKeyValue((int)BlackboardKey::IsExploding, true);
	}
}

void Bubble::LateUpdate(float elapsedSec)
{}

void Bubble::Draw()
{}
