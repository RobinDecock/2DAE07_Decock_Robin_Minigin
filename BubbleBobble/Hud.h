#pragma once
#include "Singleton.h"
#include <GameObject.h>
class PlayerHud;
class Font;

class Hud final: public Singleton<Hud>,public GameObject

{
public:
	Hud();
	~Hud() override;
	void AddLifeCounter(PlayerHud* counter);
private:
	void Initialize() override;
	
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw()const override;
private:
	int m_Score = 0;
	std::vector<PlayerHud*> counters;

};

