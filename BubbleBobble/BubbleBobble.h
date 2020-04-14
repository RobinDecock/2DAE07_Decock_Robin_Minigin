#pragma once
#include "Project.h"
class SceneManager;

class BubbleBobble :public Project
{
public:
	void Initialize() override;

	void Update(float elapsedSec) override;

	void Draw() override;

	void CleanUp() override;
	~BubbleBobble() override;
private:
	SceneManager* sceneManager = nullptr;
};
