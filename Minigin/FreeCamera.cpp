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
	
	if(InputManager::IsDown(SDL_SCANCODE_LEFT))
	{
		m_Transform->Move({ -vel * elapsedSec,0 });
	}
	if (InputManager::IsDown(SDL_SCANCODE_RIGHT))
	{
		m_Transform->Move({ vel * elapsedSec,0 });
	}
	if (InputManager::IsDown(SDL_SCANCODE_UP))
	{	
		m_Transform->Move({ 0,vel * elapsedSec });
	}
	if (InputManager::IsDown(SDL_SCANCODE_DOWN))
	{
		m_Transform->Move({ 0, -vel * elapsedSec });
	}

	if (InputManager::IsDown(SDL_SCANCODE_KP_PLUS))
	{
		m_Transform->SetScale(m_Transform->GetScale() + 5 * elapsedSec);
	}
	if (InputManager::IsDown(SDL_SCANCODE_KP_MINUS))
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
