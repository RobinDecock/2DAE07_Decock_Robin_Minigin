#include "MiniginPCH.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameScene.h"
#include "Utils.h"

RigidbodyComponent::RigidbodyComponent(bool isStatic)
{
	bodyDef.type = isStatic ? b2_staticBody : b2_dynamicBody;
	bodyDef.userData = m_pGameObject;
}

void RigidbodyComponent::Initialize()
{
	glm::vec2 pos = m_pGameObject->GetTransform()->Get2DPosition();
	bodyDef.position.Set(pos.x, pos.y);
	GameScene* scene = m_pGameObject->GetScene();
	m_Body = scene->GetColWorld()->CreateBody(&bodyDef);
}

void RigidbodyComponent::LateInitialize()
{
	for (int i = 0; i < m_pColliders.size(); i++)
	{
		b2Fixture* fix = m_Body->CreateFixture(m_pColliders[i]->GetShape(), 0.0f);
		fix->SetUserData(this->m_pGameObject);
	}
}

void RigidbodyComponent::Update(float elapsedSec)
{
	UNREF(elapsedSec);
	float y = m_Body->GetLinearVelocity().y + m_Velocity.y;
	m_Body->SetLinearVelocity(b2Vec2(m_Velocity.x, y));
	m_Velocity = glm::vec2(0, 0);

	glm::vec2 disp = glm::vec2(m_Body->GetPosition().x, m_Body->GetPosition().y);
	m_pGameObject->GetTransform()->SetPosition(disp);
}

void RigidbodyComponent::AddCollider(ColliderComponent* collider)
{
	m_pColliders.push_back(collider);
}

void RigidbodyComponent::SetBodyPosition(glm::vec2 pos)
{
	if (m_Body != nullptr)
	{
		m_Body->SetTransform(make_b2Vec2(pos), 0);
	}
}

void RigidbodyComponent::Release()
{
}

glm::vec2 RigidbodyComponent::GetVelocity()
{
	return glm::vec2(m_Body->GetLinearVelocity().x, m_Body->GetLinearVelocity().y);
}
