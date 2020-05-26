#pragma once
#include <map>
#include "vec2.hpp"
#include "GeneralStructs.h"

enum class ValueType
{
	unAssigned,
	boolValue,
	intValue,
	floatValue,
	V2Value
};


union UnionValue
{
	UnionValue(bool b):bValue(b){}
	UnionValue(float f) :fValue(f) {}
	UnionValue(int i) :iValue(i) {}
	UnionValue(glm::vec2 vec) :V2Value(vec) {}
	bool bValue;
	int iValue;
	float fValue;
	glm::vec2 V2Value;
};

//	int key;
struct BlackboardValue
{
	UnionValue value{ false };
	ValueType type = ValueType::unAssigned;

	BlackboardValue()
	{
		this->type = ValueType::unAssigned;
	}

	BlackboardValue(ValueType type)
	{
		this->type = type;
		switch (type)
		{
		case ValueType::floatValue:
			this->value.fValue = 0.f;
			break;
		case ValueType::boolValue:
			this->value.bValue = false;
			break;
		case ValueType::intValue:
			this->value.iValue = 0;
			break;
		case ValueType::V2Value:
			this->value.V2Value = glm::vec2();
			break;
		default:
			break;
		}
	}

	BlackboardValue(bool bValue)
	{
		this->value.bValue = bValue;
		this->type = ValueType::boolValue;
	}

	BlackboardValue(int iValue)
	{
		this->value.iValue = iValue;
		this->type = ValueType::intValue;
	}

	BlackboardValue(float fValue)
	{
		this->value.fValue = fValue;
		this->type = ValueType::floatValue;
	}
	BlackboardValue(glm::vec2 v2Value)
	{
		this->value.V2Value = v2Value;
		this->type = ValueType::V2Value;
	}
};

struct Req
{
	int key;
	BlackboardValue property;
	Logic logic;

	Req(int k, float value, Logic l = Logic::EQUAL)
	{
		this->key = k;
		this->property = value;
		this->logic = l;
	}
	Req(int k, int value, Logic l = Logic::EQUAL)
	{
		this->key = k;
		this->property = value;
		this->logic = l;
	}
	Req(int k, bool value, Logic l = Logic::EQUAL)
	{
		this->key = k;
		this->property = value;
		this->logic = l;
	}
	Req(int k, glm::vec2 value, Logic l = Logic::EQUAL)
	{
		this->key = k;
		this->property = value;
		this->logic = l;
	}
};

class AnimatorBlackboard
{
public:
	AnimatorBlackboard();
	~AnimatorBlackboard();

	void AddKey(int key, ValueType type);
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
