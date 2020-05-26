#include "ProjectPCH.h"
#include "AutoDestroyComponent.h"
#include "GameObject.h"
#include "GameScene.h"

AutoDestroyComponent::AutoDestroyComponent(float time)
	:delay(time)
{
}

AutoDestroyComponent::~AutoDestroyComponent()
{
}

void AutoDestroyComponent::Update(float elapsedSec)
{
	timer += elapsedSec;
	if(timer>delay)
	{
		this->m_pGameObject->GetScene()->Remove(this->m_pGameObject);
	}
}
