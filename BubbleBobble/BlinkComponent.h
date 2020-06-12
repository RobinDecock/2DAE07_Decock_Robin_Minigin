#pragma once
#include "BaseComponent.h"

class BlinkComponent:public BaseComponent
{
public:
	BlinkComponent(float interval):m_Interval{interval}
	{
	}
	~BlinkComponent();
protected:

	
	void Update(float elapsedSec) override;
private:
	float m_Interval = 0.0f;

	float m_BlinkTimer = 0.0f;
};

