#pragma once
#include "BaseEnemy.h"
#include "InputHandler.h"
class Bub;
class LevelSegment;
class RigidbodyComponent;
class Animator;
class SpriteComponent;
class Zen: public BaseEnemy
{
public:
	friend class PursuePlayerAndRush;
	friend class WanderState;
	friend class EC::GoDown;
	friend class EC::Jump;
	friend class EC::Shoot;
	friend class EC::MoveHorizontal;
	friend class EC::Rush;
	Zen(LevelSegment* segment);
	~Zen() override;
private:
	void Initialize() override;
	void Update(float elapsedSec) override;

	void SetRush(bool b);
	
	float rushVelocity = 35.0f;

	AnimatorState* m_pRoot = nullptr;
protected:
	void SetControlled(int PlayerId) override;
};

