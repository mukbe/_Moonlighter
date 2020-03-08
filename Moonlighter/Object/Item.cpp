#include "stdafx.h"
#include "Item.h"



Item::Item(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	bMove = false;
	moveTotalTime = 0.5;
	moveTime = 0.f;
	bCreate = true;
}


Item::~Item()
{
}

void Item::Init()
{
	Super::Init();
	itemTex = _ImageManager->FindTexture("Items");
	index.x = (LONG)Math::Random(0, 3);
	index.y = (LONG)Math::Random(0, 2);
	shadow = _ImageManager->FindTexture("Shadow");
	pivotPos = transform.GetPos();

	moveDir = Math::RandVec2();
	initTotalTime = 0.3f;
	initTime = 0.f;

}

void Item::Release()
{
	//Super::Release();
	_RenderPool->Remove(this, Layer_GameText);

}

void Item::Update(float tick)
{
	Super::Update(tick);

	if (bCreate)
	{
		initTime += TickTime;

		transform.SetPos(transform.GetPos() + moveDir * 50.f * TickTime);


		if (initTime >= initTotalTime)
		{
			bCreate = false;
			pivotPos = transform.GetPos();
		}

	}
	else
	{
		if (bMove)
		{
			moveTime += TickTime;
			float ratio = moveTime / moveTotalTime;
			transform.SetPos(Math::Lerp(startPos, D3DXVECTOR2(WinSizeX - 100, 150), ratio));
			if (ratio > 1.0f)
			{
				_ObjectPool->DeletaObject(this);
			}
		}
		else
		{

			//À§¾Æ·¡µÕµÕ
			transform.SetPos(pivotPos + D3DXVECTOR2(0, sinf(lifeTime) * 5.f));

		}

	}
}

void Item::Render()
{
	Super::Render();
	if (!bMove)
	{
		FloatRect shadowRect = FloatRect(transform.GetPos() + D3DXVECTOR2(0.f, size.y * 0.6f), D3DXVECTOR2(15, 15 * 0.8f), Pivot::CENTER);
		shadow->Render(shadowRect, nullptr, 0.1f);
		itemTex->FrameRender(rc, &transform, index.x, index.y);

	}
	else
	{
		p2DRenderer->SetCamera(false);

		itemTex->FrameRender(rc, &transform, index.x, index.y);

		p2DRenderer->SetCamera(true);

	}


}

void Item::OnCollisionEnter(GameObject * other)
{
	if (other->Name() == "Player")
	{
		//¾ÆÀÌÅÛ È¹µæ
		GameData::Get()->AddItem(index);
		startPos = CAMERA->WorldToScreen(transform.GetPos());
		transform.SetPos(startPos);
		transform.SetScale(2.f);
		bActive = false;
		_RenderPool->Remove(this, GetLayer());
		_RenderPool->Request(this, Layer_GameText);
		bMove = true;
	}
}
