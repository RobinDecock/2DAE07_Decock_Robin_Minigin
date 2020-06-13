#include "ProjectPCH.h"
#include "ScoreAnnouncer.h"



#include "AnimLoader.h"
#include "AutoDestroyComponent.h"
#include "RigidbodyComponent.h"
#include "TextureComponent.h"
#include "Utils.h"
ScoreAnnouncer::ScoreAnnouncer(int score)
{
	m_pScore = score;
}

void ScoreAnnouncer::Initialize()
{
	AnimData animData = Anim::Loader::Load("../BubbleBobble/Resources/ScoreFont.anim")[(m_pScore-100)/100];
	AddComponent(new AutoDestroyComponent(2.0f));
	TextureComponent* pTexComp = new TextureComponent("Sprite.png");
	pTexComp->SetSourceRectangle(make_SDL_Rect(animData.Src));
	AddComponent(pTexComp);

	AddComponent(new RigidbodyComponent());
	GetComponent<RigidbodyComponent>()->SetGravityScale(-5);
}
