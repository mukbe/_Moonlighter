#pragma once

class Bullet : public GameObject
{
	ClassInherited(GameObject)
	RequestRender(Layer_Object)
	RequestCollision(CollisionType_Dynamic)
	friend class BulletSystem;
public:
	Bullet(string name ,D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Bullet();

	virtual void Init();
	virtual void Release();
	virtual void Update(float tick);
	virtual void Render();

	virtual void OnCollisionEnter(GameObject* other);

private:
	string effectKey;
	float damge;
	D3DXVECTOR2 velocity;
	Animator* animator;
	float duration;
};

