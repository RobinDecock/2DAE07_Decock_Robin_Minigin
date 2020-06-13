#include "MiniginPCH.h"
#include "GameObject.h"
#include "GameScene.h"
#include "BaseComponent.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include <algorithm>


	GameObject::GameObject()
	{
		m_Transform = new TransformComponent();
		AddComponent(m_Transform);
	}

	void GameObject::RootInitialize()
	{
		Initialize();

		for (unsigned int i = 0; i < m_pChildren.size(); i++)
		{
			m_pChildren[i]->m_ParentScene = m_ParentScene;
			m_pChildren[i]->RootInitialize();
		}
		for (unsigned int i = 0; i < m_pComponents.size(); i++)
		{
			m_pComponents[i]->Initialize();
		}
		for (unsigned int i = 0; i < m_pComponents.size(); i++)
		{
			m_pComponents[i]->LateInitialize();
		}
		LateInitialize();
		m_IsInitialized = true;
	}

	void GameObject::RootUpdate(float elapsedSec)
	{
		Update(elapsedSec);
		for (unsigned int i = 0; i < m_pChildren.size(); i++)
		{
			m_pChildren[i]->RootUpdate(elapsedSec);
		}


		for (unsigned int i = 0; i < m_pComponents.size(); i++)
		{
			m_pComponents[i]->Update(elapsedSec);
		}
	}

	void GameObject::RootPhysicsUpdate(float elapsedSec)
	{
		PhysicsUpdate(elapsedSec);
		for (unsigned int i = 0; i < m_pChildren.size(); i++)
		{
			m_pChildren[i]->RootPhysicsUpdate(elapsedSec);
		}


		for (unsigned int i = 0; i < m_pComponents.size(); i++)
		{
			m_pComponents[i]->PhysicsUpdate(elapsedSec);
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



	void GameObject::RootDraw()const
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


	void GameObject::SetPosition(glm::vec2 pos)
	{
		RigidbodyComponent* rigid = GetComponent<RigidbodyComponent>();
		if (rigid != nullptr)
		{
			rigid->SetBodyPosition(pos);
		}
		m_Transform->SetPosition(pos);
	}

	void GameObject::SetPosition(glm::vec3 pos)
	{
		RigidbodyComponent* rigid = GetComponent<RigidbodyComponent>();
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

	void GameObject::AddComponent(BaseComponent* comp)
	{
		m_pComponents.push_back(comp);
		std::sort(std::begin(m_pComponents), std::end(m_pComponents),
			[](BaseComponent* comp1, BaseComponent* comp2)
			{
				return comp1->GetCompType() < comp2->GetCompType();
			});

		comp->m_pGameObject = this;
		if (m_IsInitialized)
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
		return m_Transform;
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
		for (unsigned int i = 0; i < m_ContactCallbacks.size(); i++)
		{
			m_ContactCallbacks[i](thisfix, other, contact, contactType);
		}
	}

	unsigned int GameObject::GetId()
	{
		return id;
	}

	void GameObject::SetId(unsigned int i)
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
		m_pChildren.push_back(child);
		child->GetTransform()->SetParent(m_Transform);
		child->SetParent(this);

		if (m_IsInitialized)
		{
			child->m_ParentScene = m_ParentScene;
			child->RootInitialize();
		}
	}

	void GameObject::RemoveChild(GameObject* child, bool deleteObj)
	{
		for (unsigned int i = 0; i < m_pChildren.size(); i++)
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

		for (auto comp : m_pComponents)
		{
			SafeDelete(comp);
		}
	}


