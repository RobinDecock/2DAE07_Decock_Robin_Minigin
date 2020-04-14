#pragma once
#include "SpriteComponent.h"
#include "GameObject.h"


class Boundary : public dae::GameObject
{
public:
	Boundary(PlayField *playField);
	void Initialize() override;
	void Update(float elapsedSec) override;
	void Trigger();
	~Boundary() = default;
private:

	float m_TriggerTimer = 0;
	float m_TriggerDelay = 2;
	bool m_IsTriggered = false;
	PlayField *m_pPlayField = nullptr;
	SpriteComponent  * m_pSprite = nullptr;
	SpriteData Idle{ 0,0,8,256,1,1 };
	SpriteData Active{ 0,0,24,256,3,1 };
};

