#include "ProjectPCH.h"
#include "BubStates.h"
#include "Animator.h"
#include "Bub.h"
#include "AnimatorState.h"
#include "Utils.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "BoxCollider.h"
#include "BubbleBobble.h"
#include "SingleScene.h"
#include "SpriteComponent.h"

void RespawnState::StartState()
{
	RigidbodyComponent* rigid = m_pBub->GetComponent<RigidbodyComponent>();
	rigid->SetGravityScale(0.0f);
	BoxCollider* boxCol = m_pBub->GetComponent<BoxCollider>();
	boxCol->SetSensor(true);
}

BubState* RespawnState::Execute(float elapsedSec)
{
	const Animator* pAnimator = m_pBub->GetComponent<Animator>();

	bool& playerR = m_pBub->m_PlayerReady;
	
	const TransformComponent *transform = m_pBub->GetComponent<TransformComponent>();
	const glm::vec2& spawnPoint = m_pBub->m_SpawnPoint;
	
	AnimatorBlackboard& blackboard = m_pBub->m_Blackboard;
	if (pAnimator->GetCurrenState()->GetValue() != int(Bub::AnimType::BubRespawn))
	{

		blackboard.SetKeyValue(Bub::Respawning, true);
		//m_pAnimator->SetCurrentState(pRespawn);
	}

	RigidbodyComponent* rigid = m_pBub->GetComponent<RigidbodyComponent>();
	
	if (glm::distance(spawnPoint, transform->Get2DPosition()) < 5.0f)
	{
		playerR = true;
	}
	else if (!playerR)
	{
		BoxCollider* boxCol = m_pBub->GetComponent<BoxCollider>();
		glm::vec2 dir = glm::normalize(spawnPoint - transform->Get2DPosition());
		boxCol->SetSensor(true);
		rigid->GetBody()->SetLinearVelocity(make_b2Vec2(dir * 100.0f));
	}
	else
	{
		rigid->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	}


	if(m_pBub->m_DoneRespawning)
	{
		blackboard.SetKeyValue((int)Bub::BKey::Respawning, false);
		return new NormalState(m_pBub);
		
	}
	
	return nullptr;
}

void RespawnState::EndState()
{
	BoxCollider* boxCol = m_pBub->GetComponent<BoxCollider>();
	boxCol->SetSensor(false);
	RigidbodyComponent* rigid = m_pBub->GetComponent<RigidbodyComponent>();
	rigid->SetGravityScale(9.81f);
}

void NormalState::StartState()
{
	//SET INPUTS
	const std::map<KeyAction, ButtonInput> keyMap = S_ButtonMap.at(m_pBub->GetPlayerId());
	const std::map<AxisAction, AxisInput> axisMap = S_AxisMap.at(m_pBub->GetPlayerId());

	m_InputHandler.AddInputButton(keyMap.at(KeyAction::K_Key2), m_pBub->m_ShootC);
	m_InputHandler.AddInputButton(keyMap.at(KeyAction::K_Key1), m_pBub->m_JumpC);
	m_InputHandler.AddInputAxis(axisMap.at(AxisAction::K_StickH), m_pBub->m_MoveHC);
	m_InputHandler.AddInputAxis(axisMap.at(AxisAction::K_StickV), m_pBub->m_GoDownC);

	m_InputHandler.AddInputButton(keyMap.at(KeyAction::C_Key2), m_pBub->m_ShootC);
	m_InputHandler.AddInputButton(keyMap.at(KeyAction::C_Key1), m_pBub->m_JumpC);
	m_InputHandler.AddInputAxis(axisMap.at(AxisAction::C_StickH), m_pBub->m_MoveHC);
	m_InputHandler.AddInputAxis(axisMap.at(AxisAction::C_StickV), m_pBub->m_GoDownC);
//
}

BubState* NormalState::Execute(float elapsedSec)
{
	RigidbodyComponent* pRigid = m_pBub->GetComponent<RigidbodyComponent>();
	pRigid->GetBody()->SetLinearVelocity(b2Vec2(0, pRigid->GetBody()->GetLinearVelocity().y));
	m_InputHandler.HandleInput(elapsedSec);
	AnimatorBlackboard& blackboard = m_pBub->m_Blackboard;
	
	if (!m_pBub->m_DoneRespawning)
	{
		blackboard.SetKeyValue((int)Bub::BKey::Respawning, true);
		return new RespawnState(m_pBub);

	}

	if(blackboard.GetBoolProperty(Bub::BKey::IsHit))
	{
		return new HitState(m_pBub);
	}
	return nullptr;
}

void NormalState::EndState()
{
	m_pBub->GetComponent<RigidbodyComponent>()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
}

BubState* HitState::Execute(float elapsedSec)
{
	const Animator * pAnimator = m_pBub->GetComponent<Animator>();
	const SpriteComponent* pSprite = m_pBub->GetComponent<SpriteComponent>();
	if(pAnimator->GetCurrenState()->GetName() == "BubHit" && pSprite->GetCycle() > 2)
	{
		return new NormalState(m_pBub);
	}
	return nullptr;
}

void HitState::EndState()
{
	AnimatorBlackboard& blackboard = m_pBub->m_Blackboard;
	
	blackboard.SetKeyValue(Bub::BKey::IsHit, false);
	m_pBub->m_IsInvincible = true;
	m_pBub->SetPosition(m_pBub->m_SpawnPoint);
	if (m_pBub->GetHealth() <= 0)
	{
		SingleScene* singleScene = static_cast<SingleScene*>(m_pBub->m_ParentScene);
		singleScene->RemovePlayer(m_pBub);
	}
}

void AerialState::StartState()
{
	const std::map<KeyAction, ButtonInput> keyMap = S_ButtonMap.at(m_pBub->GetPlayerId());
	const std::map<AxisAction, AxisInput> axisMap = S_AxisMap.at(m_pBub->GetPlayerId());
	m_InputHandler.SetPlayerId(m_pBub->GetPlayerId());
	m_InputHandler.AddInputButton(keyMap.at(KeyAction::K_Key2), m_pBub->m_ShootC);
	m_InputHandler.AddInputAxis(axisMap.at(AxisAction::K_StickH), m_pBub->m_MoveHC);

	m_InputHandler.AddInputButton(keyMap.at(KeyAction::C_Key2), m_pBub->m_ShootC);
	m_InputHandler.AddInputAxis(axisMap.at(AxisAction::C_StickH), m_pBub->m_MoveHC);
	
}


BubState* AerialState::Execute(float elapsedSec)
{
	m_InputHandler.HandleInput(elapsedSec);
	AnimatorBlackboard& blackboard = m_pBub->m_Blackboard;
	if(m_pBub->m_IsOnGround)
	{
		return new NormalState(m_pBub);
	}
	if (blackboard.GetBoolProperty(Bub::BKey::IsHit))
	{
		return new HitState(m_pBub);
	}
	return nullptr;
}
