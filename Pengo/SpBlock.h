#pragma once
#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "Pengo.h"
#include "Block.h"
static std::map<bool, SpriteData>SpBlockSprites
{
	{false,SpriteData(0, 0, 16, 16, 1, 1)},
	{true,SpriteData(64, 0, 144, 16, 9, 1)}
};


class SpBlock : public Block
{

public:
	SpBlock();
	void Initialize() override;
	void Render()const override;
	void Update(float elapsedSec)override;
	void OnTrigger(BoxCollider2D* trigger, BoxCollider2D* receive) override;
	void Break();

	~SpBlock();
private:
	SpriteComponent * m_Sprite = nullptr;
};

