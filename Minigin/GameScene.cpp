
#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Camera.h"
#include "DebugRenderer.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "TextComponent.h"
#include "Utils.h"
#include "TransformComponent.h"


	void GameScene::RootInitialize()
	{
		//FPS Monitor
#if _DEBUG
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		FPSMonitor = new GameObject();
		FPSMonitor->AddComponent(new TextComponent(font));
		FPSMonitor->GetTransform()->SetPosition({ Settings::GetWindowSize().x - 50,4 ,50.0f});
		Add(FPSMonitor);
#endif
		//
		
		Initialize();
		std::sort(m_pGameObjects.begin(), m_pGameObjects.end(), [](GameObject* a, GameObject* b) {return a->GetTransform()->GetDepth() < b->GetTransform()->GetDepth(); });
		if (m_pActiveCam == nullptr)
		{
			m_pActiveCam = new Camera();
		}
		m_IsInitialized = true;

		
	}

	void GameScene::RootDraw()const
	{
		//DRAW ORIGIN
#if _DEBUG
		DebugRenderer::DrawLine({ 0,0 }, { 1000,0 }, { 0xFF,0x0,0x00,0x0 });
		DebugRenderer::DrawLine({ 0,0 }, { 0,1000 }, { 0x0,0xFF	,0x0,0x0 });
#endif

		Draw();

		for (GameObject* obj : m_pGameObjects)
		{
			obj->RootDraw();
		}

		if (m_pPhysicsProxy.world != nullptr)
		{
			m_pPhysicsProxy.world->DrawDebugData();
		}

	}

	void GameScene::ThreadUpdate(float elapsedSec)
	{
#if _DEBUG
		FPSMonitor->GetComponent<TextComponent>()->SetText(std::to_string(int(1.0f / elapsedSec)));
#endif
		if (m_pActiveCam != nullptr)
		{
			m_pActiveCam->Update(elapsedSec);
		}

		Update(elapsedSec);

		for (size_t i = 0; i < m_pGameObjects.size(); i++)
		{
			if (m_pGameObjects[i] == nullptr)
			{
				m_pGameObjects.erase(m_pGameObjects.begin() + i);
				i -= 1;
				continue;
			}

			m_pGameObjects[i]->RootUpdate(elapsedSec);
		}


	}

	void GameScene::ThreadUpdatePhysics(float elapsedSec)
	{
		PhysicsUpdate(elapsedSec);

		m_pPhysicsProxy.isLocked = false;

		for (size_t i = 0; i < m_pGameObjects.size(); i++)
		{
			m_pGameObjects[i]->RootPhysicsUpdate(elapsedSec);
		}

		if (m_pPhysicsProxy.world != nullptr)
		{
			m_pPhysicsProxy.world->Step(1/50.0f, 8, 3);
		}

		m_pPhysicsProxy.isLocked = true;
	}

	void GameScene::RootUpdate(float elapsedSec)
	{
		updateThread = std::thread(&GameScene::ThreadUpdate, this, elapsedSec);
		physicsThread = std::thread(&GameScene::ThreadUpdatePhysics, this, elapsedSec);

		updateThread.join();
		physicsThread.join();
		while ((updateThread.joinable() || physicsThread.joinable()))
		{
			
		}
		LateUpdate(elapsedSec);
		
		while (m_pToDelete.size() >= 1)
		{
			for (unsigned int i = 0; i < m_pGameObjects.size(); i++)
			{
				if (m_pGameObjects[i] == m_pToDelete[0])
				{
					m_pGameObjects.erase(m_pGameObjects.begin() + i);
					break;
				}
			}
			std::cout << "Removes GameObject, Tag(" << m_pToDelete[0]->GetTag() << ") Id(" << m_pToDelete[0]->GetId() << ")" << std::endl;
			SafeDelete(m_pToDelete.at(0));
			
			m_pToDelete.erase(m_pToDelete.begin());
		}

		if (m_pToAdd.size() != 0)
		{
			std::sort(m_pGameObjects.begin(), m_pGameObjects.end(), [](GameObject* a, GameObject* b) { return a->GetTransform()->GetDepth() < b->GetTransform()->GetDepth(); });

			while (m_pToAdd.size() >= 1)
			{
				m_pGameObjects.push_back(m_pToAdd[0]);

				m_pToAdd[0]->RootInitialize();

				m_pToAdd.erase(m_pToAdd.begin());
			}
		}
	}

	GameScene::~GameScene()
	{
		SafeDelete(m_pPhysicsProxy.world);
		for (auto pObject : m_pGameObjects)
		{
			SafeDelete(pObject);
		}
		m_pGameObjects.clear();

		for (auto pObject : m_pToAdd)
		{
			SafeDelete(pObject);
		}


		SafeDelete(m_pActiveCam);

		m_pGameObjects.clear();


	}

	void GameScene::SetCamera(Camera* cam)
	{
		if (m_pActiveCam != nullptr)
		{
			Remove(m_pActiveCam);
		}
		m_pActiveCam = cam;
	}

	void GameScene::RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2)
	{
#if _DEBUG
		DebugRenderer::DrawLine(make_glmVec2(point1), make_glmVec2(point2), Color(255, 0, 0, 255));
#endif
		m_pPhysicsProxy.world->RayCast(callback, point1, point2);
	}


	void GameScene::Add(GameObject* obj)
	{
		m_pToAdd.push_back(obj);

		obj->SetId(idCount);
		obj->m_ParentScene = this;
		idCount += 1;

	}

	void GameScene::Remove(GameObject* obj)
	{
		std::cout << "Added GameObject For Removal, Tag(" << obj->GetTag() << ") Id(" << obj->GetId() << ")" << std::endl;

		for(int i = 0;i<m_pToDelete.size();i++)
		{
			if(m_pToDelete[i]==obj)
			{
				return;
			}
		}
		m_pToDelete.push_back(obj);
	}
