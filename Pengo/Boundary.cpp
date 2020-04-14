
#include "MiniginPCH.h"
#pragma once
#include "Boundary.h"
#include "SpriteComponent.h"
#include "InputManager.h"
#include "Snobee.h"
#include "PlayField.h"
Boundary::Boundary(PlayField * playField):m_pPlayField{playField}
{
}

void Boundary::Initialize()
{
	m_pSprite = new SpriteComponent("Boundary.png");
	this->AddComponent(m_pSprite);
	m_pSprite->SetSpeed(5.0f);
	m_Transform.SetScale(2.5f, 2.0f);

	m_pSprite->SetSpriteData(Idle);
}


void Boundary::Update(float elapsedSec)
{
	GameObject::Update(elapsedSec);
	UNREFERENCED_PARAMETER(elapsedSec);
	if (m_IsTriggered)
	{
		if (m_TriggerTimer > m_TriggerDelay)
		{
			m_IsTriggered = false;
			m_TriggerTimer = 0;
			std::vector<Snobee*>snobees = m_pPlayField->GetSnobees();
			for (size_t i = 0; i < snobees.size(); i++)
			{
				if (snobees[i] != nullptr)
				{
					snobees[i]->SetStunned(false);
				}
			}
		}
		else
		{
			m_TriggerTimer += elapsedSec;
		}
	}
	else
	{
		m_pSprite->SetSpriteData(Idle);
	}
}

void Boundary::Trigger()
{
	m_IsTriggered = true;
	m_pSprite->SetSpriteData(Active);
	m_TriggerDelay = m_ParentScene->GetStunTime();
	std::vector<Snobee*>snobees = m_pPlayField->GetSnobees();
	for (size_t i = 0; i < snobees.size(); i++)
	{
		if (snobees[i] != nullptr)
		{
			snobees[i]->SetStunned(true);
		}
	}
}
