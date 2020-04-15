#include "ProjectPCH.h"
#include "Bub.h"

#include "AnimLoader.h"
#include "Components.h"
#include "FixedCamera.h"
#include "GameScene.h"
Bub::~Bub()
{
}

void Bub::OnTrigger(BoxCollider* col, BoxCollider* other)
{
}

void Bub::Initialize()
{
	m_pRigid = NEW(RigidbodyComponent)();
	AddComponent(NEW(BoxCollider)(glm::vec2(15, 16)));
	AddComponent(m_pRigid);

	//STATES
	AnimatorState* pRoot = new AnimatorState((int)AnimType::BubRespawn,"Root");
	AnimatorState* pWalk = new AnimatorState((int)AnimType::BubWalk, "Walk");

	m_pAnimator = std::make_shared<Animator>(pRoot, m_Blackboard);
	AddComponent(m_pAnimator);

	std::map<int, AnimData> animData = AnimLoader::Load("../BubbleBobble/Resources/Bub.anim");
	m_pAnimator->SetAnimData(animData);

	//BLACKBOARD KEYS
	m_Blackboard.AddKey((int)BlackboardKey::AbsVelocityX, BlackboardValueType::floatValue);

	//LINKS
	m_pAnimator->LinkStates(pRoot, pWalk,Requirement((int)BlackboardKey::AbsVelocityX,BlackboardValueType::floatValue,Logic::BIGGER));
	
	m_pSprite = std::make_shared<SpriteComponent>("Bub.png");
	AddComponent(m_pSprite);



	

}

void Bub::Update(float elapsedSec)
{
	//FOR TESTING
	glm::vec2 pos = m_Transform->Get2DPosition();
	//GetScene()->GetCamera()->GetTransform()->SetPosition({ pos});
	//***
	
	m_Blackboard.SetKeyValue((int)BlackboardKey::AbsVelocityX,5.0f);
	

	
}

void Bub::LateUpdate(float elapsedSec)
{

}

void Bub::Draw()
{

}
