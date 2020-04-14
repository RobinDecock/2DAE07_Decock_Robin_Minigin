#pragma once
#include <memory>
#include <vector>
#include <string>
class TransformComponent;
class BaseComponent;
class BoxCollider;
class GameScene;
#include "vec2.hpp"
#include "vec3.hpp"
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
	void AddComponent(std::shared_ptr<BaseComponent> comp);
	void SetScene(GameScene* scene);
	GameScene* GetScene();
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child, bool deleteObj = false);
	TransformComponent* GetTransform();
	void SetParent(GameObject* obj);
	void SetTag(std::string t);
	std::string GetTag();
	virtual void OnTrigger(BoxCollider* col, BoxCollider* other);;

	bool GetIsInitialized();
	void SetIsInitialized(bool b);
	int GetId();
	void SetId(int i);
	bool GetVisibility();

	void SetVisibility(bool b);
	GameObject* GetParent();

	template <class T>
	std::shared_ptr<T> GetComponent()
	{
		const type_info& ti = typeid(T);
		for (const std::shared_ptr<BaseComponent> component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
			{
				return std::dynamic_pointer_cast<T>(component);
			}
		}

		return nullptr;
	}


protected:

	//* Virtual Function *//
	virtual void Initialize();
	virtual void Update(float elapsedSec);
	virtual void LateUpdate(float elapsedSec);
	virtual void Draw();
	//*                  *//


	std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
	GameScene* m_ParentScene = nullptr;
	GameObject* m_ParentObj = nullptr;
	std::vector<GameObject*> m_pChildren;
	std::shared_ptr<TransformComponent> m_Transform = nullptr;
	std::string tag = "Default";
	bool isInitialized = false;
	int id = 0;
	bool m_Visibility = true;
};
