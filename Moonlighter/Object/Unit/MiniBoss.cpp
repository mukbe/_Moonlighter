#include "stdafx.h"
#include "MiniBoss.h"
#include "./Object/Unit/Player.h"


MiniBoss::MiniBoss(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Unit(name, pos, size)
{
	unitState.insert(make_pair("Idle", new MiniBossIdle(this)));
	unitState.insert(make_pair("Walk", new MiniBossWalk(this)));
	unitState.insert(make_pair("Smash", new MiniBossSmash(this)));
	unitState.insert(make_pair("Sword", new MiniBossSword(this)));
	unitState.insert(make_pair("Hit", new MiniBossHit(this)));

	detectRange = 500.f;
	attackRange = 50.f;
	iff = IFFEnum_Monster;

	pivot = Pivot::CENTER;
	rc = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);
	renderRect = FloatRect(D3DXVECTOR2(0.f, 0.f), size, pivot);

}


MiniBoss::~MiniBoss()
{
}

void MiniBoss::Init()
{
	Super::Init();
	ChangeState("Idle");

	function<void(string)> attack = [&](string effect) {
		D3DXVECTOR2 startPos = transform.GetPos() + GetVector2Direction(attackDirection) * size.x*0.6f;

		_BulletSystem->Fire(startPos, 30, 0.1f, 30, "", attackDirection, IFFEnum::IFFEnum_Monster, D3DXVECTOR2(0.f, 0.f), effect);
	};


	function<void(string)> sword = [&](string effect) {
		D3DXVECTOR2 startPos = transform.GetPos() + GetVector2Direction(attackDirection) * size.x*0.7f;
		D3DXVECTOR2 offset = GetVector2Direction(attackDirection) * size.x * 0.1f ;
		offset.x = Math::Abs(offset.x);
		offset.y = Math::Abs(offset.y);
		D3DXVECTOR2 range = D3DXVECTOR2(45.f, 45.f) + offset;
		_BulletSystem->Fire(startPos, range , 0.1f, 30, "", attackDirection, IFFEnum::IFFEnum_Monster, D3DXVECTOR2(0.f, 0.f), effect);
	};

	animator->FindAnimation("Smash_Up")->RegisterCallBackTable("Smash", bind(attack, "Smash1"));
	animator->FindAnimation("Smash_Right")->RegisterCallBackTable("Smash", bind(attack, "Smash2"));
	animator->FindAnimation("Smash_Down")->RegisterCallBackTable("Smash", bind(attack, "Smash3"));
	animator->FindAnimation("Smash_Left")->RegisterCallBackTable("Smash", bind(attack, "Smash4"));

	animator->FindAnimation("Sword_Up")->RegisterCallBackTable("Sword", bind(sword, ""));
	animator->FindAnimation("Sword_Right")->RegisterCallBackTable("Sword", bind(sword, ""));
	animator->FindAnimation("Sword_Down")->RegisterCallBackTable("Sword", bind(sword, ""));
	animator->FindAnimation("Sword_Left")->RegisterCallBackTable("Sword", bind(sword, ""));

}

void MiniBoss::LoadAnimator()
{
	Animator::Load(&animator, ResourcePath + L"Animator/MiniBoss.anim");

}

void MiniBoss::Knockback(D3DXVECTOR2 dir)
{
	ChangeState("Hit");
	((MiniBossHit*)currentState)->SetDir(dir);

}

void MiniBoss::Damge(float dmg)
{
}

void MiniBoss::OnCollisionEnter(GameObject * other)
{
}

void MiniBoss::OnCollisionStay(GameObject * other)
{
	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) && other->GetCollisionType() == CollisionType_Dynamic)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}

}

void MiniBoss::OnCollisionExit(GameObject * other)
{
}

void MiniBossIdle::Enter()
{
	player = _ObjectPool->FindObject<Player>("Player");

	string key = "Idle_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);


}

void MiniBossIdle::Excute()
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
		if (Math::RandF()*2.f > 1.f)
			unit->ChangeState("Smash");
		else
			unit->ChangeState("Sword");

	}
	else if (len <= unit->GetDetectRange())
	{
		unit->ChangeState("Walk");
	}


}

void MiniBossWalk::Enter()
{
	string key = "Idle_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);

	player = _ObjectPool->FindObject<Player>("Player");
	speed = 70.f;
}

void MiniBossWalk::Excute()
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

	string key = "Idle_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key);

	if (len <= unit->GetAttackRange())
		unit->ChangeState("Idle");


	unit->Transform().SetPos(unit->Transform().GetPos() + speed * axis * TickTime);

}

void MiniBossSmash::Enter()
{
	player = _ObjectPool->FindObject<Player>("Player");
	string key = "Smash_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);
	unit->SetAttackDirection(unit->GetDirection());
}

void MiniBossSmash::Excute()
{
	if (unit->GetAnimator()->IsPlay() == false)
	{
		unit->ChangeState("Idle");
	}
}

void MiniBossSword::Enter()
{
	player = _ObjectPool->FindObject<Player>("Player");
	string key = "Sword_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key, true);
	unit->SetAttackDirection(unit->GetDirection());

}

void MiniBossSword::Excute()
{
	if (unit->GetAnimator()->IsPlay() == false)
	{
		unit->ChangeState("Idle");
	}
}

void MiniBossHit::Enter()
{
	time = 0.2f;
	amount = 20.f;
	view = true;
	CAMERA->Shake(2.5f, 0.1f);

}

void MiniBossHit::Excute()
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
