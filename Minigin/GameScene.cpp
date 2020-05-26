#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Camera.h"
#include "DebugRenderer.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Utils.h"

GameScene::GameScene()
{
	
}

void GameScene::RootInitialize()
{
	//FPS Monitor
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	/*FPSMonitor = new GameObject();
	FPSMonitor->AddComponent(std::make_shared<TextComponent>(font));
	Add(FPSMonitor);*/

	//

	
	Initialize();

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
	//FPSMonitor->GetComponent<TextComponent>()->SetText(std::to_string(int(1.0f/ elapsedSec)));
	if(m_pActiveCam!=nullptr)
	{
		m_pActiveCam->Update(elapsedSec);
	}
	if(m_pColWorld!=nullptr)
	{
		m_pColWorld->Step(elapsedSec, 8, 3);
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

	while(m_pToDelete.size()>=1)
	{
		delete m_pToDelete[0];
		m_pToDelete.erase(m_pToDelete.begin());
	}
}

GameScene::~GameScene()
{
	for (auto pObject : m_pGameObjects)
	{
		SafeDelete(pObject);
	}
	SafeDelete(m_pActiveCam);
	SafeDelete(m_pColWorld);
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

void GameScene::RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2)
{
	DebugRenderer::DrawLine(make_glmVec2(point1),make_glmVec2( point2), Color(255, 0, 0,255));
	
	m_pColWorld->RayCast(callback, point1, point2);
}


void GameScene::Add(GameObject* obj)
{
	m_pGameObjects.push_back(obj);
	obj->SetId(idCount);
	idCount += 1;
	obj->m_ParentScene = this;

	obj->RootInitialize();
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
			if(deleteObj)
			{
				m_pToDelete.push_back(obj);
			}
			m_pGameObjects.erase(m_pGameObjects.begin() + i);
			return;
		}
	}
}
