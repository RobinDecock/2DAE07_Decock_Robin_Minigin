#include "ProjectPCH.h"
#include "SingleScene.h"
#include "AnimLoader.h"
#include "b2DebugDraw.h"
#include "Bub.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "FreeCamera.h"
#include "Zen.h"
#include "TextureComponent.h"
#include "b2CContactListener.h"
#include "DebugRenderer.h"
#include "FixedCamera.h"
#include "GameSettings.h"
#include "Hud.h"
#include "ItemManager.h"
#include "LevelSegment.h"
#include "MainMenu.h"
#include "SceneManager.h"
#include "Settings.h"

void SingleScene::RemovePlayer(Bub* player)
{
	for (unsigned int i = 0; i < m_pPlayers.size(); i++)
	{
		if (m_pPlayers[i] == player)
		{
			m_pPlayers.erase(m_pPlayers.begin() + i);
			break;
		}
	}
	//TODO observer?
	currSegment->EnemyUnlockPlayer(player);

	Remove(player);

	if(m_pPlayers.size() ==0)
	{
		m_GameOver = true;
	}
}

void SingleScene::CreateNewSegment()
{
	isInitializing = true;
	prevSegment = currSegment;
	playersRdy = false;
	currSegment = new LevelSegment(currentLevel, this);
	if (spawnLocations.size() < m_pPlayers.size())
	{
		std::cout << "Level doesn't have enough spawnPoints" << std::endl;
	}
	else
	{
		for (unsigned int j = 0; j < m_pPlayers.size(); j++)
		{
			m_pPlayers[j]->playerR = false;
			m_pPlayers[j]->SetRespawningPoint(spawnLocations[0]);
			m_pPlayers[j]->SetRespawning(true);
			spawnLocations.erase(spawnLocations.begin());
		}
	}
}

void SingleScene::SetPaused(bool b)
{
	currSegment->SetPaused(b);
}

void SingleScene::Initialize()
{
	m_pItemManager = new ItemManager(this);
	ItemManager::SetInstance(m_pItemManager);
	
	ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");
	SetCamera(new FreeCamera());
	
	m_pActiveCam->SetPosition(glm::vec2(Settings::GetWindowSize().x/4.0f, -Settings::GetWindowSize().y / 4.0f - 3 * 8));
	m_pActiveCam->SetScale({ 2.0f,2.0f });
	m_pPhysicsProxy.world = new b2World(b2Vec2(0,9.81f));
	m_pPhysicsProxy.world->SetAllowSleeping(false);

	m_pContactListener =new  b2CContactListener();

#if DEBUG
	m_B2DebugDraw = new b2DebugDraw();
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;

	m_B2DebugDraw->SetFlags(flags);
	
	m_pPhysicsProxy.world->SetDebugDraw(m_B2DebugDraw);
	m_B2DebugDraw->SetScene(this);
#endif
	
	m_pPhysicsProxy.world->SetContactListener(m_pContactListener);


	//HUD INI
	m_pHud = new Hud();
	Add(m_pHud);
	m_pHud->SetPosition(glm::vec3(0, 0, 100));
	//*******
	
	
	Bub* pBub;
	pBub = new Bub(0);
	pBub->GetTransform()->SetPosition({75,-75});
	Add(pBub);
	m_pPlayers.push_back(pBub);

	if(GameSettings::m_Gamemode  == GameMode::Coop)
	{
		pBub = new Bub(1);
		pBub->GetTransform()->SetPosition({ 125,-75 });
		Add(pBub);
		m_pPlayers.push_back(pBub);
	}
	if(GameSettings::m_Gamemode == GameMode::Versus)
	{
		searchingControllers.push_back(1);
	}
	CreateNewSegment();


}

void SingleScene::Draw() const
{
}

void SingleScene::Update(float elapsedSec)
{
	if(m_GameOver)
	{
		if(InputManager::IsKeyboardKeyPressed(SDL_SCANCODE_R))
		{
			SceneManager::GetInstance()->AddScene(new MainMenu());
			SceneManager::GetInstance()->RemoveScene(this);
		}

		
		return;
	}

	if (levelDone)
	{
		if (doneTimer>doneDelay)
		{
			CreateNewSegment();
			doneTimer = 0.0f;
			levelDone = false;
		}
		else
		{
			doneTimer += elapsedSec;
		}
	}

	
	if(currSegment!=nullptr)
	{
		if (searchingControllers.size() != 0&&currSegment->GetEnemyCount()>0)
		{
			bool assignementComplete = true;
			while(searchingControllers.size()>0&&assignementComplete)
			{
				assignementComplete = currSegment->MakeNewController(searchingControllers[0]);
				if (assignementComplete)
				{
					searchingControllers.erase(searchingControllers.begin());
				}
			}

		}
	}
	
		if (isInitializing)
		{
			if (!camRdy)
			{
				if (glm::distance(m_pActiveCam->GetTransform()->Get2DPosition(),camLocation)<2.0f)
				{
					camRdy = true;
				}
				m_pActiveCam->MoveToLocation(elapsedSec, camLocation);
			}

			if (!playersRdy)
			{
				bool rdy = true;

				for (unsigned int j = 0; j < m_pPlayers.size(); j++)
				{
					if(!m_pPlayers[j]->playerR)
					{
						rdy = false;
					}
				}
				if (rdy)
				{
					playersRdy = true;
				}
			}

			if (playersRdy && camRdy)
			{
				spawnLocations.clear();
				camRdy = false;
				isInitializing = false;
				if(prevSegment!=nullptr)
				{
					prevSegment->Release();
					SafeDelete(prevSegment);
				}
			
				SetPaused(false);
				currSegment->IsDoneIni = true;
				for (unsigned int j = 0; j < m_pPlayers.size(); j++)
				{
					m_pPlayers[j]->SetRespawning(false);
				}
				currentLevel += 1;
			}
		}

	if(currSegment!=nullptr)
	{
		for(unsigned int i = 0;i< spawnLocations.size();i++)
		{
			DebugRenderer::DrawPoint(spawnLocations[i]);
		}
	}
	
}

void SingleScene::onNotify( int event,GameObject * obj)
{
	SceneEvent sceneEvent = SceneEvent(event);
	switch(sceneEvent)
	{
	case LevelSegmentComplete:
		{
		levelDone = true;
			
		}
		break;
	case LostControl:
		{
			BaseEnemy* pEnemy = static_cast<BaseEnemy*>(obj);
			searchingControllers.push_back(pEnemy->GetController());
		}

		break;
	default: ;
	}
}

SingleScene::~SingleScene()
{
	SafeDelete(currSegment);
	SafeDelete(m_B2DebugDraw);

	SafeDelete(m_pContactListener);
	ItemManager::DestroyInstance();
}

