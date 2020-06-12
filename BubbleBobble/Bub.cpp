#include "ProjectPCH.h"
#include "Bub.h"
#include "AnimLoader.h"
#include "Bubble.h"
#include "BubbleBobble.h"
#include "Utils.h"
#include "GameScene.h"
#include "Components.h"
#include "EffectorComponent.h"
#include "Hud.h"
#include "LifeCounter.h"
#include "PlayerCommands.h"
#include "GameObject.h"
#include "SingleScene.h"

Bub::Bub(int playerId)
{
	m_PlayerId = playerId;

	////BLACKBOARD KEYS
	m_Blackboard.AddKey((int)BKey::AbsVelocityX, ValueType::floatValue);
	m_Blackboard.AddKey((int)BKey::IsBurping, ValueType::boolValue);
	m_Blackboard.AddKey((int)BKey::OnGround, ValueType::boolValue);
	m_Blackboard.AddKey((int)BKey::VelocityY, ValueType::floatValue);
	m_Blackboard.AddKey((int)BKey::Respawning, ValueType::boolValue);
	m_Blackboard.AddKey((int)BKey::IsHit, ValueType::boolValue);
	m_Blackboard.SetKeyValue((int)Respawning, true);
}

Bub::~Bub()
{
	
}

void Bub::Initialize()
{
	m_Transform->SetDepth(0.1f);
	Hud::GetInstance().AddLifeCounter(new LifeCounter(this));
	
	m_pRigid = new RigidbodyComponent();
	AddComponent(m_pRigid);
	m_pRigid->SetGravityScale(6.0f);
	
	m_pBoxCol =  new BoxCollider(glm::vec2(15, 16));
	m_pBoxCol->SetCategory(LayerMask::Player);
	m_pBoxCol->SetIgnoreMask(LayerMask::Roof);
	AddComponent(m_pBoxCol);
	m_pBoxCol->SetFriction(0);

	SetTag("PC");

	m_pSprite = new SpriteComponent("Bub.png");
	AddComponent(m_pSprite);

	auto pRespawn = new AnimatorState(0, "BubRespawn");
	m_pAnimator = new Animator(m_pSprite, pRespawn, m_Blackboard);
	std::map<int, AnimData> animData = Anim::Loader::Load("../BubbleBobble/Resources/Bub" + std::to_string(m_PlayerId) + ".anim");
	m_pAnimator->SetAnimData(animData);
	AddComponent(m_pAnimator);


	
	
	//STATES	
	auto pRoot = new AnimatorState(5, "BubIdle");
	m_pAnimator->AddState(pRoot);
	pRoot->SetWaitUntilAnimDone(false);
	
	auto pWalk = new AnimatorState(1, "BubWalk");
	m_pAnimator->AddState(pWalk);
	pWalk->SetSpeed(5.0f);
	
	auto pBurp = new AnimatorState(3, "BubBurb");
	m_pAnimator->AddState(pBurp);
	pBurp->SetSpeed(5.0f);
	pBurp->SetWaitUntilAnimDone(true);
	
	auto pJump = new AnimatorState(2, "BubJump");
	m_pAnimator->AddState(pJump);
	
	auto pFall = new AnimatorState(8,"BubFall");
	m_pAnimator->AddState(pFall);
	
	auto pIsHit = new AnimatorState(4, "BubHit");
	m_pAnimator->AddState(pIsHit);
	pIsHit->SetSpeed(5.0f);
	
	



	//ParentStates
	auto NormalParent = new ParentState(pRoot, "NormalParent");
	m_pAnimator->AddState(NormalParent);
	pWalk->SetParent(NormalParent);
	pJump->SetParent(NormalParent);
	pFall->SetParent(NormalParent);
	pBurp->SetParent(NormalParent);

	
	auto HitParent = new ParentState(pIsHit, "HitParent");
	m_pAnimator->AddState(HitParent);
	auto RespawnParent = new ParentState(pRespawn, "RespawnParent");
	m_pAnimator->AddState(RespawnParent);






	
	//ParentLinks
	m_pAnimator->LinkStates(NormalParent, HitParent, Req(BKey::IsHit, true));
	m_pAnimator->LinkStates(HitParent,NormalParent , Req(BKey::IsHit, false));

	m_pAnimator->LinkStates(NormalParent, RespawnParent, Req(BKey::Respawning, true));
	m_pAnimator->LinkStates(RespawnParent, NormalParent, Req(BKey::Respawning, false));
	
	

	



	//LINKS
	

	
	//Root
	m_pAnimator->LinkStates(pRoot, pWalk, Req(BKey::AbsVelocityX, 2.0f, Logic::BIGGER));
	m_pAnimator->LinkStates(pRoot, pBurp, Req(BKey::IsBurping,  true ));
	m_pAnimator->LinkStates(pRoot, pJump, { Req(BKey::OnGround,false) ,Req(BKey::VelocityY,0.01f, Logic::BIGGER) });
	m_pAnimator->LinkStates(pRoot, pFall, { Req(BKey::OnGround, false) ,Req(BKey::VelocityY, 0.01f, Logic::SMALLER) });
	//Walk
	m_pAnimator->LinkStates(pWalk,pRoot , Req(BKey::AbsVelocityX, { 2.0f }, Logic::SMALLER));
	m_pAnimator->LinkStates(pWalk, pBurp, Req(BKey::IsBurping,  true ));

	pBurp->SetEndFunction([this]() {m_Blackboard.SetKeyValue(IsBurping, false); });
	m_pAnimator->LinkStates(pWalk, pFall, { Req(BKey::OnGround, false) ,Req(BKey::VelocityY, 0.01f, Logic::SMALLER) });
	m_pAnimator->LinkStates(pWalk, pJump, { Req(BKey::OnGround, false) ,Req(BKey::VelocityY, 0.01f, Logic::BIGGER) });

	//Burp
	m_pAnimator->LinkStates(pBurp, pRoot);

	//MoveVertical
	m_pAnimator->LinkStates(pJump, pFall, Req(BKey::VelocityY, 1.0f, Logic::SMALLER));
	m_pAnimator->LinkStates(pJump, pBurp, Req(BKey::IsBurping,  true ));

	//Fall
	m_pAnimator->LinkStates(pFall, pRoot, Req(BKey::OnGround, true));
	m_pAnimator->LinkStates(pFall, pWalk, { Req(BKey::OnGround, true) , Req(BKey::AbsVelocityX, {2.0f}, Logic::BIGGER) });
	m_pAnimator->LinkStates(pFall, pBurp, Req(BKey::IsBurping, true ));
	


	//SET INPUTS
	const std::map<KeyAction, ButtonInput> keyMap = S_ButtonMap.at(m_PlayerId);
	const std::map<AxisAction, AxisInput> axisMap = S_AxisMap.at(m_PlayerId);
	

	//Only use one command instance
	inputHandler.AddInputButton(keyMap.at(KeyAction::K_Key2), m_ShootC);
	inputHandler.AddInputButton(keyMap.at(KeyAction::K_Key1), m_JumpC);
	inputHandler.AddInputAxis(axisMap.at(AxisAction::K_StickH),  m_MoveHC);
	inputHandler.AddInputAxis(axisMap.at(AxisAction::K_StickV),  m_GoDownC);

	//inputHandler.AddInputButton(keyMap.at(C_Key2), new PC::ShootBubble(this));
	//inputHandler.AddInputButton(keyMap.at(C_Key1), new PC::Jump(this));
	//inputHandler.AddInputAxis(axisMap.at(aC_StickH), new PC::MoveHorizontal(this));
	//inputHandler.AddInputAxis(axisMap.at(C_StickV), new PC::GoDown(this));
}


