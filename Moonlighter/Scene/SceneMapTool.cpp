#include "stdafx.h"
#include "SceneMapTool.h"

#include "./Object/Unit/Player.h"
#include "./Object/StaticObjectBase.h"
#include "./Object/Unit/Slime.h"


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
	SubSystemManager::Get()->Init();

	 player = _ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	 player->SetRenderSize(D3DXVECTOR2(50, 50),Pivot::BOTTOM, D3DXVECTOR2(0,15));
	 Slime* slime =  _ObjectPool->CreateObject<Slime>("Slime", D3DXVECTOR2(200, 200), D3DXVECTOR2(15, 15));
	 slime->SetRenderSize(D3DXVECTOR2(25, 25), Pivot::BOTTOM, D3DXVECTOR2(0, 15));


	_LightSystem->RegisterLight(D3DXVECTOR2(0, 500)
		, D3DXCOLOR(1, 0.8, 0.4, 0.5f)
		, 100.f);



	StaticObjectBase* chest = _ObjectPool->CreateObject<StaticObjectBase>("Chest", D3DXVECTOR2(300, 300), D3DXVECTOR2(30, 30));
	chest->SetRenderSize(D3DXVECTOR2(30, 36), Pivot::BOTTOM);
	chest->LoadAnimator(ResourcePath + L"Animator/Chest.anim");
	chest->SetInteractionAniCallBack([]() {
		//아이템 떨구는거
	});







	//CAMERA->ModeTargetPlayer(player);
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
