#include "stdafx.h"
#include "LightingSystem.h"
#include "Light.h"

LightingSystem::LightingSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Super(name, pos, size)
{
	winSizeTexture = make_unique<CResource2D>(WinSizeX, WinSizeY);
	lightShader = Shaders->FindComputeShader("Lighting");
	drawShader = Shaders->FindShader("DrawToMainRTV");
	lightSystemBuffer = Buffers->FindShaderBuffer<LightSystemBuffer>();
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

	SunLightCalculate();

}

void LightingSystem::Render()
{
	RenderLightMap();

	DeviceContext->IASetInputLayout(nullptr);
	DeviceContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//CS에서 버퍼를 합친게 있으므로 백버퍼를 초기화하고 메인RTV에 복사해준다
	pRenderer->BeginDraw();

	{
		winSizeTexture->BindPSShaderResourceView(0);

		drawShader->Render();

		pRenderer->TurnOnAlphaBlend();
		DeviceContext->Draw(4, 0);
		pRenderer->TurnOffAlphaBlend();
	}


}

void LightingSystem::RenderLightMap()
{
	//스왑체인에 엮여있는 RTV를 해제해서 버퍼에 그려지게 한다
	ID3D11RenderTargetView* nullView[1] = { nullptr };
	DeviceContext->OMSetRenderTargets(1, nullView, nullptr);

	//Data bind
	{
		CAMERA->CameraDataBind();
		lightSystemBuffer->SetCSBuffer(2);
		winSizeTexture->BindResource(0);
		ID3D11ShaderResourceView* gbuffer = pRenderer->GetBackBufferSRV();
		DeviceContext->CSSetShaderResources(0, 1, &gbuffer);
		
	}
	//CS에서 기존에 그렸던 정보들과 Light를 합친다
	lightShader->BindShader();
	lightShader->Dispatch(80, 30, 1);

	winSizeTexture->ReleaseResource(0);


}

void LightingSystem::SunLightCalculate()
{
	float intencity;
	float ratio;
	float hour = (float)Time::Get()->GetHour();
	float minute = (float)Time::Get()->GetMinute();
	int area = (int)(hour / 6.f) ;
	float r = 1.f, b = 1.f;

	hour -= area * 6;
	ratio = (hour * 60.f + minute) / 360.f;

	if (area == 0)
	{
		intencity = 0.3f;
		b =  2.5f;

	}
	else if (area == 1)
	{
		intencity = Math::Lerp(0.3f, 1.f, ratio);
		b = Math::LerpSmoothArrival(2.5f, 1.f, ratio, 3);

	}
	else if (area == 2)
	{
		intencity = 1.f;
		r = Math::LerpSmoothStart(1.f, 1.5f, ratio, 3);
	}
	else if (area == 3)
	{
		intencity = Math::Lerp(1.f, 0.3f, ratio);
		r = Math::LerpSmoothArrival(1.5f, 1.f, ratio, 3);
		b = Math::LerpSmoothStart(1.f, 2.5f, ratio, 3);

	}

	lightSystemBuffer->SetSunLight(D3DXCOLOR(1.f * r , 1.f, 1.f * b, intencity));
}

int LightingSystem::RegisterLight(D3DXVECTOR2 pos, D3DXCOLOR color, float range, D3DXVECTOR2 scale, float radian)
{
	if (freeList.empty()) return -1;
	Light* light = freeList.front();

	light->bActive = true;
	light->color = color;
	light->range = range;
	light->transform = Matrix2D(pos);

	light->size = D3DXVECTOR2(range, range);
	light->rc = FloatRect(pos, range, Pivot::BOTTOM);

	activeList.push_back(freeList.front());
	freeList.pop_front();
	return activeList.back()->id_Light;
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

GameObject * LightingSystem::FindLightAsId(int id_light)
{
	ArrayIter Iter = activeList.begin();
	for (;Iter != activeList.end(); ++Iter)
	{
		if ((*Iter)->id_Light == id_light)
			return (*Iter);
	}

	Iter = freeList.begin();
	for (;Iter != freeList.end(); ++Iter)
	{
		if ((*Iter)->id_Light == id_light)
			return (*Iter);
	}


	return nullptr;
}

