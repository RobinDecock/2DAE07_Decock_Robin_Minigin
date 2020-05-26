#pragma once
#include <SDL_mixer.h>

//#include <SDL_mixer.h>


class SoundManager
{
public:
	SoundManager();
	static void Update();
	static void PlayMusic(std::string path);
	static void PlaySound(std::string path);

	static void Cleanup();
	~SoundManager();
private:
	static Mix_Music* m_pMusic ;
};
