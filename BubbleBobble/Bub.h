#pragma once
#include "AnimatorBlackboard.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Observer.h"
#include "PlayerCommands.h"
class Bub;
class RigidbodyComponent;
class Animator;
class SpriteComponent;

class EffectorComponent;
class AnimatorState;


class Bub final :
	public GameObject,public Subject
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
	int GetPlayerId()const { return m_PlayerId; }
	int GetHealth()const { return m_Health; }
	bool IsRespawning()const { return m_Respawning; }
private:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void PhysicsUpdate(float elapsedSec) override;
	enum AnimType
	{
		BubRespawn, BubWalk, BubJump, BubBurb, BubHit, BubIdle = 5, BubFall = 8
	};

	Animator* m_pAnimator = nullptr;
	AnimatorBlackboard m_Blackboard;
	RigidbodyComponent* m_pRigid = nullptr;
	SpriteComponent* m_pSprite = nullptr;
	BoxCollider * m_pBoxCol = nullptr;
	bool m_IsOnGround = false;

	const float maxXVel = 75.0f;

	enum BKey
	{
		AbsVelocityX,
		VelocityY,
		OnGround,
		IsBurping,
		Respawning,
		IsHit
	};
	bool m_IsInvincible = false;
	float invincibleTimer = 0.0f;
	float invincibleDelay = 2.0f;
	float invisibleCounter = 0.0f;

	float maxT = 0.1f;

	int m_Health = 3;
	bool isRight = true;
	bool m_Respawning = true;

	int m_PlayerId = 0;
	glm::vec2 spawnPoint = { 0,0 };
	InputHandler inputHandler;
	EffectorComponent * platformEff = nullptr;
	

	//COMMANDS
	PC::ShootBubble m_ShootC = PC::ShootBubble(this);
	PC::Jump m_JumpC = PC::Jump(this);
	PC::MoveHorizontal m_MoveHC = PC::MoveHorizontal(this);
	PC::GoDown m_GoDownC = PC::GoDown(this);
	
};

