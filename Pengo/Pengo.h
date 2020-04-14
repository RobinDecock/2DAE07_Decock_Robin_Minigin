#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"


class BoxCollider2D;




namespace PlayerMovement
{
	enum PlayerMovement { Down, Left, Right, Up, Push, Die, Idle };
}

static std::map<PlayerMovement::PlayerMovement, SpriteData>PlayerSprites
{
	{PlayerMovement::Idle,SpriteData(0, 0, 16, 16, 1, 1)},
	{PlayerMovement::Up,SpriteData(64, 0, 32, 16, 2, 1)},
	{PlayerMovement::Down,SpriteData(0, 0, 32, 16, 2, 1)},
	{PlayerMovement::Left,SpriteData(32, 0, 32, 16, 2, 1)},
	{PlayerMovement::Right,SpriteData(96, 0, 32, 16, 2, 1)},
	{PlayerMovement::Die,SpriteData(0, 32, 32, 16, 2, 1)}

};

class IceBlock;
class Pengo : public GameObject
{
public:
	Pengo(PlayField * playField);
	void Initialize() override;
	void Render() const override;
	void Update(float elapsedSec) override;
	
	void Kill();
	void Respawn();
	void SetArrayPosition(int2 pos);
	int2 GetArrayPos() { return m_ArrayPos; }
	bool GetIsDead() { return isDead; }
	~Pengo() = default;

private:
	//Priv. functions
	void Go(Direction dir);
	bool IsNextPositionValid(int2 dir);


	//Priv. Variables
	bool isDead = false;
	RigidbodyComponent * m_pRigid = nullptr;
	SpriteComponent * sprite = nullptr;
	PlayerMovement::PlayerMovement m_PlayerMovement = PlayerMovement::Idle;
	PlayerMovement::PlayerMovement m_OldPlayerMovement = PlayerMovement::Idle;
	float playerMovement = 50;
	int2 m_ArrayPos = int2(0, 0);
	bool inAction = false;
	PlayField* m_pPlayField = nullptr;
	float2 nextTarget = float2(0, 0);
	int2 nextTargetArray = int2(0, 0);
};


