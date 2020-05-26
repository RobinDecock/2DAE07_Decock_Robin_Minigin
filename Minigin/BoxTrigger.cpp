#include "MiniginPCH.h"
#include "BoxTrigger.h"

void BoxTrigger::Initialize()
{
	ColliderComponent::Initialize();

	m_pFixture->SetSensor(true);
}

BoxTrigger::BoxTrigger(glm::vec2 widthHeight, glm::vec2 localCenter)
{
	m_Shape = new b2PolygonShape();
	m_Shape->SetAsBox(widthHeight.x / 2.0f, widthHeight.y / 2.0f, b2Vec2(localCenter.x, localCenter.y), 0.0f);
	filter.maskBits = 0xFFFF;
}
