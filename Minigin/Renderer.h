#pragma once
#include <SDL.h>
class Texture2D;
struct SDL_Window;
struct SDL_Renderer;

class Renderer
{
public:
	static void Init(SDL_Window* window);
	static void Clear();
	static void Render();
	static void Destroy();

	static void RenderTexture(const Texture2D& texture);
	static void RenderTexture(const Texture2D& texture, float x, float y);
	static SDL_Renderer* GetSDLRenderer() { return m_Renderer; }
private:
	static SDL_Renderer* m_Renderer ;
};
