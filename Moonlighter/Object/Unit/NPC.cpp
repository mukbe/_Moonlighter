#include "stdafx.h"
#include "NPC.h"



NPC::NPC(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:Unit(name, pos, size)
{
	iff = IFFEnum_None;
	unitState.insert(make_pair("Idle", new NPCStateIdle(this)));
	unitState.insert(make_pair("Move", new NPCStateMove(this)));


}


NPC::~NPC()
{
}

void NPC::Init()
{
	Super::Init();
	shadow = _ImageManager->FindTexture("Shadow");
	SetRenderSize(D3DXVECTOR2(50.f, 50.f), Pivot::CENTER);

}

void NPC::Release()
{
	Super::Release();

}

void NPC::Update(float tick)
{
	Super::Update(tick);

}

void NPC::Render()
{
	FloatRect shadowRect = FloatRect(transform.GetPos() + D3DXVECTOR2(0.f, size.y * 0.6f), D3DXVECTOR2(30, 30 * 0.8f), Pivot::CENTER);
	shadow->Render(shadowRect, nullptr, 0.1f);
	
	Super::Render();
}

void NPC::LoadAnimator(wstring file)
{
	Animator::Load(&animator, file);

	animator->ChangeAnimation("Idle_Down");
	ChangeState("Idle");

}

void NPC::OnCollisionEnter(GameObject * other)
{
}

void NPC::OnCollisionStay(GameObject * other)
{
	FloatRect origin = other->GetCollider();
	FloatRect otherRc = other->GetCollider();
	if (other->Name() == "Mouse") return;

	if (Math::IsAABBInAABBReaction(&otherRc, GetCollider()) && other->GetCollisionType() == CollisionType_Dynamic)
	{
		other->Transform().SetPos(other->Transform().GetPos() + D3DXVECTOR2(otherRc.left - origin.left, otherRc.top - origin.top));
	}

}

void NPCStateIdle::Enter()
{
	string key = "Idle_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key);
	waitTime = 5.f;
}

void NPCStateIdle::Excute()
{
	waitTime -= TickTime;
	if (waitTime <= 0)
	{
		unit->ChangeState("Move");
	}
}

void NPCStateMove::Enter()
{
	dir = Math::RandVec2();
	Math::D3DXVector2Normalize(dir);
	D3DXVECTOR2 absDir = { Math::Abs(dir.x), Math::Abs(dir.y) };

	if (absDir.x >= absDir.y)
	{
		if (dir.x <= 0.f)
		{
			unit->SetDirection(UnitDirection::Left);
		}
		else
		{
			unit->SetDirection(UnitDirection::Right);
		}
	}
	else
	{
		if (dir.y <= 0.f)
		{
			unit->SetDirection(UnitDirection::Up);
		}
		else
		{
			unit->SetDirection(UnitDirection::Down);
		}
	}



	string key = "Walk_";
	key += unit->GetStringUnitDirection();
	unit->GetAnimator()->ChangeAnimation(key);
	moveLength = 100.f;
}

void NPCStateMove::Excute()
{
	float speed = 100;
	float len = D3DXVec2Length(&(dir * speed * TickTime));
	unit->Transform().SetPos(unit->Transform().GetPos() + dir * speed * TickTime);
	moveLength -= len;
	if (moveLength <= 0.f)
		unit->ChangeState("Idle");
}
