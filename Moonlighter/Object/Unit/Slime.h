#pragma once
#include "Unit.h"

class Slime : public Unit
{
	ClassInherited(Unit)
	RequestRender(Layer_Object)
	RequestCollision(CollisionType_Dynamic)

public:
	Slime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Slime();


	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);

	virtual void Render();
	virtual void ImguiRender();


	virtual void LoadAnimator();

	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other);
	virtual void OnCollisionExit(GameObject* other);

};

