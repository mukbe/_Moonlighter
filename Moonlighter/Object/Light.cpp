#include "stdafx.h"
#include "Light.h"
#include "LightingSystem.h"

Light::Light(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	id_Light = -1;
	lightSystemBuffer = Buffers->FindShaderBuffer<LightSystemBuffer>();

	//lightData = Buffers->FindShaderBuffer<LightBuffer>();
	lightingSystem = _ObjectPool->FindObject<LightingSystem>("LightingSystem");
	color = D3DXCOLOR(Math::RandF(), Math::RandF(), Math::RandF(), 0);
	color.a = 0.2f;
	range = 100.f;
	velocity.x = 150.f * Math::RandF() *2.f - 1.f;
	velocity.y = 150.f * Math::RandF() *2.f - 1.f;
}

Light::~Light()
{
}

void Light::Init()
{
	Super::Init();

	id_Light = lightingSystem->RegisterLight(transform.GetPos(), color, range);

}

void Light::Release()
{
	Super::Release();
	//lightingSystem->DeleteLight(id_Light);
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

	D3DXVECTOR2 pos = transform.GetPos();

	if (pos.x < range )
	{
		velocity.x *= -1.f;
		pos.x = range;
	}
	if (pos.x > WinSizeX-range)
	{
		velocity.x *= -1.f;
		pos.x = WinSizeX-range;

	}
	if (pos.y < range )
	{
		velocity.y *= -1.f;
		pos.y = range;

	}
	if (pos.y > WinSizeY-range)
	{
		velocity.y *= -1.f;
		pos.y = WinSizeY-range;

	}

	transform.SetPos(pos + velocity * tick);



	LightDesc desc;
	desc.Color = color;
	desc.isActive = true;
	desc.Position = transform.GetPos();
	Matrix3x2F t = transform.GetResult();
	memcpy_s(&desc.Transform, sizeof(float) * 4, &t, sizeof(float) * 4);
	desc.Range = range;
	lightSystemBuffer->SetLight(id_Light, desc);
}

void Light::Render()
{
	//CAMERA->CameraDataBind();
	//worldBuffer->Setting(transform.GetResult());
	//worldBuffer->SetCSBuffer(1);

	//lightData->SetCSBuffer(2);
	//lightingSystem->BindTexture();

	//lightShader->BindShader();

	//lightShader->Dispatch(80, 30, 1);

	//lightingSystem->ReleaseTexture();

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

