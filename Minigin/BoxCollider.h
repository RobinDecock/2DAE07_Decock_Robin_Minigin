#pragma once
#include "ColliderComponent.h"

enum LayerMask
{
	None = 0xffff,
	LevelL = 0x0001,
	EnemiesL = 0x0002,
	PlayerL = 0x0004
};

class BoxCollider final : public ColliderComponent
{
public:
	BoxCollider(const BoxCollider& other) = delete;
	BoxCollider(BoxCollider&& other) noexcept = delete;
	BoxCollider& operator=(const BoxCollider& other) = delete;
	BoxCollider& operator=(BoxCollider&& other) noexcept = delete;

	BoxCollider(glm::vec2 widthHeight, LayerMask mask = LayerMask::None, LayerMask collideWith = LayerMask::None);
	~BoxCollider();

	void Release()override;
	void CreateShape(b2Body& bd)override;
protected:
	void Initialize() override;
	void LateInitialize()override;
	void Update(float elapsedSec) override;
	void Draw() override;
private:
	LayerMask m_Mask = LayerMask::None;
	LayerMask m_CollideWith = LayerMask::None;
};

