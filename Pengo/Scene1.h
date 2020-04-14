#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "TextObject.h"
#include "PlayField.h"

class Scene1 :public dae::Scene
{
public:
	Scene1();
	void Update(float elapsedSec) override;
	~Scene1();
private:

	std::wstring levelPath = L"Level1.txt";
	TextObject * m_pScoreText = nullptr;
	void ParseFile(std::string path);
	std::vector<GameObject*>m_pLives;
	PlayField* m_pPlayField = nullptr;
};

