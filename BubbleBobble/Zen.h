#pragma once
#include "AnimatorBlackboard.h"
#include "BaseEnemy.h"
#include "GameObject.h"
#include "InputHandler.h"
class Bub;
class LevelSegment;
class RigidbodyComponent;
class Animator;
class SpriteComponent;
class Zen: public BaseEnemy
{
public:
	Zen(LevelSegment* segment);
	~Zen() override;
private:
	void Initialize() override;
	
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;

protected:
	void HandleInput(float elapsedSec) override;
	void HandleAI(float elapsedSec) override;
	void SetControlled(int PlayerId) override;
private:
	std::shared_ptr<Animator> m_pAnimator = nullptr;
	AnimatorBlackboard m_Blackboard{};
	std::shared_ptr<RigidbodyComponent> m_pRigid{};
	std::shared_ptr<SpriteComponent>m_pSprite{};
	PTR(BoxCollider)m_pBoxCol {};
	LevelSegment* m_pLevelSegment = nullptr;
	bool m_IsBubbled = false;
	GameObject* lockedPlayer = nullptr;

	float walkTimer = 0.0f;
	float walkDelay = -1.0f;

	float maxDelay = 4.0f;
	float minDelay = 0.0f;


	float m_MaxVelocity = 5.0f;
	float currVelocity = m_MaxVelocity;
	enum Behaviour
	{
		Wandering, Locked
	};
	
	Behaviour  m_Behaviour;
	enum AnimType
	{
		ZenChan, Maita, MaitaBubble, ZenChanBubble
	};
	enum BlackboardKey
	{
		InBubble
	};

	float jumpTimer = 0.0f;
	float jumpDelay = 2.0f;
	bool m_IsRight = false;
	GameObject * m_OnPlatform;


};

