#pragma once
#include "EnemyCommands.h"
#include "GameObject.h"
#include "InputHandler.h"

class BaseEnemy: public GameObject
{
public:
	~BaseEnemy() override;
	bool GetIsOnGround()const { return m_IsOnGround; }
	float GetMaxVelX() { return maxXVel; }
	void SetPaused(bool b) { isPaused = b; }
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;

	virtual void SetControlled(int PlayerId) = 0;
	virtual void HandleInput(float elapsedSec) = 0;
	virtual void HandleAI(float elapsedSec) = 0;
	bool m_IsOnGround = false;
	float maxXVel = 5.0f;

	InputHandler* m_pInputHandler = nullptr;
	
	//Commands
	EC::Jump* m_pJumpC = nullptr;
	EC::MoveHorizontal* m_pMoveHC = nullptr;
	

	
private:
	bool isPaused = false;
	bool isControlled = false;

	
	
};

