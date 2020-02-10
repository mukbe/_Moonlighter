#pragma once


class LightingSystem;
class Light : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Object )
public:
	Light(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Light();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//���� ��ƾ
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender();

	void SetRange(float val);
private:
	float range;
	D3DXCOLOR color;

	LightingSystem* lightingSystem;
	LightBuffer* lightData;
	shared_ptr<ComputeShader> lightShader;

};
