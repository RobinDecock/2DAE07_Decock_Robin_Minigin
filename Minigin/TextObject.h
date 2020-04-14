#pragma once
#include "TransformComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

namespace dae
{
	class Font;
	class TextureComponent;

	class TextObject : public GameObject
	{
	public:
		void Update(float elapsedSec) override;
		void Render() const override;

		void SetText(const std::string& text);

		explicit TextObject(std::shared_ptr<Font> font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		TextComponent * m_pTextComp = nullptr;
	};

}
