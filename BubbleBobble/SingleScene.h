#pragma once
#include "GameScene.h"
#include "ItemManager.h"
#include "Observer.h"
#include "SceneStates.h"
class LevelSegment;
class BaseEnemy;
class Bub;
class Hud;

enum class SceneEvent
{
	LevelSegmentComplete,LostControl,GameOver
};

class SingleScene final:
	public GameScene,public Observer
{
public:
	friend class BobbleScene::RespawnState;
	friend class BobbleScene::NormalState;
	friend class BobbleScene::GameOverState;
	SingleScene() = default;
	~SingleScene() override;
	Hud* GetHud() { return m_pHud; }
	std::vector<Bub*> GetPlayers() { return m_pPlayers; }
	


	void RemovePlayer(Bub* player);

	void AddLostPlayer(Bub* p) { LostPlayers.push_back(p); }
	bool IsSegmentReady() {return m_SegmentReady;}
	void SetPaused(bool b);
protected:

	
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec)override;

public:
	void onNotify(int event,GameObject* obj) override;
private:

	std::vector<Bub*> m_pPlayers;
	std::vector<int> m_SearchingControllers;
	bool m_SegmentReady = false;
	LevelSegment* currSegment = nullptr;
	LevelSegment* prevSegment = nullptr;
	BobbleScene::SceneState* m_pSceneState = nullptr;

	int currentLevel = 1;

	int maxLevel = 5;
	Hud* m_pHud = nullptr;

	ItemManager *m_pItemManager = nullptr;

	std::vector<Bub*> LostPlayers;
};

