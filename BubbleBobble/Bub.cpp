#include "ProjectPCH.h"
#include "Bub.h"
#include "AnimLoader.h"
#include "Bubble.h"
#include "BubbleBobble.h"
#include "InputDefinitions.h"
#include "InputManager.h"
#include "Utils.h"
#include "GameScene.h"
#include "Components.h"
#include "EffectorComponent.h"
#include "EnemyCommands.h"
#include "PlayerCommands.h"

Bub::Bub(int playerId)
{
	m_PlayerId = playerId;
}

Bub::~Bub()
{
}


void Bub::Attack()
{
	std::cout << "Took damage" << std::endl;
}



void Bub::MoveToLocation(float elapsedSec, glm::vec2 goPos)
{
	int speed = 300.0f;
	glm::vec2 normDir = glm::normalize(goPos - m_Transform->Get2DPosition());
	m_pRigid->GetBody()->SetLinearVelocity(make_b2Vec2(speed*elapsedSec* normDir));
}

void Bub::SetRespawning(bool b)
{
	m_Respawning = b;
	m_Blackboard.SetKeyValue((int)BKey::Respawning, b);
	if(!b)
	{
		m_pBoxCol->SetSensor(false);
		m_pRigid->SetGravityScale(9.81f);

	}
	else
	{
		m_pRigid->SetGravityScale(0.0f);
		m_pBoxCol->SetSensor(true);
	}
}

void Bub::Initialize()
{	
	m_pRigid = NEW(RigidbodyComponent)();
	AddComponent(m_pRigid);
	m_pRigid->SetGravityScale(6.0f);
	m_pBoxCol = NEW(BoxCollider)(glm::vec2(15, 16));
	m_pBoxCol->SetCategory(LayerMask::Player);
	m_pBoxCol->SetIgnoreMask(LayerMask::Bubbles);
	AddComponent(m_pBoxCol);

	SetTag("PC");
	//STATES	
	auto pRoot = NEW(AnimatorState)(5, "BubIdle");
	pRoot->m_WaitUntilAnimDone = false;
	auto pWalk = NEW(AnimatorState)(1, "BubWalk");
	pWalk->SetSpeed(5.0f);
	auto pBurp = NEW(AnimatorState)(3, "BubBurb");
	pBurp->SetSpeed(5.0f);
	pBurp->m_WaitUntilAnimDone = true;
	auto pJump = NEW(AnimatorState)(2, "BubJump");
	auto pFall = NEW(AnimatorState)(8,"BubFall");
	m_pRespawning= NEW(AnimatorState)(0,"BubRespawn");

	m_pSprite = std::make_shared<SpriteComponent>("Bub.png");
	AddComponent(m_pSprite);
	
	m_pAnimator = std::make_shared<Animator>(m_pSprite, m_pRespawning, m_Blackboard);
	std::map<int, AnimData> animData = AnimLoader::Load("../BubbleBobble/Resources/Bub" + std::to_string(m_PlayerId) + ".anim");
	m_pAnimator->SetAnimData(animData);
	AddComponent(m_pAnimator);
	


	////BLACKBOARD KEYS
	m_Blackboard.AddKey((int)BKey::AbsVelocityX, ValueType::floatValue);
	m_Blackboard.AddKey((int)BKey::IsBurping, ValueType::boolValue);
	m_Blackboard.AddKey((int)BKey::OnGround, ValueType::boolValue);
	m_Blackboard.AddKey((int)BKey::VelocityY, ValueType::floatValue);
	m_Blackboard.AddKey((int)BKey::Respawning, ValueType::boolValue);
	m_Blackboard.SetKeyValue((int)Respawning, true);
	//LINKS
	//Root
	m_pAnimator->LinkStates(pRoot, pWalk, Req(BKey::AbsVelocityX, 2.0f, BIGGER));
	m_pAnimator->LinkStates(pRoot, pBurp, Req(BKey::IsBurping,  true ));
	m_pAnimator->LinkStates(pRoot, pJump, { Req(BKey::OnGround,false) ,Req(BKey::VelocityY,0.01f, BIGGER) });
	m_pAnimator->LinkStates(pRoot, pFall, { Req(BKey::OnGround, false) ,Req(BKey::VelocityY, 0.01f, SMALLER) });
	m_pAnimator->LinkStates(pRoot, m_pRespawning, Req(BKey::Respawning, true));

	m_pAnimator->LinkStates(m_pRespawning, pRoot, Req(BKey::Respawning, false));
	//Walk
	m_pAnimator->LinkStates(pWalk,pRoot , Req(BKey::AbsVelocityX, { 2.0f }, SMALLER));
	m_pAnimator->LinkStates(pWalk, pBurp, Req(BKey::IsBurping,  true ));
	m_pAnimator->LinkStates(pWalk, pFall, { Req(BKey::OnGround, false) ,Req(BKey::VelocityY, 0.01f, SMALLER) });
	m_pAnimator->LinkStates(pWalk, pJump, { Req(BKey::OnGround, false) ,Req(BKey::VelocityY, 0.01f, BIGGER) });

	//Burp
	m_pAnimator->LinkStates(pBurp, pRoot, Req(BKey::IsBurping, false ));

	//MoveVertical
	m_pAnimator->LinkStates(pJump, pFall, Req(BKey::VelocityY, 1.0f, SMALLER));
	m_pAnimator->LinkStates(pJump, pBurp, Req(BKey::IsBurping,  true ));

	//Fall
	m_pAnimator->LinkStates(pFall, pRoot, Req(BKey::OnGround, true));
	m_pAnimator->LinkStates(pFall, pWalk, { Req(BKey::OnGround, true) , Req(BKey::AbsVelocityX, {2.0f}, BIGGER) });
	m_pAnimator->LinkStates(pFall, pBurp, Req(BKey::IsBurping, true ));
	


	//SET INPUTS
	const std::map<KeyAction, ButtonInput> keyMap = S_ButtonMap.at(m_PlayerId);
	const std::map<AxisAction, AxisInput> axisMap = S_AxisMap.at(m_PlayerId);
	

	//Only use one command instance
	inputHandler.AddInputButton(keyMap.at(K_Key2), new PC::ShootBubble(this));
	inputHandler.AddInputButton(keyMap.at(K_Key1), new PC::Jump(this));
	inputHandler.AddInputAxis(axisMap.at(K_StickH), new PC::MoveHorizontal(this));
	inputHandler.AddInputAxis(axisMap.at(K_StickV), new PC::GoDown(this));

	inputHandler.AddInputButton(keyMap.at(C_Key2), new PC::ShootBubble(this));
	inputHandler.AddInputButton(keyMap.at(C_Key1), new PC::Jump(this));
	inputHandler.AddInputAxis(axisMap.at(C_StickH), new PC::MoveHorizontal(this));
	inputHandler.AddInputAxis(axisMap.at(C_StickV), new PC::GoDown(this));
}


