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

void GameObject::RootInitialize()
{
	Initialize();
	
	for(int i = 0;i<m_pChildren.size();i++)
	{
		m_pChildren[i]->m_ParentScene = m_ParentScene;
		m_pChildren[i]->RootInitialize();
	}
	for (int i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Initialize();
	}
	for (int i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->LateInitialize();
	}
	LateInitialize();
	m_IsInitialized = true;
}

void GameObject::RootUpdate(float elapsedSec)
{
	Update(elapsedSec);
	for (int i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->RootUpdate(elapsedSec);
	}


	for (int i = 0; i<m_pComponents.size();i++)
	{
		m_pComponents[i]->Update(elapsedSec);
	}
}

void GameObject::RootLateUpdate(float elapsedSec)
{
	LateUpdate(elapsedSec);
	for (auto comp : m_pComponents)
	{
		comp->LateUpdate(elapsedSec);
	}
	for (auto child : m_pChildren)
	{
		child->RootLateUpdate(elapsedSec);
	}
}



void GameObject::RootDraw()
{
	Draw();
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
		child->RootDraw();
	}
}

void GameObject::Update(float elapsedSec)
{
	UNREF(elapsedSec);
}

void GameObject::LateUpdate(float elapsedSec)
{
	UNREF(elapsedSec); 
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
	if(m_IsInitialized)
	{
		comp->Initialize();
		comp->LateInitialize();
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
	m_Tag = t;
}

std::string GameObject::GetTag()
{
	return m_Tag;
}

void GameObject::Contact(b2Fixture* thisfix, b2Fixture* other, b2Contact* contact, ContactType contactType)
{
	for (int i = 0; i < m_ContactCallbacks.size(); i++)
	{		
		m_ContactCallbacks[i](thisfix,other,contact,contactType);
	}
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
	if(m_IsInitialized)
	{
		child->m_ParentScene = m_ParentScene;
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


