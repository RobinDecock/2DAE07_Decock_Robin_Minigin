#pragma once
#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "Pengo.h"
#include "Block.h"
static std::map<bool, SpriteData>IceBlockSprites
{
	{false,SpriteData(0, 0, 16, 16, 1, 1)},
	{true,SpriteData(64, 0, 144, 16, 9, 1)}
};


class IceBlock: public Block
{

public:
	IceBlock(PlayField * playField);
	void Initialize() override;
	void Render()const override;
	void Update(float elapsedSec)override;
	void OnTrigger(BoxCollider2D* trigger, BoxCollider2D* receive) override;
	void Break();
	~IceBlock();
private:
	SpriteComponent * m_Sprite = nullptr;
};