void Bub::Update(float elapsedSec)
{	
	m_Blackboard.SetKeyValue((int)BKey::AbsVelocityX, abs(m_pRigid->GetVelocity().x));
	m_Blackboard.SetKeyValue((int)BKey::VelocityY, -m_pRigid->GetVelocity().y);


	if(m_IsInvincible)
	{
		if(invincibleTimer>invincibleDelay)
		{
			invincibleTimer = 0.0f;
			m_IsInvincible = false;
			m_Visibility = true;
			invisibleCounter = false;
		}
		else
		{
			invincibleTimer += elapsedSec;
			
			invisibleCounter += elapsedSec;
			if (invisibleCounter / 0.2f >= 1)
			{
				m_Visibility = !m_Visibility;
				invisibleCounter = 0.0f;
			}
		}
		
	}
	m_Blackboard.SetKeyValue((int)BKey::OnGround, m_IsOnGround);

	GetComponent<SpriteComponent>()->SetFlip(!isRight);	
}

void Bub::PhysicsUpdate(float elapsedSec)
{

	if (m_pAnimator->GetCurrenState()->GetName() == "BubHit" && m_pSprite->GetCycle() > 2)
	{
		m_Blackboard.SetKeyValue(IsHit, false);
		m_IsInvincible = true;
		SetPosition(spawnPoint);
		if(m_Health <=0)
		{
			SingleScene* singleScene = static_cast<SingleScene*>(m_ParentScene);
			singleScene->RemovePlayer(this);
		}
	}


	
	m_pRigid->GetBody()->SetLinearVelocity(b2Vec2(0, m_pRigid->GetBody()->GetLinearVelocity().y));
	if (m_Respawning)
	{
		if (m_pAnimator->GetCurrenState()->GetValue() != BubRespawn)
		{
			m_Blackboard.SetKeyValue(Respawning, true);
			//m_pAnimator->SetCurrentState(pRespawn);
		}
		if (glm::distance(spawnPoint, m_Transform->Get2DPosition()) < 1.0f)
		{
			playerR = true;
		}
		else if (!playerR)
		{
			glm::vec2 dir = glm::normalize(spawnPoint - m_Transform->Get2DPosition());
			m_pBoxCol->SetSensor(true);
			m_pRigid->GetBody()->SetLinearVelocity(make_b2Vec2(dir * 100.0f));
		}
		else
		{
			m_pRigid->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		}

		return;
	}


	if (!m_Respawning)
	{
		m_pBoxCol->SetSensor(false);
		m_pRigid->SetGravityScale(9.81f);

	}
	else
	{
		m_pRigid->SetGravityScale(0.0f);
		m_pBoxCol->SetSensor(true);
	}
	
	
	if (!m_Blackboard.GetBoolProperty(BKey::IsHit) && !m_Blackboard.GetBoolProperty(BKey::Respawning))
	{
		inputHandler.HandleInput(elapsedSec);
	}



	auto raycastCallback = RaycastCallback(LayerMask::Ground | LayerMask::Platform | LayerMask::Bubbles);

	glm::vec2 startPos = m_Transform->Get2DPosition() + glm::vec2(4, 7);
	m_ParentScene->RayCast(&raycastCallback, make_b2Vec2(startPos), make_b2Vec2(startPos + glm::vec2(0, 4)));
	if (!raycastCallback.hasHit())
	{
		startPos = m_Transform->Get2DPosition() + glm::vec2(-4, 0);
		m_ParentScene->RayCast(&raycastCallback, make_b2Vec2(startPos), make_b2Vec2(startPos + glm::vec2(0, 4)));
	}

	if (raycastCallback.hasHit() && (raycastCallback.GetFixHit()->GetFilterData().categoryBits & LayerMask::Bubbles) == LayerMask::Bubbles)
	{
		m_pRigid->GetBody()->ApplyLinearImpulse(b2Vec2(0, -50), m_pRigid->GetBody()->GetWorldCenter(), true);
	}
	m_IsOnGround = raycastCallback.hasHit();


	if (raycastCallback.hasHit() && raycastCallback.m_CategoryHit == LayerMask::Platform)
	{
		GameObject* obj = static_cast<GameObject*>(raycastCallback.GetFixHit()->GetUserData());
		platformEff = obj->GetComponent<EffectorComponent>();
	}
	else
	{
		platformEff = nullptr;
	}
}

void Bub::Attack()
{
	Notify(Event::Player_Damaged,this);
	//FIX IS HIT LOGIC
	if (m_IsInvincible&&m_pAnimator->GetCurrenState()->GetValue()!=AnimType::BubHit)
		return;
	
	std::cout << "Took damage" << std::endl;
	m_Health -= 1;
	m_Blackboard.SetKeyValue(IsHit, true);
}



void Bub::MoveToLocation(float elapsedSec, glm::vec2 goPos)
{
	const float speed = 300.0f;
	glm::vec2 normDir = glm::normalize(goPos - m_Transform->Get2DPosition());
	m_pRigid->GetBody()->SetLinearVelocity(make_b2Vec2(speed * elapsedSec * normDir));
}

void Bub::SetRespawning(bool b)
{
	m_Respawning = b;
	m_Blackboard.SetKeyValue((int)BKey::Respawning, b);
}