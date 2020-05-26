#include "MiniginPCH.h"
#include "AnimatorState.h"
#include "AnimatorBlackboard.h"
#include "Utils.h"

AnimatorState::Connection::Connection(std::shared_ptr<::AnimatorState> act)
{
	AnimatorState = act;
	hasRequirement = false;
}

AnimatorState::Connection::Connection(std::shared_ptr<::AnimatorState> act, std::vector<Req> require)
{
	AnimatorState = act;
	requirements = require;
	hasRequirement = true;
}

AnimatorState::Connection::Connection(std::shared_ptr<::AnimatorState> act, Req require)
{
	requirements.push_back(require);
	AnimatorState = act;
	hasRequirement = true;
}

AnimatorState::Connection::~Connection()
{
}

AnimatorState::AnimatorState(int id,std::string name)
{
	m_EnumValue = id;
	m_pRequirements = std::vector<Req>();
	m_Name = name;
}

void AnimatorState::AddNextAnimatorState(std::shared_ptr<::AnimatorState> AnimatorState)
{
	for (size_t i = 0; i < m_NextConnections.size(); i++)
	{
		if (m_NextConnections[i]->AnimatorState == AnimatorState)
		{
			throw std::exception("[ERROR: Next AnimatorState has already been added");
			return;
		}
	}
	m_NextConnections.push_back( new Connection(AnimatorState));
}

void AnimatorState::AddNextAnimatorState(std::shared_ptr<::AnimatorState>AnimatorState, std::vector<Req> requirements)
{
	for (size_t i = 0; i < m_NextConnections.size(); i++)
	{
		if (m_NextConnections[i]->AnimatorState == AnimatorState)
		{
			throw std::exception("[ERROR: Next AnimatorState has already been added");
			return;
		}
	}
	m_NextConnections.push_back(new Connection(AnimatorState, requirements));
}

void AnimatorState::AddNextAnimatorState(std::shared_ptr<::AnimatorState> AnimatorState, Req requirement)
{
	for (size_t i = 0; i < m_NextConnections.size(); i++)
	{
		if (m_NextConnections[i]->AnimatorState == AnimatorState)
		{
			throw std::exception("[ERROR: Next AnimatorState has already been added");
			return;
		}
	}
	m_NextConnections.push_back(new Connection(AnimatorState, requirement));
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

AnimatorState::~AnimatorState()
{
	for(int i = 0;i< m_NextConnections.size();i++)
	{
		delete m_NextConnections[i];
		m_NextConnections[i] = nullptr;
	}
	m_NextConnections.clear();
}