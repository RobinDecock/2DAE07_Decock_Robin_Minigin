#include "MiniginPCH.h"
#include "TransformComponent.h"


	TransformComponent::TransformComponent(glm::vec3 pos, float rot)
	{
		m_Position = pos;
		m_Rotation = rot;
		compName = "Transform";
		m_Type = CompType::TransformC;
	}

	TransformComponent::TransformComponent()
	{
		m_Type = CompType::TransformC;
		compName = "Transform";
	}

	glm::vec3 TransformComponent::GetPosition() const
	{
		if (m_pParent != nullptr)
		{
			return m_pParent->GetPosition() + m_LocalPosition;
		}

		return m_Position;
	}


	glm::vec2 TransformComponent::Get2DPosition() const
	{
		if (m_pParent != nullptr)
		{
			return m_pParent->GetPosition() + m_LocalPosition;
		}

		return m_Position;
	}

	void TransformComponent::SetPosition(glm::vec3 pos)
	{
		if (m_pParent != nullptr)
		{
			m_LocalPosition = pos;
		}
		else
		{
			m_Position = pos;
		}
	}

	void TransformComponent::SetPosition(glm::vec2 pos)
	{
		if (m_pParent != nullptr)
		{
			m_LocalPosition.x = pos.x;
			m_LocalPosition.y = pos.y;
		}
		else
		{
			m_Position.x = pos.x;
			m_Position.y = pos.y;
		}
	}

	void TransformComponent::Move(glm::vec3 offset)
	{
		if (m_pParent != nullptr)
		{
			m_LocalPosition += offset;
		}
		else
		{
			m_Position += offset;
		}
	}

	void TransformComponent::Move(glm::vec2 offset)
	{
		if (m_pParent != nullptr)
		{
			m_LocalPosition += glm::vec3(offset.x, offset.y, 0);
		}
		else
		{
			m_Position += glm::vec3(offset.x, offset.y, 0);
		}
	}

	glm::vec2 TransformComponent::GetScale() const
	{
		if (m_pParent != nullptr)
		{
			return m_pParent->GetScale() * m_Scale;
		}

		return m_Scale;
	}

	void TransformComponent::SetScale(glm::vec2 scale)
	{
		m_Scale = scale;
	}

	float TransformComponent::GetRotation() const
	{
		if (m_pParent != nullptr)
		{
			return m_pParent->GetRotation() + m_Rotation;
		}
		return m_Rotation;
	}

	void TransformComponent::SetRotationDegree(float r)
	{
		m_Rotation = r * 3.1415f / 180.0f;
	}

	void TransformComponent::SetRotationRad(float rot)
	{
		m_Rotation = rot;
	}

	void TransformComponent::AddRotationDegree(float r)
	{
		m_Rotation += r * 3.1415f / 180.0f;
	}

