#include "MiniginPCH.h"
#include "Camera.h"


#include "DebugRenderer.h"
#include "Minigin.h"
#include "TransformComponent.h"
#include "GLMC.h"
#include "GameScene.h"
#include "b2DebugDraw .h"
Camera::Camera()
{
	tag = "Camera";
	windowSize = Minigin::m_WindSize;

	//ONLY TESTING
	ortho = { windowSize.x / 2,windowSize.y / 2 };

	DebugRenderer::SetCamera(this);
}

void Camera::Initialize()
{


}

void Camera::Draw()
{

	//ImGui::Begin("Camera");
	//ImGui::Text(("Scale: "+std::to_string(m_Transform->GetScale().x)).c_str());
	//ImGui::Text(("Position: " + std::to_string(m_Transform->Get2DPosition().x)).c_str());
	//ImGui::End();
}

glm::mat4 Camera::GetViewMatrix()const
{
	glm::vec3 position = glm::vec3(-m_Transform->GetPosition().x + ortho.x / 2.0f, m_Transform->GetPosition().y + ortho.y / 2.0f, m_Transform->GetPosition().z);
	glm::vec2 scale = m_Transform->GetScale();
	glm::mat4 view = glm::mat4(1);

	glm::vec2 middoffset = glm::vec2(ortho.x / 2.0f, ortho.y / 2.0f);

	view = glm::translate(view, (glm::vec3(middoffset, 0)));
	view = glm::rotate(view, this->m_Transform->GetRotation(), glm::vec3(0.0, 0.0, 1.0f));
	view = glm::scale(view, glm::vec3(scale.x, scale.y, 1.0f));
	view = glm::translate(view, (position));

	view = glm::translate(view, (glm::vec3(-middoffset, 0)));


	return view;
}

glm::mat4 Camera::GetProjectionMatrix()const
{
	return glm::ortho(0.0f,(float) ortho.x,0.0f, (float) ortho.y, -1.0f, 100.0f);//NES 256 x 240 
}

glm::vec2 Camera::ConvertToWorldSpace(glm::vec2 pos)
{
	float x = ((2.0f * pos.x) / ortho.x) - 1.0f;
	float y = 1.0f - (2.0f * pos.y) / (ortho.y - 20.0f);
	//TODO FIX THIS MESS

	// 3D Normalised Device Coordinates
	float z = 1.0f; // the camera looks on the negative z axis
	glm::vec3 rayNds = glm::vec3(x, y, z);

	// 4D Homogeneous Clip Coordinates
	glm::vec4 rayClip = glm::vec4(rayNds, 1.0f);

	// 4D Eye (Camera) Coordinates
	glm::vec4 rayEye = glm::inverse(this->GetProjectionMatrix()) * rayClip;

	// 4D World Coordinates
	glm::vec4 rayWorld = glm::inverse(this->GetViewMatrix()) * rayEye;

	//rayWorld = glm::normalize(rayWorld);
	return glm::vec2(rayWorld.x, rayWorld.y);
}

glm::vec2 Camera::ConvertToScreenSpace(glm::vec2 pos)
{
	glm::vec4 rayWorld = glm::vec4(pos.x, pos.y, 0, 1);
	glm::vec4 normalizedScreen = this->GetProjectionMatrix() * (this->GetViewMatrix() * rayWorld);

	float x = ((normalizedScreen.x + 1.0f) * (ortho.x)) / 2.0f;
	float y = -((normalizedScreen.y - 1.0f) * (ortho.y - 20.0f)) / 2.0f;

	return glm::vec2(x, y);
}
