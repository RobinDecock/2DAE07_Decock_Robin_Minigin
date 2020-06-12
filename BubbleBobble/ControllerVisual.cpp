#include "ProjectPCH.h"
#include "ControllerVisual.h"


#include "AutoDestroyComponent.h"
#include "BlinkComponent.h"
#include "TextureComponent.h"

void ControllerVisual::Initialize()
{
	AddComponent(new TextureComponent("CVisual.png"));
	AddComponent(new BlinkComponent(0.5f));
	AddComponent(new AutoDestroyComponent(4.0f));
}

void ControllerVisual::Update(float elapsedSec)
{
	
}
