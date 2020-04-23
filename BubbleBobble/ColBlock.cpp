#include "ColBlock.h"

#include "AnimLoader.h"
#include "ProjectPCH.h"
#include "RigidbodyComponent.h"

#include "BoxCollider.h"
#include "TextureComponent.h"

ColBlock::ColBlock(int levelNumber)
{
	std::shared_ptr<TextureComponent> texComp = NEW(TextureComponent)("Blocks.png");

	AnimData animData = AnimLoader::Load("../BubbleBobble/Resources/Blocks.anim")[levelNumber];
	AddComponent(texComp);
	texComp->SetSourceRectangle({ animData.Src.x,animData.Src.y,animData.Src.w,animData.Src.h });
	AddComponent(NEW(RigidbodyComponent)(true));
	AddComponent(NEW(BoxCollider)(glm::vec2(10, 10), LayerMask::None, LayerMask::None));
	
}
ColBlock::~ColBlock()
{
}

void ColBlock::OnTrigger(BoxCollider* col, BoxCollider* other)
{
}

void ColBlock::Initialize()
{
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
