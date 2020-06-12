#include "MiniginPCH.h"
#include "SoundManager.h"
#include <SDL_mixer.h>

Mix_Music* SoundManager::m_pMusic  =nullptr;

void SoundManager::Update()
{
	if (m_pMusic!=nullptr&&!Mix_PlayingMusic())
	{
		Mix_PlayMusic(m_pMusic,1);
	}
}


void SoundManager::PlayMusic(std::string path)
{
	if(m_pMusic!=nullptr)
	{
		//delete m_pMusic;
	}
	m_pMusic = Mix_LoadMUS(path.c_str());
	if(m_pMusic==nullptr)
	{
		std::cout << "Error:" << Mix_GetError() << std::endl;
	}
	
}
void SoundManager::PlaySound(std::string path)
{
	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
	UNREF(sound);
}

void SoundManager::Cleanup()
{
	//bgm = nullptr;
	
}


SoundManager::~SoundManager()
{
}
