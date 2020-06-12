#pragma once
#include <map>
#include "GLMS.h"
#include "GeneralStructs.h"

enum class ValueType
{
	boolValue,
	intValue,
	floatValue
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
	ValueType type = ValueType::intValue;

	BlackboardValue() = default;
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
	bool GetBoolProperty(int key);
	int GetIntProperty(int key);
	float GetFloatProperty(int key);
	BlackboardValue GetProperty(int key);

	template<class t1, class t2>
	static bool CheckLogic(t1 value1, t2 value2, Logic l)
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
	bool CheckRequirement(Req desiredProperty);
private:
	std::map<int, BlackboardValue> m_AnimatorBlackboardMap;
};
