#include "MiniginPCH.h"
#include "Components.h"

#include "Camera.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameScene.h"

SpriteComponent::SpriteComponent(std::string filePath) :
	m_Speed{1.0f}, m_Offset(0.f, 0.f)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filePath);
	m_Type = CompType::SpriteC;
}

void SpriteComponent::Initialize()
{
	//SDL_Rect rect = m_Texture->GetSourceRectangle();
	//m_TileSize = int2((int)rect.w / m_Cols, (int)rect.h / m_Rows);
	//m_SrcRect.w = (int)(m_TileSize.x);
	//m_SrcRect.h = (int)(m_TileSize.y);
	//

	////SET DESTINATION 
	//m_DestRect.x = (int)m_pGameObject->GetTransform().GetPosition().x;
	//m_DestRect.y = (int)m_pGameObject->GetTransform().GetPosition().y;
	//float v = (float)m_pGameObject->GetTransform().GetScale().x;
	//UNREF(v);
	//m_DestRect.w = (int)(m_TileSize.x*m_pGameObject->GetTransform().GetScale().x);
	//m_DestRect.h = (int)(m_TileSize.y*m_pGameObject->GetTransform().GetScale().y);
	//m_Texture->SetAngle(m_pGameObject->GetTransform().GetRotation());
	//m_Texture->SetDestinationRectangle(m_DestRect);
}

void SpriteComponent::Draw()
{
	Renderer::RenderTexture(*m_Texture);
}


void SpriteComponent::Update(float elapsedSec)
{
	UpdateDestination2D();
	UpdateSource2D();
	if ((m_Rows == 1 && m_Cols == 1) || pause)
	{
		return;
	}
	if (m_Sec > 1)
	{
		if (m_Grid.x < (m_Cols - 1))
		{
			++m_Grid.x;

			m_Sec = 0;
		}
		else
		{
			m_Cycle += 1;
			if (m_Grid.y % m_Rows == 0)
			{
				m_Grid.y = 0;
			}
			else
			{
				m_Grid.y += 1;
			}


			m_Grid.x = 0;
			m_Sec = 0;
		}
	}
	else
	{
		m_Sec += elapsedSec * m_Speed;
	}

	if (std::find(m_Exceptions.begin(), m_Exceptions.end(), m_Grid.x) != m_Exceptions.end())
	{
		++m_Grid.x;
	}
}


void SpriteComponent::SetSpriteData(AnimData data)
{
	m_Rows = data.RowsCols.x;
	m_Cols = data.RowsCols.y;
	m_StartPos = int2(data.Src.x, data.Src.y);
	m_SrcRect.x = data.Src.x;
	m_SrcRect.y = data.Src.y;
	m_SrcRect.w = data.Src.w / m_Cols;
	m_SrcRect.h = data.Src.h / m_Rows;
	m_TileSize = int2(m_SrcRect.w, m_SrcRect.h);
	m_Grid.x = 0;
	m_Grid.y = 0;
	UpdateDestination2D();
}

void SpriteComponent::UpdateDestination2D()
{
	m_Rotation = m_pGameObject->GetTransform()->GetRotation();
	m_DestRect.x = static_cast<int>(m_pGameObject->GetTransform()->GetPosition().x);
	m_DestRect.y = static_cast<int>(m_pGameObject->GetTransform()->GetPosition().y);
	m_DestRect.w = static_cast<int>(m_TileSize.x * m_pGameObject->GetTransform()->GetScale().x);
	m_DestRect.h = static_cast<int>(m_TileSize.y * m_pGameObject->GetTransform()->GetScale().y);


	Camera* cam = m_pGameObject->GetScene()->GetCamera();
	glm::vec2 scale = m_pGameObject->GetTransform()->GetScale();
	if(cam!=nullptr)
	{
		glm::vec4 beginPos = glm::vec4(m_pGameObject->GetTransform()->GetPosition(), 1.0f);


		glm::vec3 end = m_pGameObject->GetTransform()->GetPosition() + glm::vec3(m_TileSize.x * scale.x, m_TileSize.y* scale.y, 0.0f);
		glm::vec4 endPos = glm::vec4(end, 1.0f);

		glm::mat4 viewProj = cam->GetViewMatrix();

		beginPos = viewProj * beginPos;

		endPos = viewProj * endPos;

		float width = endPos.x - beginPos.x;
		float height = endPos.y - beginPos.y;

		m_Texture->SetDestRect({ (int)beginPos.x,(int)beginPos.y,(int)width ,(int)height });
		m_Texture->SetAngle(m_pGameObject->GetTransform()->GetRotation());
	}
	else
	{
		m_Texture->SetDestRect(m_DestRect);
		m_Texture->SetAngle(m_pGameObject->GetTransform()->GetRotation());
	}
	

}

void SpriteComponent::UpdateSource2D()
{
	m_SrcRect.x = m_StartPos.x + m_TileSize.x * m_Grid.x;
	m_SrcRect.y = m_StartPos.y + m_TileSize.y * m_Grid.y;
	m_SrcRect.w = m_TileSize.x;
	m_SrcRect.h = m_TileSize.y;
	m_Texture->SetSrcRect(m_SrcRect);
}


void SpriteComponent::Setoffset(glm::vec2 offset)
{
	m_Offset = offset;
}

void SpriteComponent::SetPivot(glm::vec2 pivot)
{
	m_Texture->SetPivot(pivot);
}

void SpriteComponent::ResetCycle()
{
	m_Cycle = 0;
}

void SpriteComponent::SetState(int2 grid)
{
	m_Grid = grid;
}

void SpriteComponent::ResetState()
{
	m_Grid.x = 0;
	m_Grid.y = 0;
	m_Cycle = 0;
}

int2 SpriteComponent::GetState() const
{
	return m_Grid;
}

void SpriteComponent::SetSrcY(int change)
{
	m_Change = change;
}

void SpriteComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

void SpriteComponent::SetExceptions(int change)
{
	int value{0};
	for (size_t i = 0; i < m_Exceptions.size(); i++)
	{
		if (m_Exceptions[i] == change)
		{
			++value;
		}
	}
	if (value == 0)
	{
		m_Exceptions.push_back(change);
	}
}

void SpriteComponent::ResetExceptions()
{
	m_Exceptions.clear();
}

SpriteComponent::~SpriteComponent()
{
	m_Exceptions.clear();
	delete m_Texture;
}
