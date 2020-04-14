#include "ProjectPCH.h"
#include "BubbleBobble.h"

#include "ResourceManager.h"
#include "Scene1.h"
#include "SceneManager.h"

void BubbleBobble::Initialize()
{
	sceneManager= new SceneManager();
	ResourceManager::GetInstance().Init("../BubbleBobble/Resources/");
	sceneManager->AddScene(new Scene1());
}

void BubbleBobble::Update(float elapsedSec)
{
	sceneManager->Update(elapsedSec);
}

void BubbleBobble::Draw()
{
	sceneManager->Draw();
}

void BubbleBobble::CleanUp()
{
	delete sceneManager;
	sceneManager = nullptr;
}

BubbleBobble::~BubbleBobble()
{
}
