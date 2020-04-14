#include "MiniginPCH.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <map>
#include "GameObject.h"
#include <SDL_hints.h>
#include <SDL.h>

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

void SceneManager::AddScene(GameScene* scenePtr)
{
	mScenes.push_back(scenePtr);
	scenePtr->RootInitialize();
}
