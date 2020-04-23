#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Camera.h"
#include "DebugRenderer.h"
#include "Renderer.h"
GameScene::GameScene()
{
	
}

void GameScene::RootInitialize()
{
	Initialize();
	LateInitialize();

	for (GameObject* obj : m_pGameObjects)
	{
		obj->RootInitialize();
	}


	if(m_pActiveCam==nullptr)
	{
		m_pActiveCam = new Camera();
	}
	m_IsInitialized = true;
}

void GameScene::RootDraw()
{
	//DRAW ORIGIN
	DebugRenderer::DrawLine({ 0,0 }, { 1000,0 }, { '\xFF',0x0,0x00,0x0 });
	DebugRenderer::DrawLine({ 0,0 }, { 0,1000 }, { 0x0,'\xFF'	,0x0,0x0 });
	
	Draw();
	
	for (GameObject* obj : m_pGameObjects)
	{
		obj->RootDraw();
	}

	if (m_pColWorld != nullptr)
	{
		m_pColWorld->DrawDebugData();
	}

}

void GameScene::RootUpdate(float elapsedSec)
{
	if(m_pActiveCam!=nullptr)
	{
		m_pActiveCam->Update(elapsedSec);
	}
	if(m_pColWorld!=nullptr)
	{
		m_pColWorld->Step(elapsedSec, 1, 1);
	}

	
	Update(elapsedSec);

	for (size_t i = 0; i < m_pGameObjects.size(); i++)
	{
		if (m_pGameObjects[i] == nullptr)
		{
			m_pGameObjects.erase(m_pGameObjects.begin() + i);
			i -= 1;
		}
		m_pGameObjects[i]->RootUpdate(elapsedSec);
	}
}

GameScene::~GameScene()
{
	for (auto pObject : m_pGameObjects)
	{
		SafeDelete(pObject);
	}
	m_pGameObjects.clear();
}

void GameScene::SetCamera(Camera* cam)
{
	if(m_pActiveCam!=nullptr)
	{
		Remove(m_pActiveCam, true);
	}
	m_pActiveCam = cam;
}


void GameScene::Add(GameObject* obj)
{
	m_pGameObjects.push_back(obj);
	obj->SetId(idCount);
	idCount += 1;
	obj->m_ParentScene = this;

	if(m_IsInitialized)
	{
		obj->Initialize();
	}
	//DEPRECATED SORT
	//auto lambda = [](GameObject* obj1, GameObject* obj2) {return obj1->GetTransform()->GetPosition().z < obj2->GetTransform()->GetPosition().z; };
	//std::sort(m_pGameObjects.begin(), m_pGameObjects.end(), lambda);
}

void GameScene::Remove(GameObject* obj, bool deleteObj)
{
	for (size_t i = 0; i < m_pGameObjects.size(); i++)
	{
		if (m_pGameObjects[i] == obj)
		{
			
			m_pGameObjects.erase(m_pGameObjects.begin() + i);
			if(deleteObj)
			{
				delete obj;
				obj = nullptr;
			}
			return;
		}
	}
	if (deleteObj)
	{
		delete obj;
		obj = nullptr;
	}
}
