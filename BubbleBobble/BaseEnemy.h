#pragma once
#include "AnimatorBlackboard.h"
#include "ControllerVisual.h"
#include "EnemyCommands.h"
#include "EnemyStates.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "RigidbodyComponent.h"
#include "SingleScene.h"
class Animator;
class SpriteComponent;
class LevelSegment;

class BaseEnemy: public GameObject
{
public:
	friend class WanderState;
	friend class PursuePlayer;
	friend class EC::GoDown;
	friend class EC::Jump;
	friend class EC::Shoot;
	friend class EC::MoveHorizontal;
	BaseEnemy(LevelSegment* segment);
	~BaseEnemy() override;
	bool GetIsOnGround()const { return m_IsOnGround; }
	float GetMaxVelX()const  { return m_MaxXVelocity; }
	void SetPaused(bool b) { isPaused = b; }
	bool IsControlled()const { return m_IsControlled; }
	int GetController()const { return m_ControllerId; }
	bool IsRight()const { return m_IsRight; }
	bool IsBubbled() const { return m_IsBubbled; }
	float GetJumpStrength()const {return m_JumpStength;}
	Bub* GetLockedPlayer() const { return lockedPlayer; }
	void SetLockedPlayer(Bub* p)
	{	lockedPlayer = p; }
	
	virtual void SetControlled(int PlayerId)
	{
		m_IsControlled = true;
		m_ControllerId = PlayerId;
		ControllerVisual* visual = new ControllerVisual();
		AddChild(visual);
		visual->SetPosition(glm::vec2(0, -10));
	}
	void DropItem();
	
	
	void SetBubbled(bool b);
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void Draw()const override {};

	virtual void HandleAI(float elapsedSec) = 0;
	bool m_IsOnGround = false;
	float m_MaxXVelocity = 40.0f;

	InputHandler* m_pInputHandler = nullptr;
	LevelSegment* m_pLevelSegment = nullptr;
	
	bool m_IsBubbled = false;
	enum class Behaviour
	{
		Wandering, Locked
	};
	RigidbodyComponent* m_pRigid = nullptr;

	SingleScene* singleScene = nullptr;
	float m_LockedDelay = 4.0f;
	GameObject* m_OnPlatform = nullptr;

	GameObject* m_pRoof = nullptr;
	float viewDist = 50.0f;
	Animator* m_pAnimator = nullptr;
	AnimatorBlackboard m_Blackboard{};

	SpriteComponent* m_pSprite = nullptr;

	float m_BubbledTimer = 0.0f;
	float m_BubbledDelay = 6.0f;
	BoxCollider * m_pBoxCol =nullptr;

	EC::GoDown m_pGoDownC = EC::GoDown(this);
	EC::Jump m_pJumpC = EC::Jump(this);
	EC::MoveHorizontal m_pMoveHC = EC::MoveHorizontal(this);

	enum class EnemyType
	{
		Maita,ZenChan
	};

	EnemyType m_EnemyType;
	State *m_pCurrentState =new WanderState(this);
	
	enum class AnimType
	{
		ZenChan, Maita, MaitaBubble, ZenChanBubble
	};
	enum BlackboardKey
	{
		InBubble
	};


	Bub* lockedPlayer = nullptr;




	float m_MinWalkDelay = 2.0f;
	float m_MaxWalkDelay = 6.0f;


	bool m_GoingRight = false;
	float m_JumpTimer = 0.0f;
	float m_JumpDelay = 2.0f;
	bool m_IsRight = false;
	const float m_JumpStength = 70;


	bool foundWall = false;
private:
	void PhysicsUpdate(float elapsedSec) override;
	bool isPaused = false;
	bool m_IsControlled = false;
	int m_ControllerId = -1;
	
	
};

