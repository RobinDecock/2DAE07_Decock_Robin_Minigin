#pragma once
#include "BaseComponent.h"

class AutoDestroyComponent: public BaseComponent
{
public:
	AutoDestroyComponent(float time);
	~AutoDestroyComponent() override = default;
	float timer = 0.0f;
	float delay = 1.0f;
protected:
	void Update(float elapsedSec) override;
};

