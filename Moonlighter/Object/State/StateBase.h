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
