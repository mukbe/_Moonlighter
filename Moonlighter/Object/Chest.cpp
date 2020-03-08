#include "stdafx.h"
#include "Chest.h"
#include "./Object/Item.h"


Chest::Chest(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	animator = nullptr;
}


Chest::~Chest()
{
}

void Chest::Init()
{
	Super::Init();
	LoadAnimator(L"");
	bOnce = true;

	_LightSystem->RegisterLight(transform.GetPos()
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.4f)
		, 100.f);


}

void Chest::Release()
{
	Super::Release();
}

void Chest::Update(float tick)
{
	Super::Update(tick);
	if (animator)
		animator->Update();
}

void Chest::Render()
{
	Super::Render();
	if (animator)
		animator->Render(renderRect, &transform, alpha);
}

void Chest::PlayerInteractions()
{
	if (bOnce)
	{
		if (animator)
			animator->ChangeAnimation("Interactions");

		bOnce = false;
	}
}

void Chest::LoadAnimator(wstring file)
{
		Animator::Load(&animator, ResourcePath + L"Animator/BossChest.anim");
		animator->ChangeAnimation("Awake");

		animator->FindAnimation("Awake")->RegisterCallBackTable("Idle", [&]() {
			animator->ChangeAnimation("Idle");
		});

		animator->FindAnimation("Interactions")->RegisterCallBackTable("Item", [&]() {
			
			for (int i = 0; i < 20; i++)		
				_ObjectPool->CreateObject<Item>("Item", transform.GetPos(), D3DXVECTOR2(15, 15));
		});

	

}

void Chest::OnCollisionEnter(GameObject * other)
{
	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) && other->GetCollisionType() == CollisionType_Dynamic)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}
}

void Chest::OnCollisionStay(GameObject * other)
{
	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (other->Name() == "Mouse") return;

	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) && other->GetCollisionType() == CollisionType_Dynamic)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}

}

void Chest::OnCollisionExit(GameObject * other)
{
}

void Chest::SetInteractionAniCallBack(function<void(void)> func)
{
	if (animator)
	{
		animator->FindAnimation("Interactions")->RegisterCallBackTable("Interactions", func);
	}
	else
		LOG->Error(__FILE__, __LINE__, "Anim is nullptr");
}
