#pragma once
#include "BaseComponent.h"
#include "Font.h"
class TextureComponent;

class TextComponent final : public BaseComponent
{
public:
	TextComponent(std::shared_ptr<Font> font);
	void Initialize() override;
	void Draw() override;
	void Update(float elapsedSec) override;
	void SetText(const std::string& text);
	~TextComponent();
private:
	bool m_NeedsUpdate = false;
	std::string m_Text = "";
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<TextureComponent> m_Texture;
};
