#include "stdafx.h"
#include "LightingSystem.h"



LightingSystem::LightingSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	winSizeTexture = new CResource2D(WinSizeX, WinSizeY);
	shader = Shaders->FindShader("MergeLighting");
}


LightingSystem::~LightingSystem()
{
	SafeDelete(winSizeTexture);
}

void LightingSystem::Init()
{
	Super::Init();
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
