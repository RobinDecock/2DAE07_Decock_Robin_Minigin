#include "ProjectPCH.h"
#include "LevelSegment.h"
#include "GameScene.h"
#include "AnimLoader.h"
#include "Zen.h"
#include "TransformComponent.h"
#include "BoxCollider.h"
#include "BoxTrigger.h"
#include "BubbleBobble.h"
#include "EffectorComponent.h"
#include "Maita.h"
#include "RigidbodyComponent.h"
#include "Settings.h"
#include "TextureComponent.h"
#include "Tunnel.h"

LevelSegment::LevelSegment(int levelId,SingleScene* pScene)
{
	AddObserver(pScene);
	m_LevelId = levelId;
	m_pCurrScene = pScene;

	int hudOffset = 24;
	m_pCurrScene->SetCamLocation({ Settings::GetWindowSize().x / 4.0f ,(Settings::GetWindowSize().y / 4.0f) + (Settings::GetWindowSize().y / 2.0f) * (m_LevelId - 1) - hudOffset });
	std::map<int, AnimData> blockData = Anim::Loader::Load("../BubbleBobble/Resources/Blocks.anim");

	LoadMap("../BubbleBobble/Resources/Map" + std::to_string(levelId) + ".map", "../BubbleBobble/Resources/Blocks.anim");
}

LevelSegment::~LevelSegment()
{
	
}

bool LevelSegment::MakeNewController(int controllerId)
{
	for (unsigned int i = 0; i < m_pEnemies.size(); i++)
	{
		if (!m_pEnemies[i]->IsControlled())
		{
			m_pEnemies[i]->SetControlled(controllerId);
			return true;
		}
	}
	return false;
}

void LevelSegment::EnemyUnlockPlayer(Bub* player)
{
	for (unsigned int i = 0; i < m_pEnemies.size(); i++)
	{
		if (m_pEnemies[i]->GetLockedPlayer() == player)
		{
			m_pEnemies[i]->SetLockedPlayer(nullptr);
		}
	}
}


int texDim = 8;
int halfTex = 4;
glm::vec2 CalculatePos(glm::vec2 p,int levelId)
{
	return { halfTex + texDim * p.x, halfTex + p.y * texDim + (Settings::GetWindowSize().y/2) * (levelId-1) };
}

void LevelSegment::LoadMap(std::string mapPath, std::string blockPath)
{
	std::map<int, AnimData> blockData = Anim::Loader::Load(blockPath);

	GameObject* tileMap = new GameObject();
	m_pCurrScene->Add(tileMap);
	tileMap->SetPosition({ 0,(Settings::GetWindowSize().y / 2) * (m_LevelId-1) });
	std::ifstream binFile(mapPath, std::ios::in | std::ios::binary);

	while (binFile.is_open())
	{
#pragma region LoadBlocks
		int tilemapSize = 0;
		binFile.read(reinterpret_cast<char*>(&tilemapSize), sizeof(int));
		binFile.read(reinterpret_cast<char*>(&tilemapSize), sizeof(int));

		for (int i = 0; i < tilemapSize; i++)
		{
			int id = 0;
			binFile.read(reinterpret_cast<char*>(&id), sizeof(char));
			int posX = 0;
			binFile.read(reinterpret_cast<char*>(&posX), sizeof(int));
			int posY = 0;
			binFile.read(reinterpret_cast<char*>(&posY), sizeof(int));
			bool isPlatform;
			binFile.read(reinterpret_cast<char*>(&isPlatform), sizeof(bool));

			GameObject* newObj = new GameObject();

			TextureComponent* texComp = new TextureComponent("Blocks.png");
			texComp->SetSourceRectangle(blockData.at(id).Src);
			newObj->AddComponent(texComp);
			newObj->SetTag("Block");
			newObj->GetComponent<TextureComponent>()->SetPivot(glm::vec2(0.5f, 0.5f));
			tileMap->AddChild(newObj);
			newObj->SetPosition({ halfTex + texDim * posX, halfTex + posY * texDim });
		}
#pragma endregion LoadBlocks

#pragma region LoadCollisions
		int colSize = 0;
		binFile.read(reinterpret_cast<char*>(&colSize), sizeof(int));

		for (int i = 0; i < colSize; i++)
		{
			int posX{};
			binFile.read(reinterpret_cast<char*>(&posX), sizeof(int));
			int posY{};
			binFile.read(reinterpret_cast<char*>(&posY), sizeof(int));
			int width{};
			binFile.read(reinterpret_cast<char*>(&width), sizeof(int));
			int height{};
			binFile.read(reinterpret_cast<char*>(&height), sizeof(int));
			bool IsPlatform{};
			binFile.read((char*)&IsPlatform, sizeof(bool));
			
			GameObject* col = new GameObject();
			tileMap->AddChild(col);
			col->GetTransform()->SetPosition(glm::vec2(posX, posY));
			col->AddComponent(new RigidbodyComponent(true));
			BoxCollider* pBoxC = new BoxCollider(glm::vec2(width, height));
			if (posY == 4)
			{
				pBoxC->SetCategory(LayerMask::Roof);
			}
			else
			{
				pBoxC->SetCategory(LayerMask::Ground);
			}
			col->AddComponent(pBoxC);
			if (IsPlatform)
			{
				col->SetTag("Platform");
				pBoxC->SetCategory(LayerMask::Platform);
				EffectorComponent* pEffect = new EffectorComponent(pBoxC, glm::vec2(0, -20), glm::vec2(width, 8));
				col->AddComponent(pEffect);
				pEffect->SetCategoryToAffect(LayerMask::Player | LayerMask::Enemies);
			}
			else
			{
				col->SetTag("Ground");
			}
		}

		Tunnel* tunnel = new Tunnel();
		tunnel->SetPosition(CalculatePos(glm::vec2(16, 25), m_LevelId));
		tunnel->SetTag("Tunnel");
		m_pCurrScene->Add(tunnel);
		m_pSegObjects.push_back(tunnel);
		
#pragma endregion LoadCollisions


		m_pSegObjects.push_back(tileMap);
		
#pragma region LoadPrefabs

		int prefabSize = 0;
		binFile.read(reinterpret_cast<char*>(&prefabSize), sizeof(int));
		for (int i = 0; i < prefabSize; i++)
		{
			int prefabId = 0;
			binFile.read(reinterpret_cast<char*>(&prefabId), sizeof(char));
			int posX = 0;
			binFile.read(reinterpret_cast<char*>(&posX), sizeof(int));
			int posY = 0;
			binFile.read(reinterpret_cast<char*>(&posY), sizeof(int));

			BaseEnemy* pEnemy = nullptr;
			switch(prefabId)
			{
				case 0:
					{
						pEnemy = new Zen(this);;	
					}
					break;
				case 1:
					{
						pEnemy = new Maita(this);;
					}
					break;
				case 2:
					m_pCurrScene->AddSpawnLocation(CalculatePos({ posX,posY }, m_LevelId));
					break;
			}
			
			if(pEnemy!=nullptr)
			{
				pEnemy->SetTag("Enemy");
				pEnemy->SetPosition(CalculatePos({posX,posY},m_LevelId));
				pEnemy->SetPaused(true);
				this->AddEnemy(pEnemy);
			}
		}
#pragma  endregion
		binFile.close();
	}
}