#pragma once
#include "Singleton.h"
#include <vector>
class GameScene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	void AddScene(GameScene* scenePtr);
	void Update(float elapsedSec);
	void Draw();
	void SetCurrentSceneIndex(int value) { m_CurrentSceneIndex = value; }
	void SetNextSceneIndex();
	void SetPreviousSceneIndex();
	GameScene* GetActiveScene() { return mScenes[m_CurrentSceneIndex]; }
private:
	std::vector<GameScene*> mScenes;
	int m_CurrentSceneIndex = 0;
};
