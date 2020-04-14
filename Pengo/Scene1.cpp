#include "MiniginPCH.h"
#pragma once

#include "Scene1.h"

#include <fstream>
#include "Boundary.h"
//#include "Pengo.h"
#include "GameObject.h"
#include "Pengo.h"
#include "IceBlock.h"
#include <ctime>
#include "Snobee.h"
#include "TextObject.h"
#include "ResourceManager.h"
#include "Block.h"

Scene1::Scene1() :Scene("Scene1")
{
	m_pPlayField = new PlayField();
	m_pPlayField->SetPosition(float2(0, 0));
	Add(m_pPlayField);
	m_pPlayField->ParseLevelFile("../Data/Level1.txt");




	////BOUNDARIES



	//LIVES
	for(int i = 0;i<3;i++)
	{
		auto life = new GameObject(); 
		auto sprite = new SpriteComponent("MainSpriteSheet.png");

		life->AddComponent(sprite);
		sprite->SetSpriteData(SpriteData(0, 0, 16, 16, 1, 1));
		Add(life);
		m_pLives.push_back(life);
		life->SetPosition({ 20.0f + 16.0f * i, 20.0f });
	}

	//SCORE
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	m_pScoreText = new TextObject(font);
	m_pScoreText->SetPosition({ 100, 10 });
	m_pScoreText->SetText("LOL THIS WOKS");
	Add(m_pScoreText);

	//Background Music
	//FMOD_RESULT fmodResult;
	//auto pFmodSystem = SoundManager::GetInstance().GetSystem();
	//FMOD::Sound *pSound;
	//fmodResult = pFmodSystem->createStream("./Resources/Sounds/Music_Aquaduct.mp3", FMOD_DEFAULT, 0, &pSound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D.
	//SoundManager::GetInstance().ErrorCheck(fmodResult);

	//pSound->setMode(FMOD_LOOP_NORMAL);
	//FMOD::Channel *ch = SoundManager::GetInstance().GetChannel();
	//SoundManager::GetInstance().GetChannelGroup()->setVolume(1.0f);
	//SoundManager::GetInstance().GetChannelGroup()->stop();	
	//fmodResult = pFmodSystem->playSound(pSound, SoundManager::GetInstance().GetChannelGroup(), false, &ch);
	//SoundManager::GetInstance().ErrorCheck(fmodResult);

}

void Scene1::Update(float elapsedSec)
{
	Scene::Update(elapsedSec);
	m_pScoreText->SetText("Score: "+std::to_string(m_Score));
	switch(m_Lives)
	{
	case 0:
		{
			m_pLives[0]->SetActive(false);
			m_pLives[1]->SetActive(false);
			m_pLives[2]->SetActive(false);
		}
		break;
	case 1:
		{
			m_pLives[0]->SetActive(true);
			m_pLives[1]->SetActive(false);
			m_pLives[2]->SetActive(false);
		}
		break;
	case 2:
		{
			m_pLives[0]->SetActive(true);
			m_pLives[1]->SetActive(true);
			m_pLives[2]->SetActive(false);
		}
		break;
	case 3:
		{
			m_pLives[0]->SetActive(true);
			m_pLives[1]->SetActive(true);
			m_pLives[2]->SetActive(true);
		}
		break;
	}

	//if(SnobeeVector.empty())
	//{
	//	SceneManager::GetInstance().Reset(this);
	//}
	//for(size_t i = 0;i<SnobeeVector.size();i++)
	//{
	//	if(SnobeeVector[i]->GetScene()==nullptr)
	//	{
	//		SnobeeVector.erase(SnobeeVector.begin() + i);
	//	}
	//}
}

Scene1::~Scene1()
{
}

void Scene1::ParseFile(std::string path)
{

}
