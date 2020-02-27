#pragma once
class MouseObject :public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_GameText)
	RequestCollision(CollisionType_Dynamic)
public:
	MouseObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~MouseObject();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();

	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other) ;
	virtual void OnCollisionExit(GameObject* other) ;

	GameObject* GetPicked() { return picked; }
private:
	GameObject* picked;
};

