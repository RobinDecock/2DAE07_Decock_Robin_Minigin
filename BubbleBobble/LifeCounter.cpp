#include "ProjectPCH.h"
#include "LifeCounter.h"


#include "AnimLoader.h"
#include "TextureComponent.h"
#include "Utils.h"
#include "Bub.h"
LifeCounter::LifeCounter(Bub* ref)
{
	std::map<int, AnimData> map = Anim::Loader::Load("../BubbleBobble/Resources/Lives.anim");

	ref->AddObserver(this);
	for (unsigned int i = 0; i < 3; i++)
	{
		GameObject* obj = new GameObject();
		TextureComponent* texC = new TextureComponent("Bub.png");
		texC->SetUseCam(false);
		obj->AddComponent(texC);
		texC->SetSourceRectangle(make_SDL_Rect(map[ref->GetPlayerId()].Src));

		this->AddChild(obj);
		obj->SetPosition({ 30 * i,0 });
		obj->SetScale({ 0.1f,0.1f });
		lives.push_back(obj);
	}
	
}

void LifeCounter::onNotify( int event,GameObject*  obj)
{
	if(event==Player_Damaged)
	{
		const Bub* other_cast = dynamic_cast<const Bub*>(obj);
		const int& currHealth = other_cast->GetHealth()-1;


		//TODO MAYBE DETACH
		if(currHealth>=0)
		{
			lives[currHealth]->SetVisibility(false);
		}
	}

}
