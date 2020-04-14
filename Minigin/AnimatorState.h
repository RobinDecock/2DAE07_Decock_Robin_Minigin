#pragma once

#include <vector>
#include <functional>
#include <ctime>
#include <string>
struct Requirement;


class AnimatorState
{
public:
	struct Node
	{
		Node(AnimatorState* act);

		Node(AnimatorState* act, std::vector<Requirement> require);

		Node(AnimatorState* act, Requirement require);
		bool hasRequirement = true;
		AnimatorState* AnimatorState;
		std::vector<Requirement> requirements;
	};

	friend class PlayerN;
	AnimatorState(int v, std::string name = "");
	~AnimatorState();

	void AddNextAnimatorState(AnimatorState* AnimatorState);
	void AddNextAnimatorState(AnimatorState* AnimatorState, std::vector<Requirement> requirements);
	void AddNextAnimatorState(AnimatorState* AnimatorState, Requirement requirement);
	void Execute(float elapsedSec);
	bool HasFunction();

	void LeaveState()
	{
		m_hasRun = false;
		runTime = 0;
	}

	std::vector<Node*> GetNextAnimatorStates() { return m_NextAnimatorStates; };
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

private:
	bool m_isLooping = true;
	bool m_hasRun = false;
	std::vector<Node*> m_NextAnimatorStates;
	std::vector<Requirement> m_pRequirements;

	std::vector<std::pair<float, std::function<void(void)>>> m_EventFunctions;

	float runTime = 0.f;
	std::string m_Name = "";
};
