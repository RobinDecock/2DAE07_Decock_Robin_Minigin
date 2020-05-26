#pragma once
#include <vector>
#include <functional>
#include <map>
#include "BaseComponent.h"
#include "SpriteComponent.h"

struct Req;
enum Logic;
struct AnimData;
class AnimatorBlackboard;
class AnimatorState;
class Goal;

class Animator : public BaseComponent
{
public:
	Animator(PTR(SpriteComponent) spriteComp,PTR(AnimatorState) StartNode, AnimatorBlackboard& status);
	
	~Animator();
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LinkStates(std::shared_ptr<::AnimatorState> prevAnimatorState, std::shared_ptr<::AnimatorState>nextAnimatorState);
	void LinkStates(std::shared_ptr<::AnimatorState>prevAnimatorState, std::shared_ptr<::AnimatorState>nextAnimatorState,
	                std::vector<Req> requirements);
	void LinkStates(std::shared_ptr<::AnimatorState> prevAnimatorState, std::shared_ptr<::AnimatorState> nextAnimatorState, Req requirement);
	bool CheckRequirement(Req property);
	bool CheckLogic(int value1, int value2, Logic l);
	bool CheckLogic(float value1, float value2, Logic l);
	std::shared_ptr<AnimatorState> GetPreviousState() { return m_pPreviousAnimatorState; }
	std::shared_ptr<AnimatorState> GetCurrenState() { return m_pCurrentAnimatorState; }
	void SetCurrentState(std::shared_ptr<AnimatorState> an);
	void SetAnimData(std::map<int, AnimData> data) { m_AnimData = data; };
	
private:
	std::function<void(void)> m_Switch;
	std::shared_ptr<AnimatorState> m_pCurrentAnimatorState = nullptr;
	std::shared_ptr<AnimatorState> m_pPreviousAnimatorState = nullptr;
	AnimatorBlackboard& m_pAnimatorBlackboard;
	std::map<int, AnimData> m_AnimData;

	//To delete all nodes
	std::shared_ptr<AnimatorState> startState = nullptr;

	PTR(SpriteComponent) m_pSpriteComp = nullptr;
};
