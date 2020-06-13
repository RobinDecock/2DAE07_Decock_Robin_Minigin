#include "MiniginPCH.h"
#include "Settings.h"


	SDL_Window* Settings::m_pWindow = nullptr;
	int2 Settings::m_WindowSize = int2(0, 0);

	SDL_Window* Settings::GetWindow()
	{
		return m_pWindow;
	}

	int2 Settings::GetWindowSize()
	{
		return m_WindowSize;
	}

	void Settings::SetWindowSize(int2 windSize)
	{
		m_WindowSize = windSize;
	}

	void Settings::SetWindow(SDL_Window* window)
	{
		m_pWindow = window;
	}
