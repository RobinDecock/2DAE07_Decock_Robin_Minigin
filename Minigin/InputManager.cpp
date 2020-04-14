#include "MiniginPCH.h"
#include "InputManager.h"



Uint8* InputManager::m_pCurrentState = nullptr;
Uint8* InputManager::m_pPreviousState = nullptr;
bool InputManager::m_DoOnce = false;

void InputManager::Initialize()
{
	m_pPreviousState = new Uint8[SDL_NUM_SCANCODES];
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_pPreviousState[i] = 0;
	}
	m_pCurrentState = new Uint8[SDL_NUM_SCANCODES];
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		m_pCurrentState[i] = 0;
	}
	m_DoOnce = true;
}

void InputManager::ProcessInput()
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		int scanCode = Event.key.keysym.scancode;
		if (scanCode < SDL_NUM_SCANCODES)
		{
			m_pPreviousState[scanCode] = m_pCurrentState[scanCode];
			m_pCurrentState[scanCode] = Event.key.state;
		}
	}
}

bool InputManager::IsDown(UINT8 KeyCode)
{
	return m_pCurrentState[KeyCode];
}

bool InputManager::IsUp(UINT8 KeyCode)
{
	return !m_pCurrentState[KeyCode];
}

bool InputManager::IsPressed(UINT8 KeyCode)
{
	return (m_pCurrentState[KeyCode] && (!m_pPreviousState[KeyCode]));
}
