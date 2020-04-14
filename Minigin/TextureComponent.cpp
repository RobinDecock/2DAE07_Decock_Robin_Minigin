#include "MiniginPCH.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Components.h"
TextureComponent::TextureComponent(std::string filePath)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filePath);
	m_Type = CompType::TextureC;
}

TextureComponent::~TextureComponent()
{
	delete m_Texture;
}

void TextureComponent::Draw()
{
	Renderer::RenderTexture(*m_Texture);
}

void TextureComponent::Update(float elapsedSec)
{
	UNREF(elapsedSec);
	
	Camera* cam = m_pGameObject->GetScene()->GetCamera();
	glm::vec2 scale = m_pGameObject->GetTransform()->GetScale();



	glm::vec4 beginPos = glm::vec4(m_pGameObject->GetTransform()->GetPosition(),1.0f);
	glm::vec4 endPos = glm::vec4(m_pGameObject->GetTransform()->GetPosition()+glm::vec3(m_Texture->GetWidth() * scale.x, m_Texture->GetHeight() * scale.y,0.0f),1.0f);

	glm::mat4 projView = cam->GetProjectionMatrix() * cam->GetViewMatrix();

	beginPos = projView * beginPos;
	endPos = projView * endPos;

	float width = endPos.x - beginPos.y;
	float height = endPos.y - beginPos.y;

	SetDestinationRectangle({ (int)beginPos.x,(int)beginPos.y,(int)width ,(int)height});
}

void TextureComponent::SetSourceRectangle(SDL_Rect rect)
{
	m_Texture->SetSrcRect(rect);
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
