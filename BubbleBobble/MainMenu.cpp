#include "ProjectPCH.h"
#include "MainMenu.h"
#include "GameObject.h"
#include "GameSettings.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SingleScene.h"
#include "SceneManager.h"
#include "Settings.h"
#include "TextComponent.h"
#include "TextureComponent.h"
MainMenu::~MainMenu()
{
}






void MainMenu::Initialize()
{
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	int middleX = Settings::GetWindowSize().x / 2;
	int middleY = Settings::GetWindowSize().y / 2;

	GameObject* title = new GameObject();
	title->AddComponent(new TextureComponent("Title.png"));
	title->GetComponent<TextureComponent>()->SetPivot({ 0.5f,0.5f });
	title->GetComponent<TextureComponent>()->SetUseCam(false);
	title->SetScale({ 2.0f,2.0f });
	title->SetPosition({middleX,150.0f});
	Add(title);

	
	GameObject* single = new GameObject();
	auto textC = new TextComponent(font);
	textC->SetText("SinglePlayer");
	single->AddComponent(textC);
	single->SetPosition({ middleX,middleY +75.0f});
	Add(single);
	items.push_back(textC);

	
	GameObject* coop = new GameObject();
	textC = new TextComponent(font);
	textC->SetText("Coop");
	coop->AddComponent(textC);
	coop->SetPosition({ middleX,middleY+125.0f});
	Add(coop);
	items.push_back(textC);

	GameObject* versus = new GameObject();
	textC = new TextComponent(font);
	textC->SetText("Versus");
	versus->AddComponent(textC);
	versus->SetPosition({ middleX,middleY+175.0f });
	Add(versus);
	items.push_back(textC);

	items[int(GameMode::Single)]->SetColor(selectedColor);

	inputHandler.AddInputAxis(AxisInput(KEY_UP, KEY_DOWN,false,1.0f,0.0f), m_pMenuVertical);
	inputHandler.AddInputAxis(AxisInput(JoyStick::LY,1.0f,0.0f), m_pMenuVertical);
	inputHandler.AddInputButton(ButtonInput(XINPUT_GAMEPAD_A,true), m_pConfirm);
	inputHandler.AddInputButton(ButtonInput(KEY_SPACE),m_pConfirm);
}

void MainMenu::Update(float elapsedSec)
{
	inputHandler.HandleInput(elapsedSec);
}

void MenuVertical::execute(float elapsedSec, float axisValue)
{
	if (timer < delay)
	{
		timer += elapsedSec;
		return;
	}
	GameMode& selectedItem = GameSettings::m_Gamemode;
	std::vector<TextComponent*>& items = m_pMainMenu->items;
	const SDL_Color &selectedColor = m_pMainMenu->selectedColor;
	const SDL_Color& normalColor = m_pMainMenu->normalColor;

	int gameValue = (int)(selectedItem);
	
	if(axisValue > 0.2f&& gameValue >0)
	{
		items[gameValue]->SetColor(normalColor);
		selectedItem = GameMode(gameValue -1);
		items[gameValue]->SetColor(selectedColor);
		timer = 0.0f;
	}
	else if (axisValue < -0.2f && gameValue <2)
	{
		items[gameValue]->SetColor(normalColor);
		selectedItem = GameMode(gameValue + 1);
		items[gameValue]->SetColor(selectedColor);
		timer = 0.0f;
	}

}

void Confirm::execute(float elapsedSec)
{
	SceneManager::GetInstance()->AddScene(new SingleScene());
	SceneManager::GetInstance()->RemoveScene(m_pMainMenu);
}
