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

	void LateUpdate(float elapsedSec) override;
	void Draw() override;
private:
	std::shared_ptr<Animator> m_pAnimator = nullptr;
	AnimatorBlackboard m_Blackboard;
	std::shared_ptr<RigidbodyComponent> m_pRigid;
	std::shared_ptr<SpriteComponent>m_pSprite;
	std::shared_ptr<BoxTrigger> m_pBoxTrigger;
	float moveTimer = 0.0f;
	float moveDelay = 0.25f;

	int m_PlayerId = 0;
	bool m_IsRight = false;
	enum AnimType
	{
		BubbleV1 = 6,BubbleV2 = 7
	};

	enum BlackboardKey
	{
		IsExploding
	};
};

