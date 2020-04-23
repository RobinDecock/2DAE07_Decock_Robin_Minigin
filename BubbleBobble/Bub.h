#pragma once

#include "AnimatorBlackboard.h"
#include "GameObject.h"
class RigidbodyComponent;
class Animator;
class SpriteComponent;
class Bub final :
	public GameObject
{
public:
	~Bub() override;
	void OnTrigger(BoxCollider* col, BoxCollider* other) override;
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;
private:


	enum class AnimType :int
	{
		BubRespawn, BubWalk, BubJump, BubBurb
	};

	std::shared_ptr<Animator> m_pAnimator = nullptr;
	AnimatorBlackboard m_Blackboard;
	std::shared_ptr<RigidbodyComponent> m_pRigid;
	std::shared_ptr<SpriteComponent>m_pSprite;
	
	enum class BlackboardKey
	{
		AbsVelocityX,
		VelocityY,
		OnGround,
		IsBurping
	};
	bool isRight = true;
};

