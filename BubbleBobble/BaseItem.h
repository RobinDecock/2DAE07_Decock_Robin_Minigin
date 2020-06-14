#pragma once
#include "GameObject.h"
#include "LevelSegment.h"
class b2Fixture;
class b2Contact;

enum class ItemType{Melon,Fries};

class BaseItem: public GameObject
{
public:
	BaseItem(){}
	~BaseItem();
protected:
	void Initialize() override;

	LevelSegment* m_pLevelSegment = nullptr;
	int scoreValue = 10;
	bool pickedup = false;
};

class Fries: public BaseItem
{
public:
	Fries() { scoreValue = 200; }
protected:
	void Initialize() override;
};

class Melon : public BaseItem
{
public:
	Melon() { scoreValue = 100; }
protected:
	void Initialize() override;
};