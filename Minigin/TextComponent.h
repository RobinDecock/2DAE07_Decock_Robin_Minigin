#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "GeneralStructs.h"
class Font;
class Texture2D;
class TextureComponent;


	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(Font* font, std::string textString = "");
		void Draw() override;
		void SetText(const std::string& text);
		void SetColor(SDL_Color color);
		void CreateNewTexture();
		~TextComponent();
	private:
		std::string m_Text = "";
		Font* m_Font = nullptr;
		Texture2D* m_Texture = nullptr;
		SDL_Color m_Color;
	};

