#pragma once

class Bullet;
class BulletSystem :public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Imgui)
	friend class ObjectManager;

public:
	void Fire(D3DXVECTOR2 start, float range, float duration, float damge, string bulletName, UnitDirection dir, IFFEnum iff, D3DXVECTOR2 velocity, string effectKey);
	void Fire(D3DXVECTOR2 start, D3DXVECTOR2 range, float duration, float damge, string bulletName, UnitDirection dir, IFFEnum iff, D3DXVECTOR2 velocity, string effectKey);

	void CollrectBullet(Bullet* bullet);

private:
	BulletSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~BulletSystem();

	virtual void Init();
	virtual void Release();
	void LoadBulletAnimator();

	void CreateBullet();
	Animator* FindBulletAnimator(string bulletName);


	using MapIter = unordered_map<string, Animator*>::iterator;
	unordered_map<string, Animator*> bulletAnimators;
	deque<Bullet*> freeBullets;
	deque<Bullet*> firedBullets;
};

