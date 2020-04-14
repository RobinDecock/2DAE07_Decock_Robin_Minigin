#pragma once
#include "GameObject.h"
#include "Block.h"
class PlayField:public GameObject
{
public:
	PlayField();
	void Initialize() override;
	void Update(float elapsedSec) override;
	void Render() const override;
	void ParseLevelFile(std::string path);
	float2 ConvertArrIndexToPos(int2 pos);
	std::vector<std::vector<Block*>> &GetLevelLayout() { return m_LevelLayout; }
	std::vector<Snobee*> GetSnobees() { return SnobeeVector; }
	void TriggerBoundary();

private:
	void SpawnPlayer();
	void SpawnEnemies();
	std::vector<std::vector<Block*>> m_LevelLayout;

	std::vector<Boundary*> m_pBoundaries;
	std::vector<Snobee*>SnobeeVector;
	Pengo* m_Pengo = nullptr;
};

