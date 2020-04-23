#include "MiniginPCH.h"
#include "InputManager.h"

InputManager* InputManager::m_Instance = nullptr;




InputManager::InputManager() :
	m_MousePos(0,0)
{

}


InputManager* InputManager::GetInstance()
{
	if (!m_Instance)
		m_Instance = new InputManager();

	return m_Instance;
}

void InputManager::Initialize()
{
	///--- Initialize the las frame array to 0
	memset(m_PrevKeyboardState, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	///--- Copy the current status
	memcpy(m_CurrKeyboardState, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

void InputManager::Update()
{

	memcpy(m_PrevKeyboardState, m_CurrKeyboardState, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(m_CurrKeyboardState, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);

	m_CurrMouseState = SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
}
bool InputManager::IsKeyDown(int key)
{
#if DEBUG
	CheckKey((int)key);
#endif
	return m_CurrKeyboardState[key];
}
bool InputManager::IsKeyUp(int key)
{
#if DEBUG
	CheckKey((int)key);
#endif
	return m_CurrKeyboardState[key];
}
bool InputManager::IsKeyPressed(int key)
{
#if DEBUG
	CheckKey((int)key);
#endif
	
	return m_CurrKeyboardState[key]&&!m_PrevKeyboardState[key];
}
bool InputManager::Shift()
{
	return IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT);
}
bool InputManager::Ctrl()
{
	return IsKeyPressed(KEY_LEFT_CTRL) || IsKeyPressed(KEY_RIGHT_CTRL);
}
bool InputManager::Alt()
{
	return IsKeyPressed(KEY_LEFT_ALT) || IsKeyPressed(KEY_RIGHT_ALT);
}
bool InputManager::IsMouseDown(MouseButton button)
{
	if (button >= MOUSE_MAX)
		return false;

	return m_CurrMouseState & button;
}
bool InputManager::IsMouseUp(MouseButton button)
{
	if (button >= MOUSE_MAX)
		return false;

	return !m_CurrMouseState & button;
}
bool InputManager::IsMousePressed(MouseButton button)
{
	if (button >= MOUSE_MAX)
		return false;

	return m_CurrMouseState& button &&
		   !m_PrevMouseState&button;
}
int InputManager::GetMouseX()
{
	return this->m_MousePos.x;
}
int InputManager::GetMouseY()
{
	return this->m_MousePos.y;
}

int2 InputManager::GetMousePos()
{
	return this->m_MousePos;
}
#if DEBUG
void InputManager::CheckKey(int keyCode)
{
	if (keyCode > SDL_NUM_SCANCODES)
	{
		std::cout << "[ERROR]: key " + std::to_string(keyCode) + "is not a scancode" << std::endl;
		__debugbreak();
	}
}
#endif 