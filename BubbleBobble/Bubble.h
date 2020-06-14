#pragma once
#include "AnimatorBlackboard.h"
#include "BoxTrigger.h"
#include "GameObject.h"
class RigidbodyComponent;
class Animator;
class SpriteComponent;


class Bubble final: public GameObject
{
public:
	Bubble(bool isRight,int playerId);
	~Bubble() override;
protected:
	void Initialize() override;
	void LateInitialize() override;
	void Update(float elapsedSec) override;
private:
	Animator* m_pAnimator = nullptr;
	AnimatorBlackboard m_Blackboard;
	RigidbodyComponent* m_pRigid = nullptr;
	SpriteComponent* m_pSprite = nullptr;
	BoxTrigger* m_pBoxTrigger = nullptr;

	int m_PlayerId = 0;
	bool m_IsRight = false;

	float forceDelay = 0.5f;
	
	enum AnimType
	{
		BubbleV1 = 6,BubbleV2 = 7
	};

	enum BKey
	{
		IsExploding
	};

	BoxCollider* pBoxCol = nullptr;
};

