#include "stdafx.h"
#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	for (int i = 0; i < 2; ++i)
	{
		particleBuffer[i] = nullptr;
		counterBuffer[i] = nullptr;
	}

	int* indirect = new int[4]{ 0,1,0,0 };
	indirectBuffer = new CResourceIndirect(indirect);

}


ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Init()
{
	Super::Init();
}

void ParticleEmitter::Release()
{
	Super::Release();
}

void ParticleEmitter::Update(float tick)
{
	Super::Update(tick);

	if (bUpdate == false) return;

	CResource1D* consumeBuffer = particleBuffer[currentIndex];
	CResource1D* appendBuffer = particleBuffer[!currentIndex];
	CResource1D* consumeCounter = counterBuffer[currentIndex];
	CResource1D* appendCounter = counterBuffer[!currentIndex];

	bool bEmit = (lifeTime >= delay);
	bEmit &= (lifeTime > delay + duration) || bLoop;

	D3DXVECTOR2 position = transform.GetPos();
	//float distance = D3DXVec3Length(&(emitData->Data.Position - position));

	float emitCount = (float)countPerSec * TickTime;
	//float distanceCount = (float)countPerDis * distance;


	loadedGenerateCount += emitCount - (int)emitCount;
	emitCount = (float)((int)emitCount);

	//loadedDistanceCount += distanceCount - (int)distanceCount;
	//distanceCount = (float)((int)distanceCount);

	if (loadedGenerateCount >= 1.0f)
	{
		++emitCount;
		loadedGenerateCount = 0.0f;
	}
	//if (loadedDistanceCount >= 1.0f)
	//{
	//	++distanceCount;
	//	loadedDistanceCount = 0.0f;
	//}

	//방사
	if (bEmit && bFinishEmit == false)
	{
		if (emitCount > 0)
			Emit((int)emitCount);
		//if (distanceCount > 0)
		//	Emit((int)distanceCount);

		//자동생성 추가
	}



}

void ParticleEmitter::Render()
{
	Super::Render();

}

void ParticleEmitter::ImguiRender()
{
}

void ParticleEmitter::Emit(int count)
{
	//emitData->Data.Time = Time::Get()->GetWorldTime();

	//emitData->SetCSBuffer(0);
	//textureAnimation->SetCSBuffer(3);

	particleBuffer[currentIndex]->BindResource(0);
	counterBuffer[currentIndex]->BindResource(1);
	particleEmitter->BindShader();

	int dispatchCount = (int)(count / THREAD_NUM_X) + 1;
	particleEmitter->Dispatch(dispatchCount, 1, 1);


	ID3D11UnorderedAccessView* uavs[2] = { nullptr, nullptr };
	ZeroMemory(uavs, sizeof(uavs));
	DeviceContext->CSSetUnorderedAccessViews(0, ARRAYSIZE(uavs), uavs, 0);

}
