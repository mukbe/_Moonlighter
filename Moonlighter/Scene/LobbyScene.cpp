#include "stdafx.h"
#include "LobbyScene.h"

#include "./Object/Unit/Player.h"
#include "./Object/BackGround.h"
#include "ObjectLoader.h"


LobbyScene::LobbyScene()
{
}


LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init()
{
}

void LobbyScene::OnceInit()
{
	Load();
}

void LobbyScene::Load()
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

}
