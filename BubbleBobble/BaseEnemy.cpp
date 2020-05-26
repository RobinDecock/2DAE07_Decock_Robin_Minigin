#include "ProjectPCH.h"
#include "BaseEnemy.h"

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Initialize()
{
}


void BaseEnemy::Update(float elapsedSec)
{
	if (isPaused)return;
	if(isControlled)
	{
		HandleInput(elapsedSec);
	}
	else
	{
		HandleAI(elapsedSec);
	}
	
}

void BaseEnemy::LateUpdate(float elapsedSec)
{
	
}

void BaseEnemy::Draw()
{
	
}
