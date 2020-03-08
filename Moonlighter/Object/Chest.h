#pragma once
class Chest : public GameObject
{
	ClassInherited(GameObject)
		RequestCollision(CollisionType_Static)
		RequestRender(Layer_Object)

public:
	Chest(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Chest();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();

	virtual void PlayerInteractions();

	virtual void LoadAnimator(wstring file);
	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other);
	virtual void OnCollisionExit(GameObject* other);

	void SetInteractionAniCallBack(function<void(void)> func);

private:
	bool bOnce;
};

