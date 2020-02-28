#include "stdafx.h"
#include "BackGround.h"



BackGround::BackGround(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	pivot = Pivot::LEFT_TOP;
	rc = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);
	renderRect = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);

}


BackGround::~BackGround()
{
}

void BackGround::Init()
{
	Super::Init();
}

void BackGround::Release()
{
	Super::Release();
}

void BackGround::Render()
{
	//Super::Render();

	if (animator)
		animator->Render(renderRect, &transform, alpha);
}

void BackGround::LoadAnimator(wstring file)
{
	Animator::Load(&animator, file);

	animator->ChangeAnimation("Idle");
	pivot = Pivot::LEFT_TOP;

}

void BackGround::SetTexture(string imgKey)
{
	background = _ImageManager->FindTexture(imgKey);
	imageKey = imgKey;

	this->size = background->GetFrameSize() * 0.5f;
	pivot = Pivot::LEFT_TOP;
	rc = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);
	renderRect = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);

}
