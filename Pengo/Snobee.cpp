#include "MiniginPCH.h"
#include "Snobee.h"
#include "BoxCollider2D.h"
#include "Pengo.h"
#include "IceBlock.h"
#include "PlayField.h"
Snobee::Snobee(PlayField * playField):
	m_pPlayField{playField}
{
}

void Snobee::Initialize()
{
	m_Tag = "Snobee";
	sprite = new SpriteComponent("MainSpriteSheet.png");

	sprite->SetSpeed(5.0f);
	m_Transform.SetScale(2.0f, 2.0f);
	this->AddComponent(sprite);
	sprite->SetSpriteData(SnobeeSprites[m_SnobeeMovement]);
	m_pRigid = new RigidbodyComponent(false);
	this->AddComponent(m_pRigid);
	AddComponent(new BoxCollider2D(25,25));
}

void Snobee::Update(float elapsedSec)
{
	GameObject::Update(elapsedSec);

	//UPDATE ANIMATION
	if (m_OldSnobeeMovement != m_SnobeeMovement)
	{
		sprite->SetSpriteData(SnobeeSprites[m_SnobeeMovement]);
		m_OldSnobeeMovement = m_SnobeeMovement;
	}
	if(inAction)
	{
		switch(currDir)
		{
		case Left: ;
			m_SnobeeMovement = SnobeeMovement::Left;
			break;
		case Right:
			m_SnobeeMovement = SnobeeMovement::Right;
			break;
		case Up: 
			m_SnobeeMovement = SnobeeMovement::Up;
			break;
		case Down: 
			m_SnobeeMovement = SnobeeMovement::Down;
			break;
		default: ;
		}
		
	}
	//***************************


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
	if (m_IsStunned)return;
	Go(currDir);
}

void Snobee::Render() const
{
	GameObject::Render();
}

void Snobee::OnTrigger(BoxCollider2D* trigger, BoxCollider2D* receive)
{
	UNREFERENCED_PARAMETER(trigger);
	if(receive->GetGameObject()->GetTag()=="Pengo")
	{
		Pengo * p = dynamic_cast<Pengo*>(receive->GetGameObject());
		if(!p->GetIsDead())
		{
			dynamic_cast<Pengo*>(receive->GetGameObject())->Kill();
		}

	}
}

void Snobee::Go(Direction dir)
{
	UNREFERENCED_PARAMETER(dir);
	//CHECK IF VALID

	std::vector<std::vector<Block*>>& layout = m_pPlayField->GetLevelLayout();
	int2 nextPos = int2(100, 100);
	nextPos = DirectionMap[dir];
	if (nextPos.x == 100 && nextPos.y == 100)return;

	if (nextPos.x < 0 && m_ArrayPos.x - 1 < 0) { ChangeDirection();	return; }
	if (nextPos.y < 0 && m_ArrayPos.y - 1 < 0) { ChangeDirection(); return; }

	if (nextPos.x > 0 && m_ArrayPos.x + 1 >= (int)layout[m_ArrayPos.y].size()) { ChangeDirection(); return; }
	if (nextPos.y > 0 && m_ArrayPos.y + 1 >= (int)layout.size()) { ChangeDirection(); return; }

	if (layout[m_ArrayPos.y + nextPos.y][m_ArrayPos.x + nextPos.x] != nullptr&&layout[m_ArrayPos.y + nextPos.y][m_ArrayPos.x + nextPos.x]->GetInAction() == false) { ChangeDirection(); return; }
	if (inAction == false)
	{
		m_pRigid->SetVelocity(float2((float)nextPos.x, (float)nextPos.y));
		inAction = true;
		nextTarget = m_pPlayField->ConvertArrIndexToPos(int2(m_ArrayPos.x + nextPos.x, m_ArrayPos.y + nextPos.y));
		nextTargetArray = int2(m_ArrayPos.x + nextPos.x, m_ArrayPos.y + nextPos.y);
	}
}



void Snobee::Kill()
{
	//IMPLEMENT DEATHANIMATION	
	m_ParentScene->Remove(this);
	m_ParentScene->AddToScore(100);
}

void Snobee::SetArrayPos(int2 pos)
{
	m_ArrayPos = pos;
}


void Snobee::ChangeDirection()
{
	currDir = static_cast<Direction>(rand() % 4);
}

Snobee::~Snobee()
{
}
