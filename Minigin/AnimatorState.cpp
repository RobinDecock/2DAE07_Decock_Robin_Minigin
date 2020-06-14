#include "MiniginPCH.h"
#include "AnimatorState.h"
#include "AnimatorBlackboard.h"


	Connection::Connection(BaseState* act)
	{
		AnimatorState = act;
		hasRequirement = false;
	}

	Connection::Connection(BaseState* act, std::vector<Req> require)
	{
		AnimatorState = act;
		requirements = require;
		hasRequirement = true;
	}

	Connection::Connection(BaseState* act, Req require)
	{
		requirements.push_back(require);
		AnimatorState = act;
		hasRequirement = true;
	}
	
	::AnimatorState* ::BaseState::GetNextState( ::AnimatorBlackboard& pBlackboard)
	{
		if (m_pParent != nullptr)
		{
			BaseState* nextState = GetNState(m_pParent, pBlackboard);
			if (nextState != nullptr)
			{
				ParentState* pState = static_cast<ParentState*>(nextState);
				return pState->GetStartState();
			}
		}

		return GetNState(this, pBlackboard);
	}

	AnimatorState* ::BaseState::GetNState(BaseState* currentState, AnimatorBlackboard& pBlackboard)
	{
		bool switchedFiniteStateMachineStates = false;

		std::vector<Connection> pNextConnections = currentState->GetNextConnections();


		for (size_t i = 0; i < pNextConnections.size() && switchedFiniteStateMachineStates == false; i++)
		{

			int amountOfRequirements = (int)pNextConnections[i].requirements.size();
			int amountOfRequirementsMet = 0;
			for (size_t j = 0; j < pNextConnections[i].requirements.size(); j++)
			{

				auto nextFiniteStateMachineState = pNextConnections[i];
				if (pBlackboard.CheckRequirement(nextFiniteStateMachineState.requirements[j]))
				{
					amountOfRequirementsMet += 1;
				}
			}


			if (amountOfRequirements == amountOfRequirementsMet)
			{
#pragma region DEBUGOUTPUT
#if defined DEBUGDRAW
				for (size_t j = 0; j < pNextConnections[i].requirements.size(); j++)
				{
					Req req = pNextConnections[i].requirements[j];

					std::cout << "REQ(" + BlackboardKeyStrings[req.key] << "):";


					switch (req.property.type)
					{
					case ValueType::boolValue:
						std::cout << req.property.value.bValue;
						break;
					case ValueType::intValue:
						std::cout << req.property.value.iValue;
						break;
					case ValueType::floatValue:
						std::cout << req.property.value.fValue;
						break;
					case ValueType::V2Value:
						std::cout << req.property.value.v2Value.x << "," << req.property.value.v2Value.y;
						break;
					}

				}
				std::cout << std::endl;
#endif
#pragma endregion DEBUGOUTPUT
				AnimatorState* returnValue = static_cast<AnimatorState*>(pNextConnections[i].AnimatorState);
				return returnValue;
			}
		}
		return nullptr;
	}
	AnimatorState::AnimatorState(std::string name)
	{
		m_Name = name;
		m_EnumValue = -1;
	}

	AnimatorState::AnimatorState(unsigned int id, std::string name)
	{
		m_EnumValue = id;
		m_Name = name;
	}

	void ::BaseState::AddNextAnimatorState(::BaseState* AnimatorState)
	{
		for (size_t i = 0; i < m_NextConnections.size(); i++)
		{
			if (m_NextConnections[i].AnimatorState == AnimatorState)
			{
				throw std::exception("[ERROR: Next AnimatorState has already been added");
			}
		}
		m_NextConnections.push_back(Connection(AnimatorState));
	}

	void BaseState::AddNextAnimatorState(::BaseState* AnimatorState, std::vector<::Req> requirements)
	{
		for (size_t i = 0; i < m_NextConnections.size(); i++)
		{
			if (m_NextConnections[i].AnimatorState == AnimatorState)
			{
				throw std::exception("[ERROR: Next AnimatorState has already been added");
			}
		}
		m_NextConnections.push_back(Connection(AnimatorState, requirements));
	}

	void BaseState::AddNextAnimatorState(::BaseState* AnimatorState, ::Req requirement)
	{
		for (size_t i = 0; i < m_NextConnections.size(); i++)
		{
			if (m_NextConnections[i].AnimatorState == AnimatorState)
			{
				throw std::exception("[ERROR: Next AnimatorState has already been added");
			}
		}
		m_NextConnections.push_back(Connection(AnimatorState, requirement));
	}

	void AnimatorState::RootExecute(float elapsedSec)
	{
		runTime += elapsedSec;
		Execute(elapsedSec);
	}

	void AnimatorState::SetSpeed(float speed)
	{
		m_Speed = speed;
	}

	float AnimatorState::GetSpeed() const
	{
		return m_Speed;
	}

	std::string AnimatorState::GetName() const
	{
		return m_Name;
	}

	bool AnimatorState::GetLooping()const
	{
		return m_isLooping;
	}

	void AnimatorState::LeaveState()
	{
		m_hasRun = false;
		runTime = 0;
	}

	unsigned int AnimatorState::GetValue() const
	{
		return m_EnumValue;
	}

	void AnimatorState::SetLooping(bool b)
	{
		m_isLooping = b;
	}

	AnimatorState::~AnimatorState()
	{
		m_NextConnections.clear();
	}
