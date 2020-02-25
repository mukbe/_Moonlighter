#pragma once
#include "Unit.h"
#include "./Object/State/StateBase.h"

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

class SlimeIdle : public StateBase
{
public:
	SlimeIdle(Unit* unit) : StateBase(unit) { this->unit = unit; }
	~SlimeIdle() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "SlimeIdle"; }
protected:
	Unit* unit;
	class Player* player;
};

class SlimeWalk : public StateBase
{
public:
	SlimeWalk(Unit* unit) : StateBase(unit) { this->unit = unit; }
	~SlimeWalk() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "SlimeWalk"; }
private:
	class Player* player;
	float speed;
};

class SlimeAttact : public StateBase
{
public:
	SlimeAttact(Unit* unit) : StateBase(unit) { this->unit = unit; }
	~SlimeAttact() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "SlimeAttact"; }
private:
	class Player* player;
};