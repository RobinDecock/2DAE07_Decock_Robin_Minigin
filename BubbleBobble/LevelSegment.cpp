#include "ProjectPCH.h"
#include "LevelSegment.h"
#include "GameScene.h"
#include "AnimLoader.h"
#include "ColBlock.h"
#include "Zen.h"
#include "Bub.h"
#include "TransformComponent.h"
#include "GameScene.h"
#include "Camera.h"
#include "ColorBlock.h"
#include "BoxCollider.h"
#include "BoxTrigger.h"
#include "BubbleBobble.h"
#include "EffectorComponent.h"
#include "Maita.h"
#include "RigidbodyComponent.h"
#include "Settings.h"

#include "TextureComponent.h"
#include "Utils.h"

LevelSegment::LevelSegment(int levelId,SingleScene* pScene)
{
	m_LevelId = levelId;
	currScene = pScene;
	
	camLocation = { Settings::GetWindowSize().x / 4.0f ,(Settings::GetWindowSize().y / 4.0f) + (Settings::GetWindowSize().y / 2.0f) *(m_LevelId-1) - 3 * 8};
	std::map<int, AnimData> blockData = AnimLoader::Load("../BubbleBobble/Resources/Blocks.anim");

	LoadMap("../BubbleBobble/Resources/Map" + std::to_string(levelId) + ".map", "../BubbleBobble/Resources/Blocks.anim");
}

LevelSegment::~LevelSegment()
{
	for (size_t i = 0; i < segObjects.size(); i++)
	{
		currScene->Remove(segObjects[i]);
	}
	segObjects.clear();
}

void LevelSegment::FinishPlatform(GameObject* platform)
{
	currScene->Add(platform);
	GameObject* collision = new GameObject();
	platform->AddChild(collision);
	collision->SetPosition({ float(platform->GetChildCount() * 8.0f) / 2.0f, 0 });
	collision->AddComponent(NEW(RigidbodyComponent)(true));
	PTR(BoxCollider)pBoxC = NEW(BoxCollider)(glm::vec2(platform->GetChildCount() * 8 - 8, 8));

	collision->AddComponent(pBoxC);
	pBoxC->SetCategory(LayerMask::Platform);

	PTR(EffectorComponent) pEffect = std::make_shared<EffectorComponent>(pBoxC, glm::vec2(0, -20), glm::vec2(platform->GetChildCount() * 8, 8));
	collision->AddComponent(pEffect);
	pEffect->SetCategoryToAffect(LayerMask::Player|LayerMask::Enemies);
	collision->GetComponent<EffectorComponent>();
	segObjects.push_back(platform);
	platform = nullptr;
}

bool LevelSegment::IsCamAtLoc(float tolerance)
{
	glm::vec2 camPos = currScene->GetCamera()->GetTransform()->Get2DPosition();

	
	return glm::distance(camPos, camLocation) < tolerance;
}

void LevelSegment::Remove(Zen* zen)
{
	for(size_t i = 0;i < m_pEnemies.size();i++)
	{
		if(m_pEnemies[i]==zen)
		{
			m_pEnemies.erase(m_pEnemies.begin() + i);
			return;
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
	std::map<int, AnimData> blockData = AnimLoader::Load(blockPath);

	GameObject* tileMap = new GameObject();;
	tileMap->SetPosition({ 0,(Settings::GetWindowSize().y / 2) * (m_LevelId-1) });
	std::ifstream binFile(mapPath, std::ios::in | std::ios::binary);
	//PARSING FILE

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
			Rectf src = Rectf(blockData.at(id).Src.x, blockData.at(id).Src.y, blockData.at(id).Src.w,
				blockData.at(id).Src.h);

			PTR(TextureComponent) texComp = NEW(TextureComponent)("Blocks.png");
			texComp->SetSourceRectangle(make_SDL_Rect(src));
			newObj->AddComponent(texComp);

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
			col->AddComponent(NEW(RigidbodyComponent)(true));
			PTR(BoxCollider) pBoxC = NEW(BoxCollider)(glm::vec2(width, height));
			pBoxC->SetCategory(LayerMask::Ground);
			col->AddComponent(pBoxC);
			if (IsPlatform)
			{
				col->SetTag("Platform");
				pBoxC->SetCategory(LayerMask::Platform);
				PTR(EffectorComponent) pEffect = std::make_shared<EffectorComponent>(pBoxC, glm::vec2(0, -20), glm::vec2(width, 8));
				col->AddComponent(pEffect);
				pEffect->SetCategoryToAffect(LayerMask::Player | LayerMask::Enemies);
			}
			else
			{
				col->SetTag("Ground");
			}
		}
#pragma endregion LoadCollisions

		currScene->Add(tileMap);

		
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

			GameObject *prefab = nullptr;
			switch(prefabId)
			{
			case 0:
				{
				BaseEnemy* en = new Zen(this);;
				prefab = en;
				m_pEnemies.push_back(en);
				en->SetPaused(true);
				}
				
				break;
			case 1:
				std::cout << "Maita not implemented" << std::endl;
				break;
			case 2:
				m_SpawnLocations.push_back(CalculatePos({ posX,posY }, m_LevelId));
				break;
			}
			if(prefab!=nullptr)
			{
				prefab->SetPosition(CalculatePos({posX,posY},m_LevelId));
				segObjects.push_back(prefab);
				currScene->Add(prefab);
			}
		}
#pragma  endregion

		binFile.close();

	}
}

void LevelSegment::SetPaused(bool b)
{
	
	m_IsPaused = b;
	for(int i =0;i<m_pEnemies.size();i++)
	{
		m_pEnemies[i]->SetPaused(b);
	}
}
