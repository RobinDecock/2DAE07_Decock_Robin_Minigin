#include "ProjectPCH.h"
#include "ColBlock.h"
#include "AnimLoader.h"
#include "RigidbodyComponent.h"
#include "BoxCollider.h"
#include "BubbleBobble.h"
#include "TextureComponent.h"
#include "Utils.h"

ColBlock::ColBlock(int blockId)
{
	m_BlockId = blockId;
}
ColBlock::~ColBlock()
{
}

void ColBlock::Initialize()
{
	TextureComponent* texComp = new TextureComponent("Blocks.png");

	AnimData animData = Anim::Loader::Load("../BubbleBobble/Resources/Blocks.anim")[m_BlockId];
	AddComponent(texComp);
	texComp->SetSourceRectangle(animData.Src);
	AddComponent(new RigidbodyComponent(true));
	auto pBoxCol = new BoxCollider(glm::vec2(animData.Src.w, animData.Src.h));
	AddComponent(pBoxCol);
	pBoxCol->SetCategory(LayerMask::Ground);
	SetTag("Ground");
}
