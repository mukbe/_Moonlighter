#pragma once

class Unit;
class StateBase
{
public:
	StateBase(Unit* unit) { this->unit = unit; }
	~StateBase() {}
	virtual void Enter() = 0;
	virtual void Excute() = 0;
	virtual string Name() { return "StateBase"; }
protected:
	Unit* unit;

};

class StateIdle : public StateBase
{
public:
	StateIdle(Unit* unit) :StateBase(unit) {}
	~StateIdle() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "StateIdle"; }

};

class StateMove : public StateBase
{
public:
	StateMove(Unit* unit) :StateBase(unit) {}
	~StateMove() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "StateMove"; }

};

class StateSword : public StateBase
{
public:
	StateSword(Unit* unit) :StateBase(unit) {}
	~StateSword() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "StateSword"; }

};
class StateBow : public StateBase
{
public:
	StateBow(Unit* unit) :StateBase(unit) {}
	~StateBow() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "StateBow"; }

};
class StateRoll : public StateBase
{
public:
	StateRoll(Unit* unit) :StateBase(unit) {}
	~StateRoll() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "StateRoll"; }
private:
	float startSpeed;
	float endSpeed;
};

class StateHit : public StateBase
{
public:
	StateHit(Unit* unit) :StateBase(unit) {}
	~StateHit() {}
	virtual void Enter();
	virtual void Excute();
	virtual string Name() { return "StateHit"; }
	void SetDir(D3DXVECTOR2 val) { dir = val; }
private:
	D3DXVECTOR2 dir;
	float time;
	float amount;
};