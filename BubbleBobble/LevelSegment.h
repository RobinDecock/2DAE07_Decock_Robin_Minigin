#pragma once
#include "BaseEnemy.h"
#include "GameObject.h"
#include "SingleScene.h"
class Zen;
class GameScene;

class LevelSegment
{
public:
	LevelSegment(int levelId,SingleScene* pScene);
	~LevelSegment();

	void FinishPlatform(GameObject* platform);
	bool IsCompleted() { return m_pEnemies.size() == 0; }
	std::vector<glm::vec2> GetSpawnLocations() {return m_SpawnLocations;}
	glm::vec2 GetCamLocation() { return camLocation; }
	bool IsCamAtLoc(float tolerance);
	void LoadMap(std::string mapPath,std::string blockPath);
	void SetPaused(bool b);
	void Remove(Zen* zen);
	bool IsDoneIni = false;
private:
	int m_LevelId = 0;
	bool m_IsPaused = true;

	SingleScene* currScene = nullptr;
	std::vector<BaseEnemy*> m_pEnemies;
	std::vector<GameObject*> segObjects;
	std::vector<glm::vec2> m_SpawnLocations;
	glm::vec2 camLocation{};
};

