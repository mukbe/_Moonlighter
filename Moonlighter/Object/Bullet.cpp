#include "stdafx.h"
#include "Bullet.h"



Bullet::Bullet(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{

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
}

void Bullet::Update(float tick)
{
	Super::Update(tick);
}

void Bullet::Render()
{
	Super::Render();
}

void Bullet::OnCollisionEnter(GameObject * other)
{
}
