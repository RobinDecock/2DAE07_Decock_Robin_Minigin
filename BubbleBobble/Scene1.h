#pragma once
#include "GameScene.h"

class Bub;

class Scene1 final:
	public GameScene
{
public:

	~Scene1() override;
protected:
	void LateInitialize() override;
	void Initialize() override;
	void Draw() const override;
	void Update(float elapsedSec) override;
private:
	Bub* m_pBub = nullptr;
};

