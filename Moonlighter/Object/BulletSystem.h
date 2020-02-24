#pragma once

class Bullet;
class BulletSystem :public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Imgui)
	friend class ObjectManager;

public:
	void Fire(D3DXVECTOR2 start, float range, string bulletName, IFFEnum iff, D3DXVECTOR2 velocity, string effectKey);


private:
	BulletSystem(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~BulletSystem();

	unordered_map<string, Animator*> bulletAnimators;
	vector<Bullet*> freeBullets;
	vector<Bullet*> firedBullets;
};

