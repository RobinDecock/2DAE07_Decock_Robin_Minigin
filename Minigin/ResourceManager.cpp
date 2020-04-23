#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "TextureComponent.h"
#include "Font.h"

void ResourceManager::Init(std::string&& dataPath)
{
	mDataPath = std::move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

SDL_Texture* ResourceManager::LoadTexture(const std::string& file)
{
	std::string fullPath = mDataPath + file;

	std::map<std::string, SDL_Texture*>::iterator it = m_Texturemap.find(file);
	if(it !=m_Texturemap.end())
	{
		return it->second;
	}
	
	SDL_Texture* texture = IMG_LoadTexture(Renderer::GetSDLRenderer(), fullPath.c_str());
	m_Texturemap.insert(std::pair<std::string,SDL_Texture*>(file, texture));
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	
	return texture;
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	return NEW(Font)(mDataPath + file, size);
}
