#include "stdafx.h"
#include "Slime.h"
#include "./Systems/SubSystemManager.h"


Slime::Slime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Unit(name, pos, size)
{
}


Slime::~Slime()
{
}

void Slime::Init()
{
	Super::Init();

	//ChangeState("Idle");

}

void Slime::Release()
{
	Super::Release();

}

void Slime::Update(float tick)
{
	Super::Update(tick);

}


void Slime::Render()
{
	Super::Render();
}

void Slime::ImguiRender()
{
}

void Slime::LoadAnimator()
{
	Animator::Load(&animator, ResourcePath + L"Animator/Slime.anim");
	animator->ChangeAnimation("Idle");
}

void Slime::OnCollisionEnter(GameObject * other)
{
	if (other->Name() == "Player")
	{
		D3DXVECTOR2 dir = other->Transform().GetPos() - transform.GetPos();
		Math::D3DXVector2Normalize(dir);

		_MessagePool->ReserveMessage(other, "Hit",0.f,dir);
	}
}

void Slime::OnCollisionStay(GameObject * other)
{


}

void Slime::OnCollisionExit(GameObject * other)
{

}
