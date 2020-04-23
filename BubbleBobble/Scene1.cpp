#include "ProjectPCH.h"
#include "Scene1.h"

#include "AnimLoader.h"
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
#include "ColBlock.h"
#include "FixedCamera.h"
#include "RigidbodyComponent.h"
void Scene1::Initialize()
{
	ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");
	SetCamera(new FreeCamera());
	
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

	//

	//
	m_pBub = new Bub();
	m_pBub->GetTransform()->SetPosition({7*8,7*8});
	Add(m_pBub);
	//SetCamera(new FixedCamera(m_pBub));




	//GameObject* obj = new GameObject();
	//obj->GetTransform()->SetPosition({ 0,200 });
	//obj->AddComponent(NEW(RigidbodyComponent)(true));
	//obj->AddComponent(NEW(BoxCollider)(glm::vec2(500,500),LayerMask::None,LayerMask::None));
	//Add(obj);
	int halfTexSize = 16/2;
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y <15; y++)
		{
			if (x==14||x==0||y==0||y==14)
			{
				ColBlock* colBlock = new ColBlock(0);
				colBlock->GetTransform()->SetPosition({ 0 + x * halfTexSize, 0 + y * halfTexSize });
				Add(colBlock);
			}

		}
	}
}

void Scene1::Draw() const
{
}

void Scene1::Update(float elapsedSec)
{

}

void Scene1::LateInitialize()
{
}
Scene1::~Scene1()
{
}

