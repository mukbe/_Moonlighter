#include "stdafx.h"
#include "LightingSystem.h"



LightingSystem::LightingSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	winSizeTexture = new CResource2D(WinSizeX, WinSizeY);
	shader = Shaders->FindShader("MergeLighting");
	lightShader = Shaders->FindComputeShader("Lighting");
	lightSystemBuffer = Buffers->FindShaderBuffer<LightSystemBuffer>();
	for (int i = 0;i < LIGHT_MAX;i++)
		freeList.push_back(i);
}


LightingSystem::~LightingSystem()
{
	SafeDelete(winSizeTexture);
}

void LightingSystem::Init()
{
	Super::Init();
	vector <D3DXCOLOR> temp;
	temp.assign(1600, D3DXCOLOR());
	color.assign(900, temp);
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

	//winSizeTexture->GetDatas(color);

}

int LightingSystem::RegisterLight(D3DXVECTOR2 pos, D3DXCOLOR color, float range, D3DXVECTOR2 scale, float radian)
{
	if (freeList.empty()) return -1;
	LightDesc desc;
	desc.isActive = true;
	desc.Color = color;
	desc.Position = pos;
	desc.Range = range;
	Matrix2D mat = Matrix2D(pos, scale, radian); 
	Matrix3x2F t = mat.GetResult();
	memcpy_s(&desc.Transform, sizeof(float) * 4, &t, sizeof(float) * 4);

	lightSystemBuffer->SetLight(freeList.front(), desc);
	activeList.push_back(freeList.front());
	freeList.pop_front();
	return activeList.back();
}

void LightingSystem::DeleteLight(int id_light)
{
	for (int i = 0;i < (int)activeList.size(); i++)
	{
		if (activeList[i] == id_light)
		{
			activeList.erase(activeList.begin() + i);
			break;
		}
	}
	freeList.push_back(id_light);
	lightSystemBuffer->OffLight(id_light);
}

