#pragma once
#include <map>
#include "InputManager.h"


	class AxisCommand;
	class ButtonCommand;

	struct AxisInput
	{
		AxisInput(int posKey, int negKey, bool gamePad = false, float speedChange = 0.1f, float treshold = 0.1f, Logic lg = Logic::BIGGER) :
			PositiveKey(posKey), negativeKey(negKey), isGamePad(gamePad), logic(lg), treshholdValue(treshold), currValue(0), speedChangeAxis(speedChange) {}

		AxisInput(JoyStick posKey, float treshold = 0.1f, Logic lg = Logic::BIGGER) :
			PositiveKey(int(posKey)), negativeKey(-1), isGamePad(true), logic(lg), treshholdValue(treshold), currValue(0) {}

		void SetAxisChangeSpeed(float f) { speedChangeAxis = f; }
		int PositiveKey;
		int negativeKey;

		float treshholdValue;
		float currValue;

		float speedChangeAxis = 0.1f;

		Logic logic;

		bool isGamePad;
	};


	struct ButtonInput
	{
		bool operator==(const ButtonInput& other)
		{
			return buttonKey == other.buttonKey && buttonType == other.buttonType;
		}

		ButtonInput(int key, bool Gamepad = false, ButtonType type = ButtonType::Pressed) :buttonKey(key), buttonType(type), isGamePad(Gamepad) {}

		int buttonKey;
		ButtonType buttonType;

		bool isGamePad;
	};


	class InputHandler
	{
	public:
		void AddInputButton(::ButtonInput input, ::ButtonCommand& command);
		void AddInputAxis(::AxisInput input, ::AxisCommand& command);
		void HandleInput(float elapsedSec);
		void SetPlayerId(int pId) { playerId = pId; }
		~InputHandler();
	private:
		int playerId = 0;
		std::vector<std::pair<ButtonInput, ButtonCommand&>> buttonVector{};
		std::vector<std::pair<AxisInput, AxisCommand&>> axisVector{};

	};

	enum class KeyAction
	{
		K_Key1, C_Key1, K_Key2, C_Key2
	};

	enum class AxisAction
	{
		K_StickH,
		K_StickV,
		C_StickH,
		C_StickV
	};
	//KEYMAP
	static std::map<int, std::map<KeyAction, ButtonInput>>S_ButtonMap
	{
		{0,
		{
			{KeyAction::K_Key1,ButtonInput(KEY_UP)},
			{KeyAction::C_Key1,ButtonInput(XINPUT_GAMEPAD_A,true)},
			{KeyAction::K_Key2,ButtonInput(KEY_KEYPAD_0)},
			{KeyAction::C_Key2,ButtonInput(XINPUT_GAMEPAD_X,true)}
		}
		},
		{1,
		{
			{KeyAction::K_Key1,ButtonInput(KEY_W)},
			{KeyAction::C_Key1,ButtonInput(XINPUT_GAMEPAD_A,true)},
			{KeyAction::K_Key2,ButtonInput(KEY_F)},
			{KeyAction::C_Key2,ButtonInput(XINPUT_GAMEPAD_X,true)}
		}
		}
	};

	//AXISMAP

	static std::map<int, std::map<AxisAction, AxisInput>>S_AxisMap
	{
		{0,
		{
			{AxisAction::K_StickH,AxisInput(KEY_RIGHT,KEY_LEFT,false,1.0f)},
			{AxisAction::C_StickH,AxisInput(JoyStick::LX,1.0f)},

			{AxisAction::K_StickV,AxisInput(KEY_UP,KEY_DOWN,false,1.0f)},
			{AxisAction::C_StickV,AxisInput(JoyStick::LY,1.0f)},
		}
		},
		{1,
		{
			{AxisAction::K_StickH,AxisInput(KEY_D,KEY_A,false,1.0f)},
			{AxisAction::C_StickH,AxisInput(JoyStick::LX,0.5f)},

			{AxisAction::K_StickV,AxisInput(KEY_W,KEY_S,false,1.0f)},
			{AxisAction::C_StickV,AxisInput(JoyStick::LY,0.5f)},
		}
		}
	};

