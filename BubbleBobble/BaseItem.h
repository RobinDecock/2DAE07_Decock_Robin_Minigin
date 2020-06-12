#pragma once
#include "GameObject.h"
#include "LevelSegment.h"
class b2Fixture;
class b2Contact;

enum class ItemType{Melon,Fries};

class BaseItem: public GameObject
{
public:
	void PickUp();
protected:
	void Initialize() override;

	LevelSegment* m_pLevelSegment = nullptr;
	
	int scoreValue = 10;
	
};



class Fries: public BaseItem
{
	void Initialize() override;
};

class Melon : public BaseItem
{
	void Initialize() override;
};