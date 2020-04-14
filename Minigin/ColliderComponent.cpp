#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"

void ColliderComponent::Initialize()
{
	m_pGameObject->GetComponent<RigidbodyComponent>()->AddCollider(this);
}

void ColliderComponent::Draw()
{
}

void ColliderComponent::PreDraw()
{
}

void ColliderComponent::CreateShape(b2Body& bd)
{
	UNREF(bd);
}

//std::vector<b2Vec2> ColliderComponent::GetVerticesList()
//{
//	std::vector<b2Vec2> l;
//	for (int i = 0; i < 4; i++)
//	{
//		l.push_back(m_Shape->m_vertices[i]);
//	}
//	return l;
//}

b2Shape* ColliderComponent::GetShape()
{
	return m_Shape;
}
