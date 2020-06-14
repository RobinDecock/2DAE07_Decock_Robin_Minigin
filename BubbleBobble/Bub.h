#pragma once
#include "AnimatorBlackboard.h"
#include "PlayerCommands.h"
#include "BubStates.h"
#include "GameObject.h"
#include "Observer.h"
#include "PlayerHud.h"

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
	friend class RespawnState;
	friend class NormalState;
	friend class HitState;
	friend class AerialState;
	Bub(int playerId);
	~Bub() override;
	void Attack();
	void MoveToLocation(float elapsedSec, glm::vec2 goPos);
	void SetRespawning(bool b);
	void SetRespawningPoint(glm::vec2 pos) { m_SpawnPoint = pos; }
	bool IsRespawned() { return m_DoneRespawning; }
	bool m_PlayerReady = false;
	int GetPlayerId()const { return m_PlayerId; }
	int GetHealth()const { return m_Health; }
	bool IsInvincible()const { return m_IsInvincible; }
	void AddScore(int amount)
	{
		m_Score += amount; Notify(New_Score,this);
	}
	int GetScore()const  { return m_Score; }
private:
	void SetCurrentState(BubState* state);
	void Initialize() override;
	void Update(float elapsedSec) override;
	void PhysicsUpdate(float elapsedSec) override;
	void LateInitialize() override;
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
	const float m_MaxXVel = 75.0f;

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
	float m_InvincibleTimer = 0.0f;
	float m_InvincibleDelay = 2.0f;
	float m_InvisibleTimer = 0.0f;
	bool m_DoneRespawning = false;
	int m_Health = 3;
	bool m_IsRight = true;
	bool m_JumpedOnBubble = false;
	int m_PlayerId = 0;
	int m_Score = 0;
	
	glm::vec2 m_SpawnPoint = { 0,0 };

	EffectorComponent * m_pPlatformEff = nullptr;
	

	//COMMANDS
	PC::ShootBubble m_ShootC = PC::ShootBubble(this);
	PC::Jump m_JumpC = PC::Jump(this);
	PC::MoveHorizontal m_MoveHC = PC::MoveHorizontal(this);
	PC::GoDown m_GoDownC = PC::GoDown(this);

	BubState* m_pCurrentState = nullptr;
};

