#include "stdafx.h"
#include "Light.h"

Light::Light(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	id_Light = -1;
	lightSystemBuffer = Buffers->FindShaderBuffer<LightSystemBuffer>();
	velocity = { 0.f,0.f };
	bPlayerEnter = false;
	rangeOffset = 15.f;
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

	transform.SetPos(pos + velocity * tick);

	float intencity = _LightSystem->GetIntencity();
	if (intencity < 0.65f)
	{
		color.a += 0.01f;
	}
	else
	{
		color.a -= 0.01f;
	}
	color.a = Math::Clamp(color.a, 0.f, oldColor.a);

	range = oldRange + sinf(lifeTime) * rangeOffset;



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

void Light::OnCollisionEnter(GameObject * other)
{
	if(other->Name() == "Player")
		bPlayerEnter = true;
}

void Light::OnCollisionStay(GameObject * other)
{
}

void Light::OnCollisionExit(GameObject * other)
{
	if (other->Name() == "Player")
		bPlayerEnter = false;
}
