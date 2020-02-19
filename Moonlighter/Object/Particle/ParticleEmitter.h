#pragma once

class EmitBuffer : public ShaderBuffer
{
public:
	EmitBuffer()
		: ShaderBuffer(&Data, sizeof(Data))
	{

	}

	struct Struct
	{
		float LifeTime;
		float Tick;
		D3DXVECTOR2 Force;

		D3DXVECTOR2 StartPosition;

		D3DXVECTOR2 StartSize;
		D3DXVECTOR2 EndSize;

		D3DXVECTOR2 StartVelocity;
		D3DXVECTOR2 EndVelocity;

		D3DXCOLOR Color;

	}Data;

};

class ParticleEmitter : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Particle | Layer_Imgui)
public:
	ParticleEmitter(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ParticleEmitter();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);

	virtual void Render();
	virtual void ImguiRender();


	void Emit(int count);
protected:
	const int THREAD_NUM_X = 16;
	ComputeShader * particleEmitter;
	ComputeShader * particleUpdater;
	ComputeShader * copyIndirect;
	ComputeShader * resetCounter;


	CResource1D * particleBuffer[2];
	CResource1D * counterBuffer[2];
	CResourceIndirect* indirectBuffer;

	int countPerSec; //1초동안 생성하는 파티클 총량
	int countPerDis; //거리 변화에 따른 파티클 생성


	int currentIndex;
	float loadedGenerateCount;
	float loadedDistanceCount;

	bool bLoop;
	bool bFinishEmit;
	bool bAutoRandomSeed;

	float duration;
	float delay;

	bool bUpdate;

};

