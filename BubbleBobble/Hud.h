#pragma once
#include <GameObject.h>

class Font;

class Hud :
	public GameObject
{
public:
	~Hud() override;
	void AddScore(int score) { m_Score += score; }
private:
	void Initialize() override;
	
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Draw() override;
private:
	GameObject* scoreObject = nullptr;
	std::shared_ptr<Font> pFont;
	int m_Score = 0;
};

