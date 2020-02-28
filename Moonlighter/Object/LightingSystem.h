#pragma once


class Light;
class RenderTargetBuffer;
class LightingSystem : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Light | Layer_Imgui)
	friend class ObjectManager;

public:
	int RegisterLight(D3DXVECTOR2 pos, D3DXCOLOR color, float range, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), float radian = 0.f);
	void DeleteLight(int id_light);
	GameObject* FindLightAsId(int id_light);

	float GetIntencity() { return intencity; }

private:
	LightingSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~LightingSystem();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();
	virtual void ImguiRender();
	
	void RenderLightMap();
	void SunLightCalculate();


private:
	using ArrayIter = deque<Light*>::iterator;
	unique_ptr<CResource2D> winSizeTexture;

	shared_ptr<ComputeShader> lightShader;
	shared_ptr<Shader> drawShader;

	deque<Light*> freeList;
	deque<Light*> activeList;

	LightSystemBuffer* lightSystemBuffer;
	float intencity;

};

