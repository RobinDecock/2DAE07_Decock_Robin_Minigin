#include "MiniginPCH.h"
#include "EffectorComponent.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "BoxTrigger.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "RigidbodyComponent.h"

void EffectorContactCallback::BeginContact(b2Contact* contact)
{
}

void EffectorContactCallback::EndContact(b2Contact* contact)
{
}

EffectorComponent::EffectorComponent(PTR(BoxCollider) boxCollider,glm::vec2 localCenter, glm::vec2 size):m_pBoxCollider(boxCollider)
{
	m_pTrigger = NEW(BoxTrigger)(glm::vec2(size.x, size.y), localCenter);

}

void EffectorComponent::AddIgnore(b2Fixture* fix)
{
	for(int i = 0;i<m_ToIgnore.size();i++)
	{
		if(m_ToIgnore[i]==fix)
		{
			return;
		}
	}
	m_ToIgnore.push_back(fix);
}

EffectorComponent::~EffectorComponent()
{
}


void EffectorComponent::Initialize()
{
	m_pGameObject->AddComponent(m_pTrigger);


	
	m_pGameObject->AddContactCallback([this](b2Fixture* thisFix ,b2Fixture* other,b2Contact* contact, ContactType type)
		{
			//IF TRIGGER IS HIT OR ENDED
			{
				uint16 cat = other->GetFilterData().categoryBits;

				if ((m_AffectedCat & cat) != cat)return;

				if (thisFix == m_pTrigger->GetFixture())
				{
					if (type == ContactType::BeginContact)
					{
						if (!contact->IsEnabled())
						{
							contact->SetEnabled(true);
						}
						m_ToBlock.push_back(other);
					}
					else if (type == ContactType::EndContact)
					{
						m_ToBlock.erase(std::remove(m_ToBlock.begin(), m_ToBlock.end(), other));
					}
				}
				else if (thisFix == m_pBoxCollider->GetFixture())
				{
					if (type == ContactType::PreSolve)
					{
						uint16 cat = other->GetFilterData().categoryBits;
						if ((m_AffectedCat & cat) == cat)
						{
							for (int i = 0; i < m_ToIgnore.size(); i++)
							{
								if (m_ToIgnore[i] == other)
								{
									contact->SetEnabled(false);
									return;
								}
							}

							for (int i = 0; i < m_ToBlock.size(); i++)
							{
								if (m_ToBlock[i] == other)
								{
									contact->SetEnabled(true);
									return;
								}
							}
							contact->SetEnabled(false);
						}
					}
					else if (type == ContactType::EndContact)
					{
						for (int i = 0; i < m_ToIgnore.size(); i++)
						{
							if (m_ToIgnore[i] == other)
							{
								m_ToIgnore.erase(m_ToIgnore.begin() + i);
								return;
							}
						}
					}
				}
			}
		}
	);
	
}


void EffectorComponent::Update(float elapsedSec)
{
}

void EffectorComponent::LateUpdate(float elapsedSec)
{
}

void EffectorComponent::Draw()
{
}

void EffectorComponent::PreDraw()
{
}

void EffectorComponent::Release()
{
}
