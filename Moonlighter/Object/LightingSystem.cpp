#include "stdafx.h"
#include "LightingSystem.h"
#include "Light.h"

LightingSystem::LightingSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	winSizeTexture = make_unique<CResource2D>(WinSizeX, WinSizeY);
	mergeShader = Shaders->FindShader("MergeLighting");
	lightShader = Shaders->FindComputeShader("Lighting");
	lightSystemBuffer = Buffers->FindShaderBuffer<LightSystemBuffer>();
	drawShader = Shaders->FindShader("DrawToMainRTV");
	lightMap = make_unique<RenderTargetBuffer>(WinSizeX, WinSizeY, DXGI_FORMAT_R8G8B8A8_UNORM);
	lightMap->Create();
}


LightingSystem::~LightingSystem()
{

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
	//CS에서 Lighting
	RenderLightMap();


	DeviceContext->IASetInputLayout(nullptr);
	DeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//라이팅을 위한 RTV
	lightMap->BindRenderTarget();
	{
		winSizeTexture->BindPSShaderResourceView(0);
		ID3D11ShaderResourceView* gbuffer = pRenderer->GetBackBufferSRV();
		DeviceContext->PSSetShaderResources(1, 1, &gbuffer);

		mergeShader->Render();

		pRenderer->TurnOnAlphaBlend();
		DeviceContext->Draw(4, 0);
		pRenderer->TurnOffAlphaBlend();
	}
	pRenderer->BeginDraw();


	//단순히 메인RTV에 그려줌
	{
		ID3D11ShaderResourceView* view = lightMap->GetSRV();
		DeviceContext->PSSetShaderResources(0, 1, &view);

		drawShader->Render();

		pRenderer->TurnOnAlphaBlend();
		DeviceContext->Draw(4, 0);
		pRenderer->TurnOffAlphaBlend();
	}


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
	//Data bind
	{
		CAMERA->CameraDataBind();
		lightSystemBuffer->SetCSBuffer(2);
		winSizeTexture->BindResource(0);
	}
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
			lightSystemBuffer->OffLight(id_light);
			activeList.erase(activeList.begin() + i);

			break;
		}
	}
}

