#include "MiniginPCH.h"
#include "SoundManager.h"
#include <SDL_mixer.h>


	Mix_Music* SoundManager::m_pMusic = nullptr;
	SoundManager::State SoundManager::m_State = SoundManager::State::ERR;

void SoundManager::Initialize()
{
	if (SDL_Init(SDL_INIT_AUDIO) != -1)
	{
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			throw std::exception("[ERROR]: Failed to open SDL_Mixer");
		}
		else
		{
			m_State = State::WAITING;
		}
	}
	else
	{
		throw std::exception("[ERROR]: Failed to initialize subSystem of SDL_Mixer");
	}
}

void SoundManager::PlayMusic(std::string path, int loops)
{
	if (m_State != State::ERR)
	{
		if (Mix_PlayingMusic() == 0)
		{
			SoundManager::StopMusic();
		}

		Mix_Music* pMusic = Mix_LoadMUS(path.c_str());

		if (pMusic == nullptr)
		{
			std::string str = "[ERROR] Path (" + path + ") is an invalid MusicPath";
			throw std::exception(str.c_str());
		}
		else
		{
			//Play music
			Mix_PlayMusic(pMusic, loops);
			m_State = State::PLAYING;

		}
	}
}


void SoundManager::PauseMusic()
{
	if (m_State != State::ERR)
	{
		if (Mix_PlayingMusic() == 1)
		{
			if (Mix_PausedMusic() == 1)
			{
				Mix_ResumeMusic();
				m_State = State::PLAYING;
			}
			else
			{
				Mix_PauseMusic();
				m_State = State::PAUSED;
			}
		}
	}
}

void SoundManager::StopMusic()
{
	if (m_State != State::ERR)
	{
		Mix_HaltMusic();
		m_State = State::STOPPED;
	}
}

void SoundManager::PlayFX(std::string path)
{
	if (m_State != State::ERR)
	{
		// TODO: Alter this to work for mp3 as well
		Mix_Chunk* fx = Mix_LoadWAV(path.c_str());

		if (fx == NULL)
		{
			std::string str = "[ERROR] Path (" + path + ") is an invalid SoundPath";
			throw std::exception(str.c_str());
		}
		else
		{
			Mix_PlayChannel(-1, fx, 0);
		}
	}
}

SoundManager::~SoundManager()
{
}