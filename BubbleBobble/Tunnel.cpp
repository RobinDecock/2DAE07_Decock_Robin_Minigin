#include "ProjectPCH.h"
#include "Tunnel.h"

#include "BubbleBobble.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "Bub.h"
#include "GameScene.h"
Tunnel::Tunnel()
{
	AddComponent(new RigidbodyComponent(true));
	boxT = new BoxTrigger(glm::vec2(8 * 32, 8));
}

void Tunnel::Initialize()
{
	AddComponent(boxT);

	this->AddContactCallback([this](b2Fixture* thisFix, b2Fixture* other, b2Contact* contact, ContactType type)
		{
			UNREF(thisFix);
			UNREF(contact);
			if (type==ContactType::EndContact)
			{
				if(other->GetFilterData().categoryBits == LayerMask::Player)
				{
					Bub* ref = static_cast<Bub*>(other->GetUserData());
					if (ref->IsRespawned())
					{
						hitObjects.push_back(ref);
					}
				}
				else if (other->GetFilterData().categoryBits == LayerMask::Items)
				{
					m_ParentScene->Remove(static_cast<GameObject*>(other->GetUserData()));
				}
				else
				{
					hitObjects.push_back(static_cast<GameObject*>(other->GetUserData()));
				}
				
			}
		});
	
}

void Tunnel::PhysicsUpdate(float elapsedSec)
{
	UNREF(elapsedSec);
	for (unsigned int i = 0; i < hitObjects.size(); i++)
	{

		glm::vec2 pos = m_Transform->Get2DPosition();
		hitObjects[i]->SetPosition(glm::vec2(hitObjects[i]->GetTransform()->Get2DPosition().x, pos.y - 26 * 8));
		hitObjects[i]->GetComponent<RigidbodyComponent>()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	}
	hitObjects.clear();
}
