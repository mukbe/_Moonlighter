#include "stdafx.h"
#include "SubSystemManager.h"



SingletonCpp(SubSystemManager)

SubSystemManager::SubSystemManager()
{
}


SubSystemManager::~SubSystemManager()
{
}

LightingSystem * SubSystemManager::GetLightingSubSystem()
{
	return light;
}

BulletSystem * SubSystemManager::GetBulletSubSystem()
{
	return bullet;
}



void SubSystemManager::Init()
{
	light = _ObjectPool->FindObject<LightingSystem>("LightingSystem");
	bullet = _ObjectPool->FindObject<BulletSystem>("BulletSystem");
}
