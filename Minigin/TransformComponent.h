#pragma once
#include "BaseComponent.h"
#include "GLMS.h"

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent(glm::vec3 pos, float rot);
	TransformComponent();
	~TransformComponent() = default;

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
	void SetDepth(float d) { m_Position.z = d; };
	float GetDepth() { return m_Position.z; }
	void SetParent(TransformComponent* parent)
	{
		m_pParent = parent;
	}

protected:
	TransformComponent* m_pParent = nullptr;

	float m_Rotation = 0;
	glm::vec3 m_LocalPosition{};
	glm::vec3 m_Position{};
	glm::vec2 m_Scale = glm::vec2(1, 1);
};
