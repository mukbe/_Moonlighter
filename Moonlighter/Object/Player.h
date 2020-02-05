#pragma once

class Player : public GameObject
{
public:
	Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~Player();

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//메인 루틴
	virtual void Update(float tick);

	virtual void Render();
	//imgui debugUI render
	virtual void ImguiRender();

private:
	Animator* animator;
	shared_ptr<Texture> tex;
	UINT frameX;
	UINT frameY;
};

