#pragma once

#include "AnimatorBlackboard.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Command.h"
#include "PlayerCommands.h"
class Bub;
class RigidbodyComponent;
class Animator;
class SpriteComponent;

class EffectorComponent;











class AnimatorState;


class Bub final :
	public GameObject
{
public:
	friend class PC::GoDown;
	friend class PC::Jump;
	friend class PC::ShootBubble;
	friend class PC::MoveHorizontal;
	Bub(int playerId);
	~Bub() override;
	void Attack();
	void MoveToLocation(float elapsedSec, glm::vec2 goPos);
	void SetRespawning(bool b);
	void SetRespawningPoint(glm::vec2 pos) { spawnPoint = pos; }
	bool playerR = false;
private:
	void Initialize() override;
	void Update(float elapsedSec) override;

	enum AnimType
	{
		BubRespawn=0, BubWalk=1, BubJump=2, BubBurb=3, BubDie, BubIdle=5, BubFall =8
	};
	
	std::shared_ptr<Animator> m_pAnimator = nullptr;
	AnimatorBlackboard m_Blackboard;
	std::shared_ptr<RigidbodyComponent> m_pRigid;
	std::shared_ptr<SpriteComponent>m_pSprite;
	PTR(BoxCollider)m_pBoxCol = nullptr;
	bool m_IsOnGround = false;

	float maxXVel = 2000;
	
	enum BKey
	{
		AbsVelocityX,
		VelocityY,
		OnGround,
		IsBurping,
		Respawning
	};
	bool isRight = true;
	bool m_Respawning = true;

	int m_PlayerId = 0;
	glm::vec2 spawnPoint = {0,0};
	InputHandler inputHandler;
	std::shared_ptr<EffectorComponent> platformEff = nullptr;
	PC::GoDown *m_pGoDown = nullptr;

	std::shared_ptr<AnimatorState> m_pRespawning = nullptr;
};

