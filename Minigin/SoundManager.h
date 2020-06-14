#pragma once
#include <SDL_mixer.h>

//#include <SDL_mixer.h>



	class SoundManager
	{
	public:
		enum class State
		{
			ERR=0,
			WAITING,
			PAUSED,
			STOPPED,
			PLAYING
		};
		
		SoundManager() = default;
		static void Initialize();

		//Emplaces currently playing music
		static void PlayMusic(std::string path,int loops = 1);

		//Toggles Paused
		static void PauseMusic();
		
		static void StopMusic();
		
		
		static void PlayFX(std::string path);
		~SoundManager();
	private:
		static Mix_Music* m_pMusic;
		static State m_State;
	};
