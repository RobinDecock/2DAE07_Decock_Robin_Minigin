#pragma once
#include "GeneralStructs.h"
struct SDL_Window;

class Settings
{
public:
	static void SetWindow(SDL_Window* window);
	static SDL_Window* GetWindow();
	static int2 GetWindowSize();
	static void SetWindowSize(int2 windSize);
private:
	static SDL_Window* m_pWindow;
	static int2 m_WindowSize;
};
