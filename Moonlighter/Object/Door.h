#pragma once

class Door : public GameObject
{
	ClassInherited(GameObject)
	RequestCollision(CollisionType_Static)
	RequestRender(Layer_Object)

public:
	Door(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Door();

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
	void SetFuncNextStage(function<void(void)> func);
private:
	class DoorState* current;
	unordered_map<string, class DoorState*> states;
	function<void(void)> change;

};

