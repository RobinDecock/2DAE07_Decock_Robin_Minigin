#include "ProjectPCH.h"
#include "BubbleBobble.h"


#include "MainMenu.h"
#include "ResourceManager.h"
#include "SingleScene.h"
#include "SceneManager.h"

void BubbleBobble::Initialize()
{
	
	sceneManager= new SceneManager();
	ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");
	sceneManager->AddScene(new MainMenu());
}

void BubbleBobble::Update(float elapsedSec)
{
	sceneManager->Update(elapsedSec);
}

void BubbleBobble::Draw()
{
	sceneManager->Draw();
}

BubbleBobble::~BubbleBobble()
{
	delete sceneManager;
	sceneManager = nullptr;
}
