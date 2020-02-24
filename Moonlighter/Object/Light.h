#pragma once


class Light : public GameObject
{
	ClassInherited(GameObject)
	RequestCollision(CollisionType_Static)
	RequestRender(Layer_Object)
	friend class LightingSystem;
public:
	Light(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~Light();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//메인 루틴
	virtual void Update(float tick);

	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other);
	virtual void OnCollisionExit(GameObject* other);

	

private:
	float range;
	float rangeOffset;
	float oldRange;
	D3DXCOLOR color;
	D3DXCOLOR oldColor;
	int id_Light;
	D3DXVECTOR2 velocity;

	LightSystemBuffer* lightSystemBuffer;

	bool bPlayerEnter;
};

