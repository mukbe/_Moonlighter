#pragma once
#include "Unit.h"

class Player : public Unit
{
	ClassInherited(Unit)
	RequestRender(Layer_Object | Layer_Imgui)
	RequestCollision(CollisionType_Dynamic)
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


	virtual void LoadAnimator();

	virtual void Knockback(D3DXVECTOR2 dir);
	virtual void Damge(float dmg);


	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other);
	virtual void OnCollisionExit(GameObject* other);
private:

};

