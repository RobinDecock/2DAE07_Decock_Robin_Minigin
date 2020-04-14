#pragma once
#include "GameObject.h"
#include "Pengo.h"

class Block : public GameObject
{
public:
	Block();
	void Initialize() override;
	void Update(float elapsedSec) override;
	void Render() const override;

	void Push(Direction dir);
	void Move(Direction dir);
	void SetArrayPos(int2 pos);
	bool GetInAction() { return inAction; }
	bool IsPointValid(int2 arrPoint);
	bool GetTargetFromDir(Direction dir, int2& targetArr);
	int2 GetArrayPos() { return m_ArrayPos; }
	~Block()=default;
protected:
	float Speed = 3.0f;
	bool broken = false;
	bool inAction = false;
	PlayField* m_pPlayField = nullptr;
	float2 nextTarget = float2(0, 0);
	int2 nextTargetArray = int2(0, 0);
	int2 m_ArrayPos = int2(0, 0);
	RigidbodyComponent * m_pRigid = nullptr;
	BoxCollider2D * m_Collider = nullptr;
};

