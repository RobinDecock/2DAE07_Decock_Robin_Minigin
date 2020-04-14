#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "Pengo.h"

namespace SnobeeMovement
{
	enum SnobeeMovement { Down, Left, Right, Up, Destroy, Die, Idle };
}


static std::map<SnobeeMovement::SnobeeMovement, SpriteData>SnobeeSprites
{
	{SnobeeMovement::Idle,SpriteData(256, 144, 16, 16, 1, 1)},
	{SnobeeMovement::Up,SpriteData(320, 144, 32, 16, 2, 1)},
	{SnobeeMovement::Down,SpriteData(256, 144, 32, 16, 2, 1)},
	{SnobeeMovement::Left,SpriteData(288, 144, 32, 16, 2, 1)},
	{SnobeeMovement::Right,SpriteData(352, 144, 32, 16, 2, 1)}
};

class Snobee : public GameObject
{
public:
	Snobee(PlayField * playField);
	void Initialize() override;
	void Update(float elapsedSec) override;
	void Render() const override;
	void OnTrigger(BoxCollider2D* trigger, BoxCollider2D* receive) override;
	void Go(Direction dir);
	void Kill();
	void SetArrayPos(int2 pos);
	void SetStunned(bool b) { m_IsStunned = b; }
	void ChangeDirection();
	~Snobee();
private:
	bool inAction = false;
	bool m_IsStunned = false;
	int2 m_ArrayPos = int2(0, 0);
	float2 nextTarget = float2(0, 0);
	int2 nextTargetArray = int2(0, 0);
	RigidbodyComponent * m_pRigid = nullptr;
	SpriteComponent * sprite = nullptr;
	Direction currDir = Left;
	PlayField* m_pPlayField = nullptr;
	SnobeeMovement::SnobeeMovement m_SnobeeMovement = SnobeeMovement::Idle;
	SnobeeMovement::SnobeeMovement m_OldSnobeeMovement = SnobeeMovement::Idle;
};

