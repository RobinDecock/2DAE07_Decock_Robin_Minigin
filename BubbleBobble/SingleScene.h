#pragma once
#include "AnimLoader.h"
#include "GameScene.h"
class LevelSegment;
class Bub;
class Hud;
class SingleScene final:
	public GameScene
{
public:
	SingleScene() = default;
	SingleScene(const SingleScene& other) = default;
	SingleScene& operator=(const SingleScene& other) = default;
	~SingleScene() override;
	Hud* GetHud() { return m_pHud; }
protected:
	
	void Initialize() override;
	void Draw() const override;
	void Update(float elapsedSec) override;

private:
	std::vector<Bub*> m_pPlayers;
	bool isInitializing = true;
	LevelSegment* currSegment = nullptr;
	LevelSegment* prevSegment = nullptr;
	int currentLevel = 1;
	bool camRdy = false;
	bool playersRdy = false;
	Hud* m_pHud = nullptr;
};

