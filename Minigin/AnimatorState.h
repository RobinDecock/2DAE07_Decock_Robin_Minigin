#pragma once

#include <vector>
#include <functional>
#include <string>
class AnimatorBlackboard;
class BaseState;
struct Req;

class ParentState;
class AnimatorState;


	class Connection
	{
	public:
		Connection(BaseState* act);

		Connection(BaseState* act, std::vector<Req> require);

		Connection(BaseState* act, Req require);
		bool hasRequirement = true;
		BaseState* AnimatorState;
		std::vector<Req> requirements;
	};

	class BaseState
	{
	public:
		virtual ~BaseState() {}
		void AddNextAnimatorState(::BaseState* AnimatorState);
		void AddNextAnimatorState(::BaseState* AnimatorState, std::vector<::Req> requirements);
		void AddNextAnimatorState(::BaseState* AnimatorState, ::Req requirement);
		std::vector<Connection> GetNextConnections() { return m_NextConnections; };
		AnimatorState* GetNextState(::BaseState* currentState, ::AnimatorBlackboard& pBlackboard);
		void SetParent(::ParentState* st) { m_pParent = st; }
		void EndState()
		{
			if (hasEndFunction)
			{
				endFunction();
			}
		}
		void SetEndFunction(std::function<void()> f) {
			endFunction = f; hasEndFunction
				= true;
		}
	protected:
		static AnimatorState* GetNState(::BaseState* currentState, ::AnimatorBlackboard& pBlackboard);
		::ParentState* m_pParent = nullptr;

		std::function<void()> endFunction;
		bool hasEndFunction = false;
		std::vector<Connection> m_NextConnections{};

	};


	class AnimatorState : public BaseState
	{
	public:
		friend class PlayerN;
		AnimatorState(std::string name);
		AnimatorState(unsigned int id, std::string name);
		~AnimatorState()override;

		void RootExecute(float elapsedSec);
		void LeaveState();

		//SET
		void SetSpeed(float speed);
		void SetLooping(bool b);
		void SetWaitUntilAnimDone(bool b) { m_WaitUntilAnimDone = b; }
		//******

		//GET
		float GetSpeed() const;
		unsigned int GetValue() const;
		std::string GetName() const;
		bool GetLooping()const;
		bool GetWaitUntilAnimDone() const { return m_WaitUntilAnimDone; }
		//*****




	protected:
		ParentState* parentState = nullptr;
		unsigned int m_EnumValue = 0;

		float m_Speed = 1.0f;
		bool m_isLooping = true;
		bool m_hasRun = false;
		bool m_WaitUntilAnimDone = false;

		float runTime = 0.f;
		std::string m_Name = "";

		virtual void Execute(float elapsedSec) {}
	};

	class ParentState final : public BaseState
	{
	public:
		~ParentState()override {}
		ParentState(AnimatorState* startState, std::string name) :m_pStartState(startState) { m_pStartState->SetParent(this); }
		AnimatorState* GetStartState()const
		{
			return m_pStartState;
		}
	private:

		AnimatorState* m_pStartState;
	};
