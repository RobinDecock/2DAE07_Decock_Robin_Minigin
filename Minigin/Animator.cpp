#include "MiniginPCH.h"
#include "Animator.h"
#include "Components.h"
#include "GameObject.h"



Animator::Animator(PTR(SpriteComponent) spriteComp,PTR(AnimatorState) StartNode, AnimatorBlackboard& status) :startState(StartNode),
                                                                         m_pAnimatorBlackboard{status}, m_pSpriteComp{spriteComp}
{
	m_pCurrentAnimatorState = startState;

}

Animator::~Animator()
{
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




	
	if (m_pCurrentAnimatorState->HasFunction())
	{
		m_pCurrentAnimatorState->Execute(elapsedSec);
	}

	bool switchedAnimatorStates = false;


	if(m_pCurrentAnimatorState->m_WaitUntilAnimDone&&this->GetGameObject()->GetComponent<SpriteComponent>()->GetCycle()<1)
	{
		std::cout << "Fucked" << std::endl;
		return;
	}


	
	for (size_t i = 0; i < m_pCurrentAnimatorState->GetNextAnimatorStates().size() && switchedAnimatorStates == false; i
	     ++)
	{
		
		int amountOfRequirements = (int)m_pCurrentAnimatorState->GetNextAnimatorStates()[i]->requirements.size();
		int amountOfRequirementsMet = 0;
		for (size_t j = 0; j < m_pCurrentAnimatorState->GetNextAnimatorStates()[i]->requirements.size(); j++)
		{
			
			auto nextAnimatorState = m_pCurrentAnimatorState->GetNextAnimatorStates()[i];
			if (CheckRequirement(nextAnimatorState->requirements[j]))
			{
				amountOfRequirementsMet += 1;
			}
		}
		if (amountOfRequirements == amountOfRequirementsMet)
		{
			switchedAnimatorStates = true;
			m_pCurrentAnimatorState->LeaveState();
			if (m_Switch != nullptr)
			{
				m_Switch();
			}

			
			m_pPreviousAnimatorState = m_pCurrentAnimatorState;
			m_pCurrentAnimatorState = m_pCurrentAnimatorState->GetNextAnimatorStates()[i]->AnimatorState;
			if(m_pSpriteComp ==nullptr)
			{
				std::cout << "no SpriteComponent found on current GameObject" << std::endl;
				return;
			}
			m_pSpriteComp->SetSpriteData(m_AnimData[m_pCurrentAnimatorState->GetValue()]);
			m_pSpriteComp->SetSpeed(m_pCurrentAnimatorState->GetSpeed());
			m_pSpriteComp->SetLooping(m_pCurrentAnimatorState->GetLooping());
		}
	}
}


void Animator::LinkStates(std::shared_ptr<::AnimatorState>prevAnimatorState, std::shared_ptr<::AnimatorState>nextAnimatorState)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState);
}

void Animator::LinkStates(std::shared_ptr<::AnimatorState>prevAnimatorState, std::shared_ptr<::AnimatorState> nextAnimatorState,
                          std::vector<Req> requirements)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState, requirements);
}

void Animator::LinkStates(std::shared_ptr<::AnimatorState> prevAnimatorState, std::shared_ptr<::AnimatorState> nextAnimatorState, Req requirement)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState, requirement);
}

bool Animator::CheckRequirement(Req desiredProperty)
{
	auto currentProperty = m_pAnimatorBlackboard.GetProperty(desiredProperty.key);
	switch (currentProperty.type)
	{
	case ValueType::intValue:
		return CheckLogic(currentProperty.value.iValue, desiredProperty.property.value.iValue, desiredProperty.logic);
		break;
	case ValueType::boolValue:
		return currentProperty.value.bValue == desiredProperty.property.value.bValue;
		break;
	case ValueType::floatValue:
		return CheckLogic(currentProperty.value.fValue, desiredProperty.property.value.fValue, desiredProperty.logic);
		break;
	case ValueType::V2Value:
		return currentProperty.value.V2Value == desiredProperty.property.value.V2Value;
		break;
	}
	return false;
}

//USE TYPENAMES
bool Animator::CheckLogic(int value1, int value2, Logic l)
{
	switch (l)
	{
	case Logic::BIGGER:
		return value1 > value2;
		break;
	case Logic::SMALLER:
		return value1 < value2;
		break;
	case Logic::EQUAL:
		return value1 == value2;
		break;
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
}

void Animator::SetCurrentState(std::shared_ptr<AnimatorState> an)
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
