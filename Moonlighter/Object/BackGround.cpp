#include "stdafx.h"
#include "BackGround.h"



BackGround::BackGround(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{

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
	Super::Render();

	if (background)
		background->Render(rc, &transform);
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
