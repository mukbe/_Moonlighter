#include "stdafx.h"
#include "JustRenderObject.h"



JustRenderObject::JustRenderObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{

}


JustRenderObject::~JustRenderObject()
{
}

void JustRenderObject::Init()
{
	Super::Init();

}

void JustRenderObject::Release()
{
	Super::Release();

}

void JustRenderObject::Update(float tick)
{
	Super::Update(tick);
	if (animator)
	{
		animator->Update();
		string animName = animator->Name();
		if (String::Contain(animName,"Lamp"))
		{
			float intencity = _LightSystem->GetIntencity();
			if (intencity < 0.5f)
			{
				alpha += 0.01f;
			}
			else
			{
				alpha -= 0.01f;
			}
			SetAlpha(alpha);
		}
	}

}

void JustRenderObject::Render()
{
	Super::Render();
	if (animator)
		animator->Render(renderRect, &transform, alpha);

}

void JustRenderObject::LoadAnimator(wstring file)
{
	if (file != L"")
	{
		Animator::Load(&animator, file);
		animator->ChangeAnimation("Idle");
	}

}
