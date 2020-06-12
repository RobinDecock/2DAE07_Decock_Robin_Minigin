#pragma once
#include "BaseEnemy.h"


class LevelSegment;

class Maita : public BaseEnemy
{
public:
	Maita(LevelSegment* segment);
	~Maita()override;
private:
	void Initialize() override;
	EC::Shoot m_pShootC = nullptr;
	
protected:
	void HandleAI(float elapsedSec) override;
public:
	void SetControlled(int PlayerId) override;

	
};

