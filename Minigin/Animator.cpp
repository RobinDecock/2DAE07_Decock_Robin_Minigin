#include "MiniginPCH.h"
#include "Animator.h"
#include "Components.h"
#include "GameObject.h"



Animator::Animator(AnimatorState* StartNode, AnimatorBlackboard& status) : m_pCurrentAnimatorState{StartNode},
                                                                           m_pAnimatorBlackboard{status}
{
}

Animator::~Animator()
{
	SafeDelete(m_pCurrentAnimatorState);
	SafeDelete(m_pPreviousAnimatorState);
}

void Animator::Update(float elapsedSec)
{
	BaseComponent::Update(elapsedSec);

	if (m_pCurrentAnimatorState->HasFunction())
	{
		m_pCurrentAnimatorState->Execute(elapsedSec);
	}

	bool switchedAnimatorStates = false;
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

			if(m_pGameObject->GetComponent<SpriteComponent>()==nullptr)
			{
				std::cout << "no SpriteComponent found on current GameObject" << std::endl;
			}
			m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteData(m_AnimData[m_pCurrentAnimatorState->GetValue()]);
		}
	}
}

void Animator::LinkStates(AnimatorState* prevAnimatorState, AnimatorState* nextAnimatorState)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState);
}

void Animator::LinkStates(AnimatorState* prevAnimatorState, AnimatorState* nextAnimatorState,
                          std::vector<Requirement> requirements)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState, requirements);
}

void Animator::LinkStates(AnimatorState* prevAnimatorState, AnimatorState* nextAnimatorState, Requirement requirement)
{
	prevAnimatorState->AddNextAnimatorState(nextAnimatorState, requirement);
}

bool Animator::CheckRequirement(Requirement desiredProperty)
{
	auto currentProperty = m_pAnimatorBlackboard.GetProperty(desiredProperty.key);
	switch (currentProperty.type)
	{
	case BlackboardValueType::intValue:
		return CheckLogic(currentProperty.value.iValue, desiredProperty.property.value.iValue, desiredProperty.logic);
		break;
	case BlackboardValueType::boolValue:
		return currentProperty.value.bValue == desiredProperty.property.value.bValue;
		break;
	case BlackboardValueType::floatValue:
		return CheckLogic(currentProperty.value.fValue, desiredProperty.property.value.fValue, desiredProperty.logic);
		break;
	case BlackboardValueType::Vector2Value:
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
	case Logic::SMALL:
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
		break;
	case Logic::SMALL:
		return value1 < value2;
		break;
	case Logic::EQUAL:
		return value1 == value2;
		break;
	}
	return false;
}
