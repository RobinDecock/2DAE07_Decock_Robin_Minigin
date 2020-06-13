#include "MiniginPCH.h"
#include "InputHandler.h"

#include "InputManager.h"
#include "Command.h"
#include "Input.h"

	void InputHandler::AddInputButton(::ButtonInput input, ::ButtonCommand& command)
	{
		buttonVector.push_back(std::pair<ButtonInput, ButtonCommand&>(input, command));
	}

	void InputHandler::AddInputAxis(::AxisInput input, ::AxisCommand& command)
	{
		axisVector.push_back(std::pair<AxisInput, AxisCommand&>(input, command));
	}

	void InputHandler::HandleInput(float elapsedSec)
	{
		for (const auto element : buttonVector)
		{
			bool done = InputManager::CheckButton(element.first, playerId);
			if (done)
			{
				element.second.execute(elapsedSec);
			}
		}

		for (auto& element : axisVector)
		{
			if (InputManager::CheckAxis(element.first, playerId))
			{
				element.second.execute(elapsedSec, element.first.currValue);
			}
		}
	}

	InputHandler::~InputHandler()
	{
		S_ButtonMap.clear();
		S_AxisMap.clear();
	}
