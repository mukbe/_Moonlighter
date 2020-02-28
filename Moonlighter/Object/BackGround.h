#pragma once
class BackGround : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_BackGround)
public:
	BackGround(string name, D3DXVECTOR2 pos,D3DXVECTOR2 size);
	~BackGround();

	virtual void Init();
	//메모리 해제
	virtual void Release();

	virtual void Render();

	virtual void LoadAnimator(wstring file);
	void SetTexture(string imgKey);
private:
	string imageKey;
	shared_ptr<Texture> background;
};

