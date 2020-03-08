#include "stdafx.h"
#include "TestScene.h"
#include "./Object/Unit/Player.h"
#include "./Object/BackGround.h"
#include "ObjectLoader.h"
#include "./Object/Door.h"

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

void TestScene::Init()
{
	SubSystemManager::Get()->Init();
	CAMERA->ModeTargetPlayer(_ObjectPool->FindObject<Player>("Player"));
	FloatRect area = _ObjectPool->FindObject<BackGround>("BackGround")->GetRenderArea();
	CAMERA->SetLimitPos(D3DXVECTOR2(area.right, area.bottom));

	Player* player = _ObjectPool->FindObject<Player>("Player");
	if(playerLastPosition.x > 0 && playerLastPosition.y > 0)
		player->Transform().SetPos(playerLastPosition);
	player->SetActive(true);

}

void TestScene::OnceInit()
{
	Load();

}

void TestScene::Load()
{

	_ObjectPool->CreateObject<BulletSystem>("BulletSystem", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	SubSystemManager::Get()->Init();



	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	_ObjectPool->CreateObject<BackGround>("BackGround", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	Door* door = _ObjectPool->CreateObject<Door>("Door", D3DXVECTOR2(523, 493), D3DXVECTOR2(60, 30));
	door->SetRenderSize(D3DXVECTOR2(62, 40), Pivot::CENTER);
	door->LoadAnimator(ResourcePath + L"Animator/LobbyDoor.anim");
	door->SetInteractionAniCallBack([&]() {
		playerLastPosition = _ObjectPool->FindObject<Player>("Player")->Transform().GetPos();

		_SceneManager->ChangeScene("Town", true);
	});
	door = _ObjectPool->CreateObject<Door>("Door", D3DXVECTOR2(918, 1096), D3DXVECTOR2(100, 20));
	door->SetFuncNextStage([&]() {
		playerLastPosition = _ObjectPool->FindObject<Player>("Player")->Transform().GetPos();

		_SceneManager->ChangeScene("Town", true);
	});

	ObjectLoader load;
	//load.LoadMap(ResourcePath + L"Stage/LampTest");
	load.LoadMap(ResourcePath + L"Stage/Lobby");


	_LightSystem->RegisterLight(D3DXVECTOR2(903, 275)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(777, 409)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(995, 406)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(1266, 512)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(851, 715)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(972, 805)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(866, 926)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);
	_LightSystem->RegisterLight(D3DXVECTOR2(966, 1037)
		, D3DXCOLOR(1, 0.8, 0.4, 0.4f)
		, 100.f);

}
