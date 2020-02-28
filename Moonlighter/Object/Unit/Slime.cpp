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
	unitState.insert(make_pair("Hit", new SlimeHit(this)));
	detectRange = 300.f;
	attackRange = 20.f;
	iff = IFFEnum_Monster;

}


Slime::~Slime()
{
}

void Slime::Init()
{
	Super::Init();


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
	shadowTex->Render(rc, &transform, 0.3f);

	Super::Render();
}

void Slime::ImguiRender()
{
}

void Slime::LoadAnimator(wstring file)
{
	if (file == L"")
		Animator::Load(&animator, ResourcePath + L"Animator/Slime.anim");
	else
		Animator::Load(&animator, file);

	animator->ChangeAnimation("Idle");
	ChangeState("Idle");
	function<void(string)> attack = [&](string effect) {
		D3DXVECTOR2 startPos = transform.GetPos() + GetVector2Direction(attackDirection)* 25.f;




		_BulletSystem->Fire(startPos, 25, 0.1f, 20, "", attackDirection, iff, D3DXVECTOR2(0.f, 0.f), effect);
	};

	animator->FindAnimation("Attack_Up")->RegisterCallBackTable("Attack", bind(attack, ""));
	animator->FindAnimation("Attack_Right")->RegisterCallBackTable("Attack", bind(attack, ""));
	animator->FindAnimation("Attack_Down")->RegisterCallBackTable("Attack", bind(attack, ""));
	animator->FindAnimation("Attack_Left")->RegisterCallBackTable("Attack", bind(attack, ""));


}

void Slime::Knockback(D3DXVECTOR2 dir)
{
	ChangeState("Hit");
	((SlimeHit*)currentState)->SetDir(dir);
}

void Slime::Damge(float dmg)
{

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

	if (len <= unit->GetAttackRange())
	{
		unit->ChangeState("Attack");
	}
	else if (len <= unit->GetDetectRange())
	{
		unit->ChangeState("Walk");
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
	unit->SetAttackDirection(unit->GetDirection());

}

void SlimeAttact::Excute()
{
	if (unit->GetAnimator()->IsPlay() == false)
	{
		unit->ChangeState("Idle");
	}
}

void SlimeHit::Enter()
{
	time = 0.2f;
	amount = 130.f;
	view = true;
	CAMERA->Shake(1.5f, 0.2f);

}

void SlimeHit::Excute()
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
