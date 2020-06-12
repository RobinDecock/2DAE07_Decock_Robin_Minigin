#pragma once
#include "GameObject.h"
#
class ScoreAnnouncer:public GameObject
{
public:
	ScoreAnnouncer(int score);
	void Initialize() override;
private:
	int m_pScore = 0;
};

