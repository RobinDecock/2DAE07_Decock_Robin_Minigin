#pragma once

#include "BaseComponent.h"


class RigidbodyComponent final : public BaseComponent
{
	friend class BoxCollider;
public:
	RigidbodyComponent(const RigidbodyComponent& other) = delete;
	RigidbodyComponent(RigidbodyComponent&& other) noexcept = delete;
	RigidbodyComponent& operator=(const RigidbodyComponent& other) = delete;
	RigidbodyComponent& operator=(RigidbodyComponent&& other) noexcept = delete;
	RigidbodyComponent(bool isStatic = false);

	~RigidbodyComponent();
	void Initialize() override;
	
	void Update(float elapsedSec) override;
	b2Fixture* AddCollider(const b2FixtureDef& fixDef);
	b2Body * GetBody();

	b2Body* GetConstBody()const;
	void SetBodyPosition(glm::vec2 pos);
	glm::vec2 GetVelocity()const;
	void SetGravityScale(float scale);

	void CheckLock();
	void AddVelocity(glm::vec2 vec)
	{
		b2Vec2 vel = m_Body->GetLinearVelocity();
		vel.x += vec.x;
		vel.y += vec.y;
		m_Body->SetLinearVelocity(vel);
	}

	void AddVelocityY(float v)
	{
		b2Vec2 vel = m_Body->GetLinearVelocity();
		vel.y += v;
		m_Body->SetLinearVelocity(vel);
	}

	void AddVelocityX(float v)
	{
		b2Vec2 vel = m_Body->GetLinearVelocity();
		vel.x += v;
		m_Body->SetLinearVelocity(vel);
	}
	

private:
	bool m_IsInitialized =false;
	b2Body* m_Body = nullptr;
	b2BodyDef bodyDef;
};
