#pragma once


class Light;
class LightingSystem : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Light)
public:
	LightingSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~LightingSystem();


	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//���� ��ƾ
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender() {}

	void BindTexture();
	void ReleaseTexture();


	void RenderLightMap();
	void RegisterLight(D3DXVECTOR2 pos, D3DXCOLOR color, float range, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), float radian = 0.f);
	void DeleteLight(int id_light);
private:
	shared_ptr<Shader> shader;
	CResource2D* winSizeTexture;
	shared_ptr<ComputeShader> lightShader;

	deque<Light*> freeList;
	deque<Light*> activeList;


private:
	LightSystemBuffer* lightSystemBuffer;
};

