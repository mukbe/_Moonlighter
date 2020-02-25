#include "stdafx.h"
#include "StateBase.h"
#include "./Utilities/Animator.h"
#include "./Object/Unit/Unit.h"

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
		unit->ChangeState("Roll");
	}
	else if (KeyCode->Down('X'))
	{
		unit->ChangeState("Bow");
	}
	else if (KeyCode->Down('Z'))
	{
		unit->ChangeState("Sword");
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

	if (KeyCode->Down('C'))
	{
		unit->ChangeState("Roll");
	}
	else if (KeyCode->Down('X'))
	{
		unit->ChangeState("Bow");
	}
	else if (KeyCode->Down('Z'))
	{
		unit->ChangeState("Sword");
	}

}

void StateSword::Enter()
{
	string key = "Sword_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);

}

void StateSword::Excute()
{
	if (KeyCode->Down('C'))
	{
		unit->ChangeState("Roll");
	}

	if (unit->GetAnimator()->IsPlay() == false)
	{
		unit->ChangeState("Idle");
	}

}

void StateBow::Enter()
{
	string key = "Bow_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);
}

void StateBow::Excute()
{
	if (KeyCode->Down('C'))
	{
		unit->ChangeState("Roll");
	}

	if (unit->GetAnimator()->IsPlay() == false)
	{
		unit->ChangeState("Idle");
	}
}

void StateRoll::Enter()
{
	string key = "Roll_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key);
	startSpeed = 300.f;
	endSpeed = 50.f;
}

void StateRoll::Excute()
{
	D3DXVECTOR2 axis = KeyCode->GetData();
	Math::D3DXVector2Normalize(axis);
	unit->Transform().SetPos(unit->Transform().GetPos() + axis * startSpeed * TickTime);

	if (unit->GetAnimator()->IsPlay() == false)
	{
		unit->ChangeState("Idle");
	}

}

void StateHit::Enter()
{
	time = 0.2f;
	amount = 130.f;
	CAMERA->Shake();
}

void StateHit::Excute()
{
	time -= TickTime;
	if (time <= 0)
	{
		unit->ChangeState("Idle");
	}

	unit->Transform().SetPos(unit->Transform().GetPos() + dir * amount * TickTime);
}
