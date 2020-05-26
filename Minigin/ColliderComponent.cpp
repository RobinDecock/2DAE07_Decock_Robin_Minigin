#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"

#include "../BubbleBobble/BubbleBobble.h"
#include "GameObject.h"
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "GameScene.h"
void ColliderComponent::Initialize()
{
	m_FixtureDef.shape = m_Shape;
	m_FixtureDef.filter = filter;
	m_pFixture = m_pGameObject->GetComponent<RigidbodyComponent>()->AddCollider(m_FixtureDef);
	m_pFixture->SetUserData(this->m_pGameObject);
	m_IsInitialized = true;
}
void ColliderComponent::SetCategory(uint16 i)
{
	if(m_IsInitialized)
	{
		b2Filter filter = m_pFixture->GetFilterData();
		filter.categoryBits = i;
		m_pFixture->SetFilterData(filter);
	}
	else
	{
		filter.categoryBits = i;
	}

}

void ColliderComponent::SetIgnoreMask(uint16 i)
{
	if (m_IsInitialized)
	{
		b2Filter filter = m_pFixture->GetFilterData();
		filter.maskBits = ~i;
		m_pFixture->SetFilterData(filter);
	}
	else
	{
		filter.maskBits = ~i;
	}
}

void ColliderComponent::SetSensor(bool b)
{
	if(m_IsInitialized)
	{
		m_pFixture->SetSensor(b);
	}
	else
	{
		m_FixtureDef.isSensor = b;
	}

}

bool ColliderComponent::IsSensor()
{
	return m_pFixture->IsSensor();
}

b2Shape* ColliderComponent::GetShape()
{
	return m_Shape;
}
