#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	velocity = { 0.f,0.f };
	animator = nullptr;
	duration = 0.f;
	damge = 0.f;
	bActive = false;
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	Super::Init();
}

void Bullet::Release()
{
	Super::Release();

	if (animator)
		SafeDelete(animator);
}

void Bullet::Update(float tick)
{
	Super::Update(tick);

	if (lifeTime >= duration)
	{
		bActive = false;
		_BulletSystem->CollrectBullet(this);
	}


	D3DXVECTOR2 check = velocity;
	Math::D3DXVector2Normalize(check);
	if (D3DXVec2Length(&check) != 0) 
	{
		transform.SetPos(transform.GetPos() + velocity * TickTime);
	}

	if (animator)
		animator->Update();

}

void Bullet::Render()
{
	Super::Render();
	if (animator)
		animator->Render(rc, &transform, alpha);
}

void Bullet::OnCollisionEnter(GameObject * other)
{
	//피아식별
	if (other->GetIFF() == iff) return;
	if (other->GetIFF() == IFFEnum::IFFEnum_None) return;

	D3DXVECTOR2 dir = other->Transform().GetPos() - transform.GetPos();
	Math::D3DXVector2Normalize(dir);
	//float rad = Math::Angle(other->Transform().GetPos(), transform.GetPos());
	float rad = atan2f(dir.y, dir.x);

	_MessagePool->ReserveMessage(other, "Knockback", 0.f, dir);
	_MessagePool->ReserveMessage(other, "Damge", 0.f, damge);


	if (effectKey.empty()) return;

	if(effectKey == "Arrow")
		EFFECTS->Fire(effectKey, transform.GetPos(), size * 6.f, rad, 15.f);
	else
		EFFECTS->Fire(effectKey, transform.GetPos(), size * 2.5f, rad, 15.f);
	

}
