#pragma once

#include "TextureComponent.h"
#include <vector>
#include "BaseComponent.h"
#include "GeneralStructs.h"

//#include <glm/glm.hpp>
class SpriteComponent final : public BaseComponent
{
public:
	SpriteComponent(std::string filePath);
	~SpriteComponent();


	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent(SpriteComponent&&) = delete;
	SpriteComponent& operator=(const SpriteComponent&) = delete;
	SpriteComponent& operator=(const SpriteComponent&&) = delete;
	void Initialize() override;
	void Draw() override;
	void Update(float elapsedSec) override;
	Texture2D* GetTexture2D() { return m_Texture; }


	void SetPivot(glm::vec2 rect);
	///CHANGE
	void SetSrcY(int change);
	void Setoffset(glm::vec2 offset);
	void SetState(int2 grid);
	void SetSpeed(float speed);
	void SetSpriteData(AnimData data);
	void SetGridPos(int2 pos) { m_Grid = pos; }
	///RESETS
	void ResetCycle();
	void ResetState();
	////EXCEPTIONS
	void SetExceptions(int value);
	void ResetExceptions();
	void SetPause(bool b) { pause = b; }
	////HELPER GET FUNCTIONS
	int2 GetState() const;
	int GetCycle() { return m_Cycle; }
	void SetFlip(bool flip) { m_Texture->SetFlip(flip); }
private:
	void UpdateSource2D();
	void UpdateDestination2D();
	int m_Rows=1;
	int m_Cols=1;
	int2 m_Grid{};
	int m_Change{};
	float m_Speed{};
	int m_Cycle{};
	float m_Sec{};
	int2 m_TileSize {};
	int2 m_StartPos {};
	glm::vec2 pivotOffset = glm::vec2(0.5f, 0.5f);
	glm::vec2 m_Offset {};
	std::vector<int> m_Exceptions;
	Texture2D* m_Texture = nullptr;
	SDL_Rect m_DestRect{};
	SDL_Rect m_SrcRect{};
	float m_Rotation{};
	bool pause = false;
};
