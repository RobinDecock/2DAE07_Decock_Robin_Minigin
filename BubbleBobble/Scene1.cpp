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
#include "BoxCollider.h"
#include "FixedCamera.h"
#include "RigidbodyComponent.h"
void Scene1::Initialize()
{
	ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");
	
	//m_pActiveCam = new FreeCamera();
	//m_pActiveCam->SetPosition({ -Minigin::m_WindSize.x / 2.0f,-Minigin::m_WindSize.y / 2.0f });
	//Add(m_pActiveCam);
	
	m_pColWorld = new b2World(b2Vec2(0,9.81f));
	m_pColWorld->SetAllowSleeping(false);
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

	

	
	m_pBub = new Bub();
	m_pBub->GetTransform()->SetPosition({0,0});
	Add(m_pBub);
	SetCamera(new FixedCamera(m_pBub));




	GameObject* obj = new GameObject();
	obj->GetTransform()->SetPosition({ 0,200 });
	obj->AddComponent(NEW(RigidbodyComponent)(true));
	obj->AddComponent(NEW(BoxCollider)(glm::vec2(500,500),LayerMask::None,LayerMask::None));
	Add(obj);
	
}

void Scene1::Draw() const
{
	m_pColWorld->DrawDebugData();
}

void Scene1::Update(float elapsedSec)
{
	m_pColWorld->Step(elapsedSec, 1, 1);
}

void Scene1::LateInitialize()
{
}
Scene1::~Scene1()
{
}

