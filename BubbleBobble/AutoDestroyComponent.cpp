#include "ProjectPCH.h"
#include "AutoDestroyComponent.h"
#include "GameObject.h"
#include "GameScene.h"

AutoDestroyComponent::AutoDestroyComponent(float time)
	:delay(time)
{
}

void AutoDestroyComponent::Update(float elapsedSec)
{
	timer += elapsedSec;
	if(timer>delay)
	{
		
		if(m_pGameObject->GetParent()==nullptr)
		{
			this->m_pGameObject->GetScene()->Remove(this->m_pGameObject);
		}
		else
		{
			m_pGameObject->GetParent()->RemoveChild(this->m_pGameObject);
		}
	}
}
