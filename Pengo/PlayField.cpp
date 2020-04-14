#include "MiniginPCH.h"
#include "PlayField.h"
#include "Boundary.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include "IceBlock.h"
#include "Snobee.h"
#include "Pengo.h"
#include "Settings.h"
#include "Utils.h"

PlayField::PlayField()
{
}

void PlayField::Initialize()
{
	//Playfield Pos => LeftTop
#pragma region Boundaries

	int2 windSize = Settings::GetWindowSize();
	//float halfWidth = float(windSize.x / 2);
	
	auto rightBound = new Boundary(this);
	this->AddChild(rightBound);
	rightBound->SetLocalPosition({ float(windSize.x), 70.0f });
	rightBound->GetComponent<SpriteComponent>()->SetPivot({ 1.f,0.f });
	m_pBoundaries.push_back(rightBound);



	auto leftBound = new Boundary(this);
	this->AddChild(leftBound);
	leftBound->SetLocalPosition({ 0.0f, 50.0f });
	leftBound->GetComponent<SpriteComponent>()->SetPivot({ 0,0 });
	leftBound->SetRotation(0);
	m_pBoundaries.push_back(leftBound);



	auto bottomBound = new Boundary(this);
	this->AddChild(bottomBound);
	bottomBound->SetLocalPosition({ float(windSize.x), float(windSize.y) });
	bottomBound->GetComponent<SpriteComponent>()->SetPivot({ 1.0f,0.0f });
	bottomBound->SetRotation(90.0f);

	auto topBound = new Boundary(this);
	this->AddChild(topBound);
	topBound->SetLocalPosition({ float(windSize.x), 70 });
	topBound->GetComponent<SpriteComponent>()->SetPivot({ 1.0f,0.0f });
	topBound->SetRotation(90.0f);
	
	m_pBoundaries.push_back(topBound);
#pragma endregion

	GameObject::Initialize();
}

void PlayField::Update(float elapsedSec)
{
	GameObject::Update(elapsedSec);
}

void PlayField::Render() const
{
}

void PlayField::ParseLevelFile(std::string path)
{
	std::ifstream myfile(path);
	int x = 0;
	int y = 0;
	std::vector<Block*> vector;
	
	bool spawnSet = false;
	int2 spawnLocation;
	srand((unsigned int)time(nullptr));
	if (myfile.is_open())
	{
	
		while (true)
		{
			int read;
			myfile >> read;
			bool foundBlock = (read == 1);

			if (x > 12)
			{
				x = 0;
				y += 1;
				m_LevelLayout.push_back(vector);
				vector.clear();
			}

			if (foundBlock)
			{
				auto block = new IceBlock(this);
				this->AddChild(block);
				block->SetArrayPos(int2(x, y));
				float2 Pos = this->ConvertArrIndexToPos({ x,y });
				block->GetTransform().SetPosition({ Pos.x, Pos.y });
				
				vector.push_back(block);

			}
			else
			{
				vector.push_back(nullptr);
				if (spawnSet == false)
				{
					if (rand() % 3 == 0)
					{
						spawnLocation.x = (int)x;
						spawnLocation.y = (int)y;
						spawnSet = true;
					}
				}
			}




			
			x += 1;

			if (myfile.eof())
			{
				m_LevelLayout.push_back(vector);//VECTOR
				SpawnPlayer();
				SpawnEnemies();
				
				
				vector.clear();
				break;
			}
		}
	}
	else
	{
		std::cout << "Unable to open file";
	}
}


float2 PlayField::ConvertArrIndexToPos(int2 pos)
{
	int hudHight = 62;
	int boundaryWidth = (int)(8.0f*2.5f);
	int blockWidth = 16*2;
	return float2(16+float(boundaryWidth+ pos.x* blockWidth),  float(hudHight+pos.y* blockWidth));



	//return float2(35.6f + 16.0f * 2.133f * pos.x, 68.0f + 16.0f * 2.133f * pos.y);
}

void PlayField::TriggerBoundary()
{
	for (size_t i = 0; i < m_pBoundaries.size(); i++)
	{
		m_pBoundaries[i]->Trigger();
	}
}

void PlayField::SpawnPlayer()
{
	bool foundTarget = false;
	while(!foundTarget)
	{
		int y = rand() % m_LevelLayout.size();
		int x = rand() % m_LevelLayout[y].size();
		Block* block = m_LevelLayout[y][x];
		if(block == nullptr)
		{
			m_Pengo = new Pengo(this);
			this->AddChild(m_Pengo);
			m_Pengo->SetArrayPosition(int2(x, y));
			float2 Pos = this->ConvertArrIndexToPos({ x,y });
			m_Pengo->GetTransform().SetPosition({ Pos.x, Pos.y });
			
			foundTarget = true;
		}
	}
}

void PlayField::SpawnEnemies()
{
	int enemiesSpawned = 0;
	int2 arrPos = m_Pengo->GetArrayPos();
	while (enemiesSpawned<4)
	{
		int y = rand() % m_LevelLayout.size();
		int x = rand() % m_LevelLayout[y].size();
		Block* block = m_LevelLayout[y][x];

		if (block == nullptr&& Utils::distance({ x,y }, arrPos) > 5)
		{
			auto snobee = new Snobee(this);

			snobee->SetArrayPos(int2(x, y));
			float2 Pos = this->ConvertArrIndexToPos({ x,y });
			snobee->GetTransform().SetPosition({ Pos.x, Pos.y });
			SnobeeVector.push_back(snobee);
			this->AddChild(snobee);
			enemiesSpawned+= true;
		}
	}
}
