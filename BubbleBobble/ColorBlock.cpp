#include "ProjectPCH.h"
#include "AnimLoader.h"
#include "ColorBlock.h"
#include "RigidbodyComponent.h"
#include "TextureComponent.h"

ColorBlock::ColorBlock(int blockId)
{
	m_BlockId = blockId;
}
ColorBlock::~ColorBlock()
{
}

void ColorBlock::Initialize()
{
	std::shared_ptr<TextureComponent> texComp = NEW(TextureComponent)("Blocks.png");
	std::map<int, AnimData> animMap = AnimLoader::Load("../BubbleBobble/Resources/Blocks.anim");
	AnimData animData = animMap[m_BlockId];
	AddComponent(texComp);
	texComp->SetSourceRectangle({ animData.Src.x,animData.Src.y,animData.Src.w,animData.Src.h });
	SetTag("Ground");
}

void ColorBlock::Update(float elapsedSec)
{
	UNREF(elapsedSec);
}

void ColorBlock::LateUpdate(float elapsedSec)
{
	UNREF(elapsedSec);
}

void ColorBlock::Draw()
{
}
