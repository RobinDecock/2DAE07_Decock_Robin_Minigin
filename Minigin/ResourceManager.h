#pragma once
#include <map>
#include "Singleton.h"
struct SDL_Texture;
class TextureComponent;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
	std::string mDataPath;
public:
	ResourceManager() = default;
	~ResourceManager();
	void Init(std::string&& data);

	SDL_Texture* LoadTexture(const std::string& file);
	Font* LoadFont(const std::string& file, unsigned int size);
private:
	std::map<std::string, Font*> m_FontMap;
	
	std::map<std::string, SDL_Texture*> m_Texturemap; 
};
