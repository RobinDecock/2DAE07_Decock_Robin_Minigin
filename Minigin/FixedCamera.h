#pragma once
#include "Camera.h"


class FixedCamera : public Camera
{
public:
	FixedCamera(GameObject* lock);
protected:

	void Update(float elapsedSec) override;
public:
	~FixedCamera() override;
private:
	GameObject* targetLock = nullptr;
};

