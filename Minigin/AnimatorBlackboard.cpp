#include "MiniginPCH.h"
#include "AnimatorBlackboard.h"
#include <map>


AnimatorBlackboard::AnimatorBlackboard()
{
}


AnimatorBlackboard::~AnimatorBlackboard()
{
}

void AnimatorBlackboard::AddKey(int key, BlackboardValueType type)
{
	if (m_AnimatorBlackboardMap.find(key) == m_AnimatorBlackboardMap.end())
	{
		m_AnimatorBlackboardMap.insert(std::pair<int, BlackboardValue>(key, BlackboardValue(type)));
	}
	std::cout << "" << std::endl;
}

//****************************
//SET FUNCTIONS
//****************************
void AnimatorBlackboard::SetKeyValue(int key, bool bValue)
{
	if (m_AnimatorBlackboardMap.find(key) != m_AnimatorBlackboardMap.end())
	{
		auto& pProperty = m_AnimatorBlackboardMap.at(key);
		if (pProperty.type != BlackboardValueType::boolValue)
		{
			throw std::exception("[ERROR: SetKey(bool) => keyValue is not of type bool!!]");
			return;
		}
		pProperty.value.bValue = bValue;
	}
	else
	{
		throw std::exception("[ERROR: SetKey(bool) => key doesn't exists in map!!]");
	}
}

void AnimatorBlackboard::SetKeyValue(int key, int iValue)
{
	if (m_AnimatorBlackboardMap.find(key) != m_AnimatorBlackboardMap.end())
	{
		auto& pProperty = m_AnimatorBlackboardMap.at(key);
		if (pProperty.type != BlackboardValueType::intValue)
		{
			throw std::exception("[ERROR: SetKey(int) => keyValue is not of type int!!]");
			return;
		}
		pProperty.value.iValue = iValue;
	}
	else
	{
		throw std::exception("[ERROR: SetKey(int) => key doesn't exists in map!!]");
	}
}

void AnimatorBlackboard::SetKeyValue(int key, float fValue)
{
	if (m_AnimatorBlackboardMap.find(key) != m_AnimatorBlackboardMap.end())
	{
		auto& pProperty = m_AnimatorBlackboardMap.at(key);
		if (pProperty.type != BlackboardValueType::floatValue)
		{
			throw std::exception("[ERROR: SetKey(float) => keyValue is not of type float!!]");
			return;
		}
		pProperty.value.fValue = fValue;
	}
	else
	{
		throw std::exception("[ERROR: SetKey(float) => key doesn't exists in map!!]");
	}
}

void AnimatorBlackboard::SetKeyValue(int key, glm::vec2 V2Value)
{
	if (m_AnimatorBlackboardMap.find(key) != m_AnimatorBlackboardMap.end())
	{
		auto& pProperty = m_AnimatorBlackboardMap.at(key);
		if (pProperty.type != BlackboardValueType::Vector2Value)
		{
			throw std::exception("[ERROR: SetKey(Vector2) => keyValue is not of type Vector2!!]");
		}
		pProperty.value.V2Value = V2Value;
	}
	else
	{
		throw std::exception("[ERROR: SetKey(Vector2) => key doesn't exists in map!!]");
	}
}

//****************************
//GET FUNCTIONS
//****************************
bool AnimatorBlackboard::GetBoolProperty(int key)
{
	if (m_AnimatorBlackboardMap.find(key) != m_AnimatorBlackboardMap.end())
	{
		const auto pProperty = m_AnimatorBlackboardMap.at(key);
		if (pProperty.type != BlackboardValueType::boolValue)
		{
			throw std::exception("[ERROR: SetKey(bool) => keyValue is not of type bool!!]");
		}
		return pProperty.value.bValue;
	}
	throw std::exception("[ERROR: SetKey(bool) => key doesn't exists in map!!]");
}

int AnimatorBlackboard::GetIntProperty(int key)
{
	if (m_AnimatorBlackboardMap.find(key) != m_AnimatorBlackboardMap.end())
	{
		auto& pProperty = m_AnimatorBlackboardMap.at(key);
		if (pProperty.type != BlackboardValueType::intValue)
		{
			throw std::exception("[ERROR: SetKey(int) => keyValue is not of type int!!]");
		}
		return pProperty.value.iValue;
	}
	throw std::exception("[ERROR: SetKey(int) => key doesn't exists in map!!]");
}

float AnimatorBlackboard::GetFloatProperty(int key)
{
	if (m_AnimatorBlackboardMap.find(key) != m_AnimatorBlackboardMap.end())
	{
		auto& pProperty = m_AnimatorBlackboardMap.at(key);
		if (pProperty.type != BlackboardValueType::floatValue)
		{
			throw std::exception("[ERROR: SetKey(float) => keyValue is not of type float!!]");
		}
		return pProperty.value.fValue;
	}
	throw std::exception("[ERROR: SetKey(float) => key doesn't exists in map!!]");
}

glm::vec2 AnimatorBlackboard::GetVector2Property(int key)
{
	if (m_AnimatorBlackboardMap.find(key) != m_AnimatorBlackboardMap.end())
	{
		auto& pProperty = m_AnimatorBlackboardMap.at(key);

		if (pProperty.type != BlackboardValueType::Vector2Value)
		{
			throw std::exception("[ERROR: SetKey(Vector2) => keyValue is not of type Vector2!!]");
		}
		return pProperty.value.V2Value;
	}
	throw std::exception("[ERROR: SetKey(Vector2) => key doesn't exists in map!!]");
}

BlackboardValue AnimatorBlackboard::GetProperty(int key)
{
	if (m_AnimatorBlackboardMap.size() > 0)
	{
		return m_AnimatorBlackboardMap.at(key);
	}
	return BlackboardValue{};
}
