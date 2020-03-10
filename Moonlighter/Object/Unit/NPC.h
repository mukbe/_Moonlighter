#pragma once
#include "Unit.h"
#include "./Object/State/StateBase.h"

class NPC : public Unit
{
	ClassInherited(Unit)
	RequestCollision(CollisionType_Dynamic)
	RequestRender(Layer_Object)
public:
	NPC(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~NPC();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);

	virtual void Render();

	virtual void LoadAnimator(wstring file);

	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other);

private:
	shared_ptr<Texture> shadow;
};


class NPCStateIdle : public StateBase
{
public:
	NPCStateIdle(Unit* unit) :StateBase(unit)
	{
	}
	~NPCStateIdle()
	{
	}
	virtual void Enter();
	virtual void Excute();
	virtual string Name()
	{
		return "NPCStateIdle";
	}
private:
	float waitTime;
};

class NPCStateMove : public StateBase
{
public:
	NPCStateMove(Unit* unit) :StateBase(unit)
	{
	}
	~NPCStateMove()
	{
	}
	virtual void Enter();
	virtual void Excute();
	virtual string Name()
	{
		return "NPCStateMove";
	}
private:
	D3DXVECTOR2 dir;
	float moveLength;
};
