#include "ProjectPCH.h"
#include "Bubble.h"
#include "Animator.h"
#include "AnimatorBlackboard.h"
#include "AnimatorState.h"
#include "AnimLoader.h"
#include "AutoDestroyComponent.h"
#include "BaseEnemy.h"
#include "BoxTrigger.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "BubbleBobble.h"
#include "EffectorComponent.h"
Bubble::Bubble(bool isRight,int playerId): m_PlayerId(playerId), m_IsRight(isRight)
{
	m_Tag = "Bubble";
}

Bubble::~Bubble()
{
}


void Bubble::Initialize()
{
	AddComponent(new AutoDestroyComponent(5.0f));
	m_pRigid = new RigidbodyComponent(false);
	AddComponent(m_pRigid);


	
	pBoxCol = new BoxCollider(glm::vec2(16, 16));
	AddComponent(pBoxCol);
	pBoxCol->SetCategory(LayerMask::Bubbles);
	pBoxCol->SetIgnoreMask(LayerMask::Enemies);


	//TEST
	auto pEffect = new EffectorComponent(pBoxCol, glm::vec2(0, -9), glm::vec2(4, 4));
	AddComponent(pEffect);
	pEffect->SetCategoryToAffect(LayerMask::Player);
	
	m_pBoxTrigger = new BoxTrigger(glm::vec2(14, 14));
	AddComponent(m_pBoxTrigger);
	m_pBoxTrigger->SetCategory(LayerMask::Bubbles);
	m_pBoxTrigger->SetActive(false);


	this->AddContactCallback([this](b2Fixture* thisFix, b2Fixture* other, b2Contact* contact, ContactType type)
		{
			if(type == ContactType::BeginContact &&((other->GetFilterData().categoryBits&LayerMask::Enemies)==LayerMask::Enemies))
			{
				auto pEnemy = static_cast<BaseEnemy*>(other->GetUserData());
				if(!pEnemy->IsBubbled())
				{
					pEnemy->SetBubbled(true);
					m_ParentScene->Remove(this);
				}
			}

		});



	
	m_pSprite = new SpriteComponent("Bub.png");
	AddComponent(m_pSprite);

	auto pBubble = new AnimatorState(6, "BubbleV1");

	m_pAnimator = new Animator(m_pSprite, pBubble, m_Blackboard);
	AddComponent(m_pAnimator);
	//STATES

	pBubble->SetLooping(false);
	pBubble->SetSpeed(3.0f);
	auto pBubbleExplode = new AnimatorState(7, "BubbleV2");
	m_pAnimator->AddState(pBubbleExplode);
	pBubbleExplode->SetLooping(false);
	pBubbleExplode->SetSpeed(10.0f);


	std::map<int, AnimData> animData = Anim::Loader::Load("../BubbleBobble/Resources/Bub"+ std::to_string(m_PlayerId)+".anim");
	m_pAnimator->SetAnimData(animData);

	//BLACKBOARD KEYS
	m_Blackboard.AddKey(int(BKey::IsExploding), ValueType::boolValue);

	//LINKS
	m_pAnimator->LinkStates(pBubble, pBubbleExplode, Req(int(BKey::IsExploding), true));

	m_pRigid->SetGravityScale(-2.0f);

}

void Bubble::LateInitialize()
{
	float impulse = m_pRigid->GetBody()->GetMass() * 500.0f * (m_IsRight ? 1.0f : -1.0f);
	m_pRigid->GetBody()->ApplyLinearImpulse(b2Vec2(impulse, 0), m_pRigid->GetBody()->GetWorldCenter() + b2Vec2(impulse, 0), true);
}

void Bubble::Update(float elapsedSec)
{	
	if(GetComponent<AutoDestroyComponent>()->timer>4.5f)
	{
		m_Blackboard.SetKeyValue((int)BKey::IsExploding, true);
	}
}