#pragma once
#include "ColliderComponent.h"

//enum LayerMask
//{
//	None = 0xffff,
//	LevelL = 0x0001,
//	EnemiesL = 0x0002,
//	PlayerL = 0x0004
//};

class BoxCollider final : public ColliderComponent
{
public:
	BoxCollider(const BoxCollider& other) = delete;
	BoxCollider(BoxCollider&& other) noexcept = delete;
	BoxCollider& operator=(const BoxCollider& other) = delete;
	BoxCollider& operator=(BoxCollider&& other) noexcept = delete;
	BoxCollider(glm::vec2 widthHeight, glm::vec2 localCenter=glm::vec2(0,0));
	~BoxCollider();
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
};

