#pragma once
#include <vector>

#include "Observer.h"
class SingleScene;

namespace BobbleScene
{
	class SceneState: public Observer
	{
	public:
		SceneState(SingleScene* pScene) :m_pScene(pScene)
		{}

		virtual ~SceneState() {}
		virtual SceneState* Execute(float elapsedSec) { UNREF(elapsedSec); return nullptr; }
		virtual void StartState() {}
		virtual void EndState() {}
	protected:
		SingleScene* m_pScene = nullptr;
	};


	class RespawnState :public SceneState
	{
	public:
		RespawnState(SingleScene* pScene) :SceneState(pScene)
		{}
		SceneState* Execute(float elapsedSec) override;
		void StartState() override;
		void EndState()override;
	private:
		bool camRdy = false;
		bool playersRdy = false;
		glm::vec2 camLocation{};
	};

	class NormalState :public SceneState
	{
	public:

		NormalState(SingleScene* pScene) :SceneState(pScene)
		{}
		SceneState* Execute(float elapsedSec) override;
		void onNotify(int event, GameObject* obj) override;
	private:
		bool m_LevelDone = false;
		float m_DoneTimer = 0.0f;
		float m_DoneDelay = 4.0f;
		std::vector<int> m_SearchingControllers;

		bool m_GameOver = false;
	};

	class GameOverState :public SceneState
	{
	public:
		GameOverState(SingleScene* pScene) :SceneState(pScene)
		{}
		void StartState() override;
		SceneState* Execute(float elapsedSec) override;
	};


}
