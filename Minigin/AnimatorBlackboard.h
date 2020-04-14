#pragma once

#include <map>
#include "GeneralStructs.h"

enum class Logic { BIGGER, SMALL, EQUAL };

enum class BlackboardValueType
{
	unAssigned,
	boolValue,
	intValue,
	floatValue,
	Vector2Value
};


union UnionValue
{
	bool bValue;
	int iValue;
	float fValue;
	glm::vec2 V2Value;
};

//	int key;
struct BlackboardValue
{
	UnionValue value{false};
	BlackboardValueType type = BlackboardValueType::unAssigned;

	BlackboardValue()
	{
		this->type = BlackboardValueType::unAssigned;
	}

	BlackboardValue(BlackboardValueType type)
	{
		this->type = type;
		switch (type)
		{
		case BlackboardValueType::floatValue:
			this->value.fValue = 0.f;
			break;
		case BlackboardValueType::boolValue:
			this->value.bValue = false;
			break;
		case BlackboardValueType::Vector2Value:
			this->value.V2Value = glm::vec2(0, 0);
			break;
		case BlackboardValueType::intValue:
			this->value.iValue = 0;
			break;
		}
	}

	BlackboardValue(bool bValue)
	{
		this->value.bValue = bValue;
		this->type = BlackboardValueType::boolValue;
	}

	BlackboardValue(int iValue)
	{
		this->value.iValue = iValue;
		this->type = BlackboardValueType::intValue;
	}

	BlackboardValue(float fValue)
	{
		this->value.fValue = fValue;
		this->type = BlackboardValueType::floatValue;
	}

	BlackboardValue(glm::vec2 v2Value)
	{
		this->value.V2Value = v2Value;
		this->type = BlackboardValueType::Vector2Value;
	}
};

struct Requirement
{
	int key;
	BlackboardValue property;
	Logic logic;

	Requirement(int k, BlackboardValue value, Logic l)
	{
		this->key = k;
		this->property = value;
		this->logic = l;
	}

	Requirement(int k, BlackboardValue value)
	{
		this->key = k;
		this->property = value;
		this->logic = Logic::EQUAL;
	}
};

class AnimatorBlackboard
{
public:
	AnimatorBlackboard();
	~AnimatorBlackboard();

	void AddKey(int key, BlackboardValueType type);
	void SetKeyValue(int key, bool bValue);
	void SetKeyValue(int key, int iValue);
	void SetKeyValue(int key, float fValue);
	void SetKeyValue(int key, glm::vec2 V2Value);
	bool GetBoolProperty(int key);
	int GetIntProperty(int key);
	float GetFloatProperty(int key);
	glm::vec2 GetVector2Property(int key);
	BlackboardValue GetProperty(int key);
private:
	std::map<int, BlackboardValue> m_AnimatorBlackboardMap;
};
