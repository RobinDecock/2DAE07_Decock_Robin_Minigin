#pragma once
#include <vector>
#include <functional>
#include <map>
#include "BaseComponent.h"

struct Requirement;
enum class Logic;
struct AnimData;
class AnimatorBlackboard;
class AnimatorState;
class Goal;

class Animator : public BaseComponent
{
public:
	Animator(AnimatorState* StartNode, AnimatorBlackboard& status);
	~Animator();
	void Update(float elapsedSec) override;
	void LinkStates(AnimatorState* prevAnimatorState, AnimatorState* nextAnimatorState);
	void LinkStates(AnimatorState* prevAnimatorState, AnimatorState* nextAnimatorState,
	                std::vector<Requirement> requirements);
	void LinkStates(AnimatorState* prevAnimatorState, AnimatorState* nextAnimatorState, Requirement requirement);
	bool CheckRequirement(Requirement property);
	bool CheckLogic(int value1, int value2, Logic l);
	bool CheckLogic(float value1, float value2, Logic l);
	AnimatorState* GetPreviousState() { return m_pPreviousAnimatorState; }
	AnimatorState* GetCurrenState() { return m_pCurrentAnimatorState; }

	void SetAnimData(std::map<int, AnimData> data) { m_AnimData = data; };
	
private:
	std::function<void(void)> m_Switch;
	AnimatorState* m_pCurrentAnimatorState = nullptr;
	AnimatorState* m_pPreviousAnimatorState = nullptr;
	AnimatorBlackboard& m_pAnimatorBlackboard;

	std::map<int, AnimData> m_AnimData;
};