void Bub::Update(float elapsedSec)
{	
	if (m_Respawning) 
	{
		if(m_pAnimator->GetCurrenState()->GetValue()!=BubRespawn)
		{
			m_Blackboard.SetKeyValue(Respawning, true);
			m_pAnimator->SetCurrentState(m_pRespawning);
		}
		if(glm::distance(spawnPoint,m_Transform->Get2DPosition())<1.0f)
		{
			playerR = true;
		}
		else
		{
			glm::vec2 dir = glm::normalize(spawnPoint - m_Transform->Get2DPosition());
			m_pBoxCol->SetSensor(true);
			m_pRigid->GetBody()->SetLinearVelocity(make_b2Vec2(dir*50.0f));
		}
		
		return;
	}
	b2Vec2 vel = m_pRigid->GetBody()->GetLinearVelocity();
	vel.x = 0.0f;
	m_Blackboard.SetKeyValue((int)BKey::IsBurping, false);
	m_pRigid->GetBody()->SetLinearVelocity(vel);
	inputHandler.HandleInput(elapsedSec);
	
	m_Blackboard.SetKeyValue((int)BKey::AbsVelocityX, abs(m_pRigid->GetVelocity().x));
	m_Blackboard.SetKeyValue((int)BKey::VelocityY, -m_pRigid->GetVelocity().y);

	auto raycastCallback = RaycastCallback(LayerMask::Ground | LayerMask::Platform);
	
	glm::vec2 startPos = m_Transform->Get2DPosition() + glm::vec2(4, 0);
	m_ParentScene->RayCast(&raycastCallback, make_b2Vec2(startPos), make_b2Vec2(startPos + glm::vec2(0, 15)));
	if(!raycastCallback.hasHit())
	{
		startPos = m_Transform->Get2DPosition() + glm::vec2(-4, 0);
		m_ParentScene->RayCast(&raycastCallback, make_b2Vec2(startPos), make_b2Vec2(startPos + glm::vec2(0, 15)));
	}
	
	m_IsOnGround = raycastCallback.hasHit();


	if (raycastCallback.hasHit()&&raycastCallback.m_CategoryHit==LayerMask::Platform)
	{
		GameObject * obj= static_cast<GameObject*>(raycastCallback.GetFixHit()->GetUserData());
		platformEff = obj->GetComponent<EffectorComponent>();
	}
	else
	{
		platformEff = nullptr;
	}


	
	m_Blackboard.SetKeyValue((int)BKey::OnGround, m_IsOnGround);

	GetComponent<SpriteComponent>()->SetFlip(!isRight);




	
}