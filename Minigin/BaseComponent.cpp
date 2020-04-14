#include "MiniginPCH.h"
#include "BaseComponent.h"

BaseComponent::BaseComponent()
{
}


BaseComponent::~BaseComponent()
{
}


GameObject* BaseComponent::GetGameObject()
{
	return m_pGameObject;
}

void BaseComponent::SetActive(bool active)
{
	m_IsActive = active;
}


CompType BaseComponent::GetCompType()
{
	return m_Type;
}

void BaseComponent::Initialize()
{
}

void BaseComponent::LateInitialize()
{
}

void BaseComponent::Update(float elapsedSec)
{
	UNREF(elapsedSec);
}

void BaseComponent::LateUpdate(float elapsedSec)
{
	UNREF(elapsedSec);
}

void BaseComponent::Draw()
{
}

void BaseComponent::PreDraw()
{
}

void BaseComponent::Release()
{
}
