#pragma once
#include "BaseComponent.h"
#include "GeneralStructs.h"
class Font;
class Texture2D;
class TextureComponent;

class TextComponent final : public BaseComponent
{
public:
	TextComponent(std::shared_ptr<Font> font);
	void Initialize() override;
	void Draw() override;
	void Update(float elapsedSec) override;
	void SetText(const std::string& text);
	void SetColor(SDL_Color color);
	~TextComponent();
private:
	bool m_NeedsUpdate = true;
	std::string m_Text = "";
	std::shared_ptr<Font> m_Font;
	Texture2D * m_Texture=nullptr;
	SDL_Color m_Color;
};

