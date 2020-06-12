#include "MiniginPCH.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Camera.h"
#include "GeneralStructs.h"
#include "Components.h"
TextureComponent::TextureComponent(std::string filePath)
{
	m_Texture = new Texture2D(ResourceManager::GetInstance().LoadTexture(filePath));
	m_Type = CompType::TextureC;
}

TextureComponent::~TextureComponent()
{
	SafeDelete(m_Texture);
}

void TextureComponent::Draw()
{
	if (!m_pGameObject->GetVisibility()) 
	{
		return;
	}
	Camera* cam = m_pGameObject->GetScene()->GetCamera();
	glm::vec2 scale = m_pGameObject->GetTransform()->GetScale();
	if (cam != nullptr && useCam)
	{
		glm::vec4 beginPos = glm::vec4(m_pGameObject->GetTransform()->GetPosition(), 1.0f);


		glm::vec3 end = m_pGameObject->GetTransform()->GetPosition() + glm::vec3(m_Texture->GetSrcRect().w * scale.x, m_Texture->GetSrcRect().h * scale.y, 0.0f);
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
		glm::vec2 pos = m_pGameObject->GetTransform()->Get2DPosition();

		m_Texture->SetDestRect({ (int)pos.x,(int)pos.y,(int)(m_Texture->GetWidth() * scale.x), (int)(m_Texture->GetHeight() * scale.y) });
		m_Texture->SetAngle(m_pGameObject->GetTransform()->GetRotation());
	}

	m_Texture->SetDepth(m_pGameObject->GetTransform()->GetPosition().z);
	Renderer::RenderTexture(*m_Texture);
}
void TextureComponent::SetSourceRectangle(SDL_Rect rect)
{
	m_Texture->SetSrcRect(rect);
}

void TextureComponent::SetSourceRectangle(int4 rect)
{
	SDL_Rect rc;
	rc.x = rect.x;
	rc.y = rect.y;
	rc.w = rect.w;
	rc.h = rect.h;

	m_Texture->SetSrcRect(rc);
}

void TextureComponent::SetDestinationRectangle(SDL_Rect rect)
{
	m_Texture->SetDestRect(rect);
}

Texture2D* TextureComponent::GetSDLTexture()
{
	return m_Texture;
}

int TextureComponent::GetWidth() const
{
	return m_Texture->GetWidth();
}

int TextureComponent::GetHeight() const
{
	return m_Texture->GetHeight();
}
