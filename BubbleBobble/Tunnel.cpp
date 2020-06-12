#include "ProjectPCH.h"
#include "Tunnel.h"

#include "BubbleBobble.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "Bub.h"
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
			if (type==ContactType::EndContact)
			{
				if(other->GetFilterData().categoryBits == LayerMask::Player)
				{
					Bub* ref = static_cast<Bub*>(other->GetUserData());
					if (!ref->IsRespawning())
					{
						hitObjects.push_back(ref);
					}
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
	for(unsigned int i = 0;i< hitObjects.size();i++)
	{
		
		glm::vec2 pos = m_Transform->Get2DPosition();
		hitObjects[i]->SetPosition(glm::vec2(hitObjects[i]->GetTransform()->Get2DPosition().x, pos.y - 28 * 8));
		hitObjects[i]->GetComponent<RigidbodyComponent>()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		std::cout << "******MOVED********" << std::endl;
	}
	hitObjects.clear();
}
