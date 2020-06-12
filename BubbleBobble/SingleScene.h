#pragma once
#include "GameScene.h"
#include "ItemManager.h"
#include "Observer.h"
class LevelSegment;
class BaseEnemy;
class Bub;
class Hud;

enum SceneEvent
{
	LevelSegmentComplete,LostControl
};

class SingleScene final:
	public GameScene,public Observer
{
public:
	SingleScene() = default;
	~SingleScene() override;
	Hud* GetHud() { return m_pHud; }
	std::vector<Bub*> GetPlayers() { return m_pPlayers; }

	void SetCamLocation(glm::vec2 loc) { camLocation = loc; }
	
	void AddSpawnLocation(glm::vec2 loc)
	{
		spawnLocations.push_back(loc);
	}

	void RemovePlayer(Bub* player);

	void CreateNewSegment();

	
	void SetPaused(bool b);
protected:

	void Initialize() override;
	void Draw() const override;
	void Update(float elapsedSec) override;

public:
	void onNotify(int event,GameObject* obj) override;
private:

	std::vector<Bub*> m_pPlayers;
	std::vector<int> searchingControllers;
	
	bool isInitializing = true;
	LevelSegment* currSegment = nullptr;
	LevelSegment* prevSegment = nullptr;
	glm::vec2 camLocation;
	std::vector<glm::vec2>spawnLocations;
	int currentLevel = 1;
	bool camRdy = false;
	bool playersRdy = false;

	bool levelDone = false;
	Hud* m_pHud = nullptr;

	bool m_GameOver = false;
	float doneTimer = 0.0f;
	float doneDelay = 4.0f;


	ItemManager *m_pItemManager = nullptr;
};

