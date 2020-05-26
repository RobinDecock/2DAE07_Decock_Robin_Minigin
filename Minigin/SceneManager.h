#pragma once
#include "Singleton.h"
#include <vector>
class GameScene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();
	//Singleton Get function
	static SceneManager* GetInstance();

	void RemoveScene(GameScene* scenePtr);
	void AddScene(GameScene* scenePtr);
	void Update(float elapsedSec);
	void Draw();
	void SetCurrentSceneIndex(int value) { m_CurrentSceneIndex = value; }
	void SetNextSceneIndex();
	void SetPreviousSceneIndex();
	GameScene* GetActiveScene() { return mScenes[m_CurrentSceneIndex]; }
private:
	static SceneManager* m_Instance;
	std::vector<GameScene*> mScenes;
	int m_CurrentSceneIndex = 0;
};
