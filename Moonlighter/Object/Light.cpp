#include "stdafx.h"
#include "Light.h"

Light::Light(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	id_Light = -1;
	lightSystemBuffer = Buffers->FindShaderBuffer<LightSystemBuffer>();
	velocity.x = 150.f * Math::RandF() *2.f - 1.f;
	velocity.y = 150.f * Math::RandF() *2.f - 1.f;
}

Light::~Light()
{
}

void Light::Init()
{
	Super::Init();

}

void Light::Release()
{
	Super::Release();
}

void Light::Update(float tick)
{
	Super::Update(tick);

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
	desc.isActive = this->bActive;
	desc.Color = color;
	desc.isActive = true;
	desc.Position = transform.GetPos();
	Matrix3x2F t = transform.GetResult();
	memcpy_s(&desc.Transform, sizeof(float) * 4, &t, sizeof(float) * 4);
	desc.Range = range;
	lightSystemBuffer->SetLight(id_Light, desc);
}
