#include "stdafx.h"
#include "LightingSystem.h"
#include "Light.h"


LightingSystem::LightingSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	winSizeTexture = new CResource2D(WinSizeX, WinSizeY);
	shader = Shaders->FindShader("MergeLighting");
	lightShader = Shaders->FindComputeShader("Lighting");
	lightSystemBuffer = Buffers->FindShaderBuffer<LightSystemBuffer>();
}


LightingSystem::~LightingSystem()
{
	SafeDelete(winSizeTexture);
}

void LightingSystem::Init()
{
	Super::Init();
	for (int i = 0;i < LIGHT_MAX; i++)
	{
		Light* light = _ObjectPool->CreateObject<Light>("Light", D3DXVECTOR2(), D3DXVECTOR2());
		light->id_Light = i;
		freeList.push_back(light);
	}
}

void LightingSystem::Release()
{
	Super::Release();
}

void LightingSystem::Update(float tick)
{
	Super::Update(tick);
}

void LightingSystem::Render()
{
	RenderLightMap();

	shader->Render();
	winSizeTexture->BindPSShaderResourceView(0);

	DeviceContext->IASetInputLayout(nullptr);
	DeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	pRenderer->TurnOnAlphaBlend();
	DeviceContext->Draw(4, 0);
	pRenderer->TurnOffAlphaBlend();

}

void LightingSystem::BindTexture()
{
	winSizeTexture->BindResource(0);
}

void LightingSystem::ReleaseTexture()
{
	winSizeTexture->ReleaseResource(0);


}

void LightingSystem::RenderLightMap()
{
	CAMERA->CameraDataBind();
	lightSystemBuffer->SetCSBuffer(2);
	winSizeTexture->BindResource(0);


	lightShader->BindShader();
	lightShader->Dispatch(80, 30, 1);
	winSizeTexture->ReleaseResource(0);


}

void LightingSystem::RegisterLight(D3DXVECTOR2 pos, D3DXCOLOR color, float range, D3DXVECTOR2 scale, float radian)
{
	if (freeList.empty()) return;
	Light* light = freeList.front();

	light->bActive = true;
	light->color = color;
	light->range = range;
	light->transform = Matrix2D(pos);

	light->size = D3DXVECTOR2(range, range);
	light->rc = FloatRect(pos, range, Pivot::BOTTOM);

	activeList.push_back(freeList.front());
	freeList.pop_front();

}

void LightingSystem::DeleteLight(int id_light)
{
	for (int i = 0;i < (int)activeList.size(); i++)
	{
		if (activeList[i]->id_Light == id_light)
		{
			freeList.push_back(activeList[i]);
			activeList[i]->bActive = false;
			activeList.erase(activeList.begin() + i);

			break;
		}
	}

	//lightSystemBuffer->OffLight(id_light);
}

