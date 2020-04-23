#pragma once

#include <iostream>


#pragma warning( push, 1)

#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Common/b2Draw.h"
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

#include <windows.h>
#pragma warning( pop )
#include "GLMC.h"


#define PTR(X) std::shared_ptr<X>
#define NEW(X) std::make_shared<X>
#define UNREF(X) UNREFERENCED_PARAMETER(X)

template <class T>
void SafeDelete(T& pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}
