#pragma once
#include "Unit.h"
#include "./Object/State/StateBase.h"

class MiniBoss : public Unit
{
	ClassInherited(Unit)
	RequestRender(Layer_Object)
	RequestCollision(CollisionType_Dynamic)
public:
	MiniBoss(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~MiniBoss();

	virtual void Init();

	virtual void LoadAnimator(wstring file);

	virtual void Knockback(D3DXVECTOR2 dir);
	virtual void Damge(float dmg);


	virtual void OnCollisionEnter(GameObject* other);
	virtual void OnCollisionStay(GameObject* other);
	virtual void OnCollisionExit(GameObject* other);

};

class MiniBossIdle :public MonsterBase
{
public:
	MiniBossIdle(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~MiniBossIdle() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "MiniBossIdle"; }
};

class MiniBossWalk :public MonsterBase
{
public:
	MiniBossWalk(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~MiniBossWalk() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "MiniBossWalk"; }
private:
	float speed;
};


class MiniBossSmash :public MonsterBase
{
public:
	MiniBossSmash(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~MiniBossSmash() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "MiniBossSmash"; }
};


class MiniBossSword :public MonsterBase
{
public:
	MiniBossSword(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~MiniBossSword() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "MiniBossSword"; }
};

class MiniBossHit :public MonsterBase
{
public:
	MiniBossHit(Unit* unit) : MonsterBase(unit) { this->unit = unit; }
	~MiniBossHit() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "MiniBossHit"; }
	void SetDir(D3DXVECTOR2 dir) { this->dir = dir; }

private:
	D3DXVECTOR2 dir;
	float time;
	float amount;
	bool view;

};

