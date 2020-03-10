#include "stdafx.h"
#include "StateBase.h"
#include "./Utilities/Animator.h"
#include "./Object/Unit/Unit.h"
#include "./Object/Item.h"


void StateIdle::Enter()
{
	string key = "Idle_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key);
}

void StateIdle::Excute()
{
	if (unit->GetHp() <= 0.f)
	{
		unit->ChangeState("Dead");
	}
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
	D3DXVECTOR2 axis = KeyCode->GetData();
	D3DXVECTOR2 value = axis;
	Math::D3DXVector2Normalize(axis);
	D3DXVECTOR2 unitAxis = GetVector2Direction(unit->GetDirection());
	if (Math::FloatEqual(axis.x, unitAxis.x) && Math::FloatEqual(axis.y, unitAxis.y))
	{
		unit->Transform().SetPos(unit->Transform().GetPos() + value * 50.f * TickTime);

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
	view = true;
	CAMERA->Shake();
}

void StateHit::Excute()
{
	time -= TickTime;
	if (time <= 0)
	{
		unit->SetAlpha(1.f);
		unit->ChangeState("Idle");
		return;
	}

	view = !view;
	unit->SetAlpha(0.6f*(int)view);

	unit->Transform().SetPos(unit->Transform().GetPos() + dir * amount * TickTime);
}

void StateDead::Enter()
{
	unit->GetAnimator()->ChangeAnimation("Dead");
	bOnce = true;
}

void StateDead::Excute()
{
	if (bOnce)
	{
		if (unit->GetAnimator()->IsPlay() == false)
		{
			vector<pair<POINT, int>> items = GameData::Get()->GetItems();

			for (int i = 0; i < (int)items.size(); i++)
			{
				Item* item = _ObjectPool->CreateObject<Item>("Item", unit->Transform().GetPos(), D3DXVECTOR2(15, 15));
				item->SetIndex(items[i].first);
			}
			bOnce = false;

		}
	}
}
