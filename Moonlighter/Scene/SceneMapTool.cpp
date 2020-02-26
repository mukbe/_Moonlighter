#include "stdafx.h"
#include "SceneMapTool.h"

#include "./Object/Unit/Player.h"
#include "./Object/StaticObjectBase.h"
#include "./Object/Unit/Slime.h"

#include "./Object/Unit/MiniBoss.h"
#include "./Object/Unit/Golem.h"

SceneMapTool::SceneMapTool()
{
}


SceneMapTool::~SceneMapTool()
{
}

void SceneMapTool::Init()
{
	Buffers->AddShaderBuffer<LightSystemBuffer>(new LightSystemBuffer);
	Shaders->CreateComputeShader("Lighting", L"Lighting.hlsl","CSMain");
	Shaders->CreateShader("DrawToMainRTV", L"DrawToMainRTV.hlsl");

	_ImageManager->AddTexture("Back", ResourcePath + L"Map/map.png");
	_ImageManager->AddTexture("Shadow", ResourcePath + L"Shadow.png");

	_ObjectPool->CreateObject<BulletSystem>("BulletSystem", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<GameData>("GameData", D3DXVECTOR2(), D3DXVECTOR2());
	_ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));

	_ImageManager->AddFrameTexture("fx_Arrow", ResourcePath + L"Fx/fx_hit_BowSecondary.png", 3, 1);
	_ImageManager->AddFrameTexture("fx_Sword1", ResourcePath + L"Fx/fx_hit_shortsword.png", 3, 1);
	_ImageManager->AddFrameTexture("fx_Sword2", ResourcePath + L"Fx/fx_hit_shortsword_2.png", 3, 1);

	_ImageManager->AddFrameTexture("fx_smash1", ResourcePath + L"Fx/fx_hit_smash1.png",6, 1);
	_ImageManager->AddFrameTexture("fx_smash2", ResourcePath + L"Fx/fx_hit_smash2.png",6, 1);
	_ImageManager->AddFrameTexture("fx_smash3", ResourcePath + L"Fx/fx_hit_smash3.png",6, 1);
	_ImageManager->AddFrameTexture("fx_smash4", ResourcePath + L"Fx/fx_hit_smash4.png",6, 1);

	EFFECTS->AddEffect("Arrow", "fx_Arrow");
	EFFECTS->AddEffect("Sword1", "fx_Sword1");
	EFFECTS->AddEffect("Sword2", "fx_Sword2");

	EFFECTS->AddEffect("Smash1", "fx_smash1");
	EFFECTS->AddEffect("Smash2", "fx_smash2");
	EFFECTS->AddEffect("Smash3", "fx_smash3");
	EFFECTS->AddEffect("Smash4", "fx_smash4");


	SubSystemManager::Get()->Init();

	 player = _ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	 player->SetRenderSize(D3DXVECTOR2(50, 50),Pivot::BOTTOM, D3DXVECTOR2(0,15));
	 Slime* slime =  _ObjectPool->CreateObject<Slime>("Slime", D3DXVECTOR2(500, 500), D3DXVECTOR2(15, 15));
	 slime->SetRenderSize(D3DXVECTOR2(25, 25), Pivot::BOTTOM);
	 MiniBoss* boss = _ObjectPool->CreateObject< MiniBoss>("MiniBoss", D3DXVECTOR2(700, 700), D3DXVECTOR2(40, 40));
	 boss->SetRenderSize(D3DXVECTOR2(100, 100), Pivot::CENTER);
	 Golem* golem = _ObjectPool->CreateObject< Golem>("Golem", D3DXVECTOR2(0, 700), D3DXVECTOR2(25, 25));
	 golem->SetRenderSize(D3DXVECTOR2(50, 65), Pivot::CENTER);



	_LightSystem->RegisterLight(D3DXVECTOR2(0, 500)
		, D3DXCOLOR(1, 0.8, 0.4, 0.5f)
		, 100.f);



	StaticObjectBase* chest = _ObjectPool->CreateObject<StaticObjectBase>("Chest", D3DXVECTOR2(300, 300), D3DXVECTOR2(30, 30));
	chest->SetRenderSize(D3DXVECTOR2(30, 36), Pivot::BOTTOM);
	chest->LoadAnimator(ResourcePath + L"Animator/Chest.anim");
	chest->SetInteractionAniCallBack([]() {
		//아이템 떨구는거
	});







	CAMERA->ModeTargetPlayer(player);
}

void SceneMapTool::ImguiRender()
{
	SceneBase::ImguiRender();


}

void SceneMapTool::Update(float tick)
{
	SceneBase::Update(tick);

	//FloatRect rc = player->GetCollider();
	//D3DXVECTOR2 mouse = CAMERA->GetMousePos();
	//if (Mouse::Get()->Down(0))
	//{
	//	if (Math::IsPointInAABB(rc, mouse))
	//	{
	//		_MessagePool->ReserveMessage(player, "IsClick");
	//	}
	//}

}
