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
#include "GameScene.h"
#include "TransformComponent.h"
#include "LevelSegment.h"
#include "Utils.h"

Zen::Zen(LevelSegment* segment) :BaseEnemy(segment)
{
	
}

Zen::~Zen()
{
	SafeDelete(m_pInputHandler);
}

void Zen::Initialize()
{
	BaseEnemy::Initialize();
	
	m_pRigid =new RigidbodyComponent();
	AddComponent(m_pRigid);
	m_pRigid->SetGravityScale(6.0f);
	
	m_pBoxCol = new BoxCollider(glm::vec2(14, 14));
	m_pBoxCol->SetCategory(LayerMask::Enemies);
	m_pBoxCol->SetIgnoreMask(LayerMask::Player|LayerMask::Enemies|LayerMask::Roof);
	AddComponent(m_pBoxCol);
	m_pBoxCol->SetFriction(0);
	
	auto pTrigger = new BoxTrigger(glm::vec2(14, 14));
	AddComponent(pTrigger);
	pTrigger->SetCategory(LayerMask::Enemies);
	//pTrigger->SetIgnoreMask(LayerMask::Player|LayerMask::Bubbles);
	m_pSprite = new SpriteComponent("Enemies.png");
	AddComponent(m_pSprite);
	
	//STATES
	auto pRoot =  new AnimatorState(0,"ZenChan");

	m_pAnimator = new Animator(m_pSprite, pRoot, m_Blackboard);
	AddComponent(m_pAnimator);
	auto pBubbled = new AnimatorState(3,"ZenChanBubble");
	m_pAnimator->AddState(pBubbled);

	std::map<int, AnimData> animData = Anim::Loader::Load("../BubbleBobble/Resources/Enemies.anim");
	
	m_pAnimator->SetAnimData(animData);

	////BLACKBOARD KEYS
	m_Blackboard.AddKey((int)BlackboardKey::InBubble,ValueType::boolValue);
	////LINKS
	m_pAnimator->LinkStates(pRoot, pBubbled, Req((int)BlackboardKey::InBubble, true));
	m_pAnimator->LinkStates(pBubbled, pRoot, Req((int)BlackboardKey::InBubble, false));
}



void Zen::Update(float elapsedSec)
{
	BaseEnemy::Update(elapsedSec);
	
	m_pSprite->SetFlip(m_IsRight);

	glm::vec2 pos = m_Transform->Get2DPosition();
	
	auto groundRaycast = RaycastCallback(LayerMask::Platform | LayerMask::Ground);
	m_ParentScene->RayCast(&groundRaycast, make_b2Vec2(pos), make_b2Vec2(pos + glm::vec2(-8, 10)));

	if(!groundRaycast.hasHit())
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

	if(roofRaycast.hasHit())
	{
		m_pRoof = static_cast<GameObject*>(roofRaycast.GetFixHit()->GetUserData());
	}

	m_IsRight = m_pRigid->GetVelocity().x > 0.0f;
}



void Zen::HandleAI(float elapsedSec)
{
}

void Zen::SetControlled(int PlayerId)
{
	BaseEnemy::SetControlled(PlayerId);

	m_pInputHandler = new InputHandler();
	
	//SET INPUTS
	const std::map<KeyAction, ButtonInput> keyMap = S_ButtonMap.at(PlayerId);
	const std::map<AxisAction, AxisInput> axisMap = S_AxisMap.at(PlayerId);

	
	//KEYBOARD
	m_pInputHandler->AddInputButton(keyMap.at(KeyAction::K_Key1), m_pJumpC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::K_StickV), m_pGoDownC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::K_StickH), m_pMoveHC);

	//CONTROLLER
	m_pInputHandler->AddInputButton(keyMap.at(KeyAction::C_Key1), m_pJumpC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::C_StickV), m_pGoDownC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::C_StickH), m_pMoveHC);
}
