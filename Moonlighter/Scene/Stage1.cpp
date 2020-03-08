#include "stdafx.h"
#include "Stage1.h"
#include "./Object/Unit/Player.h"
#include "./Object/BackGround.h"
#include "ObjectLoader.h"
#include "./Object/Door.h"
#include "./Object/Unit/MiniBoss.h"
Stage1::Stage1()
{
}


Stage1::~Stage1()
{
}

void Stage1::Init()
{
	SubSystemManager::Get()->Init();
	CAMERA->ModeTargetPlayer(_ObjectPool->FindObject<Player>("Player"));
	FloatRect area = _ObjectPool->FindObject<BackGround>("BackGround")->GetRenderArea();
	CAMERA->SetLimitPos(D3DXVECTOR2(area.right, area.bottom));

	Player* player = _ObjectPool->FindObject<Player>("Player");
	if (playerLastPosition.x > 0 && playerLastPosition.y > 0)
		player->Transform().SetPos(playerLastPosition);
	player->SetActive(true);
	GameData::Get()->PlayerProgressBarInit(player);
	GameData::Get()->bPlayerBarRender = true;
	player->SetHp(GameData::Get()->GetPlayerHp());

}

void Stage1::OnceInit()
{
	Load();

}

void Stage1::Load()
{

	_ObjectPool->CreateObject<BulletSystem>("BulletSystem", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0))->SetStageLight(true);
	SubSystemManager::Get()->Init();


	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	_ObjectPool->CreateObject<BackGround>("BackGround", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));

	Door* door = _ObjectPool->CreateObject<Door>("Door", D3DXVECTOR2(320, 35), D3DXVECTOR2(60, 30));
	door->SetRenderSize(D3DXVECTOR2(80, 40), Pivot::CENTER, D3DXVECTOR2(0, 0));
	door->LoadAnimator(ResourcePath + L"Animator/StageDoorUp.anim");
	door->SetInteractionAniCallBack([&]() {
		playerLastPosition = _ObjectPool->FindObject<Player>("Player")->Transform().GetPos();
		GameData::Get()->RenderOff();

		_SceneManager->ChangeScene("Stage2", true);
	});

	door = _ObjectPool->CreateObject<Door>("Door", D3DXVECTOR2(320, 310), D3DXVECTOR2(60, 30));
	door->SetRenderSize(D3DXVECTOR2(80, 40), Pivot::CENTER, D3DXVECTOR2(0, 20));

	door->LoadAnimator(ResourcePath + L"Animator/StageDoorDown.anim");
	door->SetInteractionAniCallBack([&]() {
		playerLastPosition = _ObjectPool->FindObject<Player>("Player")->Transform().GetPos();
		GameData::Get()->RenderOff();

		_SceneManager->ChangeScene("Stage0", true);
	});


	ObjectLoader load;
	load.LoadMap(ResourcePath + L"Stage/Stage1");

	_LightSystem->RegisterLight(D3DXVECTOR2(568.f, 278.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(66.f, 171.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(118.f, 55.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(63.f, 94.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(82.f, 117.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);

	_LightSystem->RegisterLight(D3DXVECTOR2(510.f, 302.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(553.f, 302.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(575.f, 302.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);


}
