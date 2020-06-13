#pragma once
class Project;

struct SDL_Window;
struct int2;


	class Minigin
	{
		//TODO MAKE PRIVATE
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();

		void Cleanup();
		void Run();
		//TODO MAKE PRIVATE
		Project* m_pProject = nullptr;
		static int2 m_WindSize;


	private:

		float m_elapsedSec = 0;
	};
