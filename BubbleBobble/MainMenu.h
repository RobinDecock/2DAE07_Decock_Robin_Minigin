#pragma once

#include "Command.h"
#include "GameScene.h"

#include "InputHandler.h"
class TextComponent;


class MainMenu;
class MenuVertical :public AxisCommand
{
public:
	MenuVertical(MainMenu* mainMenu) :m_pMainMenu(mainMenu) {}
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



class MainMenu final: public GameScene
{
public:
	friend class MenuVertical;
	friend class Confirm;
	~MainMenu() override;
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
private:

	std::vector<TextComponent*> items;

	SDL_Color selectedColor = { 255,0,0 ,255};
	SDL_Color normalColor = { 255,255,255 ,255};

	InputHandler inputHandler;


	//Commands
	MenuVertical m_pMenuVertical = MenuVertical(this);
	Confirm m_pConfirm = Confirm(this);
	
};

