#pragma once
#include "BaseComponent.h"
//#include <vector>

//struct b2Vec2;
class b2Body;
class b2Shape;
class b2PolygonShape;


class ColliderComponent : public BaseComponent
{
public:
	void Initialize() override;

	void Draw() override;;

	void PreDraw() override;;

	virtual void CreateShape(b2Body& bd);;
	//virtual void CreateNewShape(b2Vec2 dim, bool isStatic) {}//DEPRECATED?


	//std::vector<b2Vec2> GetVerticesList();//DEPRECATED ??
	b2Shape* GetShape();
protected:
	b2PolygonShape* m_Shape;
};
