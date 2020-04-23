#pragma once
#include "GameObject.h"

class Texture2D;
class ColBlock:public GameObject
{
public:
	ColBlock(int levelNumber);
	~ColBlock() override;
	void OnTrigger(BoxCollider* col, BoxCollider* other) override;
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;
};

