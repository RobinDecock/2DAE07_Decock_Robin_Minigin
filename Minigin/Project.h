#pragma once
#include "SceneManager.h"


	class Project
	{
	public:
		virtual ~Project() = default;
		virtual void Initialize() = 0;
		virtual void Update(float elapsedSec) = 0;
		virtual void Draw() = 0;
	private:
		SceneManager* m_pSceneManager = nullptr;
	};
