#include "stdafx.h"
#include "Stage2.h"
#include "./Object/Unit/Player.h"
#include "./Object/BackGround.h"
#include "ObjectLoader.h"
#include "./Object/Door.h"
#include "./Object/Unit/MiniBoss.h"
Stage2::Stage2()
{
}


Stage2::~Stage2()
{
}

void Stage2::Init()
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
	GameData::Get()->BossProgressBarInit(_ObjectPool->FindObject< MiniBoss>("MiniBoss"));
	GameData::Get()->bPlayerBarRender = true;
	GameData::Get()->bBossBarRender = true;
	player->SetHp(GameData::Get()->GetPlayerHp());

}

void Stage2::OnceInit()
{
	Load();

}

void Stage2::Load()
{

	_ObjectPool->CreateObject<BulletSystem>("BulletSystem", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0))->SetStageLight(true);
	SubSystemManager::Get()->Init();


	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	_ObjectPool->CreateObject<BackGround>("BackGround", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));

	//Door* door = _ObjectPool->CreateObject<Door>("Door", D3DXVECTOR2(320, 35), D3DXVECTOR2(60, 30));
	//door->SetRenderSize(D3DXVECTOR2(80, 40), Pivot::CENTER, D3DXVECTOR2(0, 0));
	//door->LoadAnimator(ResourcePath + L"Animator/StageDoorUp.anim");
	//door->SetInteractionAniCallBack([&]() {
	//	playerLastPosition = _ObjectPool->FindObject<Player>("Player")->Transform().GetPos();
	//	GameData::Get()->RenderOff();

	//	_SceneManager->ChangeScene("Stage2", true);

	//});

	Door* door = _ObjectPool->CreateObject<Door>("Door", D3DXVECTOR2(320, 310), D3DXVECTOR2(60, 30));
	door->SetRenderSize(D3DXVECTOR2(80, 40), Pivot::CENTER, D3DXVECTOR2(0, 20));

	door->LoadAnimator(ResourcePath + L"Animator/StageDoorDown.anim");
	door->SetInteractionAniCallBack([&]() {
		playerLastPosition = _ObjectPool->FindObject<Player>("Player")->Transform().GetPos();
		GameData::Get()->RenderOff();

		_SceneManager->ChangeScene("Stage1", true);
	});


	ObjectLoader load;
	load.LoadMap(ResourcePath + L"Stage/StageMiniBoss");


	_LightSystem->RegisterLight(D3DXVECTOR2(137.f, 69.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);

	_LightSystem->RegisterLight(D3DXVECTOR2(577.f, 57.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);

	_LightSystem->RegisterLight(D3DXVECTOR2(74.f, 225.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(145.f, 292.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(61.f, 300.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(520.f, 246.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(480.f, 289.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.25f)
		, 30.f);

	_LightSystem->RegisterLight(D3DXVECTOR2(566.f, 257.f)
		, D3DXCOLOR(0.4f, 0.4f, 0.8, 0.4f)
		, 100.f);

}
