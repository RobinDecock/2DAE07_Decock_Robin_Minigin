#include "MiniginPCH.h"
#include "BoxCollider.h"
#include "GeneralStructs.h"
#include "BOX2DS.h"

BoxCollider::BoxCollider(glm::vec2 widthHeight, glm::vec2 localCenter)
{
	m_Shape = b2PolygonShape();
	m_Shape.SetAsBox(widthHeight.x / 2.0f, widthHeight.y / 2.0f,b2Vec2(localCenter.x, localCenter.y),0.0f);
	filter.maskBits = 0xFFFF;
	m_FixtureDef.density = 1.0f;
	;
}



void BoxCollider::Initialize()
{
	ColliderComponent::Initialize();

	m_pFixture->SetSensor(false);
}

void BoxCollider::Update(float elapsedSec)
{
	UNREF(elapsedSec);
}

BoxCollider::~BoxCollider()
{
}