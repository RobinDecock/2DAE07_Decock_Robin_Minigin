#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "Settings.h"
#include "Project.h"

int2 Minigin::m_WindSize = int2(256*2, 224*2);;

void Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}


	Settings::SetWindowSize(m_WindSize);
	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_WindSize.x,
		m_WindSize.y,
		SDL_WINDOW_OPENGL
	);
	Settings::SetWindow(window);
	if (window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::Init(window);

}

void Minigin::Cleanup()
{
	m_pProject->CleanUp();
	Renderer::Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void Minigin::Run()
{
	Initialize();

	m_pProject->Initialize();
	{

		SDL_Event evt;
		bool doContinue = true;
		bool doOnce = true;
		while (doContinue)
		{
			while (SDL_PollEvent(&evt))
			{
				switch (evt.type)
				{
				case SDL_QUIT:  doContinue = false;   break;
				}
			}


			if(doOnce)
			{
				InputManager::GetInstance()->Initialize();
				doOnce = false;
			}

			
			auto loopStart = std::chrono::high_resolution_clock::now();
			InputManager::GetInstance()->Update();

			Renderer::Clear();



			
			m_pProject->Update(m_elapsedSec);
			m_pProject->Draw();

			
			Renderer::Render();

			//std::this_thread::sleep_until(loopStart+ std::chrono::milliseconds(5));
			auto loopEnd = std::chrono::high_resolution_clock::now();
			m_elapsedSec = std::chrono::duration<float>(loopEnd - loopStart).count();
		}
	}

	Cleanup();
}
