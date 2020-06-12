#include "ProjectPCH.h"
#include "BlinkComponent.h"
#include "GameObject.h"
BlinkComponent::~BlinkComponent()
{
	m_pGameObject->SetVisibility(true);
}

void BlinkComponent::Update(float elapsedSec)
{
	m_BlinkTimer += elapsedSec;
	if(m_BlinkTimer>m_Interval)
	{
		m_pGameObject->SetVisibility(!m_pGameObject->GetVisibility());
		m_BlinkTimer = 0.0f;
	}
}
