#include "ProjectPCH.h"
#include "SingleScene.h"
#include "AnimLoader.h"
#include "b2DebugDraw.h"
#include "Bub.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "FreeCamera.h"
#include "Zen.h"
#include "TextureComponent.h"
#include "b2CContactListener.h"
#include "DebugRenderer.h"
#include "FixedCamera.h"
#include "GameSettings.h"
#include "Hud.h"
#include "ItemManager.h"
#include "LevelSegment.h"
#include "MainMenu.h"
#include "SceneManager.h"
#include "Settings.h"
#include "SoundManager.h"
#include "ResourceManager.h"
void SingleScene::Initialize()
{
	m_pItemManager = new ItemManager(this);
	ItemManager::SetInstance(m_pItemManager);
	
	ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");






	ResourceManager::GetInstance().LoadTexture("Bub.png");
	ResourceManager::GetInstance().LoadTexture("Blocks.png");
	ResourceManager::GetInstance().LoadTexture("CVisual.png");
	ResourceManager::GetInstance().LoadTexture("Enemies.png");
	ResourceManager::GetInstance().LoadTexture("Sprite.png");

	ResourceManager::GetInstance().LoadTexture("Title.png");













	
	SetCamera(new FreeCamera());
	
	m_pActiveCam->SetPosition(glm::vec2(Settings::GetWindowSize().x/4.0f, -Settings::GetWindowSize().y / 4.0f - 3 * 8));
	m_pActiveCam->SetScale({ 2.0f,2.0f });
	m_pPhysicsProxy.world = new b2World(b2Vec2(0,9.81f));
	m_pPhysicsProxy.world->SetAllowSleeping(false);
	m_pContactListener =new  b2CContactListener();

#if _DEBUG
	
	m_B2DebugDraw = new b2DebugDraw();
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;

	m_B2DebugDraw->SetFlags(flags);
	
	m_pPhysicsProxy.world->SetDebugDraw(m_B2DebugDraw);
	m_B2DebugDraw->SetScene(this);
#endif

#if NDEBUG
	SoundManager::PlayMusic("../BubbleBobble/Resources/Audio/MainTheme.mp3");
#endif
	
	
	
	m_pPhysicsProxy.world->SetContactListener(m_pContactListener);


	//HUD INI
	m_pHud = new Hud();
	Add(m_pHud);
	m_pHud->SetPosition(glm::vec3(0, 0, 100));
	//*******
	
	
	Bub* pBub;
	pBub = new Bub(0);
	pBub->GetTransform()->SetPosition({75,-75});
	Add(pBub);
	m_pPlayers.push_back(pBub);

	if(GameSettings::m_Gamemode  == GameMode::Coop)
	{
		pBub = new Bub(1);
		pBub->GetTransform()->SetPosition({ 125,-75 });
		Add(pBub);
		m_pPlayers.push_back(pBub);
	}
	if(GameSettings::m_Gamemode == GameMode::Versus)
	{
		m_SearchingControllers.push_back(1);
	}


	m_pSceneState = new BobbleScene::RespawnState(this);
	m_pSceneState->StartState();

	
}

void SingleScene::Update(float elapsedSec)
{
	BobbleScene::SceneState* state = m_pSceneState->Execute(elapsedSec);

	if(state!=nullptr)
	{
		m_pSceneState->EndState();
		SafeDelete(m_pSceneState);
		m_pSceneState = state;
		m_pSceneState->StartState();
	}
	
}

void SingleScene::LateUpdate(float elapsedSec)
{
	UNREF(elapsedSec);
	for(unsigned int i= 0;i<LostPlayers.size();i++)
	{
		currSegment->EnemyUnlockPlayer(LostPlayers[i]);
	}
	LostPlayers.clear();
}

void SingleScene::onNotify( int event,GameObject * obj)
{
	SceneEvent sceneEvent = SceneEvent(event);
	m_pSceneState->onNotify(event, obj);
	switch (sceneEvent)
	{
	case SceneEvent::LostControl:
	{
		BaseEnemy* pEnemy = static_cast<BaseEnemy*>(obj);
		m_SearchingControllers.push_back(pEnemy->GetController());
	}
	break;
	default:;
	}
}

void SingleScene::RemovePlayer(Bub* player)
{
	for (unsigned int i = 0; i < m_pPlayers.size(); i++)
	{
		if (m_pPlayers[i] == player)
		{
			m_pPlayers.erase(m_pPlayers.begin() + i);
			break;
		}
	}
	//TODO observer?
	LostPlayers.push_back(player);
	if (m_pPlayers.size() == 0)
	{
		onNotify(int(SceneEvent::GameOver),nullptr);
		if(currSegment!=nullptr)
		{
			currSegment->SetPaused(true);
		}
	}
}

void SingleScene::SetPaused(bool b)
{
	currSegment->SetPaused(b);
}


SingleScene::~SingleScene()
{
	SafeDelete(m_pSceneState);
	SafeDelete(currSegment);
	SafeDelete(m_B2DebugDraw);

	SafeDelete(m_pContactListener);
	SoundManager::StopMusic();
	ItemManager::DestroyInstance();
}

