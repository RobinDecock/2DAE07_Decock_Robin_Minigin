#pragma once
#include <map>
#include "Command.h"
#include "InputManager.h"

struct AxisInput
{
	AxisInput(int posKey,int negKey,bool gamePad = false, float treshold = 0.1f, Logic lg = Logic::BIGGER) :PositiveKey(posKey),negativeKey(negKey),isGamePad(gamePad),logic(lg),treshholdValue(treshold),currValue(0){}

	AxisInput(int posKey, float treshold = 0.1f, Logic lg = Logic::BIGGER) :PositiveKey(posKey), negativeKey(-1), isGamePad(true), logic(lg), treshholdValue(treshold), currValue(0) {}

	float PositiveKey;
	float negativeKey;
	
	float treshholdValue;
	float currValue;
	Logic logic;

	bool isGamePad;
};


struct ButtonInput
{
	bool operator==(const ButtonInput& other)
	{
		return buttonKey == other.buttonKey && buttonType == other.buttonType;
	}

	ButtonInput(int key, bool Gamepad = false,ButtonType type = ButtonType::Pressed):buttonKey(key),buttonType(type),isGamePad(Gamepad){}
	
	int buttonKey;
	ButtonType buttonType;

	bool isGamePad;
};


class InputHandler
{
public:
	
	void AddInputButton(ButtonInput input, ButtonCommand* command);
	void AddInputAxis(AxisInput input, AxisCommand* command);
	void HandleInput(float elapsedSec);
	~InputHandler();
private:
	int playerId;
	std::vector<std::pair<ButtonInput, ButtonCommand*>> buttonVector;
	std::vector<std::pair<AxisInput, AxisCommand*>> axisVector;

};


//Key : PlayerId
//Value::map
//
//Key: ActionKey
//Key : ButtonInput

enum KeyAction
{
	K_Key1,C_Key1,K_Key2,C_Key2
};

enum AxisAction
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
		{K_Key1,ButtonInput(KEY_UP)},
		{C_Key1,ButtonInput(XINPUT_GAMEPAD_A,true)},
		{K_Key2,ButtonInput(KEY_KEYPAD_0)},
		{C_Key2,ButtonInput(XINPUT_GAMEPAD_X,true)}
	}
	},
	{1,
	{
		{K_Key1,ButtonInput(KEY_W)},
		{C_Key1,ButtonInput(XINPUT_GAMEPAD_A,true)},
		{K_Key2,ButtonInput(KEY_F)},
		{C_Key2,ButtonInput(XINPUT_GAMEPAD_X,true)}
	}
	}
};

//AXISMAP

static std::map<int, std::map<AxisAction, AxisInput>>S_AxisMap
{
	{0,
	{
		{K_StickH,AxisInput(KEY_RIGHT,KEY_LEFT)},
		{C_StickH,AxisInput((int)JoyStick::LX)},
		
		{K_StickV,AxisInput(KEY_UP,KEY_DOWN)},
		{C_StickV,AxisInput((int)JoyStick::LY)},
	}
	},
	{1,
	{
		{K_StickH,AxisInput(KEY_D,KEY_A)},
		{C_StickH,AxisInput((int)JoyStick::LX)},

		{K_StickV,AxisInput(KEY_W,KEY_S)},
		{C_StickV,AxisInput((int)JoyStick::LY)},
	}
	}
};