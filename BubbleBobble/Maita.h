#pragma once
#include "BaseEnemy.h"


class LevelSegment;

class Maita : public BaseEnemy
{
public:
	friend class PursuePlayerAndShoot;
	friend class EC::Shoot;
	Maita(LevelSegment* segment);
	~Maita()override;
	void Update(float elapsedSec)override;
	void SetControlled(int PlayerId) override;	
private:
	void Initialize() override;
	EC::Shoot m_pShootC = EC::Shoot(this);
	float m_ShootDelay = 2.0f;
	float m_ShootTimer = 0.0f;
};

