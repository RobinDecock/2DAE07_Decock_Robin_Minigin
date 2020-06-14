#pragma once
#include "BaseEnemy.h"
#include "GameObject.h"
#include "Observer.h"
#include "SingleScene.h"

class Zen;
class GameScene;

class LevelSegment:public Subject
{
public:
	LevelSegment(int levelId,SingleScene* pScene);
	~LevelSegment();

	size_t GetEnemyCount()
	{
		return m_pEnemies.size();
	}
	bool MakeNewController(int controllerId);

	void EnemyUnlockPlayer(Bub* player);
	void LoadMap(std::string mapPath,std::string blockPath);
	void AddObj(GameObject* obj) { m_pSegObjects.push_back(obj); }

	void AddEnemy(BaseEnemy* enemy) { m_pEnemies.push_back(enemy); m_pCurrScene->Add(enemy); }

	void SetPaused(bool b)
	{
		for (unsigned int i = 0; i < m_pEnemies.size(); i++)
		{
			m_pEnemies[i]->SetPaused(b);
		}
	}
	
	void RemoveEnemy(BaseEnemy* enemy)
	{
		for(unsigned int i = 0;i<m_pEnemies.size();i++)
		{
			if(m_pEnemies[i]==enemy)
			{
				m_pEnemies.erase(m_pEnemies.begin()+i);
				break;
			}
		}
		m_pCurrScene->Remove(enemy);

		if(enemy->IsControlled())
		{
			Notify(int(SceneEvent::LostControl), enemy);
		}
		
		if(m_pEnemies.size()==0)
		{
			Notify(int(SceneEvent::LevelSegmentComplete));
		}
	}
	void Release()
	{
		ItemManager::GetInstance().Clear();
		for (size_t i = 0; i < m_pSegObjects.size(); i++)
		{
			m_pCurrScene->Remove(m_pSegObjects[i]);
		}
		m_pSegObjects.clear();
	}
	std::vector<glm::vec2> GetSpawnLocations()
	{
		return spawnLocations;
	}
	glm::vec2 GetCamLocation() { return camLocation; }
	
	bool IsDoneIni = false;
private:

	glm::vec2 camLocation;
	int m_LevelId = 0;
	SingleScene* m_pCurrScene = nullptr;
	std::vector<glm::vec2>spawnLocations;

	std::vector<BaseEnemy*> m_pEnemies;
	std::vector<GameObject*> m_pSegObjects;
};

