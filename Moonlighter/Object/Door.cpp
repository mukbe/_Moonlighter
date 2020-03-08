#include "stdafx.h"
#include "Door.h"
#include "./Object/Unit/Player.h"


Door::Door(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
	animator = nullptr;
}


Door::~Door()
{
}

void Door::Init()
{
	Super::Init();
}

void Door::Release()
{
	Super::Release();
}

void Door::Update(float tick)
{
	Super::Update(tick);
	
	if (animator)
	{
		animator->Update();
	}
}

void Door::Render()
{
	Super::Render();
	if (animator)
		animator->Render(renderRect, &transform, alpha);
}

void Door::LoadAnimator(wstring file)
{
	if (file != L"")
	{
		Animator::Load(&animator, file);
		animator->ChangeAnimation("Idle");
	}

	animator->FindAnimation("Open")->RegisterCallBackTable("OpenIdle", [&]() {
		animator->ChangeAnimation("OpenIdle");
	});
	animator->FindAnimation("Close")->RegisterCallBackTable("Idle", [&]() {
		animator->ChangeAnimation("Idle");
	});
	animator->FindAnimation("Interactions")->RegisterCallBackTable("PlayerOff", [&]() {
		_ObjectPool->FindObject<Player>("Player")->SetActive(false);
	});

}

void Door::PlayerInteractions()
{
	if (animator)
		animator->ChangeAnimation("Interactions",true);
}

void Door::OnCollisionEnter(GameObject * other)
{
	if (animator)
	{
		animator->ChangeAnimation("Open", true);
	}
	else
	{
		change();
	}
}

void Door::OnCollisionStay(GameObject * other)
{
	if (animator == nullptr) return;

	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (other->Name() == "Mouse") return;

	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) && other->GetCollisionType() == CollisionType_Dynamic)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}

}

void Door::OnCollisionExit(GameObject * other)
{
	if (animator)
	{
		if (animator->GetCurrentAnim() == animator->FindAnimation("Interactions") &&
			animator->FindAnimation("Interactions")->IsPlay())
			return;

		animator->ChangeAnimation("Close", true);
	}

}

void Door::SetInteractionAniCallBack(function<void(void)> func)
{
	if (animator)
		animator->FindAnimation("Interactions")->RegisterCallBackTable("Interactions", func);
	else
		LOG->Error(__FILE__, __LINE__, "Anim is nullptr");
}

void Door::SetFuncNextStage(function<void(void)> func)
{
	change = func;
}
