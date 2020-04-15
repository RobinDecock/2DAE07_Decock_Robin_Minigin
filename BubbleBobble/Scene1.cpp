#include "ProjectPCH.h"
#include "Scene1.h"
#include "b2DebugDraw .h"
#include "Bub.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Camera.h"
#include "TransformComponent.h"
#include "FreeCamera.h"
#include "Minigin.h"

void Scene1::Initialize()
{
	ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");
	
	m_pActiveCam = new FreeCamera();
	m_pActiveCam->SetPosition({ -Minigin::m_WindSize.x / 2.0f,-Minigin::m_WindSize.y / 2.0f });
	Add(m_pActiveCam);
	
	m_pColWorld = new b2World(b2Vec2(0,9.81f));
	//m_pColWorld->SetDebugDraw(new b2DebugDraw());
	m_pBub = new Bub();
	m_pBub->GetTransform()->SetScale({ 10,10});
	m_pBub->GetTransform()->SetPosition({0,0});
	Add(m_pBub);

	
}

void Scene1::Draw() const
{
	//m_pColWorld->DrawDebugData();
}

void Scene1::Update(float elapsedSec)
{
	//m_pColWorld->Step(elapsedSec, 1, 1);
}

void Scene1::LateInitialize()
{
}
Scene1::~Scene1()
{
}

