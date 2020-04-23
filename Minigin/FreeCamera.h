#pragma once
#include "Camera.h"
#include "GameObject.h"
class FreeCamera:public Camera
{
public:
	void OnTrigger(BoxCollider* col, BoxCollider* other) override;
	~FreeCamera() override;
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;
private:
	bool m_IsLocked = false;
};

