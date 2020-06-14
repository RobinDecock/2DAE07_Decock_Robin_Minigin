#include "MiniginPCH.h"
#include "FixedCamera.h"
#include "TransformComponent.h"

FixedCamera::FixedCamera(GameObject* lock)
{
	targetLock = lock;
}

void FixedCamera::Update(float elapsedSec)
{
	UNREF(elapsedSec);
	glm::vec3 pos = targetLock->GetTransform()->GetPosition();
	m_Transform->SetPosition(glm::vec3(pos.x,-pos.y,pos.z)-glm::vec3(ortho.x / 2.0f, -ortho.y / 2.0f, 1));
}

FixedCamera::~FixedCamera()
{
}
