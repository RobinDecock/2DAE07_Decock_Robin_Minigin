#pragma once

#include "BaseComponent.h"
#include <vector>
#include "ColliderComponent.h"
#include "GeneralStructs.h"
class b2Body;

class RigidbodyComponent final : public BaseComponent
{
	friend class BoxCollider;
public:
	RigidbodyComponent(const RigidbodyComponent& other) = delete;
	RigidbodyComponent(RigidbodyComponent&& other) noexcept = delete;
	RigidbodyComponent& operator=(const RigidbodyComponent& other) = delete;
	RigidbodyComponent& operator=(RigidbodyComponent&& other) noexcept = delete;
	RigidbodyComponent(bool isStatic = false);

	void Initialize() override;
	void LateInitialize() override;
	void Update(float elapsedSec) override;
	void AddCollider(ColliderComponent* collider);

	void SetBodyPosition(glm::vec2 pos);
	void Release() override;
	glm::vec2 GetVelocity();

	void AddVelocity(glm::vec2 vec)
	{
		m_Velocity += vec;
	}

	void AddVelocityY(float v)
	{
		m_Velocity.y += v;
	}

	void AddVelocityX(float v)
	{
		m_Velocity.x += v;
	}

private:
	b2Body* m_Body = nullptr;
	b2BodyDef bodyDef;
	glm::vec2 m_Velocity = glm::vec2(0, 0);
	std::vector<ColliderComponent*> m_pColliders;
};
