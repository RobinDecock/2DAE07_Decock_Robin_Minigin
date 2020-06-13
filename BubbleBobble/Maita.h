#pragma once
#include "BaseEnemy.h"


class LevelSegment;

class Maita : public BaseEnemy
{
public:
	friend class PursuePlayerAndShoot;
	Maita(LevelSegment* segment);
	~Maita()override;
	void SetControlled(int PlayerId) override;
protected:
	void HandleAI(float elapsedSec) override;
	
private:
	void Initialize() override;
	EC::Shoot m_pShootC = EC::Shoot(this);
	float m_ShootDelay = 2.0f;
};

