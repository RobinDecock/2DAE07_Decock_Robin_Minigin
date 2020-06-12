#pragma once
#include <vector>
#include <functional>
#include <map>
#include "BaseComponent.h"
#include "SpriteComponent.h"

class BaseState;
struct Req;
enum class Logic;
struct AnimData;
class AnimatorBlackboard;
class AnimatorState;
class Goal;

class Animator : public BaseComponent
{
public:
	Animator(SpriteComponent* spriteComp, AnimatorState* StartNode, AnimatorBlackboard& status);

	~Animator();
	void Initialize() override;
	void Update(float elapsedSec) override;
	
	void LinkStates(BaseState* prevAnimatorState, BaseState* nextAnimatorState);
	void LinkStates(BaseState* prevAnimatorState, BaseState* nextAnimatorState,
		std::vector<Req> requirements);
	void LinkStates(BaseState* prevAnimatorState, BaseState* nextAnimatorState, Req requirement);
	bool CheckLogic(int value1, int value2, Logic l);
	bool CheckLogic(float value1, float value2, Logic l);
	AnimatorState* GetPreviousState()const { return m_pPreviousAnimatorState; }
	AnimatorState* GetCurrenState()const { return m_pCurrentAnimatorState; }
	void SetCurrentState(AnimatorState* an);
	void SetAnimData(std::map<int, AnimData> data) { m_AnimData = data; };
	void AddState(BaseState* state);

private:

	

	std::function<void(void)> m_Switch;
	AnimatorState* m_pCurrentAnimatorState = nullptr;
	AnimatorState* m_pPreviousAnimatorState = nullptr;
	AnimatorBlackboard& m_pAnimatorBlackboard;
	std::map<int, AnimData> m_AnimData{};

	std::vector<BaseState*> m_pStates;

	SpriteComponent* m_pSpriteComp = nullptr;
};
