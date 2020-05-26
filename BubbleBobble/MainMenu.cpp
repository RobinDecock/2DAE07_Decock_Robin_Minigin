#include "ProjectPCH.h"
#include "MainMenu.h"
#include "GameObject.h"
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
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	float middleX = Settings::GetWindowSize().x / 2.0f;
	float middleY = Settings::GetWindowSize().y / 2.0f;

	GameObject* title = new GameObject();
	title->AddComponent(NEW(TextureComponent)("Title.png"));
	title->GetComponent<TextureComponent>()->SetPivot({ 0.5f,0.5f });
	title->GetComponent<TextureComponent>()->SetUseCam(false);
	title->SetScale({ 2.0f,2.0f });
	title->SetPosition({middleX,150.0f});
	Add(title);

	
	GameObject* single = new GameObject();
	auto textC = NEW(TextComponent)(font);
	textC->SetText("SinglePlayer");
	single->AddComponent(textC);
	single->SetPosition({ middleX,middleY +75.0f});
	Add(single);
	items.push_back(textC);

	
	GameObject* coop = new GameObject();
	textC = NEW(TextComponent)(font);
	textC->SetText("Coop");
	coop->AddComponent(textC);
	coop->SetPosition({ middleX,middleY+125.0f});
	Add(coop);
	items.push_back(textC);

	GameObject* versus = new GameObject();
	textC = NEW(TextComponent)(font);
	textC->SetText("Versus");
	versus->AddComponent(textC);
	versus->SetPosition({ middleX,middleY+175.0f });
	Add(versus);
	items.push_back(textC);

	items[selectedOption]->SetColor(selectedColor);

	inputHandler.AddInputAxis(AxisInput(KEY_UP, KEY_DOWN,false,0.1f),new MenuVertical(this));
	inputHandler.AddInputAxis(AxisInput(JoyStick::LY,0.1f), new MenuVertical(this));
	inputHandler.AddInputButton(ButtonInput(XINPUT_GAMEPAD_A,true), new Confirm(this));
	inputHandler.AddInputButton(ButtonInput(KEY_SPACE), new Confirm(this));
}

void MainMenu::Update(float elapsedSec)
{
	inputHandler.HandleInput(elapsedSec);
	
}

void MainMenu::Draw() const
{
}

void MenuVertical::execute(float elapsedSec, float axisValue)
{


	if (timer < delay)
	{
		timer += elapsedSec;
		return;
	}

	
	GameSettings::Gamemode& selectedItem = m_pMainMenu->selectedOption;
	std::vector<std::shared_ptr<TextComponent>>& items = m_pMainMenu->items;
	const SDL_Color &selectedColor = m_pMainMenu->selectedColor;
	const SDL_Color& normalColor = m_pMainMenu->normalColor;
	
	if(axisValue > 0.2f&& selectedItem>0)
	{
		items[selectedItem]->SetColor(normalColor);
		selectedItem = GameSettings::Gamemode(selectedItem-1);
		items[selectedItem]->SetColor(selectedColor);
		timer = 0.0f;
	}
	else if (axisValue < -0.2f && selectedItem <2)
	{
		items[selectedItem]->SetColor(normalColor);
		selectedItem = GameSettings::Gamemode(selectedItem + 1);
		items[selectedItem]->SetColor(selectedColor);
		timer = 0.0f;
	}

}

void Confirm::execute(float elapsedSec)
{

	switch(m_pMainMenu->selectedOption)
	{
	case GameSettings::Single: 
		SceneManager::GetInstance()->AddScene(new SingleScene());
		break;
	case GameSettings::Coop:
		
		//ADD Coop Scene
		break;
	case GameSettings::Versus:
		
		//Add Versus Scene
		break;
	default: ;
	}
	SceneManager::GetInstance()->RemoveScene(m_pMainMenu);
}
