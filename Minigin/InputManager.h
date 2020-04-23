#include "GeneralStructs.h"
#include "InputDefinitions.h"
#include "SDL.h"

class InputManager
{
public:
	InputManager();
	
	//Singleton Get function
	static InputManager* GetInstance();

	void Initialize();
	//General update of all states
	void Update();

	//Get certain key states
	bool IsKeyDown(int key);
	bool IsKeyUp(int key);
	bool IsKeyPressed(int key);

	//Quick shortcuts
	bool Shift();
	bool Ctrl();
	bool Alt();
	
#if DEBUG
	//Debug check if key exists
	void CheckKey(int keyCode);
#endif

	//Get Mousebutton State
	bool IsMouseDown(MouseButton button);
	bool IsMouseUp(MouseButton button);
	bool IsMousePressed(MouseButton button);

	//Get Mouse positions
	int GetMouseX();
	int GetMouseY();
	int2 GetMousePos();
private:
	
	static InputManager* m_Instance;
	Uint8 m_CurrKeyboardState[SDL_NUM_SCANCODES];
	Uint8 m_PrevKeyboardState[SDL_NUM_SCANCODES];

	Uint32 m_CurrMouseState;
	Uint32 m_PrevMouseState;
	
	int2 m_MousePos;
};