#pragma once
#include "BaseComponent.h"
#include "vec2.hpp"
#include "vec3.hpp"

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent(glm::vec3 pos, float rot);
	TransformComponent();
	~TransformComponent();

	glm::vec3 GetPosition() const;
	glm::vec2 Get2DPosition() const;
	void SetPosition(glm::vec3 pos);
	void SetPosition(glm::vec2 pos);
	void Move(glm::vec3 offset);
	void Move(glm::vec2 offset);
	glm::vec2 GetScale() const;
	void SetScale(glm::vec2 scale);
	float GetRotation() const;
	void SetRotationDegree(float r);
	void SetRotationRad(float rot);
	void AddRotationDegree(float r);

	void SetParent(std::shared_ptr<TransformComponent> parent)
	{
		m_pParent = parent;
	}

protected:
	std::shared_ptr<TransformComponent> m_pParent = nullptr;

	float m_Rotation = 0;
	glm::vec3 m_LocalPosition{};
	glm::vec3 m_Position{};
	glm::vec2 m_Scale = glm::vec2(1, 1);
};
