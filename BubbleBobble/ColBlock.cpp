#include "ColBlock.h"

#include "TextureComponent.h"

ColBlock::~ColBlock()
{
}

void ColBlock::OnTrigger(BoxCollider* col, BoxCollider* other)
{
}

void ColBlock::Initialize()
{
	AddComponent(std::make_shared<TextureComponent>(""));
}

void ColBlock::Update(float elapsedSec)
{
}

void ColBlock::LateUpdate(float elapsedSec)
{
}

void ColBlock::Draw()
{
}
