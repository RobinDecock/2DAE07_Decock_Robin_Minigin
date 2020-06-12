#include "ProjectPCH.h"
#include "ColorBlock.h"
#include "AnimLoader.h"
#include "GeneralStructs.h"
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
	TextureComponent* texComp = new TextureComponent("Blocks.png");
	std::map<int, AnimData> animMap = Anim::Loader::Load("../BubbleBobble/Resources/Blocks.anim");
	AnimData animData = animMap[m_BlockId];
	AddComponent(texComp);
	texComp->SetSourceRectangle(animData.Src);
	SetTag("Ground");
}
