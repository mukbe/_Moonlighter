#include "stdafx.h"
#include "StaticObjectBase.h"
#include "./Object/Item.h"


StaticObjectBase::StaticObjectBase(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	animator = nullptr;
	bOnce = true;
}


StaticObjectBase::~StaticObjectBase()
{
}

void StaticObjectBase::Init()
{
	Super::Init();
}

void StaticObjectBase::Release()
{
	Super::Release();
}

void StaticObjectBase::Update(float tick)
{
	Super::Update(tick);
	if(animator)
		animator->Update();
}

void StaticObjectBase::Render()
{
	Super::Render();
	if(animator)
		animator->Render(renderRect, &transform, alpha);
}

void StaticObjectBase::PlayerInteractions()
{
	if (bOnce)
	{
		if (animator)
			animator->ChangeAnimation("Interactions");

		bOnce = false;
	}
}

void StaticObjectBase::LoadAnimator(wstring file)
{	
	if (file != L"")
	{
		Animator::Load(&animator, file);
		animator->ChangeAnimation("Idle");
		AnimationClip* clip = animator->FindAnimation("Interactions");
		if (clip)
		{
			clip->RegisterCallBackTable("Item", [&]() {
				for (int i = 0; i < 5; i++)
					_ObjectPool->CreateObject<Item>("Item", transform.GetPos(), D3DXVECTOR2(15, 15));

			});

		}
	}
}

void StaticObjectBase::OnCollisionEnter(GameObject * other)
{
	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) && other->GetCollisionType() == CollisionType_Dynamic)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}
}

void StaticObjectBase::OnCollisionStay(GameObject * other)
{
	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (other->Name() == "Mouse") return;

	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) && other->GetCollisionType() == CollisionType_Dynamic)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}

}

void StaticObjectBase::OnCollisionExit(GameObject * other)
{
}

void StaticObjectBase::SetInteractionAniCallBack(function<void(void)> func)
{
	if (animator)
	{
		animator->FindAnimation("Interactions")->RegisterCallBackTable("Interactions", func);
	}
	else
		LOG->Error(__FILE__, __LINE__, "Anim is nullptr");
}
