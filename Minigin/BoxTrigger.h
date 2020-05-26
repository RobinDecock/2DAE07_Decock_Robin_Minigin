#pragma once
#include "ColliderComponent.h"
class BoxTrigger :public ColliderComponent
{
public:
	void Initialize() override;
	BoxTrigger(glm::vec2 widthHeight,glm::vec2 localCenter = glm::vec2(0,0));
};

