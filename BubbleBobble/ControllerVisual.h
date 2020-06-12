#pragma once
#include "GameObject.h"

class ControllerVisual: public GameObject
{
private:
	void Initialize() override;
	void Update(float elapsedSec) override;
};

