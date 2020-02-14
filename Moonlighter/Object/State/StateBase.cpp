#include "stdafx.h"
#include "StateBase.h"
#include "./Utilities/Animator.h"
#include "./Object/Unit.h"

void StateIdle::Enter()
{
	string key = "Idle_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key);
}

void StateIdle::Excute()
{
	if (KeyCode->Press(VK_LEFT))
	{
		unit->SetDirection(UnitDirection::Left);
		unit->ChangeState("Move");
	}
	else if (KeyCode->Press(VK_RIGHT))
	{
		unit->SetDirection(UnitDirection::Right);
		unit->ChangeState("Move");
	}
	else if (KeyCode->Press(VK_UP))
	{
		unit->SetDirection(UnitDirection::Up);
		unit->ChangeState("Move");
	}
	else if (KeyCode->Press(VK_DOWN))
	{
		unit->SetDirection(UnitDirection::Down);
		unit->ChangeState("Move");
	}

}

void StateMove::Enter()
{
	string key = "Move_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key);

}

void StateMove::Excute()
{

	if (KeyCode->Up(VK_LEFT))
	{
		unit->SetDirection(UnitDirection::Left);
		unit->ChangeState("Idle");
	}
	else if (KeyCode->Up(VK_RIGHT))
	{
		unit->SetDirection(UnitDirection::Right);
		unit->ChangeState("Idle");
	}
	else if (KeyCode->Up(VK_UP))
	{
		unit->SetDirection(UnitDirection::Up);
		unit->ChangeState("Idle");

	}
	else if (KeyCode->Up(VK_DOWN))
	{
		unit->SetDirection(UnitDirection::Down);
		unit->ChangeState("Idle");

	}

}
