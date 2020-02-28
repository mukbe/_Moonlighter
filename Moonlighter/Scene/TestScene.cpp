#include "stdafx.h"
#include "TestScene.h"
#include "./Object/Unit/Player.h"
#include "./Object/BackGround.h"
#include "ObjectLoader.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

void TestScene::Init()
{
	SubSystemManager::Get()->Init();
}

void TestScene::OnceInit()
{
	Load();
}

void TestScene::Load()
{

	_ObjectPool->CreateObject<BulletSystem>("BulletSystem", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<GameData>("GameData", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));



	SubSystemManager::Get()->Init();
	_ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	_ObjectPool->CreateObject<BackGround>("BackGround", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));

	ObjectLoader load;
	//load.LoadMap(ResourcePath + L"Stage/LampBackUp");
	load.LoadMap(ResourcePath + L"Stage/Lobby");


	//시발노가다... 하...
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
