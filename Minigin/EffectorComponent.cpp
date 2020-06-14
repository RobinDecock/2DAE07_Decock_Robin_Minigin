#include "MiniginPCH.h"
#include "EffectorComponent.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "BoxTrigger.h"
#include "RigidbodyComponent.h"

EffectorComponent::EffectorComponent(BoxCollider* boxCollider,glm::vec2 localCenter, glm::vec2 size):m_pBoxCollider(boxCollider)
{
	m_pTrigger = new BoxTrigger(glm::vec2(size.x, size.y), localCenter);

}

void EffectorComponent::AddIgnore(b2Fixture* fix)
{
	for(unsigned int i = 0;i<m_ToIgnore.size();i++)
	{
		if(m_ToIgnore[i]==fix)
		{
			return;
		}
	}
	m_ToIgnore.push_back(fix);
}

void EffectorComponent::Initialize()
{
	m_pGameObject->AddComponent(m_pTrigger);


	
	m_pGameObject->AddContactCallback([this](b2Fixture* thisFix ,b2Fixture* other,b2Contact* contact, ContactType type)
		{
			UNREF(thisFix);
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
						uint16 ct = other->GetFilterData().categoryBits;
						if ((m_AffectedCat & ct) == ct)
						{
							for (unsigned int i = 0; i < m_ToIgnore.size(); i++)
							{
								if (m_ToIgnore[i] == other)
								{
									contact->SetEnabled(false);
									return;
								}
							}

							for (unsigned int i = 0; i < m_ToBlock.size(); i++)
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
						for (unsigned int i = 0; i < m_ToIgnore.size(); i++)
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

