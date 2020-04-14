#include "MiniginPCH.h"
#include "Block.h"
#include "Pengo.h"

#include "PlayField.h"
Block::Block()
{
}

void Block::Initialize()
{
	GameObject::Initialize();
	m_pRigid = new RigidbodyComponent(false);
	AddComponent(m_pRigid);
	m_Collider = new BoxCollider2D(25, 25);
	AddComponent(m_Collider);
}

void Block::Update(float elapsedSec)
{
	GameObject::Update(elapsedSec);

	std::vector<std::vector<Block*>>& layout = m_pPlayField->GetLevelLayout();
	m_Collider->SetActive(inAction);
	if (inAction)
	{
		//CHECK IF ACTION IS COMPLETED
		/*if(m_ParentScene->ConvertArrIndexToPos)
		{

			m_Transform.GetPosition()
		}*/

		
		if (abs(m_Transform.GetPosition().x - nextTarget.x) < 2.0f&&abs(m_Transform.GetPosition().y - nextTarget.y) < 2.0f)
		{
			inAction = false;
			m_pRigid->SetVelocity(float2(0.f, 0.f));
			layout[nextTargetArray.y][nextTargetArray.x] = this;
			m_ArrayPos = nextTargetArray;
		}
		return;
	}
}

void Block::Render() const
{
	GameObject::Render();
}

void Block::Push(Direction dir)
{

		std::vector<std::vector<Block*>>& layout = m_pPlayField->GetLevelLayout();
		if(!inAction&&GetTargetFromDir(dir, nextTargetArray))
		{
			inAction = true;
			layout[m_ArrayPos.y][m_ArrayPos.x] = nullptr;
			nextTarget = m_pPlayField->ConvertArrIndexToPos(nextTargetArray);
			Move(dir);
		}
}

bool Block::IsPointValid(int2 arrPoint)
{
	std::vector<std::vector<Block*>>& layout = m_pPlayField->GetLevelLayout();
	return (arrPoint.x > -1 && arrPoint.x < layout[m_ArrayPos.y].size()) && (arrPoint.y > -1 && arrPoint.y < layout.size());
}


bool Block::GetTargetFromDir(Direction dir,int2& targetArr)
{
	std::vector<std::vector<Block*>>& layout = m_pPlayField->GetLevelLayout();
	bool foundTarget = false;


	int2 dirValue = DirectionMap[dir];
	int2 beginPoint = { m_ArrayPos.x+ dirValue.x,m_ArrayPos.y + dirValue.y };

	for (int2 i = beginPoint; IsPointValid(i);i+={dirValue.x, dirValue.y})
	{
		if (layout[i.y][i.x] == nullptr)
		{
			targetArr = int2((int)i.x, (int)i.y);
			foundTarget = true;
		}
		else
		{
			break;
		}
	}

	if (foundTarget)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Block::Move(Direction dir)
{
	switch (dir)
	{
	case Left:
		m_pRigid->SetVelocity(float2(-1.0f*Speed, 0));
		break;
	case Right:
		m_pRigid->SetVelocity(float2(1.0f*Speed, 0));
		break;
	case Up:
		m_pRigid->SetVelocity(float2(0.f, -1.0f*Speed));
		break;
	case Down:
		m_pRigid->SetVelocity(float2(0.f, 1.0f*Speed));
		break;
	default: ;
	}
}

void Block::SetArrayPos(int2 pos)
{
	m_ArrayPos = pos;
}