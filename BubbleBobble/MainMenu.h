#pragma once
#include <SDL.h>

#include "Command.h"
#include "GameScene.h"
#include "GameSettings.h"
#include "InputHandler.h"
#include "TextComponent.h"

class MainMenu final: public GameScene
{
public:
	friend class MenuVertical;
	friend class Confirm;
	~MainMenu() override;
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void Draw() const override;
private:

	std::vector<std::shared_ptr<TextComponent>> items;
	GameSettings::Gamemode selectedOption = GameSettings::Single;

	SDL_Color selectedColor = { 255,0,0 };
	SDL_Color normalColor = { 255,255,255 };

	InputHandler inputHandler;
};

class MenuVertical:public AxisCommand
{
public:
	MenuVertical(MainMenu* mainMenu):m_pMainMenu(mainMenu){}
	void execute(float elapsedSec, float axisValue) override;
private:
	MainMenu* m_pMainMenu = nullptr;
	float delay = 0.2f;
	float timer = 0.0f;
};

class Confirm :public ButtonCommand
{
public:
	Confirm(MainMenu* mainMenu) :m_pMainMenu(mainMenu) {}
	void execute(float elapsedSec) override;
private:
	MainMenu* m_pMainMenu = nullptr;
};