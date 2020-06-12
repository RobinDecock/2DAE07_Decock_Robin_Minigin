#pragma once
#include "GeneralStructs.h"
#include "InputDefinitions.h"
#include <Xinput.h>
struct AxisInput;
struct ButtonInput;

enum class JoyStick
{
	LX=0,LY=1,RX=2,RY=3
};

enum class ButtonType
{
	Pressed, Down, Up
};
class InputManager
{
public:
	static void Initialize();
	//General update of all states
	static void Update();
	static void CleanUp();
	//Get certain key states
	static bool IsKeyboardKeyDown(int key);
	static bool IsKeyboardKeyUp(int key);
	static bool IsKeyboardKeyPressed(int key);

	static bool IsGamePadKeyDown(int key,int playerId);
	static bool IsGamePadKeyUp(int key,int playerId);
	static bool IsGamePadKeyPressed(int key,int playerId);
	static float GetGamePadJoyStick(int key,const int playerId);
	
	static bool CheckButton(const ButtonInput input,const int playerId);
	static bool CheckAxis(AxisInput& input,const int playerId);
	//Quick shortcuts
	static bool Shift();
	static bool Ctrl();
	static bool Alt();
	
#if DEBUG
	//Debug check if key exists
	static void CheckKeyboardKey(int keyCode);
#endif

	//Get Mousebutton State
	static bool IsMouseDown(MouseButton button);
	static bool IsMouseUp(MouseButton button);
	static bool IsMousePressed(MouseButton button);

	//Get Mouse positions
	static int GetMouseX();
	static int GetMouseY();
	static int2 GetMousePos();
private:

	static Uint8 m_CurrKeyboardState[SDL_NUM_SCANCODES];
	static Uint8 m_PrevKeyboardState[SDL_NUM_SCANCODES];

	static Uint32 m_CurrMouseState;
	static Uint32 m_PrevMouseState;
	
	static int2 m_MousePos;

	static std::vector<XINPUT_STATE> m_pCurGamepadStates;
	static std::vector<XINPUT_STATE> m_pPrevGamepadStates;
};