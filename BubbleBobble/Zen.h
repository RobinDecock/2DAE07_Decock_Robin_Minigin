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
	friend class WanderState;
	friend class EC::GoDown;
	friend class EC::Jump;
	friend class EC::Shoot;
	friend class EC::MoveHorizontal;
	Zen(LevelSegment* segment);
	~Zen() override;
private:
	void Initialize() override;
	
	void Update(float elapsedSec) override;

protected:
	void HandleAI(float elapsedSec) override;
	void SetControlled(int PlayerId) override;
private:




};

