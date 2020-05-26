#pragma once
#include "BaseComponent.h"
class BoxTrigger;
class BoxCollider;

class EffectorContactCallback : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};





class EffectorComponent:public BaseComponent
{
public:
	EffectorComponent(PTR(BoxCollider) boxCollider,glm::vec2 localCenter,glm::vec2 size);
	void SetCategoryToAffect(uint16 category) { m_AffectedCat = category; }
	void AddIgnore(b2Fixture* fix);
	~EffectorComponent() override;
protected:
	void Initialize() override;

	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;
	void PreDraw() override;
	void Release() override;
private:
	PTR(BoxCollider) m_pBoxCollider{};
	PTR(BoxTrigger)m_pTrigger = nullptr;
	std::vector<b2Fixture*>m_ToBlock;
	std::vector<b2Fixture*>m_ToIgnore;

	
	uint16 m_AffectedCat = 0;
};

