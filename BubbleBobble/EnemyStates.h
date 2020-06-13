#pragma once
#include "Bub.h"
class BaseEnemy;
class State;

class State
{
public:
	virtual State* Execute(float elapsedSec) { return nullptr; };
	
};




class WanderState:public State
{
public:
	WanderState(BaseEnemy* pEnemy):m_pEnemy(pEnemy){}
	State* Execute(float elapsedSec) override;
private:
	BaseEnemy* m_pEnemy = nullptr;
	float m_WalkDelay = 2.0f;
	float m_WalkTimer = 0.0f;
	
};

class PursuePlayer :public State
{
public:
	PursuePlayer(BaseEnemy* pEnemy,Bub* lockedPlayer) :m_pEnemy(pEnemy), m_pLockedPlayer(lockedPlayer){}
	State *Execute(float elapsedSec) override;
protected:
	BaseEnemy* m_pEnemy = nullptr;
	Bub* m_pLockedPlayer = nullptr;

	float m_LockedTimer = 0.0f;

};

class PursuePlayerAndShoot :public PursuePlayer
{
public:
	PursuePlayerAndShoot(BaseEnemy* pEnemy, Bub* lockedPlayer);
	State* Execute(float elapsedSec) override;
protected:

	
	float m_ShootTimer = 0.0f;
	
};
