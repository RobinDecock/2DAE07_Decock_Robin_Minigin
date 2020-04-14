#include "MiniginPCH.h"
#pragma once


#include "GameObject.h"
#include "InputManager.h"
#include "Pengo.h"
#include "Scene.h"
#include "IceBlock.h"
#include "PlayField.h"
using namespace dae;
Pengo::Pengo(PlayField * playField):m_pPlayField{playField}
{

}

void Pengo::Initialize()
{
	m_Tag = "Pengo";
	sprite = new SpriteComponent("MainSpriteSheet.png");

	this->AddComponent(sprite);
	sprite->SetSpeed(5.0f);
	m_Transform.SetScale(2.0f, 2.0f);
	sprite->SetSpriteData(PlayerSprites[m_PlayerMovement]);
	m_pRigid = new RigidbodyComponent(false);
	this->AddComponent(m_pRigid);
	AddComponent(new BoxCollider2D(16, 16));
}


void Pengo::Update(float elapsedSec)
{
	GameObject::Update(elapsedSec);
	if (m_OldPlayerMovement != m_PlayerMovement)
	{
		sprite->SetSpriteData(PlayerSprites[m_PlayerMovement]);
		m_OldPlayerMovement = m_PlayerMovement;
	}

	if (isDead) 
	{
		if (sprite->GetCycle() > 3) 
		{
			SceneManager::GetInstance().Reset(this->m_ParentScene);
		}
		return;
	}
	if (inAction)
	{
		//CHECK IF ACTION IS COMPLETED
		if (abs(m_Transform.GetPosition().x - nextTarget.x) < 2.0f&&abs(m_Transform.GetPosition().y - nextTarget.y) < 2.0f)
		{
			inAction = false;
			m_pRigid->SetVelocity(float2(0.f, 0.f));
			m_ArrayPos = nextTargetArray;
		}
		return;
	}

	if (InputManager::IsDown(SDL_SCANCODE_UP))
	{
		sprite->SetPause(false);
		m_PlayerMovement = PlayerMovement::Up;
		Go(Up);
	}
	else if (InputManager::IsDown(SDL_SCANCODE_DOWN))
	{
		sprite->SetPause(false);
		m_PlayerMovement = PlayerMovement::Down;
		Go(Down);
	}
	else if (InputManager::IsDown(SDL_SCANCODE_LEFT))
	{
		sprite->SetPause(false);
		m_PlayerMovement = PlayerMovement::Left;
		Go(Left);
	}
	else if (InputManager::IsDown(SDL_SCANCODE_RIGHT))
	{
		sprite->SetPause(false);
		m_PlayerMovement = PlayerMovement::Right;
		Go(Right);
	}
	else
	{
		sprite->SetPause(true);
		m_pRigid->SetVelocity(float2(0, 0));
	}

	std::vector<std::vector<Block*>>& layout = m_pPlayField->GetLevelLayout();
	if (InputManager::IsPressed(SDL_SCANCODE_SPACE))
	{
		int2 dir = DirectionMap[(Direction)((int)m_PlayerMovement)];

		int yIndex = m_ArrayPos.y + dir.y;
		int xIndex = m_ArrayPos.x + dir.x;
		if(layout[yIndex][xIndex]!=nullptr)
		{
			layout[yIndex][xIndex]->Push((Direction)((int)m_PlayerMovement));
		}
	}
}

void Pengo::Render()const
{
	GameObject::Render();
}

void Pengo::Go(Direction dir)
{
	//CHECK IF VALID DIRECTION
	if (dir > 3)return;
	int2 offset = DirectionMap[dir];
	int2 nextPos = m_ArrayPos+ offset;
	
	if (!IsNextPositionValid(nextPos))return;

	
	
	if (inAction == false)
	{
		m_pRigid->SetVelocity(float2((float)offset.x, (float)offset.y));
		inAction = true;
		nextTarget = m_pPlayField->ConvertArrIndexToPos(int2(nextPos.x, nextPos.y));
		nextTargetArray = int2(nextPos.x, nextPos.y);
	}


}

bool Pengo::IsNextPositionValid(int2 nextPos)
{

	std::vector<std::vector<Block*>>& layout = m_pPlayField->GetLevelLayout();

	if (nextPos.x < 0) { return false; ; }
	else if (nextPos.x >= (int)layout[m_ArrayPos.y].size()) { return false; }
	
	if (nextPos.y < 0) { return false; ; }
	else if (nextPos.y >= (int)layout.size()) { return false; ; }

	if (layout[nextPos.y][nextPos.x] != nullptr)return false; ;

	return true;
}

void Pengo::Kill()
{
	isDead = true;
	m_PlayerMovement = PlayerMovement::Die;
	sprite->ResetCycle();
	m_pRigid->SetVelocity(float2(0.f, 0.f));
}

void Pengo::Respawn()
{

	std::vector<std::vector<Block*>>& layout = m_pPlayField->GetLevelLayout();
	for(size_t i = 0;i<layout[m_ArrayPos.y].size();i++)
	{
		if(rand()%5==0&&layout[m_ArrayPos.y][i]==nullptr)
		{
			SetArrayPosition(int2((int)i, m_ArrayPos.y));
			isDead = false;
			m_PlayerMovement = PlayerMovement::Idle;
			m_ParentScene->SetLives(m_ParentScene->GetLives() - 1);
		}
	}
}

void Pengo::SetArrayPosition(int2 pos)
{
	m_ArrayPos = pos;
	float2 Pos = m_pPlayField->ConvertArrIndexToPos(m_ArrayPos);
	m_Transform.SetPosition({ Pos.x, Pos.y });
}

