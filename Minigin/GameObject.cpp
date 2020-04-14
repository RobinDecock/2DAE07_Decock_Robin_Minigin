#include "MiniginPch.h"
#include "GameObject.h"
#include "GameScene.h"
#include "BaseComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include <algorithm>

GameObject::GameObject()
{
	m_Transform = NEW(TransformComponent)();
	AddComponent(m_Transform);
}


void GameObject::Initialize()
{
	for (auto comp : m_pComponents)
	{
		comp->Initialize();
	}
	for (auto comp : m_pComponents)
	{
		comp->LateInitialize();
	}
	for (auto child : m_pChildren)
	{
		child->Initialize();
	}
	isInitialized = true;
}


void GameObject::Update(float elapsedSec)
{
	for (auto child : m_pChildren)
	{
		child->Update(elapsedSec);
	}


	for (auto comp : m_pComponents)
	{
		comp->Update(elapsedSec);
	}
}

void GameObject::LateUpdate(float elapsedSec)
{
	for (auto comp : m_pComponents)
	{
		comp->LateUpdate(elapsedSec);
	}
	for (auto child : m_pChildren)
	{
		child->LateUpdate(elapsedSec);
	}
}

void GameObject::Draw()
{
	for (auto comp : m_pComponents)
	{
		comp->PreDraw();
	}
	for (auto comp : m_pComponents)
	{
		comp->Draw();
	}
	for (auto child : m_pChildren)
	{
		child->Draw();
	}
}

void GameObject::SetPosition(glm::vec2 pos)
{
	m_Transform->SetPosition(pos);
}

void GameObject::SetPosition(glm::vec3 pos)
{
	std::shared_ptr<RigidbodyComponent> rigid = GetComponent<RigidbodyComponent>();
	if (rigid != nullptr)
	{
		rigid->SetBodyPosition(pos);
	}
	m_Transform->SetPosition(pos);
}

void GameObject::SetScale(glm::vec2 scale)
{
	m_Transform->SetScale(scale);
}

void GameObject::SetRotationDegree(float rot)
{
	m_Transform->SetRotationDegree(rot);
}

void GameObject::SetRotationRad(float rot)
{
	m_Transform->SetRotationRad(rot);
}

void GameObject::AddComponent(std::shared_ptr<BaseComponent> comp)
{
	m_pComponents.push_back(comp);
	std::sort(std::begin(m_pComponents), std::end(m_pComponents),
	          [](std::shared_ptr<BaseComponent> comp1, std::shared_ptr<BaseComponent> comp2)
	          {
		          return comp1->GetCompType() < comp2->GetCompType();
	          });

	comp->m_pGameObject = this;
	if (isInitialized)
	{
		comp->Initialize();
	}
}

void GameObject::SetScene(GameScene* scene)
{
	m_ParentScene = scene;
}

GameScene* GameObject::GetScene()
{
	return m_ParentScene;
}

TransformComponent* GameObject::GetTransform()
{
	return m_Transform.get();
}

void GameObject::SetParent(GameObject* obj)
{
	m_ParentObj = obj;
}

void GameObject::SetTag(std::string t)
{
	tag = t;
}

std::string GameObject::GetTag()
{
	return tag;
}

void GameObject::OnTrigger(BoxCollider* col, BoxCollider* other)
{
	UNREF(col);
	UNREF(other);
}

bool GameObject::GetIsInitialized()
{
	return isInitialized;
}

void GameObject::SetIsInitialized(bool b)
{
	isInitialized = b;
}

int GameObject::GetId()
{
	return id;
}

void GameObject::SetId(int i)
{
	id = i;
}

bool GameObject::GetVisibility()
{
	return m_Visibility;
}

void GameObject::SetVisibility(bool b)
{
	m_Visibility = b;
}

GameObject* GameObject::GetParent()
{
	return m_ParentObj;
}

void GameObject::AddChild(GameObject* child)
{
	child->GetTransform()->SetParent(m_Transform);
	m_pChildren.push_back(child);
	child->SetParent(this);
	child->m_ParentScene = this->m_ParentScene;
	if (isInitialized)
	{
		child->Initialize();
	}
}

void GameObject::RemoveChild(GameObject* child, bool deleteObj)
{
	for (int i = 0; i < m_pChildren.size(); i++)
	{
		if (m_pChildren[i] == child)
		{
			m_pChildren.erase(m_pChildren.begin() + i);
			return;
		}
	}
	if (deleteObj)
	{
		delete child;
	}
}

GameObject::~GameObject()
{
	for (auto child : m_pChildren)
	{
		SafeDelete(child);
	}
}


