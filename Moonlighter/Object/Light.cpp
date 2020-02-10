#include "stdafx.h"
#include "Light.h"
#include "LightingSystem.h"

Light::Light(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	lightData = Buffers->FindShaderBuffer<LightBuffer>();
	lightShader = Shaders->FindComputeShader("Lighting");
	lightingSystem = _ObjectPool->FindObject<LightingSystem>("LightingSystem");
	color = ColorWhite;
	color.a = 0.2f;
}

Light::~Light()
{
}

void Light::Init()
{
	Super::Init();
	range = 30.f;


}

void Light::Release()
{
	Super::Release();
}

void Light::Update(float tick)
{
	Super::Update(tick);
	//if (KeyCode->Press('W'))
	//{
	//	transform.SetPos(transform.GetPos() + D3DXVECTOR2(0, -100) * tick);
	//}
	//else if (KeyCode->Press('S'))
	//{
	//	transform.SetPos(transform.GetPos() + D3DXVECTOR2(0, 100) * tick);

	//}
	//if (KeyCode->Press('A'))
	//{
	//	transform.SetPos(transform.GetPos() + D3DXVECTOR2(-100,0) * tick);

	//}
	//else if (KeyCode->Press('D'))
	//{
	//	transform.SetPos(transform.GetPos() + D3DXVECTOR2(100,0) * tick);
	//}
	//range -= tick * 50.f;
	lightData->SetColor(color);
	lightData->SetRagne(range);


}

void Light::Render()
{
	CAMERA->CameraDataBind();
	worldBuffer->Setting(transform.GetResult());
	worldBuffer->SetCSBuffer(1);

	lightData->SetCSBuffer(2);
	lightingSystem->BindTexture();

	lightShader->BindShader();

	lightShader->Dispatch(80, 30, 1);

	lightingSystem->ReleaseTexture();

}

void Light::ImguiRender()
{
	static bool bOpen = true;
	ImGui::Begin("Light", &bOpen);
	ImGui::ColorEdit4("Color", color);
	ImGui::End();
}

void Light::SetRange(float val)
{
	range = val;
}

