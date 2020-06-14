#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"


#include "Settings.h"
#include "Project.h"
#include "SoundManager.h"


	int2 Minigin::m_WindSize = int2(640,480);;//256 *	 2, 224 * 2	 512,448

	void Minigin::Initialize()
	{
		ResourceManager::SetInstance(new ResourceManager());
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
		SoundManager::Initialize();
		srand(static_cast<unsigned int>(time(nullptr)));
	}


	void Minigin::Run()
	{
		Initialize();
		m_pProject->Initialize();
		{

			SDL_Event evt;
			bool doContinue = true;
			InputManager::Initialize();
			while (doContinue)
			{

				auto loopStart = std::chrono::high_resolution_clock::now();
				InputManager::Update();
				Renderer::Clear();

				m_pProject->Draw();
				m_pProject->Update(m_elapsedSec);

				Renderer::Render();

				//std::this_thread::sleep_until(loopStart+ std::chrono::milliseconds(5));
				auto loopEnd = std::chrono::high_resolution_clock::now();
				m_elapsedSec = std::chrono::duration<float>(loopEnd - loopStart).count();

				while (SDL_PollEvent(&evt))
				{
					switch (evt.type)
					{
					case SDL_QUIT:  doContinue = false;   break;
					}
				}
			}
		}

		Cleanup();
	}

	void Minigin::Cleanup()
	{
		SafeDelete(m_pProject);

		ResourceManager::GetInstance().DestroyInstance();

		Renderer::Destroy();

		SDL_DestroyWindow(window);
		SDL_Quit();
	}
