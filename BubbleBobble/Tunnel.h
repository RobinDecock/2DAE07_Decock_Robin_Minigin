#pragma once
#include "BoxTrigger.h"
#include "GameObject.h"

class Tunnel final:public GameObject
{
public:
	Tunnel();

	void Initialize() override;
	void PhysicsUpdate(float elapsedSec) override;
private:
	BoxTrigger *  boxT = nullptr;

	//might give problems if both players fall at the same time
	std::vector<GameObject*> hitObjects;
};

