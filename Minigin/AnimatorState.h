#pragma once

#include <vector>
#include <functional>
#include <ctime>
#include <string>
struct Req;


class AnimatorState
{
public:
	class Connection
	{
	public:
		Connection(std::shared_ptr<AnimatorState>act);

		Connection(std::shared_ptr<AnimatorState>act, std::vector<Req> require);

		Connection(std::shared_ptr<AnimatorState> act, Req require);
		~Connection();
		bool hasRequirement = true;
		std::shared_ptr<AnimatorState> AnimatorState;
		std::vector<Req> requirements;
	};

	friend class PlayerN;
	AnimatorState(int id,std::string name);
	~AnimatorState();

	void AddNextAnimatorState(std::shared_ptr<::AnimatorState> AnimatorState);
	void AddNextAnimatorState(std::shared_ptr<::AnimatorState> AnimatorState, std::vector<Req> requirements);
	void AddNextAnimatorState(std::shared_ptr<::AnimatorState> AnimatorState, Req requirement);
	void SetSpeed(float speed) { m_Speed = speed; }
	float GetSpeed() { return m_Speed; }
	void Execute(float elapsedSec);
	bool HasFunction();

	void LeaveState()
	{
		m_hasRun = false;
		runTime = 0;
	}

	std::vector<Connection*> GetNextAnimatorStates() { return m_NextConnections; };
	std::string GetName() { return m_Name; }
	std::function<void(void)> m_Function;

	void SetEventFunction(float time, std::function<void(void)> f)
	{
		m_EventFunctions.push_back(std::pair<float, std::function<void(void)>>(time, f));
	}

	int m_EnumValue = 0;

	int GetValue()
	{
		return m_EnumValue;
	}
	void SetLooping(bool b)
	{
		m_isLooping = b;
	}
	bool GetLooping() { return m_isLooping; }
	bool m_WaitUntilAnimDone = false;
private:
	
	float m_Speed = 1.0f;
	bool m_isLooping = true;
	bool m_hasRun = false;
	std::vector<Connection*> m_NextConnections;
	std::vector<Req> m_pRequirements;

	std::vector<std::pair<float, std::function<void(void)>>> m_EventFunctions;

	float runTime = 0.f;
	std::string m_Name = "";
	
};
