#include "stdafx.h"
#include "SceneMapTool.h"

#include "./Object/Player.h"

#include "./Object/LightingSystem.h"

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

	 player = _ObjectPool->CreateObject<Player>("Player", D3DXVECTOR2(100, 100), D3DXVECTOR2(15, 15));
	 player->SetRenderSize(D3DXVECTOR2(50, 50),Pivot::BOTTOM, D3DXVECTOR2(0,10));
	//LightingSystem* light = _ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	//for (int i = 0; i < 30; i++)
	//{	
	//	light->RegisterLight(D3DXVECTOR2(1600 * Math::RandF(), 900 * Math::RandF())
	//		, D3DXCOLOR(1, 0.8, 0.4, 0.6f)
	//		, 100.f);

	//}

	CAMERA->ModeTargetPlayer(player);
	
}

void SceneMapTool::ImguiRender()
{
	SceneBase::ImguiRender();


}

void SceneMapTool::Update(float tick)
{
	SceneBase::Update(tick);

	FloatRect rc = player->GetCollider();
	D3DXVECTOR2 mouse = CAMERA->GetMousePos();
	if (Mouse::Get()->Down(0))
	{
		if (Math::IsPointInAABB(rc, mouse))
		{
			_MessagePool->ReserveMessage(player, "IsClick");
		}
	}

}
