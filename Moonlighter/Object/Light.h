#pragma once


class Light : public GameObject
{
	ClassInherited(GameObject)
	friend class LightingSystem;
public:
	Light(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Light();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//���� ��ƾ
	virtual void Update(float tick);

private:
	float range;
	D3DXCOLOR color;
	int id_Light;
	D3DXVECTOR2 velocity;

	LightSystemBuffer* lightSystemBuffer;
};

