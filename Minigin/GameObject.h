#pragma once
#include <functional>
#include <vector>
#include <string>
#include "BOX2DS.h"
#include "GameObject.h"


	class TransformComponent;
	class BaseComponent;
	class BoxCollider;
	class GameScene;
	enum class ContactType
	{
		BeginContact, EndContact, PreSolve, PostSolve
	};

	typedef std::function<void(b2Fixture*, b2Fixture*, b2Contact*, ContactType)> ContactCallback;
	class GameObject
	{
	public:
		friend class GameScene;
		GameObject();
		virtual ~GameObject();

		void SetPosition(glm::vec3 pos);
		void SetPosition(glm::vec2 pos);
		void SetScale(glm::vec2 scale);
		void SetRotationDegree(float rot);
		void SetRotationRad(float rot);
		void AddComponent(BaseComponent* comp);
		void SetScene(GameScene* scene);
		GameScene* GetScene();
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child, bool deleteObj = false);
		int GetChildCount() { return m_pChildren.size(); }
		TransformComponent* GetTransform();
		void SetParent(GameObject* obj);
		void SetTag(std::string t);
		std::string GetTag();
		void Contact(b2Fixture* thisfix, b2Fixture* other, b2Contact* contact, ContactType contactType);
		unsigned int GetId();
		void SetId(unsigned int i);
		bool GetVisibility();
		bool IsInitialized() { return m_IsInitialized; }
		void SetVisibility(bool b);
		GameObject* GetParent();

		template <typename T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (BaseComponent* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
				{
					return  dynamic_cast<T*>(component);
				}
			}

			return nullptr;
		}
		void AddContactCallback(ContactCallback callback)
		{
			m_ContactCallbacks.push_back(callback);
		}

	protected:

		void RootInitialize();
		void RootUpdate(float elapsedSec);

		void RootPhysicsUpdate(float elapsedSec);

		void RootLateUpdate(float elapsedSec);
		void RootDraw()const;

		std::vector<BaseComponent*> m_pComponents{};
		GameScene* m_ParentScene = nullptr;
		GameObject* m_ParentObj = nullptr;
		std::vector<GameObject*> m_pChildren;
		TransformComponent* m_Transform = nullptr;
		std::string m_Tag = "Default";
		unsigned int id = 0;
		bool m_Visibility = true;
		bool m_IsInitialized = false;

	private:
		//* Virtual Function *//
		virtual void Initialize() {}
		virtual void LateInitialize() {}
		virtual void Update(float elapsedSec) {}
		virtual void PhysicsUpdate(float elapsedSec) {}
		virtual void LateUpdate(float elapsedSec) {}
		virtual void Draw()const {}
		//*                  *//
		std::vector<ContactCallback> m_ContactCallbacks;

	};
