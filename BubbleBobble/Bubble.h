#pragma once
#include "GameObject.h"

class Bubble: public GameObject
{
public:
	~Bubble() override;
	void OnTrigger(BoxCollider* col, BoxCollider* other) override;
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;
};

