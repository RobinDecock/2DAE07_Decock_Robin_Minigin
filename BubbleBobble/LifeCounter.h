#pragma once
#include "GameObject.h"
#include "Observer.h"
class Bub;
class LifeCounter:public GameObject,public Observer
{
public:
	LifeCounter(Bub* ref);
	void onNotify(int event,GameObject* obj = nullptr) override;
private:
	std::vector<GameObject*> lives;
};

