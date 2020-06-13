#pragma once
#include "Camera.h"


	class FreeCamera :public Camera
	{
	public:

	protected:
		void Initialize() override;
		void Update(float elapsedSec) override;
	private:
		bool m_IsLocked = true;
	};

