#pragma once
#include <string>

class GameObject;

enum class CompType
{
	None = 20,
	TransformC = 6,
	RigidbodyC = 1,
	BoxColliderC = 2,
	SpriteC = 3,
	TextureC = 4
};

class BaseComponent
{
	friend class GameObject;
public:
	BaseComponent();

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) noexcept = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

	GameObject* GetGameObject();
	void SetActive(bool active);
	virtual ~BaseComponent();
	CompType GetCompType();
protected:

	//* Virtual Functions *//
	virtual void Initialize();

	virtual void LateInitialize();

	virtual void Update(float elapsedSec);

	virtual void LateUpdate(float elapsedSec);;

	virtual void Draw();

	virtual void PreDraw();

	virtual void Release();

	//*                   *//


	GameObject* m_pGameObject = nullptr;
	bool m_IsActive = true;
	std::string compName = "";
	CompType m_Type = CompType::None;
};

