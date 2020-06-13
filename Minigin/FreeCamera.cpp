#include "MiniginPCH.h"
#include "FreeCamera.h"

#include "InputManager.h"
#include "TransformComponent.h"

void FreeCamera::Initialize()
{
}

void FreeCamera::Update(float elapsedSec)
{
	float vel = 200;
	if(InputManager::IsKeyboardKeyPressed(KEY_R))
	{
		m_IsLocked = !m_IsLocked;
	}

	if (m_IsLocked) 
	{
		return;
	}
	
	if(InputManager::IsKeyboardKeyDown(KEY_LEFT))
	{
		m_Transform->Move({ -vel * elapsedSec,0 });
	}
	if (InputManager::IsKeyboardKeyDown(KEY_RIGHT))
	{
		m_Transform->Move({ vel * elapsedSec,0 });
	}
	if (InputManager::IsKeyboardKeyDown(KEY_UP))
	{	
		m_Transform->Move({ 0,-vel * elapsedSec });
	}
	if (InputManager::IsKeyboardKeyDown(KEY_DOWN))
	{
		m_Transform->Move({ 0, vel * elapsedSec });
	}

	if (InputManager::IsKeyboardKeyDown(KEY_KEYPAD_PLUS))
	{
		m_Transform->SetScale(m_Transform->GetScale() + 5 * elapsedSec);
	}
	if (InputManager::IsKeyboardKeyDown(KEY_KEYPAD_MINUS))
	{
		m_Transform->SetScale(m_Transform->GetScale() - 5 * elapsedSec);
	}
	Camera::Update(elapsedSec);
}

