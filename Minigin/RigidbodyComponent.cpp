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
	m_Type = CompType::RigidbodyC;
}

RigidbodyComponent::~RigidbodyComponent()
{
	b2World* pWorld = m_pGameObject->GetScene()->GetPhysicsProxy().world;
	if(pWorld !=nullptr)
	{
		pWorld->DestroyBody(m_Body);
	}

}

void RigidbodyComponent::Initialize()
{
	bodyDef.position = make_b2Vec2(m_pGameObject->GetTransform()->Get2DPosition());
	GameScene* scene = m_pGameObject->GetScene();
	bodyDef.fixedRotation = true;
	m_Body = scene->GetPhysicsProxy().world->CreateBody(&bodyDef);
	m_IsInitialized = true;
}

void RigidbodyComponent::Update(float elapsedSec)
{
	UNREF(elapsedSec);
	if(m_Body!=nullptr)
	{
		glm::vec2 disp = glm::vec2(m_Body->GetPosition().x, m_Body->GetPosition().y);
		m_pGameObject->GetTransform()->SetPosition(disp);
	}

}

b2Fixture *  RigidbodyComponent::AddCollider(const b2FixtureDef & fixDef)
{
	return m_Body->CreateFixture(&fixDef);
}

b2Body *  RigidbodyComponent::GetBody()
{
	CheckLock();
	
	return m_Body;
}

b2Body* RigidbodyComponent::GetConstBody() const
{
	return m_Body;
}

void RigidbodyComponent::SetBodyPosition(glm::vec2 pos)
{
	CheckLock();
	
	if (m_Body != nullptr)
	{
		m_Body->SetTransform(make_b2Vec2(pos), 0);
	}
}
glm::vec2 RigidbodyComponent::GetVelocity()const
{
	return glm::vec2(m_Body->GetLinearVelocity().x, m_Body->GetLinearVelocity().y);
}

void RigidbodyComponent::SetGravityScale(float scale)
{
	CheckLock();
	
	if(m_IsInitialized)
	{
		m_Body->SetGravityScale(scale);
	}
	else
	{
		bodyDef.gravityScale = scale;
	}

}

void RigidbodyComponent::CheckLock()
{
	if(m_pGameObject->IsInitialized()&&m_pGameObject->GetScene()->GetPhysicsProxy().isLocked)
	{
		__debugbreak();
		std::cout<<"[ERROR: physics changes should be applied in the PhysicsUpdate(...)]";
	}
}
