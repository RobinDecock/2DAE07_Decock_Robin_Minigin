#include "ProjectPCH.h"
#include "Maita.h"

#include "AnimatorState.h"
#include "BoxTrigger.h"
#include "BubbleBobble.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "AnimLoader.h"
#include "Bub.h"
Maita::Maita(LevelSegment* segment):BaseEnemy(segment)
{
	
}

Maita::~Maita()
{
	SafeDelete(m_pInputHandler);
}

void Maita::Initialize()
{
	BaseEnemy::Initialize();
	
	m_pRigid = new RigidbodyComponent();
	AddComponent(m_pRigid);
	m_pRigid->SetGravityScale(6.0f);

	m_pBoxCol = new BoxCollider(glm::vec2(14, 14));
	m_pBoxCol->SetCategory(LayerMask::Enemies);
	m_pBoxCol->SetIgnoreMask(LayerMask::Player);
	AddComponent(m_pBoxCol);
	m_pBoxCol->SetFriction(0);

	auto pTrigger = new BoxTrigger(glm::vec2(14, 14));
	AddComponent(pTrigger);
	pTrigger->SetCategory(LayerMask::Enemies);
	//pTrigger->SetIgnoreMask(LayerMask::Player|LayerMask::Bubbles);

	m_pSprite = new SpriteComponent("Enemies.png");
	AddComponent(m_pSprite);

	
	auto pRoot = new AnimatorState(1, "Maita");
	
	m_pAnimator = new Animator(m_pSprite, pRoot, m_Blackboard);
	AddComponent(m_pAnimator);

	
	auto pBubbled = new AnimatorState(2, "MaitaBubble");
	m_pAnimator->AddState(pBubbled);



	std::map<int, AnimData> animData = Anim::Loader::Load("../BubbleBobble/Resources/Enemies.anim");

	m_pAnimator->SetAnimData(animData);

	////BLACKBOARD KEYS
	m_Blackboard.AddKey((int)BlackboardKey::InBubble, ValueType::boolValue);
	////LINKS
	m_pAnimator->LinkStates(pRoot, pBubbled, Req((int)BlackboardKey::InBubble, true));
	m_pAnimator->LinkStates(pBubbled, pRoot, Req((int)BlackboardKey::InBubble, false));



}


void Maita::HandleAI(float elapsedSec)
{
}

void Maita::SetControlled(int PlayerId)
{
	BaseEnemy::SetControlled(PlayerId);

	m_pInputHandler = new InputHandler();

	//SET INPUTS
	const std::map<KeyAction, ButtonInput>& keyMap = S_ButtonMap.at(PlayerId);
	const std::map<AxisAction, AxisInput>& axisMap = S_AxisMap.at(PlayerId);


	//KEYBOARD
	m_pInputHandler->AddInputButton(keyMap.at(KeyAction::K_Key1), m_pJumpC);
	m_pInputHandler->AddInputButton(keyMap.at(KeyAction::K_Key2), m_pShootC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::K_StickV), m_pGoDownC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::K_StickH), m_pMoveHC);

	//CONTROLLER
	m_pInputHandler->AddInputButton(keyMap.at(KeyAction::C_Key1), m_pJumpC);
	m_pInputHandler->AddInputButton(keyMap.at(KeyAction::C_Key2), m_pShootC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::C_StickV), m_pGoDownC);
	m_pInputHandler->AddInputAxis(axisMap.at(AxisAction::C_StickH), m_pMoveHC);
}
