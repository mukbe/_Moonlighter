#pragma once

class Player : public GameObject
{
public:
	Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual ~Player();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//���� ��ƾ
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

