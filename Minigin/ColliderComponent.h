#pragma once
#include "BaseComponent.h"
typedef unsigned short uint16;
class b2Body;
class b2Shape;
class b2PolygonShape;
class b2Fixture;


	class ColliderComponent : public BaseComponent
	{
	public:
		void Initialize() override;

		void SetCategory(uint16 i);
		void SetIgnoreMask(uint16 i);
		void SetSensor(bool b);
		bool IsSensor();
		void SetRestitution(float f);
		//std::vector<b2Vec2> GetVerticesList();//DEPRECATED ??
		b2Shape& GetShape();
		b2Fixture* GetFixture() { return m_pFixture; }
		void SetFriction(float v);
		b2FixtureDef m_FixtureDef;
	protected:
		b2PolygonShape m_Shape{};

		b2Fixture* m_pFixture = nullptr;
		b2Filter filter;
		bool m_IsInitialized = false;
	};
