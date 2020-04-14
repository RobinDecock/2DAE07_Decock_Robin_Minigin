#pragma once
#include "Singleton.h"
#include "Texture2D.h"
#include <string>
#include <memory>
class TextureComponent;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
	std::string mDataPath;
public:
	ResourceManager() = default;

	void Init(std::string&& data);

	Texture2D* LoadTexture(const std::string& file);
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
};
