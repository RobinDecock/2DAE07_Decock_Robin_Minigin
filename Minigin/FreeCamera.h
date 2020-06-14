#pragma once
#include "Camera.h"


	class FreeCamera :public Camera
	{
	public:

	protected:
		void Initialize() override;
		void Update(float elapsedSec) override;
		void HandleInput(float elapsedSec);
	private:
		bool m_IsLocked = true;
	};

