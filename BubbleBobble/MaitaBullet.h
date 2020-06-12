#pragma once
#include "GameObject.h"
#include "RigidbodyComponent.h"

class MaitaBullet: public GameObject
{
public:
	MaitaBullet(bool isRight) :m_IsRight(isRight){}
private:
	void Initialize() override;
	void PhysicsUpdate(float elapsedSec) override;

	bool m_IsRight = false;
	RigidbodyComponent* m_pRigid = nullptr;
	float maxVelX = 10;
};

