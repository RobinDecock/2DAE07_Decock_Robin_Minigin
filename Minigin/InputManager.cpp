#include "MiniginPCH.h"
#include "InputManager.h"

#include "InputHandler.h"
	Uint8 InputManager::m_CurrKeyboardState[SDL_NUM_SCANCODES];
	Uint8 InputManager::m_PrevKeyboardState[SDL_NUM_SCANCODES];

	Uint32 InputManager::m_CurrMouseState;
	Uint32 InputManager::m_PrevMouseState;

	int2 InputManager::m_MousePos;
	std::vector<XINPUT_STATE> InputManager::m_pCurGamepadStates;
	std::vector<XINPUT_STATE> InputManager::m_pPrevGamepadStates;
	void InputManager::Initialize()
	{
		///--- Initialize the las frame array to 0
		memset(m_PrevKeyboardState, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
		///--- Copy the current status
		memcpy(m_CurrKeyboardState, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);

		m_pCurGamepadStates.resize(4);
		m_pPrevGamepadStates.resize(4);
	}

	void InputManager::Update()
	{
		memcpy(m_PrevKeyboardState, m_CurrKeyboardState, sizeof(Uint8) * SDL_NUM_SCANCODES);
		memcpy(m_CurrKeyboardState, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);

		m_CurrMouseState = SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);


		for (unsigned int i = 0; i < 4; i++)
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			if (XInputGetState(i, &state) == ERROR_SUCCESS)
			{
				m_pPrevGamepadStates[i] = m_pCurGamepadStates[i];
				m_pCurGamepadStates[i] = state;
			}
		}
	}
	bool InputManager::IsKeyboardKeyDown(int key)
	{
#if DEBUG
		CheckKeyboardKey((int)key);
#endif
		return m_CurrKeyboardState[key];
	}
	bool InputManager::IsKeyboardKeyUp(int key)
	{
#if DEBUG
		CheckKeyboardKey((int)key);
#endif
		return m_CurrKeyboardState[key];
	}
	bool InputManager::IsKeyboardKeyPressed(int key)
	{
#if DEBUG
		CheckKeyboardKey((int)key);
#endif
		return m_CurrKeyboardState[key] == 1 && m_PrevKeyboardState[key] == 0;
	}

	bool InputManager::IsGamePadKeyDown(int key, int playerId)
	{
		return (m_pCurGamepadStates[playerId].Gamepad.wButtons & key) != 0;
	}

	bool InputManager::IsGamePadKeyUp(int key, int playerId)
	{
		return (m_pCurGamepadStates[playerId].Gamepad.wButtons & key) == 0;
	}

	bool InputManager::IsGamePadKeyPressed(int key, int playerId)
	{
		return (m_pCurGamepadStates[playerId].Gamepad.wButtons & key) != 0 && (m_pPrevGamepadStates[playerId].Gamepad.wButtons & key) == 0;
	}

	float InputManager::GetGamePadJoyStick(int key, const int playerId)
	{
		JoyStick enumValue = JoyStick(key);

		float StickMax = 32767.0f;
		switch (enumValue)
		{
		case JoyStick::LX:
			return m_pCurGamepadStates[playerId].Gamepad.sThumbLX / StickMax;
		case JoyStick::LY:
			return m_pCurGamepadStates[playerId].Gamepad.sThumbLY / StickMax;
		case JoyStick::RX:
			return m_pCurGamepadStates[playerId].Gamepad.sThumbRX / StickMax;
		case JoyStick::RY:
			return m_pCurGamepadStates[playerId].Gamepad.sThumbRY / StickMax;
		}
		return 0.0f;
	}

	bool InputManager::CheckButton(const ButtonInput input, const int playerId)
	{

		if (input.isGamePad)
		{
			switch (input.buttonType)
			{
			case ButtonType::Pressed:
				return IsGamePadKeyPressed(input.buttonKey, playerId);
			case ButtonType::Down:
				return IsGamePadKeyDown(input.buttonKey, playerId);
			case ButtonType::Up:
				return IsGamePadKeyUp(input.buttonKey, playerId);
			default:;
			}
		}
		else
		{
			switch (input.buttonType)
			{
			case ButtonType::Pressed:
				return IsKeyboardKeyPressed(input.buttonKey);
			case ButtonType::Down:
				return IsKeyboardKeyDown(input.buttonKey);
			case ButtonType::Up:
				return IsKeyboardKeyUp(input.buttonKey);
			default:;
			}
		}
		return false;
	}
	bool InputManager::CheckAxis(AxisInput& input, const int playerId)
	{
		if (input.isGamePad)
		{
			if (input.negativeKey == -1)
			{
				input.currValue = GetGamePadJoyStick(input.PositiveKey, playerId);
			}
			else
			{
				if (IsGamePadKeyDown(input.PositiveKey, playerId))
				{
					input.currValue += input.speedChangeAxis;
					if (input.currValue > 1)
					{
						input.currValue = 1;
					}
				}
				else if (IsGamePadKeyDown(input.negativeKey, playerId))
				{
					input.currValue -= input.speedChangeAxis;
					if (input.currValue < -1)
					{
						input.currValue = -1;
					}
				}
				else
				{
					if (input.currValue != 0)
					{
						input.currValue += (input.currValue > 0 ? -1.0f : 1.0f) * input.speedChangeAxis;
						if (abs(input.currValue) < 0.05f)
						{
							input.currValue = 0.0f;
						}
					}
				}
			}
		}
		else
		{
			if (IsKeyboardKeyDown(input.PositiveKey))
			{
				input.currValue += input.speedChangeAxis;
				if (input.currValue > 1)
				{
					input.currValue = 1;
				}
			}
			else if (IsKeyboardKeyDown(input.negativeKey))
			{
				input.currValue -= input.speedChangeAxis;
				if (input.currValue < -1)
				{
					input.currValue = -1;
				}
			}
			else
			{
				if (input.currValue != 0)
				{
					input.currValue += (input.currValue > 0 ? -1.0f : 1.0f) * input.speedChangeAxis;
					if (abs(input.currValue) < 0.05f)
					{
						input.currValue = 0.0f;
					}
				}
			}
		}



		switch (input.logic)
		{
		case Logic::BIGGER:
			return abs(input.currValue) >= input.treshholdValue;
		case Logic::SMALLER:
			return abs(input.currValue) <= input.treshholdValue;
		case Logic::EQUAL:
			return abs(input.currValue) == input.treshholdValue;
		}

		//TODO FIX THIS MESS

		return false;
	}


	bool InputManager::Shift()
	{
		return IsKeyboardKeyPressed(KeyboardKey::KEY_LEFT_SHIFT) || IsKeyboardKeyPressed(KeyboardKey::KEY_RIGHT_SHIFT);
	}
	bool InputManager::Ctrl()
	{
		return IsKeyboardKeyPressed(KeyboardKey::KEY_LEFT_CTRL) || IsKeyboardKeyPressed(KeyboardKey::KEY_RIGHT_CTRL);
	}
	bool InputManager::Alt()
	{
		return IsKeyboardKeyPressed(KeyboardKey::KEY_LEFT_ALT) || IsKeyboardKeyPressed(KeyboardKey::KEY_RIGHT_ALT);
	}
	bool InputManager::IsMouseDown(MouseButton button)
	{
		if (button >= MouseButton::MOUSE_MAX)
			return false;

		return m_CurrMouseState & int(button);
	}
	bool InputManager::IsMouseUp(MouseButton button)
	{
		if (button >= MouseButton::MOUSE_MAX)
			return false;

		return !(m_CurrMouseState & int(button));
	}
	bool InputManager::IsMousePressed(MouseButton button)
	{
		if (button >= MouseButton::MOUSE_MAX)
			return false;

		return m_CurrMouseState & int(button) &&
			!(m_PrevMouseState & int(button));
	}
	int InputManager::GetMouseX()
	{
		return m_MousePos.x;
	}
	int InputManager::GetMouseY()
	{
		return m_MousePos.y;
	}

	int2 InputManager::GetMousePos()
	{
		return m_MousePos;
	}
#if DEBUG
	void InputManager::CheckKeyboardKey(int keyCode)
	{
		if (keyCode > SDL_NUM_SCANCODES)
		{
			std::cout << "[ERROR]: key " + std::to_string(keyCode) + "is not a scancode" << std::endl;
			__debugbreak();
		}
	}
#endif 


