#include "stdafx.h"
#include "Slime.h"
#include "./Systems/SubSystemManager.h"
#include "./Object/Unit/Player.h"


Slime::Slime(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Unit(name, pos, size)
{
	unitState.insert(make_pair("Idle", new SlimeIdle(this)));
	unitState.insert(make_pair("Walk", new SlimeWalk(this)));
	unitState.insert(make_pair("Attack", new SlimeAttact(this)));
	detectRange = 300.f;
	attackRange = 40.f;
	iff = IFFEnum_Monster;

}


Slime::~Slime()
{
}

void Slime::Init()
{
	Super::Init();

	ChangeState("Idle");

}

void Slime::Release()
{
	Super::Release();

}

void Slime::Update(float tick)
{
	Super::Update(tick);

}


void Slime::Render()
{
	Super::Render();
}

void Slime::ImguiRender()
{
}

void Slime::LoadAnimator()
{
	Animator::Load(&animator, ResourcePath + L"Animator/Slime.anim");
	animator->ChangeAnimation("Idle");
}

void Slime::OnCollisionEnter(GameObject * other)
{
	if (other->Name() == "Player")
	{
		D3DXVECTOR2 dir = other->Transform().GetPos() - transform.GetPos();
		Math::D3DXVector2Normalize(dir);

		_MessagePool->ReserveMessage(other, "Knockback",0.f,dir);
	}
}

void Slime::OnCollisionStay(GameObject * other)
{


}

void Slime::OnCollisionExit(GameObject * other)
{

}

void SlimeIdle::Enter()
{
	unit->GetAnimator()->ChangeAnimation("Idle");
	player = _ObjectPool->FindObject<Player>("Player");

}

void SlimeIdle::Excute()
{

	D3DXVECTOR2 axis = player->Transform().GetPos() - unit->Transform().GetPos();
	float len = D3DXVec2Length(&axis);
	if (len<= unit->GetAttackRange())
	{
		unit->ChangeState("Attack");
	}
	else if (len <= unit->GetDetectRange())
	{
		unit->ChangeState("Walk");
	}

	Math::D3DXVector2Normalize(axis);
	D3DXVECTOR2 absAxis = { Math::Abs(axis.x), Math::Abs(axis.y) };
	if (absAxis.x >= absAxis.y)
	{
		if (axis.x >= 0)
		{
			unit->SetDirection(UnitDirection::Right);
		}
		else
		{
			unit->SetDirection(UnitDirection::Left);
		}
	}
	else
	{
		if (axis.y >= 0)
		{
			unit->SetDirection(UnitDirection::Down);
		}
		else
		{
			unit->SetDirection(UnitDirection::Up);
		}
	}


}

void SlimeWalk::Enter()
{
	unit->GetAnimator()->ChangeAnimation("Walk");
	player = _ObjectPool->FindObject<Player>("Player");
	speed = 90.f;
}

void SlimeWalk::Excute()
{
	D3DXVECTOR2 axis = player->Transform().GetPos() - unit->Transform().GetPos();
	
	float len = D3DXVec2Length(&axis);
	if (len <= unit->GetAttackRange())
		unit->ChangeState("Idle");

	Math::D3DXVector2Normalize(axis);
	D3DXVECTOR2 absAxis = { Math::Abs(axis.x), Math::Abs(axis.y) };
	if (absAxis.x >= absAxis.y)
	{
		if (axis.x >= 0)
		{
			unit->SetDirection(UnitDirection::Right);
		}
		else
		{
			unit->SetDirection(UnitDirection::Left);
		}
	}
	else
	{
		if (axis.y >= 0)
		{
			unit->SetDirection(UnitDirection::Down);
		}
		else
		{
			unit->SetDirection(UnitDirection::Up);
		}
	}


	unit->Transform().SetPos(unit->Transform().GetPos() + speed * axis * TickTime);

}

void SlimeAttact::Enter()
{
	player = _ObjectPool->FindObject<Player>("Player");
	string key = "Attack_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key,true);
}

void SlimeAttact::Excute()
{
	if (unit->GetAnimator()->IsPlay() == false)
	{
		unit->ChangeState("Idle");
	}
}
