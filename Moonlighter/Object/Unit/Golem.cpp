#include "stdafx.h"
#include "Golem.h"
#include "./Object/Unit/Player.h"


Golem::Golem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Unit(name, pos, size)
{

	unitState.insert(make_pair("Idle", new GolemIdle(this)));
	unitState.insert(make_pair("Walk", new GolemWalk(this)));
	unitState.insert(make_pair("Hit", new GolemHit(this)));
	unitState.insert(make_pair("Attack", new GolemAttack(this)));

	detectRange = 300.f;
	attackRange = 40.f;
	iff = IFFEnum_Monster;

	pivot = Pivot::CENTER;
	rc = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);
	renderRect = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);

}


Golem::~Golem()
{
}

void Golem::Init()
{
	Super::Init();
	ChangeState("Idle");

	function<void(string)> attack = [&](string effect) {
		D3DXVECTOR2 startPos = transform.GetPos() + GetVector2Direction(direction) * size.x*0.7f;

		_BulletSystem->Fire(startPos, 25, 0.1f, 30, "", direction, IFFEnum::IFFEnum_Monster, D3DXVECTOR2(0.f, 0.f), effect);
	};



	animator->FindAnimation("Attack_Up")->RegisterCallBackTable("Attack", bind(attack, ""));
	animator->FindAnimation("Attack_Right")->RegisterCallBackTable("Attack", bind(attack, ""));
	animator->FindAnimation("Attack_Down")->RegisterCallBackTable("Attack", bind(attack, ""));
	animator->FindAnimation("Attack_Left")->RegisterCallBackTable("Attack", bind(attack, ""));


}

void Golem::LoadAnimator()
{
	Animator::Load(&animator, ResourcePath + L"Animator/Golem.anim");
}

void Golem::Knockback(D3DXVECTOR2 dir)
{
	ChangeState("Hit");
	((GolemHit*)currentState)->SetDir(dir);

}

void Golem::Damge(float dmg)
{
}

void Golem::OnCollisionStay(GameObject * other)
{
	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) && other->GetCollisionType() == CollisionType_Dynamic)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}

}

void GolemIdle::Enter()
{
	player = _ObjectPool->FindObject<Player>("Player");

	string key = "Move_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);
}

void GolemIdle::Excute()
{
	D3DXVECTOR2 axis = player->Transform().GetPos() - unit->Transform().GetPos();
	float len = D3DXVec2Length(&axis);
	if (len <= unit->GetAttackRange())
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

void GolemWalk::Enter()
{
	string key = "Move_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);

	player = _ObjectPool->FindObject<Player>("Player");
	speed = 80.f;

}

void GolemWalk::Excute()
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

	string key = "Move_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key);

	unit->Transform().SetPos(unit->Transform().GetPos() + speed * axis * TickTime);

}

void GolemAttack::Enter()
{
	player = _ObjectPool->FindObject<Player>("Player");
	string key = "Attack_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);
}

void GolemAttack::Excute()
{
	if (unit->GetAnimator()->IsPlay() == false)
	{
		unit->ChangeState("Idle");
	}
}

void GolemHit::Enter()
{
	time = 0.2f;
	amount = 45.f;
	view = true;
	CAMERA->Shake(1.5f, 0.1f);

}

void GolemHit::Excute()
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
