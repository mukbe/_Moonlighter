#include "stdafx.h"
#include "BulletSystem.h"
#include "Bullet.h"


BulletSystem::BulletSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name,pos,size)
{
}


BulletSystem::~BulletSystem()
{
}

void BulletSystem::Fire(D3DXVECTOR2 start, float range, string bulletName, IFFEnum iff, D3DXVECTOR2 velocity, string effectKey)
{
}
