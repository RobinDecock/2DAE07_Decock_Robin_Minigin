#include "MiniginPCH.h"
#include "Animator.h"
#include "Components.h"
#include "GameObject.h"
#include "AnimatorState.h"
#include "SpriteComponent.h"

Animator::Animator(SpriteComponent* spriteComp,AnimatorState* StartNode, AnimatorBlackboard& status) :m_pCurrentAnimatorState(StartNode),
                                                                         m_pAnimatorBlackboard{status}, m_pSpriteComp{spriteComp}
{
	m_pStates.push_back(StartNode);
}


Animator::~Animator()
{
	for (auto p : m_pStates)
	{
		delete p;
		p = nullptr;
	}
	m_pStates.clear();

}

void Animator::Initialize()
{
	m_pSpriteComp->SetSpriteData(m_AnimData[m_pCurrentAnimatorState->GetValue()]);
	m_pSpriteComp->SetSpeed(m_pCurrentAnimatorState->GetSpeed());
	m_pSpriteComp->SetLooping(m_pCurrentAnimatorState->GetLooping());
}

void Animator::Update(float elapsedSec)
{
	BaseComponent::Update(elapsedSec);
	AnimatorState* state = m_pCurrentAnimatorState->GetNextState(m_pCurrentAnimatorState,m_pAnimatorBlackboard);
	if (state == nullptr)
	{
		m_pCurrentAnimatorState->RootExecute(elapsedSec);
	}
	else if (state != m_pCurrentAnimatorState&&
				(!m_pCurrentAnimatorState->GetWaitUntilAnimDone()|| (m_pCurrentAnimatorState->GetWaitUntilAnimDone() &&m_pSpriteComp->GetCycle()>=1)))
	{

		m_pCurrentAnimatorState->EndState();
		
		m_pCurrentAnimatorState = state;
		m_pSpriteComp->SetSpriteData(m_AnimData[m_pCurrentAnimatorState->GetValue()]);
		m_pSpriteComp->SetSpeed(m_pCurrentAnimatorState->GetSpeed());
		m_pSpriteComp->SetLooping(m_pCurrentAnimatorState->GetLooping());
		m_pSpriteComp->SetSpriteData(m_AnimData[m_pCurrentAnimatorState->GetValue()]);
	}
}



void Animator::LinkStates(::BaseState *prevAnimatorState, ::BaseState*nextAnimatorState)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState);
}

void Animator::LinkStates(::BaseState*prevAnimatorState, ::BaseState* nextAnimatorState,
                          std::vector<Req> requirements)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState, requirements);
}

void Animator::LinkStates(::BaseState* prevAnimatorState, ::BaseState* nextAnimatorState, Req requirement)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState, requirement);
}

//USE TYPENAMES
bool Animator::CheckLogic(int value1, int value2, Logic l)
{
	switch (l)
	{
	case Logic::BIGGER:
		return value1 > value2;
	case Logic::SMALLER:
		return value1 < value2;
	case Logic::EQUAL:
		return value1 == value2;
	}
	return false;
}

bool Animator::CheckLogic(float value1, float value2, Logic l)
{
	switch (l)
	{
	case Logic::BIGGER:
		return value1 > value2;
	case Logic::SMALLER:
		return value1 < value2;
	case Logic::EQUAL:
		return value1 == value2;
	default:
		break;
	}
	return false;
}

void Animator::SetCurrentState(AnimatorState* an)
{
	m_pCurrentAnimatorState->LeaveState();
	if (m_Switch != nullptr)
	{
		m_Switch();
	}


	m_pPreviousAnimatorState = m_pCurrentAnimatorState;
	m_pCurrentAnimatorState = an;
	if (m_pSpriteComp == nullptr)
	{
		std::cout << "no SpriteComponent found on current GameObject" << std::endl;
		return;
	}
	m_pSpriteComp->SetSpriteData(m_AnimData[m_pCurrentAnimatorState->GetValue()]);
	m_pSpriteComp->SetSpeed(m_pCurrentAnimatorState->GetSpeed());
	m_pSpriteComp->SetLooping(m_pCurrentAnimatorState->GetLooping());
}

void Animator::AddState(BaseState* state)
{

#if _DEBUG
	for(unsigned int i = 0;i<m_pStates.size();i++)
	{
		if(m_pStates[i]==state)
		{
			std::cout << "STATE WAS ALREADY ADDED IN ANIMATOR" << std::endl;
		}
	}
#endif

	
	
	m_pStates.push_back(state);
}
