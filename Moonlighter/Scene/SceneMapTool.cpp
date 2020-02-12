#include "stdafx.h"
#include "SceneMapTool.h"

#include "./Object/Player.h"

#include "./Object/Light.h"
#include "./Object/LightingSystem.h"

SceneMapTool::SceneMapTool()
{
}


SceneMapTool::~SceneMapTool()
{
}

void SceneMapTool::Init()
{
	Buffers->AddShaderBuffer<LightBuffer>(new LightBuffer);
	Buffers->AddShaderBuffer<LightSystemBuffer>(new LightSystemBuffer);

	Shaders->CreateComputeShader("Lighting", L"Lighting.hlsl","CSMain");
	Shaders->CreateShader("MergeLighting", L"MergeLighting.hlsl");


	_ObjectPool->CreateObject<Player>("", D3DXVECTOR2(100, 100), D3DXVECTOR2(100, 100));
	LightingSystem* light = _ObjectPool->CreateObject<LightingSystem>("LightingSystem", D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0));
	//_ObjectPool->CreateObject<Light>("Light", D3DXVECTOR2(300, 300), D3DXVECTOR2(0, 0));
	for (int i = 0; i < 30; i++)
	{
		light->RegisterLight(D3DXVECTOR2(1600 * Math::RandF(), 900 * Math::RandF())
			, D3DXCOLOR(Math::RandF(), Math::RandF(), Math::RandF(), 0.3f)
			, 100.f);
		//_ObjectPool->CreateObject<Light>("Light", D3DXVECTOR2(1600* Math::RandF(), 900* Math::RandF()) , D3DXVECTOR2(0, 0));
	
	}
	

}

void SceneMapTool::ImguiRender()
{
	SceneBase::ImguiRender();


}
