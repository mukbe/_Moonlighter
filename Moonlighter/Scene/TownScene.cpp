#include "stdafx.h"
#include "TownScene.h"

#include "./Object/Unit/Player.h"
#include "./Object/BackGround.h"
#include "ObjectLoader.h"
#include "./Object/Door.h"

#include "./Object/Item.h"
#include "./Object/Chest.h"

TownScene::TownScene()
{
}


TownScene::~TownScene()
{
}

void TownScene::Init()
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

void TownScene::OnceInit()
{
	Load();

}

void TownScene::Update(float tick)
{
	SceneBase::Update(tick);
	if (KeyCode->Down('G'))
	{
		_ObjectPool->CreateObject<Chest>("Chest", CAMERA->GetMousePos(), D3DXVECTOR2(40, 40));
	}
}

void TownScene::Load()
{
	_ObjectPool->CreateObject<BulletSystem>("BulletSystem", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	SubSystemManager::Get()->Init();



	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	_ObjectPool->CreateObject<BackGround>("BackGround", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));

	Door* door = _ObjectPool->CreateObject<Door>("Door", D3DXVECTOR2(1490, 388), D3DXVECTOR2(20, 100));
	door->SetFuncNextStage([&]() {
		playerLastPosition = _ObjectPool->FindObject<Player>("Player")->Transform().GetPos();

		GameData::Get()->RenderOff();
		_SceneManager->ChangeScene("Lobby", true);
	});


	ObjectLoader load;
	load.LoadMap(ResourcePath + L"Stage/Town");



	//라이트 넣어라
	_LightSystem->RegisterLight(D3DXVECTOR2(460.f, 196.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(898.f, 300.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(1286.f, 310.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(1130.f, 442.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(1153.f, 677.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(1117.f, 959.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(854.f, 1036.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(637.f, 838.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(159.f, 1052.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(337.f, 607.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(332.f, 383.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);

	_LightSystem->RegisterLight(D3DXVECTOR2(562.f, 432.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(555.f, 691.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(883.f, 533.f)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);



}
