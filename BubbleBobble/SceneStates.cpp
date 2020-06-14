#include "ProjectPCH.h"
#include "SceneStates.h"
#include "Camera.h"
#include "SingleScene.h"
#include "TransformComponent.h"
#include "Bub.h"
#include "LevelSegment.h"
#include "MainMenu.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Settings.h"
#include "TextComponent.h"
namespace BobbleScene
{

	void RespawnState::StartState()
	{
		//Set cam locatino set spawn location
		const int level = m_pScene->currentLevel;
		if(level==m_pScene->maxLevel)
		{
			return;
		}

		
		LevelSegment* &pCurrSegment = m_pScene->currSegment;
		LevelSegment* & pPrevSegment = m_pScene->prevSegment;

		std::vector<Bub*> &pPlayers = m_pScene->m_pPlayers;
		
		pPrevSegment = pCurrSegment;
		playersRdy = false;
		pCurrSegment = new LevelSegment(level, m_pScene);

		camLocation = pCurrSegment->GetCamLocation();
		std::vector<glm::vec2> spawnLocations = pCurrSegment->GetSpawnLocations();
		
		if (spawnLocations.size() < pPlayers.size())
		{
			std::cout << "Level doesn't have enough spawnPoints" << std::endl;
		}
		else
		{
			for (unsigned int j = 0; j < pPlayers.size(); j++)
			{
				pPlayers[j]->m_PlayerReady = false;
				pPlayers[j]->SetRespawningPoint(spawnLocations[0]);
				pPlayers[j]->SetRespawning(true);
				spawnLocations.erase(spawnLocations.begin());
			}
		}
	}

	SceneState* RespawnState::Execute(float elapsedSec)
	{
		int& level = m_pScene->currentLevel;
		if (level ==m_pScene->maxLevel)
		{
			return new GameOverState(m_pScene);
		}
		std::vector <Bub*>& players= m_pScene->m_pPlayers;
		
		Camera* pActiveCam = m_pScene->m_pActiveCam;

		if (!camRdy)
		{
			if (glm::distance(pActiveCam->GetTransform()->Get2DPosition(), camLocation) < 2.0f)
			{
				camRdy = true;
			}
			pActiveCam->MoveToLocation(elapsedSec, camLocation);
		}

		if (!playersRdy)
		{
			bool rdy = true;

			for (unsigned int j = 0; j < players.size(); j++)
			{
				if (!players[j]->m_PlayerReady)
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
			camRdy = false;
			std::vector<Bub*>& pPlayers = m_pScene->m_pPlayers;
			LevelSegment*& pCurrSegment = m_pScene->currSegment;
			LevelSegment*& pPrevSegment = m_pScene->prevSegment;
			if (pPrevSegment != nullptr)
			{
				pPrevSegment->Release();
				SafeDelete(pPrevSegment);
			}

			pCurrSegment->SetPaused(false);
			
			pCurrSegment->IsDoneIni = true;
			for (unsigned int j = 0; j < pPlayers.size(); j++)
			{
				pPlayers[j]->SetRespawning(false);
			}
			level += 1;
			return new NormalState(m_pScene);
		}
		return nullptr;
	}
	void RespawnState::EndState()
	{

	}


	SceneState* NormalState::Execute(float elapsedSec)
	{

		std::vector<int>& searchingControllers = m_pScene->m_SearchingControllers;
		
		if (m_LevelDone)
		{
			if (m_DoneTimer > m_DoneDelay)
			{
				return new RespawnState(m_pScene);
			}
			else
			{
				m_DoneTimer += elapsedSec;
			}
		}

		LevelSegment* currSegment = m_pScene->currSegment;
		
		if (currSegment != nullptr)
		{
			if (searchingControllers.size() != 0 && currSegment->GetEnemyCount() > 0)
			{
				bool assignementComplete = true;
				while (searchingControllers.size() > 0 && assignementComplete)
				{
					assignementComplete = currSegment->MakeNewController(searchingControllers[0]);
					if (assignementComplete)
					{
						searchingControllers.erase(searchingControllers.begin());
					}
				}

			}
		}

		if (m_GameOver)
		{
			return new GameOverState(m_pScene);
		}
		return nullptr;
	}

	void NormalState::onNotify(int event, GameObject* obj)
	{
		UNREF(obj);
		SceneEvent sceneEvent = SceneEvent(event);

		switch(sceneEvent)
		{
		case SceneEvent::LevelSegmentComplete:
			{
				m_LevelDone = true;
			}
			break;
		case SceneEvent::GameOver:
			{
				m_GameOver = true;
			}
			break;
		}
	}

	void GameOverState::StartState()
	{
		GameObject* returnScreen = new GameObject();
		Font* pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		returnScreen->AddComponent(new TextComponent(pFont, "Press R to Retry"));
		m_pScene->Add(returnScreen);
		returnScreen->SetPosition(glm::vec2(Settings::GetWindowSize().x / 2.0f, Settings::GetWindowSize().y / 2.0f));
	}

	SceneState* GameOverState::Execute(float elapsedSec)
	{
		UNREF(elapsedSec);
		if (InputManager::IsKeyboardKeyPressed(SDL_SCANCODE_R))
		{
			SceneManager::GetInstance()->AddScene(new MainMenu());
			SceneManager::GetInstance()->RemoveScene(m_pScene);
		}


		return nullptr;
	}
}
