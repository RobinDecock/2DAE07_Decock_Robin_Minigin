#include "ProjectPCH.h"
#include "ColBlock.h"

#include "AnimLoader.h"
#include "ProjectPCH.h"
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
	std::shared_ptr<TextureComponent> texComp = NEW(TextureComponent)("Blocks.png");

	AnimData animData = AnimLoader::Load("../BubbleBobble/Resources/Blocks.anim")[m_BlockId];
	AddComponent(texComp);
	texComp->SetSourceRectangle({ animData.Src.x,animData.Src.y,animData.Src.w,animData.Src.h });
	AddComponent(NEW(RigidbodyComponent)(true));
	auto pBoxCol = NEW(BoxCollider)(glm::vec2(animData.Src.w, animData.Src.h));
	AddComponent(pBoxCol);
	pBoxCol->SetCategory(LayerMask::Ground);
	SetTag("Ground");
}


void ColBlock::Update(float elapsedSec)
{
	UNREF(elapsedSec);
}

void ColBlock::LateUpdate(float elapsedSec)
{
	UNREF(elapsedSec);
}

void ColBlock::Draw()
{
}
