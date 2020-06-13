#pragma once
#include "Camera.h"


class FixedCamera : public Camera
{
public:
	FixedCamera(GameObject* lock);
protected:

	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
public:
	void Initialize() override;
	~FixedCamera() override;
private:
	GameObject* targetLock = nullptr;
};

