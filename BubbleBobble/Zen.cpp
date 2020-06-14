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
	m_EnemyType = EnemyType::ZenChan;
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
	m_pRoot =  new AnimatorState(0,"ZenChan");

	m_pAnimator = new Animator(m_pSprite, m_pRoot, m_Blackboard);
	AddComponent(m_pAnimator);
	m_pBubbledAnim = new AnimatorState(3,"ZenChanBubble");
	m_pAnimator->AddState(m_pBubbledAnim);

	std::map<int, AnimData> animData = Anim::Loader::Load("../BubbleBobble/Resources/Enemies.anim");
	
	m_pAnimator->SetAnimData(animData);

	////BLACKBOARD KEYS
	m_Blackboard.AddKey((int)BlackboardKey::InBubble,ValueType::boolValue);
	////LINKS
	m_pAnimator->LinkStates(m_pRoot, m_pBubbledAnim, Req((int)BlackboardKey::InBubble, true));
	m_pAnimator->LinkStates(m_pBubbledAnim, m_pRoot, Req((int)BlackboardKey::InBubble, false));
}



void Zen::Update(float elapsedSec)
{
	BaseEnemy::Update(elapsedSec);



}

void Zen::SetRush(bool b)
{
	if(b)
	{
		m_pRoot->SetValue(7);
	}
	else
	{
		m_pRoot->SetValue(0);
	}
}

void Zen::SetControlled(int PlayerId)
{
	BaseEnemy::SetControlled(PlayerId);

	m_pInputHandler = new InputHandler();
	
	const int playerId = 1;
	//SET INPUTS
	const std::map<KeyAction, ButtonInput> keyMap = S_ButtonMap.at(playerId);
	const std::map<AxisAction, AxisInput> axisMap = S_AxisMap.at(playerId);
	m_pInputHandler->SetPlayerId(playerId);

	
	//KEYBOARD
	m_pInputHandler->AddInputButton(keyMap.at(KeyAction::K_Key1), m_pJumpC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::K_StickV), m_pGoDownC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::K_StickH), m_pMoveHC);

	//CONTROLLER
	m_pInputHandler->AddInputButton(keyMap.at(KeyAction::C_Key1), m_pJumpC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::C_StickV), m_pGoDownC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::C_StickH), m_pMoveHC);
}
