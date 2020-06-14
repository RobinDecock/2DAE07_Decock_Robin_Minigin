#include "MiniginPCH.h"
#include "b2CContactListener.h"

#include "GameObject.h"

void b2CContactListener::BeginContact(b2Contact* contact)
{
	GameObject* obj1 = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
	GameObject* obj2 = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());
	
	if (obj1 != nullptr && obj2 != nullptr)
	{
		obj1->Contact(contact->GetFixtureA(), contact->GetFixtureB(), contact, ContactType::BeginContact);
		obj2->Contact(contact->GetFixtureB(), contact->GetFixtureA(), contact, ContactType::BeginContact);
	}
}

void b2CContactListener::EndContact(b2Contact* contact)
{
	GameObject* obj1 = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
	GameObject* obj2 = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());

	if (obj1 != nullptr && obj2 != nullptr)
	{
		obj1->Contact(contact->GetFixtureA(),contact->GetFixtureB(), contact, ContactType::EndContact);
		obj2->Contact(contact->GetFixtureB(),contact->GetFixtureA(), contact, ContactType::EndContact);
	}
}

void b2CContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	UNREF(oldManifold);
	GameObject* obj1 = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
	GameObject* obj2 = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());

	if (obj1 != nullptr && obj2 != nullptr)
	{
		obj1->Contact(contact->GetFixtureA(), contact->GetFixtureB(), contact, ContactType::PreSolve);
		obj2->Contact(contact->GetFixtureB(), contact->GetFixtureA(), contact, ContactType::PreSolve);
	}
}

void b2CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	UNREF(impulse);
	GameObject* obj1 = static_cast<GameObject*>(contact->GetFixtureA()->GetUserData());
	GameObject* obj2 = static_cast<GameObject*>(contact->GetFixtureB()->GetUserData());

	if (obj1 != nullptr && obj2 != nullptr)
	{
		obj1->Contact(contact->GetFixtureA(), contact->GetFixtureB(), contact, ContactType::PostSolve);
		obj2->Contact(contact->GetFixtureB(), contact->GetFixtureA(), contact, ContactType::PostSolve);
	}
}

