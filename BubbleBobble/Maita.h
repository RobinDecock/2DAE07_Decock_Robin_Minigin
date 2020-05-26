#pragma once
#include "BaseEnemy.h"


class LevelSegment;

class Maita : public BaseEnemy
{
public:
	Maita(LevelSegment* segment);
private:
	void Initialize() override;
	
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;
};

