#include "stdafx.h"
#include "SceneMapTool.h"

#include "./Object/Unit/Player.h"
#include "./Object/StaticObjectBase.h"
#include "./Object/Unit/Slime.h"

#include "./Object/Unit/MiniBoss.h"
#include "./Object/Unit/Golem.h"
#include "./Object/BackGround.h"


SceneMapTool::SceneMapTool()
{
}


SceneMapTool::~SceneMapTool()
{
}

void SceneMapTool::Init()
{
	CAMERA->ModeTargetPlayer(player);
	SubSystemManager::Get()->Init();


}

void SceneMapTool::OnceInit()
{
	Load();

	BackGround* back = _ObjectPool->CreateObject< BackGround>("BackGround", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	back->SetTexture("Lobby");


	player = _ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	player->SetRenderSize(D3DXVECTOR2(50, 50), Pivot::CENTER );
	player->LoadAnimator(L"");
	Slime* slime = _ObjectPool->CreateObject<Slime>("Slime", D3DXVECTOR2(500, 500), D3DXVECTOR2(15, 15));
	slime->SetRenderSize(D3DXVECTOR2(25, 25), Pivot::CENTER);
	slime->LoadAnimator(L"");
	MiniBoss* boss = _ObjectPool->CreateObject< MiniBoss>("MiniBoss", D3DXVECTOR2(700, 700), D3DXVECTOR2(40, 40));
	boss->SetRenderSize(D3DXVECTOR2(100, 100), Pivot::CENTER);
	boss->LoadAnimator(L"");
	Golem* golem = _ObjectPool->CreateObject< Golem>("Golem", D3DXVECTOR2(0, 700), D3DXVECTOR2(25, 25));
	golem->SetRenderSize(D3DXVECTOR2(50, 65), Pivot::CENTER);
	golem->LoadAnimator(L"");


	_LightSystem->RegisterLight(D3DXVECTOR2(0, 500)
		, D3DXCOLOR(1, 0.8, 0.4, 0.5f)
		, 100.f);



	StaticObjectBase* chest = _ObjectPool->CreateObject<StaticObjectBase>("Chest", D3DXVECTOR2(300, 300), D3DXVECTOR2(30, 30));
	chest->SetRenderSize(D3DXVECTOR2(30, 36), Pivot::CENTER);
	chest->LoadAnimator(ResourcePath + L"Animator/Chest.anim");
	chest->SetInteractionAniCallBack([]() {
		//아이템 떨구는거
	});

}

void SceneMapTool::Load()
{

	_ObjectPool->CreateObject<BulletSystem>("BulletSystem", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<GameData>("GameData", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));



	SubSystemManager::Get()->Init();

}

void SceneMapTool::ImguiRender()
{
	SceneBase::ImguiRender();
}
