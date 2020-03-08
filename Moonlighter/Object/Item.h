#pragma once

class Item : public GameObject
{
	ClassInherited(GameObject)
	RequestCollision(CollisionType_Dynamic)
	RequestRender(Layer_Object)
public:
	Item(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Item();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();


	virtual void OnCollisionEnter(GameObject* other);

private:
	shared_ptr<Texture> itemTex;
	POINT index;
	bool bMove;
	shared_ptr<Texture> shadow;
	D3DXVECTOR2 pivotPos;

	D3DXVECTOR2 startPos;
	float moveTotalTime;
	float moveTime;

	bool bCreate;
	D3DXVECTOR2 moveDir;
	float initTotalTime;
	float initTime;
};

