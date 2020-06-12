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

int2 Minigin::m_WindSize = int2(256*2, 224*2);;

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

	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
	{
		std::cout << "Error: " << Mix_GetError() << std::endl;
	}
	Renderer::Init(window);
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
			SoundManager::Update();
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
	
	SoundManager::Cleanup();
	Renderer::Destroy();

	SDL_DestroyWindow(window);
	SDL_Quit();
}