#include "MiniginPCH.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <map>
#include "GameObject.h"
#include <SDL.h>

SceneManager* SceneManager::m_Instance = nullptr;


SceneManager::SceneManager()
{
	m_Instance = this;
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < mScenes.size(); i++)
	{
		SafeDelete(mScenes[i]);
	}
}


void SceneManager::Update(float elapsedSec)
{
	mScenes[m_CurrentSceneIndex]->RootUpdate(elapsedSec);

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_F2])
	{
		SetNextSceneIndex();
	}
	else if (pStates[SDL_SCANCODE_F1])
	{
		SetPreviousSceneIndex();
	}
}

void SceneManager::Draw()
{
	mScenes[m_CurrentSceneIndex]->RootDraw();
}

void SceneManager::SetNextSceneIndex()
{
	if (m_CurrentSceneIndex < static_cast<int>(mScenes.size()) - 1)
	{
		m_CurrentSceneIndex += 1;
	}
}

void SceneManager::SetPreviousSceneIndex()
{
	if (m_CurrentSceneIndex > 0)
	{
		m_CurrentSceneIndex -= 1;
	}
}

SceneManager* SceneManager::GetInstance()
{
		if (!m_Instance)
			m_Instance = new SceneManager();

		return m_Instance;
}

void SceneManager::RemoveScene(GameScene* scenePtr)
{
	for(int i = 0; i<mScenes.size();i++)
	{
		if(mScenes[i] == scenePtr)
		{
			mScenes.erase(mScenes.begin() + i);
			return;
		}
	}
}

void SceneManager::AddScene(GameScene* scenePtr)
{
	mScenes.push_back(scenePtr);
	scenePtr->RootInitialize();
}
