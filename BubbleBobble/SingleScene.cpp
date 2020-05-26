#include "ProjectPCH.h"
#include "SingleScene.h"

#include "AnimLoader.h"
#include "b2DebugDraw .h"
#include "Bub.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "FreeCamera.h"
#include "ColBlock.h"
#include "RigidbodyComponent.h"
#include "SoundManager.h"
#include "Zen.h"
#include "TextureComponent.h"
#include "b2CContactListener.h"
#include "BoxCollider.h"
#include "DebugRenderer.h"
#include "FixedCamera.h"
#include "GameSettings.h"
#include "Hud.h"
#include "LevelSegment.h"
#include "Settings.h"

void SingleScene::Initialize()
{
	ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");
	SetCamera(new FreeCamera());
	
	m_pActiveCam->SetPosition(glm::vec2(Settings::GetWindowSize().x/4.0f, -Settings::GetWindowSize().y / 4.0f - 3 * 8));
	m_pActiveCam->SetScale({ 2.0f,2.0f });
	m_pColWorld = new b2World(b2Vec2(0,9.81f));
	m_pColWorld->SetAllowSleeping(false);

	m_pContactListener = new b2CContactListener();

#if DEBUG
	b2Deb = new b2DebugDraw();
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;

	b2Deb->SetFlags(flags);
	
	m_pColWorld->SetDebugDraw(b2Deb);
	b2Deb->SetScene(this);
#endif
	m_pColWorld->SetContactListener(m_pContactListener);
	Bub* pBub;
	pBub = new Bub(0);
	pBub->GetTransform()->SetPosition({75,-75});
	Add(pBub);
	m_pPlayers.push_back(pBub);
	
	pBub = new Bub(1);
	pBub->GetTransform()->SetPosition({ 125,-75 });
	Add(pBub);
	m_pPlayers.push_back(pBub);

	
	m_pHud = new Hud();
	Add(m_pHud);
}

void SingleScene::Draw() const
{
}

void SingleScene::Update(float elapsedSec)
{

		if(currSegment==nullptr||(currSegment->IsCompleted()&&currSegment->IsDoneIni))
		{
			isInitializing = true;
			prevSegment = currSegment;
			playersRdy = false;
			currSegment = new LevelSegment(currentLevel, this);
			std::vector<glm::vec2> spawnLocs = currSegment->GetSpawnLocations();
			if(spawnLocs.size()<m_pPlayers.size())
			{
				std::cout << "Level doesn't have enough spawnPoints" << std::endl;
			}
			else
			{
				for (int j = 0; j < m_pPlayers.size(); j++)
				{
					m_pPlayers[j]->playerR = false;

					
					m_pPlayers[j]->SetRespawningPoint(spawnLocs[0]);
					m_pPlayers[j]->SetRespawning(true);
					spawnLocs.erase(spawnLocs.begin());
				}
			}
		}
		if (isInitializing)
		{
			if (!camRdy && currSegment->IsCamAtLoc(2.0f))
			{
				camRdy = true;
			}
			else
			{
				m_pActiveCam->MoveToLocation(elapsedSec, currSegment->GetCamLocation());
			}
			if (!playersRdy)
			{
				bool rdy = false;

				for (int j = 0; j < m_pPlayers.size(); j++)
				{
					rdy = m_pPlayers[j]->playerR;
				}
				if (rdy)
				{
					playersRdy = true;
				}
			}

			if (playersRdy && camRdy)
			{
				isInitializing = false;
				SafeDelete(prevSegment);
				currSegment->SetPaused(false);
				currSegment->IsDoneIni = true;
				for (int j = 0; j < m_pPlayers.size(); j++)
				{
					m_pPlayers[j]->SetRespawning(false);
				}
				currentLevel += 1;
			}
		}

	if(currSegment!=nullptr)
	{
		std::vector<glm::vec2> spawnLocs = currSegment->GetSpawnLocations();
		for(int i = 0;i< spawnLocs.size();i++)
		{
			DebugRenderer::DrawPoint(spawnLocs[i]);
		}
	}
	
}

SingleScene::~SingleScene()
{
	delete m_pContactListener;
	m_pContactListener = nullptr;
	
	delete b2Deb;
	b2Deb = nullptr;
}

