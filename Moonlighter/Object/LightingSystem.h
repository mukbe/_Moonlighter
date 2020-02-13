#pragma once


class Light;
class RenderTargetBuffer;
class LightingSystem : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Light)
	friend class ObjectManager;
public:
	LightingSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~LightingSystem();


	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender() {}

	void BindTexture();
	void ReleaseTexture();

	
	void RenderLightMap();
	void SunLightCalculate();
	void RegisterLight(D3DXVECTOR2 pos, D3DXCOLOR color, float range, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), float radian = 0.f);
	void DeleteLight(int id_light);
private:
	unique_ptr<CResource2D> winSizeTexture;

	shared_ptr<ComputeShader> lightShader;
	shared_ptr<Shader> drawShader;

	deque<Light*> freeList;
	deque<Light*> activeList;

private:
	LightSystemBuffer* lightSystemBuffer;


};

