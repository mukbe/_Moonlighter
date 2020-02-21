#pragma once

class Unit;
class StateBase
{
public:
	StateBase(Unit* unit) { this->unit = unit; }
	~StateBase() {}
	virtual void Enter() = 0;
	virtual void Excute() = 0;
	virtual void Exit() {}
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
	virtual void Exit() {}

};

class StateMove : public StateBase
{
public:
	StateMove(Unit* unit) :StateBase(unit) {}
	~StateMove() {}
	virtual void Enter();
	virtual void Excute();
	virtual void Exit() {}

};

class StateSword : public StateBase
{
public:
	StateSword(Unit* unit) :StateBase(unit) {}
	~StateSword() {}
	virtual void Enter();
	virtual void Excute();
	virtual void Exit() {}

};
class StateBow : public StateBase
{
public:
	StateBow(Unit* unit) :StateBase(unit) {}
	~StateBow() {}
	virtual void Enter();
	virtual void Excute();
	virtual void Exit() {}

};
class StateRoll : public StateBase
{
public:
	StateRoll(Unit* unit) :StateBase(unit) {}
	~StateRoll() {}
	virtual void Enter();
	virtual void Excute();
	virtual void Exit() {}
private:
	float startSpeed;
	float endSpeed;
};
