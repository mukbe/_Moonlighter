#pragma once
#include "Unit.h"
#include "./Object/State/StateBase.h"

class Golem : public Unit
{
	ClassInherited(Unit)
	RequestRender(Layer_Object)
	RequestCollision(CollisionType_Dynamic)
public:
	Golem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Golem();


	virtual void Init();

	virtual void LoadAnimator(wstring file);

	virtual void Knockback(D3DXVECTOR2 dir);
	virtual void Damge(float dmg);
	virtual void OnCollisionStay(GameObject* other);


};



class GolemIdle :public MonsterBase
{
public:
	GolemIdle(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~GolemIdle() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "GolemIdle"; }
};

class GolemWalk :public MonsterBase
{
public:
	GolemWalk(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~GolemWalk() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "GolemWalk"; }
private:
	float speed;
};


class GolemAttack :public MonsterBase
{
public:
	GolemAttack(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~GolemAttack() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "GolemAttack"; }
};



class GolemHit :public MonsterBase
{
public:
	GolemHit(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~GolemHit() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "GolemHit"; }
	void SetDir(D3DXVECTOR2 dir) { this->dir = dir; }
private:
	D3DXVECTOR2 dir;
	float time;
	float amount;
	bool view;

};

