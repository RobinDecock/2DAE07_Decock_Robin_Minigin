#include "MiniginPCH.h"
#include "AnimatorState.h"
#include "AnimatorBlackboard.h"

AnimatorState::Node::Node(::AnimatorState* act)
{
	AnimatorState = act;
	hasRequirement = false;
}

AnimatorState::Node::Node(::AnimatorState* act, std::vector<Requirement> require)
{
	AnimatorState = act;
	requirements = require;
	hasRequirement = true;
}

AnimatorState::Node::Node(::AnimatorState* act, Requirement require)
{
	requirements.push_back(require);
	AnimatorState = act;
	hasRequirement = true;
}

AnimatorState::AnimatorState(int v, std::string name)
{
	m_EnumValue = v;
	m_isLooping = false;
	m_pRequirements = std::vector<Requirement>();
	m_Name = name;
}


AnimatorState::~AnimatorState()
{
	for (int i = 0; i < m_NextAnimatorStates.size(); i++)
	{
		SafeDelete(m_NextAnimatorStates[i]);
	}
}

void AnimatorState::AddNextAnimatorState(AnimatorState* AnimatorState)
{
	for (size_t i = 0; i < m_NextAnimatorStates.size(); i++)
	{
		if (m_NextAnimatorStates[i]->AnimatorState == AnimatorState)
		{
			throw std::exception("[ERROR: Next AnimatorState has already been added");
			return;
		}
	}
	m_NextAnimatorStates.push_back(new Node(AnimatorState));
}

void AnimatorState::AddNextAnimatorState(AnimatorState* AnimatorState, std::vector<Requirement> requirements)
{
	for (size_t i = 0; i < m_NextAnimatorStates.size(); i++)
	{
		if (m_NextAnimatorStates[i]->AnimatorState == AnimatorState)
		{
			throw std::exception("[ERROR: Next AnimatorState has already been added");
			return;
		}
	}
	m_NextAnimatorStates.push_back(new Node(AnimatorState, requirements));
}

void AnimatorState::AddNextAnimatorState(AnimatorState* AnimatorState, Requirement requirement)
{
	for (size_t i = 0; i < m_NextAnimatorStates.size(); i++)
	{
		if (m_NextAnimatorStates[i]->AnimatorState == AnimatorState)
		{
			throw std::exception("[ERROR: Next AnimatorState has already been added");
			return;
		}
	}
	m_NextAnimatorStates.push_back(new Node(AnimatorState, requirement));
}

bool AnimatorState::HasFunction()
{
	return (m_Function != nullptr);
}

void AnimatorState::Execute(float elapsedSec)
{
	if (!m_isLooping)
	{
		if (!m_hasRun)
		{
			m_Function();
			m_hasRun = true;
		}
	}
	else
	{
		m_Function();
	}
	runTime += elapsedSec;
	for (size_t i = 0; i < m_EventFunctions.size(); i++)
	{
		if (runTime > m_EventFunctions[i].first - 0.1f && runTime < m_EventFunctions[i].first + 0.1f)
		{
			m_EventFunctions[i].second();
		}
	}
}
