#include "MiniginPCH.h"
#include "FreeCamera.h"

#include "InputManager.h"
#include "TransformComponent.h"
void FreeCamera::OnTrigger(BoxCollider* col, BoxCollider* other)
{
	UNREF(other);
	UNREF(col);
}

void FreeCamera::Initialize()
{
}

void FreeCamera::Update(float elapsedSec)
{
	float vel = 200;
	InputManager *  input = InputManager::GetInstance();

	if(input->IsKeyPressed(KEY_R))
	{
		m_IsLocked = !m_IsLocked;
	}

	if (m_IsLocked) 
	{
		return;
	}
	
	if(input->IsKeyDown(KEY_LEFT))
	{
		m_Transform->Move({ -vel * elapsedSec,0 });
	}
	if (input->IsKeyDown(KEY_RIGHT))
	{
		m_Transform->Move({ vel * elapsedSec,0 });
	}
	if (input->IsKeyDown(KEY_UP))
	{	
		m_Transform->Move({ 0,vel * elapsedSec });
	}
	if (input->IsKeyDown(KEY_DOWN))
	{
		m_Transform->Move({ 0, -vel * elapsedSec });
	}

	if (input->IsKeyDown(KEY_KEYPAD_PLUS))
	{
		m_Transform->SetScale(m_Transform->GetScale() + 5 * elapsedSec);
	}
	if (input->IsKeyDown(KEY_KEYPAD_MINUS))
	{
		m_Transform->SetScale(m_Transform->GetScale() - 5 * elapsedSec);
	}
}

void FreeCamera::LateUpdate(float elapsedSec)
{
	UNREF(elapsedSec);
}

void FreeCamera::Draw()
{

}

FreeCamera::~FreeCamera()
{
}
