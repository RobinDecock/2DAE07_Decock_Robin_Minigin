#pragma once
#include "GameObject.h"
#include "Observer.h"
class Bub;

enum Event
{
	Player_Damaged,
	New_Score



};

class PlayerHud:public GameObject,public Observer
{
public:
	PlayerHud(Bub* ref);
	void Initialize() override;
	void onNotify(int event,GameObject* obj = nullptr) override;
private:
	std::vector<GameObject*> lives;
	GameObject* scoreObject = nullptr;
};

