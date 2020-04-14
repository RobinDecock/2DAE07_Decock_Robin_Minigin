#pragma once
typedef unsigned char UINT8;
typedef unsigned char Uint8;
enum class ControllerButton
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	Up,
	Down,
	Left,
	Right
};

class InputManager final
{
public:
	static void Initialize();
	static void ProcessInput();
	static bool IsDown(UINT8 KeyCode);
	static bool IsUp(UINT8 KeyCode);
	static bool IsPressed(UINT8 KeyCode);
private:
	static Uint8* m_pCurrentState;
	static Uint8* m_pPreviousState;
	static bool m_DoOnce;
};
