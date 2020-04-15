#include "MiniginPCH.h"
#include "BoxCollider.h"
#include "GeneralStructs.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
BoxCollider::BoxCollider(glm::vec2 widthHeight, LayerMask mask, LayerMask collideWith)
{
	UNREFERENCED_PARAMETER(mask);
	UNREFERENCED_PARAMETER(collideWith);
	m_Shape = new b2PolygonShape();
	m_Shape->SetAsBox(widthHeight.x/2.0f, widthHeight.y/2.0f);
}

void BoxCollider::Initialize()
{
	ColliderComponent::Initialize();
}

void BoxCollider::LateInitialize()
{

}
void BoxCollider::Update(float elapsedSec)
{
	UNREF(elapsedSec);
}

void BoxCollider::Draw()
{

}

void BoxCollider::CreateShape(b2Body& bd)
{
	UNREF(bd);
}
BoxCollider::~BoxCollider()
{
	delete m_Shape;
	//m_GameObject->GetScene()->GetCollisionManager().RemoveCollider(this);
}

void BoxCollider::Release()
{
}
