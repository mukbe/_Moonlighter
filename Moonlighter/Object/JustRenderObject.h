#pragma once
class JustRenderObject : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Object)

public:
	JustRenderObject(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~JustRenderObject();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();


	virtual void LoadAnimator(wstring file);

};

