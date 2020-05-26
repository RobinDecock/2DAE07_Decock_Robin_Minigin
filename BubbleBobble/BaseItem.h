#pragma once
#include "GameObject.h"
class b2Fixture;
class b2Contact;
class BaseItem: public GameObject
{
public:
	~BaseItem() override;
protected:
	void Initialize() override;

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