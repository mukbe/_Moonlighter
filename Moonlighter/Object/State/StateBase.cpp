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

	if (KeyCode->Down('C'))
	{

	}
	else if (KeyCode->Down('X'))
	{

	}
	else if (KeyCode->Down('Z'))
	{

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
	float speed = 150;
	D3DXVECTOR2 axis = KeyCode->GetData();
	Math::D3DXVector2Normalize(axis);
	unit->Transform().SetPos(unit->Transform().GetPos() + axis * speed * TickTime);



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

void StateSword::Enter()
{
}

void StateSword::Excute()
{
}

void StateBow::Enter()
{
}

void StateBow::Excute()
{
}

void StateRoll::Enter()
{
}

void StateRoll::Excute()
{
}