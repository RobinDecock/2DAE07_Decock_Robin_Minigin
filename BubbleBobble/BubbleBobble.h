#pragma once
#include "Project.h"
class SceneManager;

enum LayerMask :unsigned short
{
	None = 1 << 0,
	Ground = 1 << 1,
	Platform = 1<<2,
	Enemies = 1 << 3,
	Player = 1 << 4,
	Bubbles = 1<<5,
	Roof = 1<<6,
	Items = 1 << 7
};

class BubbleBobble :public Project
{
public:
	void Initialize() override;

	void Update(float elapsedSec) override;

	void Draw() override;

	~BubbleBobble() override;
private:
	SceneManager* sceneManager = nullptr;
};
