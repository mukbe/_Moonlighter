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

void BulletSystem::Init()
{
	Super::Init();

	LoadBulletAnimator();

	for (int i = 0; i < 20; i++)
	{
		CreateBullet();
	}
}

void BulletSystem::Release()
{
	Super::Release();

	MapIter Iter = bulletAnimators.begin();
	for (;Iter != bulletAnimators.end(); Iter++)
	{
		SafeDelete(Iter->second);
	}
	bulletAnimators.clear();
}

void BulletSystem::LoadBulletAnimator()
{
	
	WCHAR path[128] = L"../_Resources/Animator";
	Path::FileSearch(path, [&](wstring file) {
		if (String::Contain(file, L"Bullet"))
		{
			Animator* anim = nullptr;
			wstring fileW = file;
			String::Replace(&fileW, L"\\", L"/");
			Animator::Load(&anim, file);

			string fileM = String::WStringToString(fileW);
			fileM = Path::GetFileNameWithoutExtension(fileM);
			bulletAnimators.insert(make_pair(fileM, anim));
		}
	});
}

void BulletSystem::CreateBullet()
{
	Bullet* bullet = _ObjectPool->CreateObject<Bullet>("Bullet", D3DXVECTOR2(), D3DXVECTOR2());
	freeBullets.push_back(bullet);
}

Animator * BulletSystem::FindBulletAnimator(string bulletName)
{
	MapIter Iter  = bulletAnimators.find(bulletName);
	if (Iter != bulletAnimators.end())
		return Iter->second;

	return nullptr;
}

void BulletSystem::Fire(D3DXVECTOR2 start, float range, float duration,float damge, string bulletName, UnitDirection dir, IFFEnum iff, D3DXVECTOR2 velocity, string effectKey)
{
	if (freeBullets.empty() != false)
	{
		Log_Print("freeBullets is empty");
		return;
	}

	firedBullets.push_back(freeBullets.front());
	freeBullets.pop_front();
	Bullet* bullet = firedBullets.back();
	bullet->transform = Matrix2D(start);
	bullet->rc = FloatRect(D3DXVECTOR2(0, 0), range, Pivot::CENTER);
	bullet->size = D3DXVECTOR2(range, range);
	bullet->duration = duration;
	bullet->damge = damge;

	Animator* anim = FindBulletAnimator(bulletName);
	if (anim)
	{
		anim->Clone((void**)&bullet->animator);
		bullet->animator->ChangeAnimation(GetStringDirection(dir));

	}

	bullet->iff = iff;
	bullet->velocity = velocity;
	bullet->effectKey = effectKey;

	bullet->lifeTime = 0.f;
	bullet->bActive = true;
}

void BulletSystem::Fire(D3DXVECTOR2 start, D3DXVECTOR2 range, float duration, float damge, string bulletName, UnitDirection dir, IFFEnum iff, D3DXVECTOR2 velocity, string effectKey)
{
	if (freeBullets.empty() != false)
	{
		Log_Print("freeBullets is empty");
		return;
	}

	firedBullets.push_back(freeBullets.front());
	freeBullets.pop_front();
	Bullet* bullet = firedBullets.back();
	bullet->transform = Matrix2D(start);
	bullet->rc = FloatRect(D3DXVECTOR2(0, 0), range, Pivot::CENTER);
	bullet->size = range;
	bullet->duration = duration;
	bullet->damge = damge;

	Animator* anim = FindBulletAnimator(bulletName);
	if (anim)
	{
		anim->Clone((void**)&bullet->animator);

		bullet->animator->ChangeAnimation(GetStringDirection(dir));
	}

	bullet->iff = iff;
	bullet->velocity = velocity;
	bullet->effectKey = effectKey;

	bullet->lifeTime = 0.f;
	bullet->bActive = true;

}

void BulletSystem::CollrectBullet(Bullet * bullet)
{
	for (int i = 0;i < (int)firedBullets.size(); i++)
	{
		if (firedBullets[i] == bullet)
		{
			SafeDelete(bullet->animator);
			freeBullets.push_back(firedBullets[i]);
			firedBullets.erase(firedBullets.begin() + i);
			break;
		}
	}
}
