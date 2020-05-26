#include "ProjectPCH.h"
#include "ScoreAnnouncer.h"



#include "BoxTrigger.h"
#include "RigidbodyComponent.h"
#include "TextureComponent.h"
#include "Utils.h"
ScoreAnnouncer::ScoreAnnouncer(int score)
{
	score -= 500;
	score /= 100;
	m_pScore = score;
}

void ScoreAnnouncer::Initialize()
{
	AnimData animData = AnimLoader::Load("../BubbleBobble/Resources/ScoreFont.anim")[m_pScore];

	PTR(TextureComponent) pTexComp = NEW(TextureComponent)("Sprite.png");
	pTexComp->SetSourceRectangle(make_SDL_Rect(animData.Src));
	AddComponent(pTexComp);

	AddComponent(std::make_shared<RigidbodyComponent>());
	AddComponent(std::make_shared<BoxTrigger>(glm::vec2(10, 10)));
	GetComponent<RigidbodyComponent>()->SetGravityScale(-5);
}
