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

RigidbodyComponent::~RigidbodyComponent()
{
	GameScene* scene = m_pGameObject->GetScene();
	scene->GetColWorld()->DestroyBody(m_Body);
}

void RigidbodyComponent::Initialize()
{
	bodyDef.position = make_b2Vec2(m_pGameObject->GetTransform()->Get2DPosition());
	GameScene* scene = m_pGameObject->GetScene();
	bodyDef.fixedRotation = true;
	m_Body = scene->GetColWorld()->CreateBody(&bodyDef);
	m_IsInitialized = true;
}

void RigidbodyComponent::Update(float elapsedSec)
{
	UNREF(elapsedSec);
	glm::vec2 disp = glm::vec2(m_Body->GetPosition().x, m_Body->GetPosition().y);
	m_pGameObject->GetTransform()->SetPosition(disp);
}

b2Fixture *  RigidbodyComponent::AddCollider(const b2FixtureDef & fixDef)
{
	return m_Body->CreateFixture(&fixDef);
}

b2Body *  RigidbodyComponent::GetBody()
{
	return m_Body;
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

void RigidbodyComponent::SetGravityScale(float scale)
{
	if(m_IsInitialized)
	{
		m_Body->SetGravityScale(scale);
	}
	else
	{
		bodyDef.gravityScale = scale;
	}

}
